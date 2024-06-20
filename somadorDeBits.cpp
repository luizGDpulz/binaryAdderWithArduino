int nibble_A[4], nibble_B[4], sumOut[4]; // arrays globais para armazenar os nibbles e a soma
int carryBit; // variavel globa para o carry bit

void setup(){ // função setup para definir as funções dos pinos do Arduino
  // pinos da manipulação dos estados
  pinMode(2, INPUT); // botão para somar os nibbles
  pinMode(3, INPUT); // botão para dar switch dos nibbles

  // pinos dos bits de entrada
  pinMode(4, INPUT); // bit 2^0
  pinMode(5, INPUT); // bit 2^1
  pinMode(6, INPUT); // bit 2^2
  pinMode(7, INPUT); // bit 2^3

  // pinos dos bits de saída
  pinMode( 8, OUTPUT); // bit 2^0
  pinMode( 9, OUTPUT); // bit 2^1
  pinMode(10, OUTPUT); // bit 2^2
  pinMode(11, OUTPUT); // bit 2^3
  pinMode(12, OUTPUT); // bit 2^4 ou carry bit
}

void calculateCarryBit(int i){ // função que calcula a existência de carry bit
  if((nibble_A[i] & nibble_B[i]) | (nibble_A[i] & carryBit) | (nibble_B[i] & carryBit)){
    carryBit = 1;
  }else{
    carryBit = 0;
  }
}

void sumBit(){ // função que soma os bits e os armazena em arrays
  for(int i = 0; i < 4; ++i){
    if((nibble_A[i] ^ nibble_B[i]) ^ carryBit){
      sumOut[i] = 1;
    }else{
      sumOut[i] = 0;
    }
    calculateCarryBit(i); // chama a função que define o carry bit
  }
}

void readNibble(){ // função que lê um nibble por vez
  if(digitalRead(3) == 0){ // se estado do switch dos nibbles for 0 (desligado/LOW)
    for(int i = 0; i < 4; ++i){
      nibble_A[i] = digitalRead(i+4); // lê valores para o nibble A
    }    
  }else if(digitalRead(3) == 1){ // se estado do switch dos nibbles for 1 (ligado/HIGH)
    for(int i = 0; i < 4; ++i){
      nibble_B[i] = digitalRead(i+4); // lê valores para o nibble B
    }        
  }
}

void showOutput(){ // exibe a soma dos bits nos LEDs 
  for(int i = 0; i < 4; ++i){
    digitalWrite(i+8, sumOut[i]); // utiliza a função digitalWrite() para passar os valores de saída 
  }    
  digitalWrite(12, carryBit); // // utiliza a função digitalWrite() para passar o valor do carry bit 
}

void loop(){
  readNibble();
  if(digitalRead(2) == 1){
    carryBit = 0;
    sumBit();
    showOutput();
  }
}
