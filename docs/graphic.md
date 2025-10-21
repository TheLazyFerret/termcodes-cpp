# termcodes - graphic
In this namespace, all the functions related to the different
graphic modes that ANSI supports are found here.

## Usage
#### ENUM: `Color`
|Value|Effect|
|---|---|
|Black|The text will be displayed in black.|
|Red|The text will be displayed in red.|
|Green|The text will be displayed in green.|
|Yellow|The text will be displayed in yellow.|
|Blue|The text will be displayed in blue.|
|Magenta|The text will be displayed in magenta.|
|Cyan|The text will be displayed in cyan.|
|White|The text will be displayed in white.|
|Default|The text will be displayed in the default terminal color.|

#### ENUM: `Mode`
|Value|Effect|
|---|---|
|Bold|The text will be displayed in bold.|
|Dim|The text will be displayed dimmed.|
|Italic|The text will be displayed in italic.|
|Underline|The text will be displayed with an underline.|
|Blinking|The text will blink.|
|Inverse|The background and foreground will be swapped.|
|Strike|The text will be displayed with a strikethrough.|

#### FUNCTION: `set_color(Color foreground, Color background)`
Sets the foreground and background colors.
- If only one parameter is supplied, the `background` will be set to `Default`.
- If no parameter is supplied, both foreground and background will be set to `Default`.

#### FUNCTION: `set_mode({Mode, Mode...})`
The supplied list of modes will be activated.
- If no parameter is supplied, well, nothing happens.

#### FUNCTION: `reset_mode({Mode, Mode...})`
The supplied list of modes will be reset (to the terminal default).
- If no parameter is supplied, all modes will be reset.
- `Bold` and `Dime` use the same code for disabling. So if reseted, both will be reseted.

#### FUNCTION: `reset_all()`
Reset all modes and color to the terminal defaults. 
- It is marked as `constexpr`, so it can be evaluated at compile time.

## Example
You can see a complete example in [example/graphic.cpp](../example/graphic.cpp)

```cpp
using namespace termcodes::graphic;

int main() {
  std::cout << set_mode({Mode::Underline, Mode::Bold}) 
  << set_color(Color::Black, Color::White) 
  << "Hello World!" << reset_all() << std::endl;
  return 0;
}
```