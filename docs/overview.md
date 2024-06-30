# Overview

This project uses an Arduino to perform the addition of two binary nibbles (4 bits each) and display the result on LEDs. The project logic involves reading bit inputs, executing binary addition, and displaying the result.

## How the Binary Base Works

The binary base uses only the digits 0 and 1. Each position in a binary number represents a power of 2, similar to how each position in a decimal number represents a power of 10. For example, the binary number `1010` represents:


* 1 &times; 2<sup>3</sup> + 0 &times; 2<sup>2</sup> + 1 &times; 2<sup>1</sup> + 0 &times; 2<sup>0</sup> = 8 + 0 + 2 + 0 = 10

## How to Add Binary Numbers

To add binary numbers, you must add each column of bits, similar to decimal addition, but remembering that \(1 + 1 = 10\) in binary. The result can have a carry that must be added to the next column.

### Example of Binary Addition:

```
  0101 (5 in decimal)
+ 0110 (6 in decimal)
-------
  1011 (11 in decimal)
```

## Usage with Arduino

The Arduino is used to read the values of the nibbles, execute the binary addition logic, and display the result on LEDs. Buttons are used to control when the nibbles are read and when the addition is performed.
