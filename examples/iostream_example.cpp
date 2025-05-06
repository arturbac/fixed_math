#include "../../fixed_math/fixed_lib/include/fixedmath/fixed_math.hpp"
#include "../../fixed_math/fixed_lib/include/fixedmath/iostream.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

int main() 
{
  using namespace fixedmath;
  
  std::cout << "Fixed Math I/O Stream Example" << std::endl;
  std::cout << "==============================" << std::endl;
  
  // Output stream examples
  std::cout << "\n1. Output Stream Examples:" << std::endl;
  
  // Create some fixed_t values
  fixed_t pi = fixed_t{3.14159265};
  fixed_t negative = fixed_t{-42.5};
  fixed_t large = fixed_t{123456.789};
  fixed_t small = fixed_t{0.000125};
  fixed_t zero = fixed_t{0};
  fixed_t nan = quiet_NaN_result();
  
  // Output with different precision settings
  std::cout << "Default precision:" << std::endl;
  std::cout << "  Pi: " << pi << std::endl;
  std::cout << "  Negative: " << negative << std::endl;
  std::cout << "  Large: " << large << std::endl;
  std::cout << "  Small: " << small << std::endl;
  std::cout << "  Zero: " << zero << std::endl;
  std::cout << "  NaN: " << nan << std::endl;
  
  // Set different precision
  std::cout << "\nPrecision 2:" << std::endl;
  std::cout << std::setprecision(2);
  std::cout << "  Pi: " << pi << std::endl;
  std::cout << "  Negative: " << negative << std::endl;
  std::cout << "  Large: " << large << std::endl;
  
  std::cout << "\nPrecision 10:" << std::endl;
  std::cout << std::setprecision(10);
  std::cout << "  Pi: " << pi << std::endl;
  std::cout << "  Small: " << small << std::endl;
  
  // Input stream examples
  std::cout << "\n2. Input Stream Examples:" << std::endl;
  
  // Use string streams for testing, simulating user input
  const std::vector<std::string> test_inputs = {
    "3.14159",
    "-42.5",
    "0",
    "123.456",
    "NaN",
    "nan",
    "invalid"
  };
  
  for (const auto& input : test_inputs) {
    std::istringstream iss(input);
    fixed_t value;
    
    std::cout << "Parsing \"" << input << "\": ";
    if (iss >> value) {
      std::cout << "Success, value: " << value << std::endl;
    } else {
      std::cout << "Failed to parse" << std::endl;
    }
  }
  
  // User input example
  std::cout << "\n3. User Input Example:" << std::endl;
  std::cout << "Enter a fixed point number (or NaN): ";
  
  fixed_t user_input;
  if (std::cin >> user_input) {
    std::cout << "You entered: " << user_input << std::endl;
    
    // Demonstrate some operations
    std::cout << "Double: " << (user_input * 2) << std::endl;
    std::cout << "Square: " << (user_input * user_input) << std::endl;
    
    // Check if it's NaN
    if (fobj::isnan(user_input)) {
      std::cout << "The value is NaN" << std::endl;
    }
  } else {
    std::cout << "Invalid input" << std::endl;
    // Clear error state
    std::cin.clear();
    // Ignore remainder of the line
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  
  return 0;
} 