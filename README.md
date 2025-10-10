# CODESCAPE-CPP
Easy ANSI codescapes for `C++`.

## USAGE
All declarations are inside the namespace `ansi`.

### ansi::graphic
Inside `ansi::graphic` can be found all statements related to ANSI graphics modes.
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
- If no parameters are supplied, both foreground and background will be set to `Default`.

#### FUNCTION: `set_mode({Mode, Mode...})`
The supplied list of modes will be activated.

#### FUNCTION: `reset_mode({Mode, Mode...})`
The supplied list of modes will be reset (the terminal default).
- If no parameters are supplied, all modes will be reset.

#### FUNCTION: `reset_all()`
Resets all modes to the terminal defaults. It is marked as `constexpr`, so it can be evaluated at compile time. 

## REQUIREMENTS
- `C++ std` >= 17

## LICENSE
This library is released under the [MIT](LICENSE) license.