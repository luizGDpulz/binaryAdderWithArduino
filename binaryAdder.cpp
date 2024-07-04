int nibble_A[4], nibble_B[4], sumOut[4]; // global arrays to store the nibbles and the sum
int carryBit; // global variable for the carry bit

void setup(){ // setup function to define the functions of the Arduino pins
  // pins for state manipulation
  pinMode(2, INPUT); // button to add the nibbles
  pinMode(3, INPUT); // button to switch the nibbles

  // pins for input bits
  pinMode(4, INPUT); // bit 2^0
  pinMode(5, INPUT); // bit 2^1
  pinMode(6, INPUT); // bit 2^2
  pinMode(7, INPUT); // bit 2^3

  // pins for output bits
  pinMode(8, OUTPUT); // bit 2^0
  pinMode(9, OUTPUT); // bit 2^1
  pinMode(10, OUTPUT); // bit 2^2
  pinMode(11, OUTPUT); // bit 2^3
  pinMode(12, OUTPUT); // bit 2^4 or carry bit
}

void calculateCarryBit(int i){ // function that calculates the existence of a carry bit
  if((nibble_A[i] & nibble_B[i]) | (nibble_A[i] & carryBit) | (nibble_B[i] & carryBit)){
    carryBit = 1;
  }else{
    carryBit = 0;
  }
}

void sumBit(){ // function that adds the bits and stores them in arrays
  for(int i = 0; i < 4; ++i){
    if((nibble_A[i] ^ nibble_B[i]) ^ carryBit){
      sumOut[i] = 1;
    }else{
      sumOut[i] = 0;
    }
    calculateCarryBit(i); // calls the function that defines the carry bit
  }
}

void readNibble(){ // function that reads one nibble at a time
  if(digitalRead(3) == 0){ // if the state of the nibble switch is 0 (off/LOW)
    for(int i = 0; i < 4; ++i){
      nibble_A[i] = digitalRead(i+4); // reads values for nibble A
    }    
  }else if(digitalRead(3) == 1){ // if the state of the nibble switch is 1 (on/HIGH)
    for(int i = 0; i < 4; ++i){
      nibble_B[i] = digitalRead(i+4); // reads values for nibble B
    }        
  }
}

void showOutput(){ // displays the sum of the bits on the LEDs 
  for(int i = 0; i < 4; ++i){
    digitalWrite(i+8, sumOut[i]); // uses the digitalWrite() function to pass the output values 
  }    
  digitalWrite(12, carryBit); // uses the digitalWrite() function to pass the carry bit value 
}

void loop(){
  readNibble();
  if(digitalRead(2) == 1){
    carryBit = 0;
    sumBit();
    showOutput();
  }
}
