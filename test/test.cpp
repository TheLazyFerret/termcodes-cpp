//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Test file
//!   Compilation: g++ test/test.cpp -Iinclude/ -o test.out

#include <iostream>

#include "ansi/ansi_color.hpp"

int main(int argc, char** argv) {
  std::cout << ansi::color::KRed << "Hello!" << ansi::color::KResetAll << std::endl;
}