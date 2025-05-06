// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

#pragma once

#include "types.h"
#include "core_ops.h"
#include <string>
#include <string_view>
#include <optional>
#include <algorithm>

#include "detail/static_call_operator_prolog.h"

namespace fixedmath::inline v2
  {
  namespace func
    {
    /// Convert a string to fixed_t without using floating point operations
    /// @param str The string to convert
    /// @return An optional fixed_t, which will be nullopt if the conversion failed
    [[nodiscard]]
    inline constexpr auto from_string(std::string_view str) noexcept -> std::optional<fixed_t>
      {
      // Skip leading whitespace
      size_t start = 0;
      while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
        ++start;
        
      if (start == str.size())
        return std::nullopt;
        
      // Check for NaN
      if (start + 2 < str.size() && 
          (str[start] == 'N' || str[start] == 'n') && 
          (str[start+1] == 'A' || str[start+1] == 'a') && 
          (str[start+2] == 'N' || str[start+2] == 'n')) {
        
        // Skip to the end of "NaN"
        start += 3;
        
        // Verify there's nothing after "NaN" except whitespace
        while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
          ++start;
          
        // If we reached the end, it's a valid NaN
        if (start == str.size())
          return quiet_NaN_result();
        else
          return std::nullopt;
      }
        
      // Check for sign
      bool negative = false;
      if (str[start] == '-') {
        negative = true;
        ++start;
      } else if (str[start] == '+') {
        ++start;
      }
      
      if (start >= str.size())
        return std::nullopt;
        
      // Parse integer part
      fixed_internal int_part = 0;
      size_t pos = start;
      
      while (pos < str.size() && std::isdigit(static_cast<unsigned char>(str[pos]))) {
        // Check for overflow
        if (int_part > (std::numeric_limits<fixed_internal>::max() / 10))
          return std::nullopt;
          
        int_part = int_part * 10 + (str[pos] - '0');
        ++pos;
      }
      
      // Convert integer part to fixed point (shift left by 16 bits)
      fixed_internal result = int_part << 16;
      
      // Parse decimal part if exists
      if (pos < str.size() && str[pos] == '.') {
        ++pos;
        
        // 16 bits of precision = 65536 units
        // Each position after decimal point is a power of 10:
        // .1 = 6553.6      * 65536
        // .01 = 655.36     * 65536
        // .001 = 65.536    * 65536
        // etc.
        fixed_internal fraction = 0;
        constexpr fixed_internal power[5] = {429496730, 42949673, 4294967, 429497, 42950};  // 10^-1 * 2^16 (rounded down)
        uint8_t i = 0;
        
        while (pos < str.size() && std::isdigit(static_cast<unsigned char>(str[pos]))) {
          int digit = str[pos] - '0';
          
          // Add digit * current power of 10
          fraction += digit * power[i];
          
          // Next decimal place (divide by 10)
          if(i == sizeof(power) / sizeof(fixed_internal) - 1)  // Stop if we've reached our precision limit
            break;
            
          ++pos;
          ++i;
        }
        
        result += fraction >> 16;
      }
        
      // After parsing, skip all spaces and digits; if any other char, return nullopt
      while (pos < str.size()) {
        unsigned char c = static_cast<unsigned char>(str[pos]);
        if (std::isspace(c) || std::isdigit(c)) {
          ++pos;
        } else {
          return std::nullopt;
        }
      }
        
      // Apply sign
      if (negative)
        result = -result;
      
      return as_fixed(result);
      }
      
    /// Convert fixed_t to string without using floating point operations
    /// @param value The fixed_t value to convert
    /// @param precision The number of decimal places (default: 5)
    /// @return A string representation of the fixed_t value
    [[nodiscard]]
    inline auto to_string(std::same_as<fixed_t> auto value, int precision = 5) noexcept -> std::string
      {
      // Check if value is NaN
      if (fobj::isnan(value))
        return "NaN";
        
      std::string result;
      
      // Handle negative numbers
      bool negative = value.v < 0;
      fixed_internal abs_value = negative ? -value.v : value.v;
      
      // Extract integer part (high 48 bits)
      fixed_internal int_part = abs_value >> 16;
      
      // Convert integer part to string
      if (int_part == 0) {
        result = "0";
      } else {
        while (int_part > 0) {
          result.push_back('0' + static_cast<char>(int_part % 10));
          int_part /= 10;
        }
        std::reverse(result.begin(), result.end());
      }
      
      // Add decimal point and fractional part if precision > 0
      if (precision > 0) {
        result.push_back('.');
        
        // Extract fractional part (low 16 bits)
        fixed_internal frac_part = abs_value & 0xFFFF;
        
        // Convert to decimal places
        for (int i = 0; i < precision; ++i) {
          // Multiply by 10
          frac_part *= 10;
          
          // Extract digit
          char digit = static_cast<char>((frac_part >> 16) % 10);
          result.push_back('0' + digit);
          
          // Remove used digit
          frac_part &= 0xFFFF;
          
          // If remaining fraction is zero, stop
          if (frac_part == 0)
            break;
        }
        
        // Remove trailing zeros
        while (result.back() == '0' && result[result.size() - 2] != '.')
          result.pop_back();
      }
      
      // Add negative sign if needed
      if (negative)
        result.insert(result.begin(), '-');
        
      return result;
      }
    } // namespace func
    
  struct from_string_t
    {
    [[nodiscard]]
    static_call_operator constexpr auto operator()(std::string_view str
    ) static_call_operator_const noexcept -> std::optional<fixed_t>
      {
      return func::from_string(str);
      }
    };
    
  struct to_string_t
    {
    [[nodiscard]]
    static_call_operator auto operator()(std::same_as<fixed_t> auto value, int precision = 6
    ) static_call_operator_const noexcept -> std::string
      {
      return func::to_string(value, precision);
      }
    };
    
  ///\brief Converts a string to fixed_t
  inline constexpr from_string_t from_string{};
  
  ///\brief Converts a fixed_t to string
  inline constexpr to_string_t to_string{};
    
  } // namespace fixedmath::inline v2

#include "detail/static_call_operator_epilog.h" 