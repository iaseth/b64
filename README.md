# b64

A lightweight command-line tool to encode or decode files using Base64.

> 🛠️ Written in C. Supports multiple input files, flexible CLI flags, and streams output to stdout by default.

## 🚀 Features

- ✅ Encode or decode Base64
- ✅ Combine multiple input files
- ✅ Output to a file or stdout
- ✅ Flexible CLI argument order
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

| Option       | Description                          |
|--------------|--------------------------------------|
| `-d`         | Decode instead of encode             |
| `-o <file>`  | Output to file instead of stdout     |

### Examples

**Encode files and write to stdout:**

```bash
./b64 file1.bin file2.bin > encoded.b64
```

**Decode Base64 file to binary:**

```bash
./b64 -d -o output.bin encoded.b64
```

**Flexible argument order:**

```bash
./b64 -o result.b64 file1 file2
./b64 file1 -d -o decoded.bin
```

## 📂 Project Structure

```
b64/
├── src/
│   └── b64.c         # Source code
├── build/            # Build artifacts (ignored by git)
├── CMakeLists.txt    # Build configuration
└── README.md         # Project documentation
```

## 📄 License

MIT License

---

Feel free to fork, hack, and improve. PRs welcome!
