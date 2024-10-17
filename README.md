# Base Converter
The Base Converter is a C program designed to convert numbers from one base to another, supporting base conversions between 2 and 36.

## Overview
The program takes three inputs:
1. A number represented as a string in an arbitrary base (between 2 and 36).
2. The base of the input number.
3. The target base to convert the number to.

Upon execution, it converts the number from its original base to the specified output base and displays the result.

---

## Code Overview
- **`string2Int`**: Converts an input string representing a number in a specified base to a decimal integer. It validates if each character belongs to the specified base.
- **`char2Int`**: Helper function that converts a character to its corresponding integer index in the lookup table.
- **`int2String`**: Converts a decimal integer to a string representation in the target base by calculating the remainder iteratively.
- **`reverseString`**: Reverses a character array in place.

---

## Compilation and Execution
1. **Compile the Program**:
   ```bash
   gcc -o baseConverter base2Base.c
   ```

2. **Run the Program**:
   ```bash
   ./baseConverter [number] [input base] [output base]
   ```
   - **Example**:
     ```bash
     ./baseConverter 1A 16 10
     ```
     This converts the hexadecimal number `1A` to its decimal equivalent, `26`.

## Example Usage
![base2Base](https://user-images.githubusercontent.com/21160813/186040035-049edeb2-2ecf-41d6-917e-a9f5f2616327.jpg)
