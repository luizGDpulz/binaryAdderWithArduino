# User Guide 👤

## Code Explanation
An in-depth explanation of code intelligence, that is, how the adder practically sums the bits and returns the result to us with LEDs lighting up or turning off.



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
  pinMode(2, INPUT);   // button to add the nibbles
  pinMode(3, INPUT);   // button to switch the nibbles
  pinMode(4, INPUT);   // bit 2^0
  pinMode(5, INPUT);   // bit 2^1
  pinMode(6, INPUT);   // bit 2^2
  pinMode(7, INPUT);   // bit 2^3
  pinMode(8, OUTPUT);  // bit 2^0
  pinMode(9, OUTPUT);  // bit 2^1
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
Adds the bits and stores the result:
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

## calculateCarryBit() Function
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
### Logical Operators in the sumBit() Function
- `^` (XOR): Used to add bits without carry.
- `&` (AND): Used to check for the presence of carry.
- `|` (OR): Used to determine if a carry should be propagated.


## readNibble() Function
Reads the input nibbles:
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

## showOutput() Function
Displays the sum result:
```cpp
void showOutput(){
  for(int i = 0; i < 4; ++i){
    digitalWrite(i + 8, sumOut[i]);
  }    
  digitalWrite(12, carryBit);
}
```