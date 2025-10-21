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

namespace termcodes::graphic {

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

inline std::string set_mode(const std::initializer_list<Mode>&);
inline std::string reset_mode(const std::initializer_list<Mode>&);

constexpr inline std::string_view reset_all() noexcept;

}

namespace termcodes::cursor {

/// Enum class representing the possible directions when moving the cursor around.
enum class Direction {
  Up,
  Down,
  Left,
  Right
};

inline std::string move(const Direction, const std::size_t);
inline constexpr std::string_view jump_line_begin() noexcept;
inline std::string jump(const std::size_t, const std::size_t);

inline constexpr std::string_view hide_cursor() noexcept;
inline constexpr std::string_view show_cursor() noexcept;

}

namespace termcodes::erase {

inline constexpr std::string_view clear_screen() noexcept;

inline constexpr std::string_view erase_line() noexcept;
inline constexpr std::string_view erase_begin_to_cursor() noexcept;
inline constexpr std::string_view erase_end_to_cursor() noexcept;

}

namespace termcodes::utils {

/// GRAPHIC

/// Beginning of any ANSI CodeEscape.
constexpr std::string_view KAnsiCodeEscape = "\x1b[";
/// Set both foreground and background to default (reset).
constexpr std::string_view KAnsiResetAllGraphicColor = "\x1b[39;49m";
/// Reset all modes (colors not included).
constexpr std::string_view KAnsiResetAllGraphicModes = "\x1b[22;23;24;25;27;28;29m";
/// Reset all graphical options (colors and modes).
constexpr std::string_view KAnsiResetAllGraphic = "\x1b[0m";

constexpr inline std::string_view translate_color(const graphic::Color, const bool) noexcept;
constexpr inline std::string_view translate_graphic_mode(const graphic::Mode, const bool) noexcept;

/// CURSOR

/// Move the cursor to the home position (0, 0) usually in top left corner.
constexpr std::string_view KAnsiResetCursor = "\x1b[H";
/// Moves the cursor to the begin of the line.
constexpr std::string_view KAnsiMoveToStart = "\x1b[0E";

/// Save the cursor position.
constexpr std::string_view KAnsiSaveCursorPosition = "\x1b[s";
/// Loads the last saved cursor position.
constexpr std::string_view KAnsiLoadCursorPosition = "\x1b[u";

/// makes the cursor visible. NOT COMPATIBLE WITH ALL TERMINALS.
constexpr std::string_view KAnsiEnableCursor = "\x1b[?25h";
/// makes the cursor invisible. NOT COMPATIBLE WITH ALL TERMINALS.
constexpr std::string_view KAnsiDisableCursor = "\x1b[?25l";

constexpr inline std::string_view translate_direction(const cursor::Direction) noexcept;

/// ERASE

/// Erase the line, from the cursor to the end.
constexpr std::string_view KAnsiEraseLineCursorToEnd = "\x1b[0K";
/// Erase the line, from the cursor to the begin.
constexpr std::string_view KAnsiEraseLineFromCursorToBegin = "\x1b[1K";
/// Erase the line.
constexpr std::string_view KAnsiEraseLine = "\x1b[2K";

/// Clear all the screen and move the cursor to the begin.
constexpr std::string_view KAnsiClearScreen = "\x1b[0J\x1b[1J\x1b[H";
/// Erase line and moves cursor to start of line
constexpr std::string_view KAnsiEraseLineAndMove = "\x1b[2K\x1b[0G";

}

/// Implementation

