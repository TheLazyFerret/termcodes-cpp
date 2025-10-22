# termcodes-cpp
The idea of this small library is abstracting the obscure and complex ANSI
codescapes in a simpler and friendly way.

I chose to simplify the codes as much as possible, so not all codes are
included. In addition, I chose to leave out most codes that are not widely
supported.

Only compatible with unix-like systems. Although only tested on linux.

Please remember this library is a work in progress.

Using my own [style guide](https://github.com/TheLazyFerret/dots-and-templates/blob/master/cpp/style_guide.md).

## Usage
See the [docs](docs/index.md) for more information.

## Example
Check [this](example/) for some examples.

## Installation
Not external compilation required, just include the header in your project.

`#include "termcodes/ansi.hpp"`

## Requirements
`C++ std >= 17`

## Project structure
```sh
docs/     # Documentation and usage.
example/  # Example of use.
include/  # Library source code and public header.
LICENSE   # MIT license.
```

## License
This library is released under the [MIT](LICENSE) license.
