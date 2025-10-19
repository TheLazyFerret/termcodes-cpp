//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Example cursor file
//!   Compilation: g++ -Wall -Werror --pedantic -std=c++17 -Iinclude/ example/cursor.cpp -o cursor.out

#include <iostream>
#include <cstdio>

#include "termcodes/ansi.hpp"

using namespace ansi::cursor;

void loading();

int main() {
  loading();
  return 0;
}

/// Snippet of a moving character, like a loading screen.
void loading() {
  // Important to flush after each written character.
  // If not flushed, all characters will be flushed off the buffer at the same time
  // And won´t have the movement effect.
  std::size_t counter = 0;
  std::cout << hide_cursor() << "Loading: "; // Hides the cursor. Not compatible with all the terminals
  std::cout.flush();
  while(counter < 10) {
    // Moves one column to left. So, the next written character in the standard output will rewrite the '|'
    std::cout << "|" << move(Direction::Left, 1);
    std::cout.flush();
    std::system("sleep 0.2");

    // Moves one column to left. So, the next written character in the standard output will rewrite the '/'
    std::cout << "/" << move(Direction::Left, 1);
    std::cout.flush();
    std::system("sleep 0.2");

    // Moves one column to left. So, the next written character in the standard output will rewrite the '-'
    std::cout << "-" << move(Direction::Left, 1);
    std::cout.flush();
    std::system("sleep 0.2");

    // Moves one column to left. So, the next written character in the standard output will rewrite the '\'
    std::cout << '\\' << move(Direction::Left, 1);
    std::cout.flush();
    std::system("sleep 0.2");

    ++counter;
  }
  // Reminder that std::endl flush the buffer.
  std::cout << "done" << show_cursor() << std::endl; // Shows back the cursor. Again, not compatible with all terminals
}