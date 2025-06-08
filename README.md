# Text-to-Math

Welcome to **Text-to-Math** — a calculator library written in C.

It supports:

* Arithmetic operations
* Scientific functions (trigonometric, hyperbolic, logarithmic, factorial, etc.)
* Constants like `pi` and `e`
* Custom base logarithms `logX`
* Unit conversions (length, temperature, etc.)
* Intelligent output formatting (clean scientific notation)

This program initially supported KiCAD\_Coil but grew to a fast offline calculator!

---

## 📖 Table of Contents

* [Features](#features)
* [Installation](#installation)
* [Usage](#usage)
* [Supported Operations](#supported-operations)
* [Project Structure](#project-structure)
* [How It Works](#how-it-works)
* [Functions Overview](#functions-overview)
* [Contributing](#contributing)
* [License](#license)

---

## 🚀 Features

* ✅ Infix to Postfix (Shunting Yard Algorithm)
* ✅ Postfix Expression Evaluation
* ✅ Extensive Math Functions: `sin`, `cos`, `tan`, `log`, `ln`, `round`, etc.
* ✅ Trigonometric functions in degrees: `sind`, `cosd`, `tand`, etc.
* ✅ Hyperbolic and Reciprocal Trigonometric Functions
* ✅ Constants like `pi`, `e`
* ✅ Unit Conversion System (Length, Temperature)
* ✅ Custom Base Logarithms (e.g., `log21(100)`)
* ✅ Intelligent formatting: removes unnecessary trailing zeros

---

## 🛠️ Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your_username/scientific-calculator.git
   cd scientific-calculator
   ```

2. **Build an example project**:

   * Console interactive calculator:

   ```bash
   cd examples/console
   make
   ./calculator
   ```

   * Inline input calculator:

   ```bash
   cd examples/inline_input
   make
   ./calculator "2 + 2 * 3"
   ```

---

## 🔖 Usage

* **Console Interactive Mode**

  ```bash
  ./calculator
  ```

* **Inline Input Mode**

  ```bash
  ./calculator "5 + 5"
  ```

* **Exit** the calculator:

  ```bash
  > exit
  ```

---

## 📂 Supported Operations

Supports mathematical expressions similar to:

* Basic arithmetic: `+`, `-`, `*`, `/`, `^`, `%`
* Parentheses `{}`, `[]`, `()`
* Trigonometric Functions: `sin`, `cos`, `tan`, `cot`, `asin`, `acos`, `atan`, `acot` (rad) and `sind`, `cosd`, `tand`, `cotd`, etc. (deg)
* Hyperbolic Functions: `sinh`, `cosh`, `tanh`, `sech`, `csch`, `coth`
* Logarithmic Functions: `log`, `ln`, `logX`
* Special Functions: `sqrt`, `round`, `floor`, `ceil`, `abs`, `factorial (!)`
* Constants: `pi`, `e`
* Unit Conversion: `C=>K`, `F=>C`, `km=>m`, `mi=>km`, etc.
* Degrees/Radians conversion: `(90)deg` to radians

Example usage:

* `2 + 3 * 4`
* `sin(90deg)`
* `log2(8)`
* `sqrt(16)`
* `32F=>C`
* `5mi=>km`

---

## 📚 Project Structure

```
.
├── README.md
├── examples
│   ├── console
│   │   ├── Makefile
│   │   ├── calculator
│   │   └── main.c
│   └── inline_input
│       ├── Makefile
│       ├── calculator
│       └── main.c
├── internal
│   ├── evaluator
│   │   ├── evaluator.c
│   │   └── evaluator.h
│   ├── shuntingYard
│   │   ├── shuntingYard.c
│   │   └── shuntingYard.h
│   ├── tokenizer
│   │   ├── tokenizer.c
│   │   └── tokenizer.h
│   ├── unitConversion
│   │   ├── unitConversion.c
│   │   └── unitConversion.h
│   └── utils
│       ├── utils.c
│       └── utils.h
└── src
    ├── mathParser
    │   ├── mathParser.c
    │   └── mathParser.h
    └── mathStructs
        └── mathStructs.h
```

---

## ⚙️ How It Works

### 🛠️ Parsing

* **Tokenizer** breaks input into tokens.
* **Shunting Yard Algorithm** converts infix to postfix notation.

### 💪 Evaluation

* **Postfix Evaluator** processes expressions using a stack.
* Supports all basic and advanced math functions.
* **Custom base logarithms** and **degree-based trigonometry**.
* **Smart error handling** (e.g., divide-by-zero, invalid input).

### 🌡️ Unit Conversion

* Units defined relative to SI base.
* Converts between compatible units only.
* Intelligent `A=>B` syntax for conversions.

---

## 📚 Functions Overview

| Function                                                                                      | Description                                            |
| --------------------------------------------------------------------------------------------- | ------------------------------------------------------ |
| `double textCalc(const char *input_expr)`                                                     | Evaluates a string and returns a `double` result.      |
| `char* textCalcString(const char *input_expr, char *output_buffer, size_t buffer_size)`       | Evaluates and returns a **trimmed scientific string**. |
| `uint32_t tokenize(const char *expr, Token *tokens)`                                          | Breaks an input into an array of tokens.               |
| `uint32_t shuntingYard(const Token *infixTokens, Token *postfixTokens)`                       | Converts infix tokens to postfix.                      |
| `double evaluatePostfix(const Token *postfixTokens)`                                          | Evaluates postfix tokens and returns a double.         |
| `int convert_units(double value, const char *from_unit, const char *to_unit, double *result)` | Converts between units based on SI base.               |

**Public API:**

* `textCalc()` and `textCalcString()` are the main user functions.
* Other functions are `static` internal to the library.

---

## 🤝 Contributing

Contributions are welcome! Fork the repository and submit pull requests.

### 👷 How to Contribute

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Ensure clean and documented code.
5. Submit a pull request.

Please:

* Follow the **code style** and **commenting conventions**.
* Document any new features.

---

## 📜 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

> Made with 💻, ☕, and lots of 🧠 by Ozgur Tuna Ozturk.

## 📈 Examples

### Example 1

```bash
./example1

2.45*e^round(1.36*(10.4+sqrt(8)*pi)/3)
Solution: 1.985255e+04
```

### Example 2

```bash
./example2 180deg
Solution: 3.1415926536
```

---

## 📍 Contact

For bug reports or suggestions:
Email: [tunaozturk2001@hotmail.com](mailto:tunaozturk2001@hotmail.com?subject=[GitHub]ScientificCalculator)

---

*Last updated: 2025-06-07*
