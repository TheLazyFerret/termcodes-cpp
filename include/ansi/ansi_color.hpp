//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Simple header file containing definitions for a easily usage of ANSI color codes
//! References used: 
//!   - https://notes.burke.libbey.me/ansi-escape-codes/
//!   - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
//!  
//! Control sequence: 0x1B + '[' + [zero or more number] + [function letter]

#pragma once

#include <string_view>

namespace ansi::color {

constexpr std::string_view KResetAll      = "\x1b[0m";

constexpr std::string_view KBlack         = "\x1b[0;30m";
constexpr std::string_view KBrightBlack   = "\x1b[1;30m";

constexpr std::string_view KRed           = "\x1b[0;31m";
constexpr std::string_view KBrightRed     = "\x1b[1;31m";

constexpr std::string_view KGreen         = "\x1b[0;32m";
constexpr std::string_view KBrightGreen   = "\x1b[0;32m";

constexpr std::string_view KYellow        = "\x1b[0;33m";
constexpr std::string_view KBrightYellow  = "\x1b[1;33m";

constexpr std::string_view KBlue          = "\x1b[0;34m";
constexpr std::string_view KBrightBlue    = "\x1b[0;34m";

constexpr std::string_view KMagenta       = "\x1b[0;35m";
constexpr std::string_view KBrightMagenta = "\x1b[1;35m";

constexpr std::string_view KCyan          = "\x1b[0;36m";
constexpr std::string_view KBrightCyan    = "\x1b[1;36m";

constexpr std::string_view KWhite         = "\x1b[0;37m";
constexpr std::string_view KBrightWhite   = "\x1b[0;37m";

}