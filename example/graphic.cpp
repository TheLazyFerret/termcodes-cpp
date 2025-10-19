//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Example graphics file
//!   Compilation: g++ -Wall -Werror --pedantic -std=c++17 -Iinclude/ example/graphic.cpp -o graphic.out

#include <iostream>

#include "termcodes/ansi.hpp"

using namespace ansi::graphic;

int main() {
  // Set the foreground color to red. 
  // Notice that you must reset the color, just as like using normal ANSI codes.
  std::cout << set_color(Color::Red) << "Red" << set_color() << std::endl;

  // Set the foreground color to red and the background to white.
  std::cout << set_color(Color::Red, Color::White) << "Red over white" 
  << set_color() << std::endl;

  // Set the underline mode. As same with colors, you need to reset them.
  std::cout << set_mode({Mode::Underline}) << "Underlined" << reset_mode({Mode::Underline}) << std::endl;

  // When you need to use a color and a mode, you can easily reset them with reset_all()
  std::cout << set_color(Color::Red) << set_mode({Mode::Italic}) << "red and italic" 
  << reset_all() << std::endl;
  
  // You can set multiple modes at the same time. You can set multiple times
  // the same mode, but only will be applied one time.
  std::cout << set_color(Color::Cyan) << set_mode({Mode::Italic, Mode::Bold, Mode::Italic}) 
  << "Cyan, italic and bold" << reset_all() << std::endl;
  return 0;
}