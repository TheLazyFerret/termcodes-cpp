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
#include <initializer_list>

/// Declaration

namespace ansi::graphic {

/// Enum class representing the basic colors.
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

/// Enum class representing all graphic mode, except for colors.
enum class Mode {
  Bold,
  Dim,
  Italic,
  Underline,
  Blinking,
  Inverse,
  Invisible,
  Strike
};

inline std::string set_color(const Color = Color::Default, const Color = Color::Default);

inline std::string set_mode(std::initializer_list<Mode>);
inline std::string reset_mode(std::initializer_list<Mode>);

constexpr inline std::string_view reset_all();

}

namespace ansi::cursor {

enum class Direction {
  Up,
  Down,
  Left,
  Right
};

inline std::string move_cursor(const Direction, const std::size_t);

}

namespace ansi::utils {

/// Beginning of any ANSI CodeEscape.
constexpr std::string_view KAnsiCodeEscape = "\x1b[";
/// Set both foreground and background to default (reset).
constexpr std::string_view KAnsiResetAllGraphicColor = "\x1b[39;49m";
// Reset all modes (colors not included).
constexpr std::string_view KAnsiResetAllGraphicModes = "\x1b[22;23;24;25;27;28;29m";
// Reset all graphical options (colors and modes).
constexpr std::string_view KAnsiResetAllGraphic = "\x1b[0m";

constexpr inline std::string_view translate_color(const graphic::Color, const bool);
constexpr inline std::string_view translate_graphic_mode(const graphic::Mode, const bool);

constexpr inline std::string_view translate_direction(const cursor::Direction);

}

/// Implementation

/// Constexpr function that returns the ANSI numerical code of each color.
///  param:  const ansi::graphic::Color
///  param:  const bool
///  return: std::string_view
constexpr std::string_view ansi::utils::translate_color(const graphic::Color color, 
const bool background) {
  switch (color) {
    case graphic::Color::Black:
      return (background) ? "40" : "30";
    case graphic::Color::Red:
      return (background) ? "41" : "31";
    case graphic::Color::Green:
      return (background) ? "42" : "32";
    case graphic::Color::Yellow:
      return (background) ? "43" : "33";
    case graphic::Color::Blue:
      return (background) ? "44" : "34";
    case graphic::Color::Magenta:
      return (background) ? "45" : "35";
    case graphic::Color::Cyan:
      return (background) ? "46" : "36";
    case graphic::Color::White:
      return (background) ? "47" : "37";
    case graphic::Color::Default:
      return (background) ? "49" : "39";
    default: // Not reachable
    return "0";
  }
}

/// Constexpr function that returns the ansi numerical code of each graphic mode.
/// It does not take into account colors, which go in a separate function and namespace.
///  param:  const ansi::graphic::Mode 
///  param:  const bool
///  return: std::string_view
constexpr std::string_view ansi::utils::translate_graphic_mode(const graphic::Mode mode, 
const bool enable) {
  switch(mode) {
    case graphic::Mode::Bold:
      return (enable) ? "1" : "22";
    case graphic::Mode::Dim:
      return (enable) ? "2" : "22";
    case graphic::Mode::Italic:
      return (enable) ? "3" : "23";
    case graphic::Mode::Underline:
      return (enable) ? "4" : "24";
    case graphic::Mode::Blinking:
      return (enable) ? "5" : "25";
    case graphic::Mode::Inverse:
      return (enable) ? "7" : "27";
    case graphic::Mode::Invisible:
      return (enable) ? "8" : "28";
    case graphic::Mode::Strike:
      return (enable) ? "9" : "29";
    default: // Not reachable
      return "0";
  }
}

/// Return an ANSI codescape setting the foreground color and background.
/// If background color is not set, set the default terminal color.
/// If no parameters are supplied, both colors are set to the default color.
///  param:  ansi::graphic::Color 
///  param:  ansi::graphic::Color 
///  return: std::string
std::string ansi::graphic::set_color(const Color foreground, const Color background) {
    if (foreground == Color::Default && background == Color::Default) {
    return std::string(utils::KAnsiResetAllGraphicColor);
  }
  std::string result(utils::KAnsiCodeEscape);
  // Reserve memory to reduce the number of system calls.
  result.reserve(16); // a few bytes more than strictly necessary.
  result.append(utils::translate_color(foreground, false))
    .append(";") // parameter separator.
    .append(utils::translate_color(background, true))
    .append("m"); // function letter.
  return result;
}

/// Return an ANSI codescape setting all the graphic modes (beside the colors).
///  param:  std::initializer_list<ansi::graphic::Mode>
///  return: std::string 
std::string ansi::graphic::set_mode(std::initializer_list<Mode> list) {
  static constexpr std::size_t KSizePerParam = 4; // An estimated size in bytes of each parameter.
  if (list.size() == 0) {
    return "";
  }
  std::string result(utils::KAnsiCodeEscape);
  // Reserve memory to reduce the number of system calls.
  result.reserve(result.size() + (list.size() * KSizePerParam));
  for (auto iter = list.begin(); iter != list.end(); ++iter) {
    result.append(utils::translate_graphic_mode(*iter, 1));
    if (std::next(iter) != list.end()) {
      result.append(";"); // Only appends if there are more parameters.
    }
  }
  result.append("m"); // function letter.
  return result;
}

/// Return an ANSI codescape unsetting all the graphic modes (beside the colors).
///  param:  std::initializer_list<ansi::graphic::Mode>
///  return: std::string
std::string ansi::graphic::reset_mode(std::initializer_list<Mode> list) {
  static constexpr std::size_t KSizePerParam = 4; // An estimated size in bytes of each parameter.
  if (list.size() == 0) { // No parameters supplied.
    return std::string(utils::KAnsiResetAllGraphicModes);
  }
  std::string result(utils::KAnsiCodeEscape);
  // Reserve memory to reduce the number of system calls.
  result.reserve(result.size() + (list.size() * KSizePerParam));
  for (auto iter = list.begin(); iter != list.end(); ++iter) {
    result.append(utils::translate_graphic_mode(*iter, 0));
    if (std::next(iter) != list.end()) {
      result.append(";"); // Only appends if there are more parameters.
    }
  }
  result.append("m"); // function letter.
  return result;
}

/// Constexpr function that reset all ANSI graphical (both colors and modes).
///  return: std::string_view
constexpr std::string_view ansi::graphic::reset_all() {
  return utils::KAnsiResetAllGraphic;
}

/// Constexpr function that return the function code for each cursor direction.
///  param:  ansi::cursor::Mode
///  return: std::string_view
constexpr std::string_view ansi::utils::translate_direction(const cursor::Direction direction) {
  switch (direction) {
    case cursor::Direction::Up:
      return std::string_view{"A"};
    break;
    case cursor::Direction::Down:
      return std::string_view{"B"};
    break;
    case cursor::Direction::Left:
      return std::string_view{"C"};
    break;
    case cursor::Direction::Right:
      return std::string_view{"D"};
    break;
    default: // Not reachable
      return "0";
  }
}

/// Return an ANSI codespace that moves the cursor n positions to one direction.
///  param:  ansi::cursor::Direction
///  param:  std::string
///  return: std::string
std::string ansi::cursor::move_cursor(const Direction direction, const std::size_t n) {
  static constexpr std::size_t KReserveEstimation = 10;
  const std::string n_string = std::to_string(n);
}