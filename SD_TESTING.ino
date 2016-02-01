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
#define CMD42 B01101010
#define CMD55 B01110111
#define CMD56 B01111000
#define CMD58 B01111010
#define CMD59 B01111011

int clockPin = 9;
int dataOut = 10;
int dataIn = 11;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initSD()
{

}

void sendCommand(uint64_t commandToSend)
{
  for(uint8_t i = 47; i > -1; i--)
  {
    digitalWrite(clockPin, LOW);

    digitalWrite(dataOut, commandToSend >> & 1);

    digitalWrite(clockPin, HIGH);
  }
}

void recieveData()
{
  
}
