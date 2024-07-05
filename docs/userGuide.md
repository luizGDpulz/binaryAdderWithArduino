# User Guide 👤

Here you will find a detailed demonstration of the code intelligence, the heart of our project. This guide is structured to facilitate understanding, providing information and explanations about the C++ language used on Arduino platforms. It presents a solid foundation on the structure of the code for these microcontrollers, including explanations of the main dedicated functions of Arduino.

## 1. Declaration of Global Variables
Declares global variables that can be accessed in any scope of the program.
```cpp
int nibble_A[4], nibble_B[4], sumOut[4]; // global arrays to store the nibbles and the sum Output
int carryBit; // global variable for the carry bit
```

## 2. `setup()` Function
The `setup()` configures the Arduino pins.  

```cpp
void setup(){
  pinMode(2, INPUT); // button to add the nibbles
  pinMode(3, INPUT); // button to switch the nibbles

  pinMode(4, INPUT); // bit 2^0
  pinMode(5, INPUT); // bit 2^1
  pinMode(6, INPUT); // bit 2^2
  pinMode(7, INPUT); // bit 2^3

  pinMode(8, OUTPUT); // bit 2^0
  pinMode(9, OUTPUT); // bit 2^1
  pinMode(10, OUTPUT); // bit 2^2
  pinMode(11, OUTPUT); // bit 2^3
  
  pinMode(12, OUTPUT); // bit 2^4 or carry bit
}
```
`pinMode()` function is used to configure a specific pin on the Arduino board as either an input or an output.

```cpp
pinMode(pin, mode);
```

* `pin` : Specifies the pin number you want to configure.
* `mode` : Specifies the mode of the pin, which can be either  `INPUT`, `OUTPUT`, or `INPUT_PULLUP`.  

Modes:

* `INPUT` : This mode configures the pin to accept input from an external device or sensor. Typically used when you want to read data from a sensor or another device connected to that pin.
* `OUTPUT` : This mode configures the pin to send output to another device or component. It's used when you want to control an external device such as an LED, motor, or another component connected to that pin.
* `INPUT_PULLUP` : This mode configures the pin as an input with an internal pull-up resistor enabled. It's useful when you are connecting a push-button or switch to the pin, and you want to ensure a default state (typically HIGH) when the button is not pressed.

## 3. `loop()` Function
The main program loop executes indefinitely in cycles, performing tasks, initializing other functions, and sending/receiving data.
```cpp
void loop(){
  readNibble();
  if(digitalRead(2) == 1){
    carryBit = 0;
    sumBit();
    showOutput();
  }
}
```
## 4. `readNibble()` Function
The first function to be executed in the loop. It reads the values from digital inputs for Nibbles_A and Nibble_B using the digitalRead() function.

```cpp
void readNibble(){
  if(digitalRead(3) == 0){
    for(int i = 0; i < 4; ++i){
      nibble_A[i] = digitalRead(i + 4);
    }    
  } else if(digitalRead(3) == 1){
    for(int i = 0; i < 4; ++i){
      nibble_B[i] = digitalRead(i + 4);
    }        
  }
}
```
`digitalRead()` function is used to read the state (high or low voltage level) of a digital input pin.

```cpp
int digitalRead(pin);
```
* `pin` : Specifies the digital input pin number you want to read.

Return Value:
* Returns `HIGH (1)` if the voltage on the specified pin is above a certain threshold (typically around 3V when powered by 5V), indicating a logical HIGH or a voltage close to the board's operating voltage.
* Returns `LOW (0)` if the voltage on the specified pin is below the threshold, indicating a logical LOW or a voltage close to 0V.

Using `digitalRead()` allows Arduino programs to respond to the state changes of digital inputs, enabling interactive behaviors with external components like buttons, switches, and sensors.

## 5. `sumBit()` Function
Function that performs bit-bit addition using the `XOR` logic gate.

```cpp
void sumBit(){
  for(int i = 0; i < 4; ++i){
    if((nibble_A[i] ^ nibble_B[i]) ^ carryBit){
      sumOut[i] = 1;
    } else {
      sumOut[i] = 0;
    }
    calculateCarryBit(i);
  }
}
```

An `XOR` (`exclusive OR`) gate is a type of digital logic gate that outputs true or high (1) only when the number of true or high inputs is odd. For two inputs, this means the output is true when the inputs are different, and false or low (0) when the inputs are the same. 

### Truth Table

| Input A | Input B | Output (A XOR B) |
|---------|---------|------------------|
|    0    |    0    |        0         |
|    0    |    1    |        1         |
|    1    |    0    |        1         |
|    1    |    1    |        0         |

When both inputs are 0 or both are 1, the output is 0.  
When one input is 0 and the other is 1, the output is 1.

### Symbol

The `XOR` gate is typically represented by a symbol similar to the `OR` gate but with an extra curved line on the input side. 

In C++ language is represented by the symbol `^` .

### Boolean Expression

The Boolean expression for the XOR gate with inputs A and B is:

$`A \oplus B = (A \cdot \overline{B}) + (\overline{A} \cdot B)`$

- This expression states that the output is true if A is true and B is false, or A is false and B is true.


## 6. `calculateCarryBit()` Function
Calculates the carry bit:
```cpp
void calculateCarryBit(int i){
  if((nibble_A[i] & nibble_B[i]) | (nibble_A[i] & carryBit) | (nibble_B[i] & carryBit)){
    carryBit = 1;
  } else {
    carryBit = 0;
  }
}
```

The function calculates the carry bit for the addition of the `i` bits of `nibble_A` and `nibble_B`, considering the current carry bit.

### Bitwise `AND` Operation (`&`)
* 
  ```cpp
  nibble_A[i] & nibble_B[i]
  ``` 

  Checks if both bits at position `i` in `nibble_A` and `nibble_B` are 1.

*  
  ```cpp
  nibble_A[i] & carryBit
  ```
  Checks if the bit at position `i` in `nibble_A` and the current `carry bit`are both 1.

* 
  ```cpp
  nibble_B[i] & carryBit
  ``` 
  Checks if the bit at position `i` in `nibble_B` and the current `carry bit` are both 1.

### Bitwise `OR` Operation (`|`)
Combines the results of the above AND operations. The OR operation will result in 1 if any of the AND operations result in 1, meaning that any pair of bits or the current carry bit results in a carry.  

### Conditional Statement
If any of the combined conditions (AND results) are true (1), it means that a carry should be generated for the next higher bit. Therefore, carryBit is set to 1.
If none of the conditions are true (all AND results are 0), no carry is generated, and carryBit is set to 0.

## 7. `showOutput()` Function
Displays the sum result.

```cpp
void showOutput(){
  for(int i = 0; i < 4; ++i){
    digitalWrite(i + 8, sumOut[i]);
  }    
  digitalWrite(12, carryBit);
}
```

`digitalWrite()` function in Arduino programming is used to set a digital pin to either HIGH or LOW. This function is crucial for controlling various electronic components such as LEDs, motors, and other devices that can be switched on or off.

### Syntax

```cpp
digitalWrite(pin, value);
```

* `pin` : The number of the digital pin you want to control.

* `value`: The state you want to set the pin to. It can be either HIGH (on) or LOW (off).

### Parameters

* `pin` : The number of the digital pin on the Arduino board you are controlling. It must be a valid digital pin number for your specific Arduino model.

* `value` : The desired state of the pin. HIGH sets the pin to 5V (or 3.3V on 3.3V boards), and LOW sets the pin to 0V.
