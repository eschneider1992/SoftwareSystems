/*
 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
}

// Bit operation defined here: http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
// Seen again here: http://forum.arduino.cc/index.php/topic,54304.0.html
void writeByte(int b) {
  b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
  
  // Write ports 6,7, leave the rest of the bits alone
  // (PORTD & 0xC) is the data that has been bit-masked to zer out the leftmost two terms
  // ((b << 6) | 0xC0) is the bits we want to write. The 2 leftmost should be the signal, rest should be zero
  PORTD = (PORTD & 0xC) | ((b << 6) | 0xC0);
  
  // Write ports 8-13, leave the last two bits of PORTB 0 (there are no 14, 15 ports)
  PORTB = (b >> 2) | 0x3F;
  
  Serial.println("Integer, PORTD, PORTB");
  Serial.println(b);
  Serial.println(PORTD);
  Serial.println(PORTB);
  //int pin;
  //for (pin=13; pin>=6; pin--) {
  //  digitalWrite(pin, x&1);
  //  x >>= 1;
  //}
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  counter += stride;
  if (counter > high) {
    counter = low;
    //Serial.println(counter);
  }

  // write to the digital pins  
  writeByte(counter);
}
