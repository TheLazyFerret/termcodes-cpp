//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Example erase file
//!   Compilation: g++ -Wall -Werror --pedantic -std=c++17 -Iinclude/ example/erase.cpp -o erase.out

#include <iostream>
#include <cstdio>

#include "termcodes/ansi.hpp"

using namespace termcodes::erase;
using namespace termcodes::cursor;

void loading_dots();

int main() {
  loading_dots();
  return 0;
}

/// Snippet of a three dots loading.
void loading_dots() {
  std::size_t counter = 0;
  // As in the cursor example, it is important calling flush after each call.
  std::cout << hide_cursor() << "Loading";
  std::cout.flush();
  while(counter < 5) {
    std::cout << ".";
    std::cout.flush();
    std::system("sleep 0.5");

    std::cout << ".";
    std::cout.flush();
    std::system("sleep 0.5");

    std::cout << ".";
    std::cout.flush();
    std::system("sleep 0.5");

    /// Moves three columns to the left the cursor, the erase from the cursor to the end of the line.
    std::cout << move(Direction::Left, 3) << erase_cursor_to_end();
    std::cout.flush();
    std::system("sleep 0.5");
    ++counter;
  }
  std::cout << " done" << show_cursor() << std::endl;
}