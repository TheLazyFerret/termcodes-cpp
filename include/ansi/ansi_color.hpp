//! Author TheLazyFerret (https://github.com/TheLazyFerret).
//! Copyright (c) 2025 TheLazyFerret.
//!   Using the license MIT.
//!   See the LICENSE file in the project root for full license information.
//!
//! Simple header file containing definitions for a easily usage of ANSI color codes
//! References used
//!  
//! Control sequence: 0x1B + '[' + [zero or more number]+ [;]? + [function letter]

#pragma once

#include <string_view>
#include <string>

/// Declaration

namespace ansi {

enum class Color {
  Default,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White
};

inline std::string set_color(const ansi::Color, const ansi::Color = ansi::Color::Default);

}

namespace ansi::utils {

constexpr std::string_view KAnsiCodeEscape = "\x1b[";
constexpr std::string_view KAnsiColorReset = "\x1b[39;49m";

constexpr inline std::string_view translate_color(const ansi::Color, const bool);

}

/// Implementation

/// @brief Constexpr function that returns the ANSI code of each color.
/// @param color 
/// @param background 
/// @return std::string_view
constexpr std::string_view ansi::utils::translate_color(const ansi::Color color, const bool background) {
  switch (color) {
    case Color::Black:
      return (background) ? std::string_view("40") : std::string_view("30");
    case Color::Red:
      return (background) ? std::string_view("41") : std::string_view("31");
    case Color::Green:
      return (background) ? std::string_view("42") : std::string_view("32");
    case Color::Yellow:
      return (background) ? std::string_view("43") : std::string_view("33");
    case Color::Blue:
      return (background) ? std::string_view("44") : std::string_view("34");
    case Color::Magenta:
      return (background) ? std::string_view("45") : std::string_view("35");
    case Color::Cyan:
      return (background) ? std::string_view("46") : std::string_view("36");
    case Color::White:
      return (background) ? std::string_view("47") : std::string_view("37");
    default:
      return (background) ? std::string_view("49") : std::string_view("39");
  }
}

/// @brief Return an ANSI codescape setting the foreground color and background.
///   If background color is not set, set the default terminal color.
/// @param foreground 
/// @param background 
/// @return 
std::string ansi::set_color(const ansi::Color foreground, const ansi::Color background) {
  if (foreground == Color::Default && background == Color::Default) {
    return std::string(utils::KAnsiColorReset);
  }
  std::string result;
  result.reserve(16);
  result.append(utils::KAnsiCodeEscape)
    .append(utils::translate_color(foreground, false))
    .append(";")
    .append(utils::translate_color(background, true))
    .append("m");
  return result;
}