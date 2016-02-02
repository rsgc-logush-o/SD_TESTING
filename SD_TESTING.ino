#define CMD0 B01000000
#define CMD1 B01000001
#define CMD6 B01000110
#define CMD9 B01001001
#define CMD10 B01001010
#define CMD12 B01001100
#define CMD13 B01001101
#define CMD16 B01010000
#define CMD17 B01010001
#define CMD18 B01010010
#define CMD24 B01011000
#define CMD25 B01011001
#define CMD27 B01011011
#define CMD28 B01011100
#define CMD29 B01011101
#define CMD30 B01011110
#define CMD32 B01100000
#define CMD33 B01100001
#define CMD38 B01100110
#define CMD41 B01101001
#define CMD42 B01101010
#define CMD55 B01110111
#define CMD56 B01111000
#define CMD58 B01111010
#define CMD59 B01111011

#define R1 8
#define R2 16
#define R3 40

int clockPin = 9;
int dataOut = 10;
int dataIn = 11;
int cardSelect = 8;
int cardIn = 4;
int cardOut = 5;
int statusLedRed = 6;
int statusLedGreen = 7;

void setup() 
{
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(dataOut, OUTPUT);
  pinMode(dataIn, INPUT);
  pinMode(cardSelect, OUTPUT);
  pinMode(cardIn, INPUT);
  pinMode(cardOut, INPUT);
  pinMode(statusLedRed, OUTPUT);
  pinMode(statusLedGreen, OUTPUT);
}

void loop() 
{
  if(digitalRead(cardIn))initSD();
}

void initSD()
{

  boolean isInit = false;
  
  digitalWrite(cardSelect, HIGH);
  digitalWrite(dataOut, HIGH);
  
  for(int i = 0; i < 74; i++)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(clockPin, HIGH);
  }

  digitalWrite(cardSelect, LOW);

  sendCommand(CMD0, 0);

  recieveData(R1);

  while(!isInit)
  {
    sendCommand(CMD55, 0);

    recieveData(R1);

    sendCommand(CMD41, 0);

    if(recieveData == 0)isInit = true;
  }

  sendCommand(CMD58, 0);

  recieveData(R3);

 

}

void sendCommand(uint8_t command, uint32_t arguments)
{

  uint64_t fullCommand = command << 40 | arguments << 8 | 1;
  
  for(uint8_t i = 47; i > -1; i--)
  {
    digitalWrite(clockPin, LOW);

    digitalWrite(dataOut, fullCommand >> i & 1);

    digitalWrite(clockPin, HIGH);
  }
}

uint64_t recieveData(uint8_t responseSize)
{

  uint64_t dataRecieved = 0;
  for(uint8_t i = 0; i < responseSize; i++)
  {
    digitalWrite(clockPin, HIGH);
    
    dataRecieved |= digitalRead(dataIn) << responseSize - i;

    digitalWrite(clockPin, LOW);
  }

  return dataRecieved;
}
