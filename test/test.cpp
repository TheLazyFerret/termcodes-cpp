//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Test file
//!   Compilation: g++ test/test.cpp -Iinclude/ -o test.out

#include <iostream>

#include "ansi/ansi_color.hpp"

using namespace ansi;

int main(int argc, char** argv) {
  std::cout << set_color(Color::Red, Color::Blue) << "a" << set_color(Color::Default) << std::endl;
  return 0;
}