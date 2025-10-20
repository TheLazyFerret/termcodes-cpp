# Termccodes - cursor
In this namespace, all the functions that works with the cursor or the screen. Due they are quite related, I decided to not split them.

*When using with `std::basic_ostream`, please remember
that this is a buffered stream. You probably want to
flush the buffer after each call.*

## Usage
#### ENUM: `Direction`
|Value|Effect|
|---|---|
|Up|Move the cursor n rows up.|
|Down|Move the cursor n rows down.|
|Left|Move the cursor n columns left.|
|Right|Move the cursor n columns right.|

#### FUNCTION: `move(Direction, std::size_t n)`
Move the cursor n positions to a single direction.

#### FUNCTION: `jump(std::size_t n, std::size_t m)`
Move the cursor to the row = n and column = m
- Remember that the position (0, 0) corresponds to the first character in the terminal, usually the top-left corner.

#### FUNCTION: `clear_screen()`
Cleans the screen, and moves the cursor to the position (0, 0).
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `show_cursor()`
Shows the cursor if it is hidden. In any other case, it does nothing.
- It is marked as `constexpr`, so it can be evaluated at compile time.
- Although it should work for most devices, it is not guaranteed to work on all of them.

#### FUNCTION: `hide_cursor()`
Hides the cursor if it is vissible. In any other case, it does nothing.
- It is marked as `constexpr`, so it can be evaluated at compile time.
- Although it should work for most devices, it is not guaranteed to work on all of them.

#### FUNCTION: `erase_line()`
Erase all the line where the cursor is placed and moves the cursor to
the start of the line.
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `erase_begin_to_cursor()`
Erase the line from the cursor to the begin of itself.
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `erase_end_to_cursor()`
Erase the line from the cursor to the end of itself.
- It is marked as `constexpr`, so it can be evaluated at compile time.

## Example
You can see a complete example in [example/cursor.cpp](../example/cursor.cpp)

```cpp
using namespace ansi::cursor;

  int main() {
    std::cout << clear_screen() << "Hello world!" << std::endl;    
    return 0;
  }
```