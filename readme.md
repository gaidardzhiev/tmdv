# Terminal Markdown Viewer

A simple and fast Markdown viewer written in C that renders Markdown files directly in your terminal. It supports common Markdown features such as headings, lists, blockquotes, code blocks, and tables, making it easy to preview Markdown content without leaving the command line.

## Features

- Syntax highlighted headers with different colors by level
- Nested ordered and unordered lists with proper indentation
- Blockquote rendering with visual markers
- Code block and inline code with distinct coloring
- Basic table rendering with column borders
- Handles inline styles like bold and italic text
- Supports links and resets formatting cleanly after spans

## Usage

Clone the repo and bild the tool with a C compiler linked to the `md4c` library, then run it with a Markdown file as an argument:

```
git clone https://github.com/gaidardzhiev/tmd
cd tmd
make
make strip
make install
./tmd readme.md
```

The Markdown content will be displayed with enhanced formatting that improves terminal readability.

## Contributing

Feel free to submit issues or pull requests to improve features, add support for extended Markdown elements, or enhance terminal styling.

## License

This project is provided under the GPL3 License.
