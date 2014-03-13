/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))  
void writeByte(int b);
uint8_t reverseByte(uint8_t in);

// Hardware data
int ledPin = 5;       // select the pin for the LED
int ledVal = LOW;
int buttonPin1 = 2;
int buttonPin2 = 3;
int button1;
int button2;

// Waveform data
int signal[] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250};
int signalSize = NELEMS(signal);
int low = 35;
int high = 255;
int stride = 1;
int counter = low;
//int counter1 = low;
int counter1 = 0;
int writeVal;
//int amplitude = (high - low)/2;
//float rad_scale = 2*3.14159/(stride*(high-low));

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

  // Disable/enable interrupts: http://playground.arduino.cc/Main/AVR#.Uxs5h_ldVjI
  cli(); // This disables interrupts

  // Setting up interupt timer 1
  TCCR0A = 0; TCCR0B = 0; TCNT0  = 0;

  // set compare match register
  // (16*10^6 * stride) / (freq*1024*220*(number of 220 loops in a cycle)) - 1
  // (16*10^6) / (freq*1024*signallength) - 1
  // must be <256
  OCR0A = 34;
  TCCR0A |= (1 << WGM01);

  // Set bits for prescaler. Table of set values here: http://goo.gl/QSg3Di
//  TCCR0B |= (1 << CS01);                // Prescaler: 8
  TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler: 64
//  TCCR0B |= (1 << CS02);                // Prescaler: 256
//  TCCR0B |= (1 << CS02) | (1 << CS00);  // Prescaler: 1024

  TIMSK0 |= (1 << OCIE0A);

  sei(); // This enables interrupts
}

ISR(TIMER0_COMPA_vect){
//  button1 = digitalRead(buttonPin1);
  button1 = PIND & B00000100; // Assuming the button is on digital pin 2
  if (button1) return;

//  // LED Code for testing the interrupts
//  digitalWrite(ledPin, ledVal);
//  if (counter1 > high) {
//    ledVal = !ledVal;
//    counter1 = low;
//  }
//  counter1 += 1;
//  writeByte(counter1);

//  // Create a sine wave
//  float floater;
//  
//  counter1 += 1;
//  if (counter1 > high) counter1 = low;
//
////    Serial.println("");
//    floater = sin((float) (counter - low)*rad_scale);
//    Serial.println(floater);
//    writeVal = (int) amplitude*floater + amplitude + low;
//    Serial.println(writeVal);

//  writeVal = counter1;

// // Read Allen's sine wave
  writeVal = signal[counter1];
  writeByte(writeVal);
  
  counter1 ++;
  if (counter1 == signalSize) counter1 = 0;
}

// Writes a byte to the Arduino 6-13 pins, with the largest/first bit in the integer writing to pin 6
// http://playground.arduino.cc/Code/BitMath#registers
void writeByte(int b) {
//  uint8_t setInt = reverseByte((uint8_t) b);
  uint8_t setInt = b;
  
  // Set pins 8-13
  uint8_t bitmask = B00111111;
  PORTB = (setInt >> 2) & bitmask;
  
  // Set pins 6,7
  bitmask = B11000000;
  PORTD = (PORTD & (uint8_t) ~bitmask) | ((setInt << 6) & bitmask);
}

// Mirrors the bits in a byte
// Information found here: http://forum.arduino.cc/index.php/topic,54304.0.html
uint8_t reverseByte(uint8_t in)
{
  uint8_t out;
  out = 0;
  if (in & 0x01) out |= 0x80;
  if (in & 0x02) out |= 0x40;
  if (in & 0x04) out |= 0x20;
  if (in & 0x08) out |= 0x10;
  if (in & 0x10) out |= 0x08;
  if (in & 0x20) out |= 0x04;
  if (in & 0x40) out |= 0x02;
  if (in & 0x80) out |= 0x01;
  return(out);
}

void loop() {
//  button1 = digitalRead(buttonPin1);
////  button1 = PIND & B00000100; // Assuming the button is on digital pin 2
//  if (button1) return;
//  
////  counter += stride;
//  counter ++;
//  if (counter > high) counter = low;
//  
//  // write to the digital pins  
//  writeByte(counter);
}
