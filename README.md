# b64

A lightweight command-line tool to encode or decode files using Base64.

> 🛠️ Written in C. Supports multiple input files, flexible CLI flags, and streams output to stdout by default.

## 🚀 Features

- ✅ Encode or decode Base64
- ✅ Input from file(s) or stdin
- ✅ Combine multiple input files
- ✅ Output to a file or stdout
- ✅ Support for URL-safe encoding with `--url-safe`
- ✅ Small, fast, and dependency-free

## 📦 Build

```bash
git clone https://github.com/iaseth/b64.git
cd b64/build
cmake ..
make
```

This builds the `b64` binary in the `build/` directory.

## 📚 Usage

```bash
b64 [options] <file1> [file2 ...]
```

### Options

| Option       | Long Option     | Description                          |
|--------------|-----------------|--------------------------------------|
| `-o <file>`  |                 | Output to file instead of stdout     |
| `-d`         | `--decode`      | Decode instead of encode             |
| `-u`         | `--url-safe`    | Use Base64URL encoding               |
| `-w`         | `--wrap`        | Wrap lines after 80 characters       |
| `-h`         | `--help`        | Show help info                       |
| `-l`         | `--list`        | List all available encodings         |
| `-v`         | `--version`     | Show version info                    |

### Examples

**Encode files and write to stdout:**

```bash
./b64 file1.txt file2.txt
```

**Encode files and write to file:**

```bash
./b64 file1.txt file2.txt -o encoded.b64
```

**Decode Base64 file to stdout:**

```bash
./b64 -d encoded.b64
```

**Encode and then Decode the same file:**

```bash
./b64 README.md | ./b64 -d
```

`./b64 README.md` encodes the file to base64,
`|` redirects the output to `./b64 -d`,
which then decodes it back.

<!-- ## 📂 Project Structure

```
b64/
├── src/
│   └── b64.c         # Source code
├── build/            # Build artifacts (ignored by git)
├── CMakeLists.txt    # Build configuration
└── README.md         # Project documentation
``` -->

## 📄 License

MIT License