/// Constexpr function that returns the ANSI numerical code of each color.
///  param:  const termcodes::graphic::Color
///  param:  const bool
///  return: std::string_view
constexpr std::string_view termcodes::utils::translate_color(const graphic::Color color, 
const bool background) noexcept {
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

/// Constexpr function that returns the ANSI numerical code of each graphic mode.
/// It does not take into account colors, which go in a separate function and namespace.
///  param:  const termcodes::graphic::Mode 
///  param:  const bool
///  return: std::string_view
constexpr std::string_view termcodes::utils::translate_graphic_mode(const graphic::Mode mode, 
const bool enable) noexcept {
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
///  param:  termcodes::graphic::Color 
///  param:  termcodes::graphic::Color 
///  return: std::string
std::string termcodes::graphic::set_color(const Color foreground, const Color background) {
    if (foreground == Color::Default && background == Color::Default) {
    return std::string{utils::KAnsiResetAllGraphicColor};
  }
  std::string result{utils::KAnsiCodeEscape};
  // Reserve memory to reduce the number of system calls.
  result.reserve(16); // a few bytes more than strictly necessary.
  result.append(utils::translate_color(foreground, false))
    .append(";") // parameter separator.
    .append(utils::translate_color(background, true))
    .append("m"); // function letter.
  return result;
}

/// Return an ANSI codescape setting all the graphic modes (beside the colors).
///  param:  std::initializer_list<termcodes::graphic::Mode>
///  return: std::string 
std::string termcodes::graphic::set_mode(const std::initializer_list<Mode>& list) {
  static constexpr std::size_t KSizePerParam = 4; // An estimated size in bytes of each parameter.
  if (list.size() == 0) {
    return std::string{""};
  }
  std::string result{utils::KAnsiCodeEscape};
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
///  param:  std::initializer_list<termcodes::graphic::Mode>
///  return: std::string
std::string termcodes::graphic::reset_mode(const std::initializer_list<Mode>& list) {
  static constexpr std::size_t KSizePerParam = 4; // An estimated size in bytes of each parameter.
  if (list.size() == 0) { // No parameters supplied.
    return std::string{utils::KAnsiResetAllGraphicModes};
  }
  std::string result{utils::KAnsiCodeEscape};
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
constexpr std::string_view termcodes::graphic::reset_all() noexcept {
  return utils::KAnsiResetAllGraphic;
}

/// Constexpr function that return the function code for each cursor direction.
///  param:  termcodes::cursor::Mode
///  return: std::string_view
constexpr std::string_view termcodes::utils::translate_direction(const cursor::Direction direction) noexcept {
  switch (direction) {
    case cursor::Direction::Up:
      return "A";
    break;
    case cursor::Direction::Down:
      return "B";
    break;
    case cursor::Direction::Right:
      return "C";
    break;
    case cursor::Direction::Left:
      return "D";
    break;
    default: // Not reachable
      return "0";
  }
}

/// Return the ANSI code escape to move one line or column in the terminal.
///  param:  termcodes::cursor::Direction
///  param:  std::std::size_t
///  return: std::string
std::string termcodes::cursor::move(const Direction direction, const std::size_t n) {
  std::string result{utils::KAnsiCodeEscape};
  result.append(std::to_string(n))
    .append(utils::translate_direction(direction));
  return result;
}

/// Return the ANSI code that moves the cursor to line [n], column [m].
///  param:  std::size_t
///  param:  std::size_t
///  return: std::string
std::string termcodes::cursor::jump(const std::size_t n, const std::size_t m) {
  std::string result{utils::KAnsiCodeEscape};
  result.append(std::to_string(n))
    .append(";")
    .append(std::to_string(m))
    .append("H");
  return result;
}

/// Constexpr function that return the ANSI code to move the cursor to the start of the current line.
///  return: std::string_view
constexpr std::string_view termcodes::cursor::jump_line_begin() noexcept {
  return utils::KAnsiMoveToStart;
}

/// Constexpr function that return the ANSI code that shows the cursor. If already visible, does nothing.
/// Not compatible will all terminals.
///  return: std::string_view
constexpr std::string_view termcodes::cursor::show_cursor() noexcept {
  return utils::KAnsiEnableCursor;
}

/// Constexpr function that return the ANSI code that hides the cursor. If already invisible, does nothing.
/// Not compatible with all terminals.
///  return: std::string_view
constexpr std::string_view termcodes::cursor::hide_cursor() noexcept {
  return utils::KAnsiDisableCursor;
}


/// Constexpr function that return the ANSI code that first clear the screen and moves the cursor to home (0, 0).
///  return: std::string_view
constexpr std::string_view termcodes::erase::clear_screen() noexcept {
  return utils::KAnsiClearScreen;
}

/// Constexpr function that return the ANSI code to erase the line where the cursor is positioned.
///  return: std::string_view
constexpr std::string_view termcodes::erase::erase_line() noexcept {
  return utils::KAnsiEraseLineAndMove;
}

/// Constexpr function that return the ANSI code to erase the line where the cursor is positioned.
/// from the cursor position to the begin of the line.
///  return: std::string_view
constexpr std::string_view termcodes::erase::erase_begin_to_cursor() noexcept {
  return utils::KAnsiEraseLineFromCursorToBegin;
}

/// Constexpr function that return the ANSI code to erase the line where the cursor is positioned.
/// from the cursor position to the end of the line.
///  return: std::string_view
constexpr std::string_view termcodes::erase::erase_end_to_cursor() noexcept {
  return utils::KAnsiEraseLineCursorToEnd;
}