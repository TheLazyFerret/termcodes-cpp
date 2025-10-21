# termcodes - erase
This namespace contains all the functions that works around erasing
printed symbols in the terminal.

*When using with `std::basic_ostream`, please remember
that this is a buffered stream. You probably want to
flush the buffer after each call.*

# Usage
#### FUNCTION: `clear_screen()`
Clear all the screen, and moves the cursor to the home position (0, 0)
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `erase_line()`
Erase the current line and moves the cursor to the column 0.
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `erase_cursor_to_begin()`
Erase the symbols in the current line, from the cursor to the first position (including the cursor).
- It is marked as `constexpr`, so it can be evaluated at compile time.

#### FUNCTION: `erase_cursor_to_end()`
Erase the symbols in the current line, from the cursor to the first
position (including the cursor).
- It is marked as `constexpr`, so it can be evaluated at compile time.

## Example
You can see a complete example in [example/erase.cpp](../example/erase.cpp)

```cpp
using namespace termcodes::cursor;

  int main() {
    std::cout << clear_screen() << "Hello world!";
    std::cout.flush();    
    return 0;
  }
```