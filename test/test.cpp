//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Test file
//!   Compilation: g++ -std=c++17 -Iinclude/ test/test.cpp -o test.out

#include <iostream>

#include "ansi/ansi.hpp"

using namespace ansi::graphic;

int main(int argc, char** argv) {
  std::cout << set_color(Color::Black, Color::White) << set_mode({Mode::Blinking}) << "a" << reset_all() << std::endl;

}