# User Guide

## Code Explanation

### Declaration of Global Variables
```cpp
int nibble_A[4], nibble_B[4], sumOut[4]; // global arrays to store the nibbles and the sum
int carryBit; // global variable for the carry bit
```

### setup() Function
Configures the Arduino pins:
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

### sumBit() Function
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

### calculateCarryBit() Function
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
#### Logical Operators in the sumBit() Function
- `^` (XOR): Used to add bits without carry.
- `&` (AND): Used to check for the presence of carry.
- `|` (OR): Used to determine if a carry should be propagated.


### readNibble() Function
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

### showOutput() Function
Displays the sum result:
```cpp
void showOutput(){
  for(int i = 0; i < 4; ++i){
    digitalWrite(i + 8, sumOut[i]);
  }    
  digitalWrite(12, carryBit);
}
```

### loop() Function
Controls the reading and adding of nibbles:
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
