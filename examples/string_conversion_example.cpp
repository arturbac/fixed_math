#include "../fixed_lib/include/fixedmath/fixed_math.hpp"
#include "../fixed_lib/include/fixedmath/iostream.h"
#include <iostream>
#include <string>
#include <iomanip>

int main() 
{
  using namespace fixedmath;
  
  std::cout << "Fixed Math String Conversion Example (Pure Integer Implementation)" << std::endl;
  std::cout << "=============================================================" << std::endl;
  
  // Convert string to fixed_t
  std::string input = "3.99994";
  auto fixed_pi = from_string(input);
  
  if (fixed_pi) {
    std::cout << "Converted string \"" << input << "\" to fixed_t: " << *fixed_pi << std::endl;
    
    // Perform some operations
    auto doubled = *fixed_pi * 2;
    std::cout << "Doubled value: " << doubled << std::endl;
    
    // Convert back to string with different precisions
    std::cout << "String representations with different precisions:" << std::endl;
    std::cout << "  2 digits: " << to_string(*fixed_pi, 2) << std::endl;
    std::cout << "  4 digits: " << to_string(*fixed_pi, 4) << std::endl;
    std::cout << "  6 digits: " << to_string(*fixed_pi, 6) << std::endl;
  } else {
    std::cout << "Failed to convert \"" << input << "\" to fixed_t" << std::endl;
  }
  
  std::cout << "\nExact Fraction Representation:" << std::endl;
  
  // Test exact binary fractions
  fixed_t binary_fractions[] = {
    fixed_t{0.5},      // 1/2
    fixed_t{0.25},     // 1/4
    fixed_t{0.125},    // 1/8
    fixed_t{0.0625},   // 1/16
    fixed_t{0.0000152587890625},  // 1/65536
  };
  
  for (const auto& value : binary_fractions) {
    std::cout << "  Value: " << std::setw(10) << value 
              << " | String: " << std::setw(10) << to_string(value, 20) << std::endl;
  }
  
  std::cout << "\nDisadvantaged Decimal Fractions:" << std::endl;
  
  // Test decimal fractions that don't have exact binary representations
  fixed_t decimal_fractions[] = {
    fixed_t{0.1},      // 1/10
    fixed_t{0.01},     // 1/100
    fixed_t{0.001},    // 1/1000
    fixed_t{0.33333},  // ~1/3
  };
  
  for (const auto& value : decimal_fractions) {
    std::cout << "  Value: " << std::setw(10) << value 
              << " | String: " << std::setw(10) << to_string(value, 6) << std::endl;
  }
  
  std::cout << "\nEdge Cases:" << std::endl;
  
  // Test some invalid inputs
  auto invalid = from_string("not a number");
  std::cout << "  Conversion of \"not a number\": " << (invalid ? "succeeded" : "failed") << std::endl;
  
  // Test various values
  fixed_t large_number{12345.6789};
  std::cout << "  Large number: " << to_string(large_number) << std::endl;
  
  fixed_t negative{-42.5};
  std::cout << "  Negative number: " << to_string(negative) << std::endl;
  
  fixed_t zero{0};
  std::cout << "  Zero: " << to_string(zero) << std::endl;
  
  auto nan_value = quiet_NaN_result();
  std::cout << "  NaN value: " << to_string(nan_value) << std::endl;
  
  return 0;
} 