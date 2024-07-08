unsigned long lastDebounceTime = 0; // última vez que o botão foi pressionado
unsigned long debounceDelay = 5;   // O intervalo, igual ao delay do código anterior
int nibble_A[4] = {0, 0, 0, 0}, nibble_B[4] = {0, 0, 0, 0}, sumOut[4] = {0, 0, 0, 0}; // global arrays to store the nibbles and the sum
int carryBit; // global variable for the carry bit
int switchNibble = 0;
int switchSum = 1;

void setup(){
  // pins for state manipulation
  pinMode(2, INPUT); // button to add the nibbles
  pinMode(3, INPUT); // button to switch the nibbles
  pinMode(13, OUTPUT); // pin to show if the sum is showing or not

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

void readInputPins(){
  if(digitalRead(2)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(switchSum){
        switchSum = 0;
      }else{
        switchSum = 1;
        carryBit = 0;
        sumNibbles();
      }
    }
    lastDebounceTime = millis();
  }

  if(digitalRead(3)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(switchNibble){
        switchNibble = 0;
      }else{
        switchNibble = 1;
      }
    }
    lastDebounceTime = millis();
  }

  if(digitalRead(4)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(!switchNibble){
        if(nibble_A[0]){
          nibble_A[0] = 0;
        }else{
          nibble_A[0] = 1;
        }
      }else if(switchNibble){
        if(nibble_B[0]){
          nibble_B[0] = 0;
        }else{
          nibble_B[0] = 1;
        }
      }
    }
    lastDebounceTime = millis();
  }
  if(digitalRead(5)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(!switchNibble){
        if(nibble_A[1]){
          nibble_A[1] = 0;
        }else{
          nibble_A[1] = 1;
        }
      }else if(switchNibble){
        if(nibble_B[1]){
          nibble_B[1] = 0;
        }else{
          nibble_B[1] = 1;
        }
      }
    }
    lastDebounceTime = millis();
  }

  if(digitalRead(6)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(!switchNibble){
        if(nibble_A[2]){
          nibble_A[2] = 0;
        }else{
          nibble_A[2] = 1;
        }
      }else if(switchNibble){
        if(nibble_B[2]){
          nibble_B[2] = 0;
        }else{
          nibble_B[2] = 1;
        }
      }
    }
    lastDebounceTime = millis();
  }
  if(digitalRead(7)){
    if((millis() - lastDebounceTime) > debounceDelay){
      if(!switchNibble){
        if(nibble_A[3]){
          nibble_A[3] = 0;
        }else{
          nibble_A[3] = 1;
        }
      }else if(switchNibble){
        if(nibble_B[3]){
          nibble_B[3] = 0;
        }else{
          nibble_B[3] = 1;
        }
      }
    }
    lastDebounceTime = millis();
  }
}
void showOutput(){
  digitalWrite(13, switchSum);
  if(switchSum){
    for(int i = 0; i < 4; ++i){
      digitalWrite(i+8, sumOut[i]); // uses the digitalWrite() function to pass the output values 
    }
    digitalWrite(12, carryBit);
  }else{
    if(!switchNibble){
      for(int i = 0; i < 4; ++i){
        digitalWrite(i+8, nibble_A[i]); // uses the digitalWrite() function to pass the output values 
      }
      digitalWrite(12, switchNibble);
    }else{
      for(int i = 0; i < 4; ++i){
        digitalWrite(i+8, nibble_B[i]); // uses the digitalWrite() function to pass the output values 
      }
      digitalWrite(12, switchNibble);
    }
  } 
}

void calculateCarryBit(int i){ // function that calculates the existence of a carry bit
  if((nibble_A[i] & nibble_B[i]) | (nibble_A[i] & carryBit) | (nibble_B[i] & carryBit)){
    carryBit = 1;
  }else{
    carryBit = 0;
  }
}

void sumNibbles(){ // function that adds the bits and stores them in arrays
  for(int i = 0; i < 4; ++i){
    if((nibble_A[i] ^ nibble_B[i]) ^ carryBit){
      sumOut[i] = 1;
    }else{
      sumOut[i] = 0;
    }
    calculateCarryBit(i); // calls the function that defines the carry bit
  }
}

void loop(){
  readInputPins();
  showOutput();
}