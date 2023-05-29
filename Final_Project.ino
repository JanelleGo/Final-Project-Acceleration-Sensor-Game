#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
#include <Wire.h>
#include <SPI.h>

AsyncDelay delay_5s;

float Z, accel;
int buttonA = 4;
int count = 0;
int level = 1;
volatile bool buttonFlagA = 0;
float midi[127];
int A_four = 440; // a is 440 hz...

// Arrays to store Scale MIDI pitch sequence
int c_major[8] = {60, 62, 64, 65, 67, 69, 71, 72}; // c_major scale on C4
int c_minor[8] = {60, 62, 63, 65, 67, 68, 70, 72}; // c_minor scale on C4

int winSong[7][2] = {
    {64, 200},  // song[0][0]], song[0][1]]
    {62, 200},  // song[1][0]], song[1][1]]
    {60, 200},  // song[2][0]], song[2][1]]
    {62, 200},
    {64, 200},
    {64, 200},
    {64, 200},
};

// Lines 27 - 29 derived from speech Demo 
const uint8_t spGAMES[]             PROGMEM ={0xAA,0x15,0x24,0x2A,0xD6,0xE4,0xB6,0xB6,0x79,0x13,0xB1,0x5C,0xB2,0xF3,0x93,0x97,0xA4,0x66,0x3E,0x75,0x77,0x3E,0xF2,0x52,0x8D,0xCD,0x26,0xF6,0xCC,0x7B,0xDE,0x8A,0x9A,0x14,0x2D,0xBA,0xD2,0xAC,0x66,0xDD,0xEB,0xDE,0x8E,0xB6,0x7A,0x47,0x0D,0xAF,0x95,0x3A,0x6D,0xB1,0x9A,0xDA,0x8E,0xED,0x6C,0x67,0x3A,0x6E,0xA5,0x46,0x42,0xB1,0xED,0x74,0x27,0x3A,0x62,0x32,0xC2,0x23,0x76,0xEA,0x7F,0x22,0x36,0x11,0xF5,0x06,0x38,0x1C,0xC8,0x00,0xDF,0x29,0x39,0xE0,0x7B,0x56,0x03,0x7C,0xCD,0xCA,0x80,0xCC,0x83,0x1E,0x00,0x00};
const uint8_t spOVER[]              PROGMEM ={0xA7,0xD0,0xAE,0x2F,0x50,0xBA,0x9D,0x5C,0xDB,0xFA,0x24,0xCE,0x3A,0x72,0x19,0xFA,0x15,0x25,0x73,0xCB,0x45,0xAE,0x67,0xB4,0x2E,0xAD,0x10,0xB1,0x4E,0xC1,0x3D,0xB7,0x3A,0x1A,0x57,0x95,0x70,0xD4,0x9A,0x6C,0x4C,0x85,0xCD,0x4D,0xAF,0x5A,0xA5,0x7D,0x9A,0x9B,0xBB,0x1B,0x8D,0x69,0x66,0xE9,0xDC,0xAD,0xB5,0xA6,0x84,0xD8,0xA8,0xB6,0xD4,0xE9,0x2E,0x56,0x23,0x7E,0x42,0xAF,0xBB,0xC8,0x94,0x78,0x76,0xBD,0x99,0x2C,0x59,0xEC,0xCB,0xF5,0xB2,0x98,0x64,0xA6,0xE4,0x07,0x00,0x00};
const uint8_t spNEXT[]              PROGMEM ={0xAE,0xF6,0x16,0x3E,0x33,0x25,0x85,0xDA,0x5B,0x78,0x8F,0x34,0x5D,0xEA,0xE0,0x60,0x2C,0x5B,0xF6,0xA9,0x73,0xD6,0x50,0xED,0x3A,0xA7,0xCE,0x55,0x53,0x6C,0xEA,0x9E,0x3A,0x77,0x4D,0x8E,0x49,0x72,0x9A,0xDC,0x35,0xC4,0x37,0xC9,0x6C,0x52,0x53,0x2E,0xA9,0xF2,0x44,0x04,0x30,0xC0,0x91,0x51,0x06,0x78,0x29,0x42,0x03,0x12,0x90,0x00,0x08,0x60,0x04,0x55,0x02,0x9C,0xE0,0x82,0x81,0x07,0x00,0x00};


void setup() {
  Serial.begin(9600);

  CircuitPlayground.begin();
  generateMIDI();
  delay_5s.start(5000, AsyncDelay::MILLIS);

  pinMode(buttonA, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(buttonA), pressedA, FALLING);

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
}


void loop() {
 
   delay_5s.start(5000, AsyncDelay::MILLIS);

 if(buttonFlagA){
  CircuitPlayground.playTone(midi[70], 200); //Starting melody
  // buttonFlagA = 0;
  delay(1);
  
while(level = 1 && count < 5 && !delay_5s.isExpired()){

  Z = 0; // Author: Carter Nelson MIT License (https://opensource.org/licenses/MIT) (Lines 38-44)
    for (int i=0; i<10; i++) {
     Z += CircuitPlayground.motionZ();
      delay(1);
  }
  Z /= 10;
  accel = Z;

  Serial.print("Accel: ");
  Serial.println(accel);
  delay(200);

    if(accel > 20){
      count++;
      Serial.print(" Count: ");
      Serial.println(count);
    }
    else if(accel < -20){
      count++;
      Serial.print(" Count: ");
      Serial.println(count);
    }
    else{
      Serial.print(" Count: ");
      Serial.println(count);
    }
    
 }
 if(level = 1 && delay_5s.isExpired() && count < 5){
      Serial.print("            Game Over :( ");
      CircuitPlayground.speaker.say(spGAMES);
      CircuitPlayground.speaker.say(spOVER);
      lose(50);
      buttonFlagA = 0;
      level = 1;
    }
    if(level = 1 && count >= 5){
      level = 2;
      Serial.print("             On to Level 2   -  Shake 8 times");
      CircuitPlayground.speaker.say(spNEXT);
      sparkleLevel1(50);
      buttonFlagA = 0; //turns game completely off
      count = 0;
      delay_5s.start(5000, AsyncDelay::MILLIS);
    }

    
 while(level = 2 && count < 8 && !delay_5s.isExpired()){

  Z = 0; // Author: Carter Nelson MIT License (https://opensource.org/licenses/MIT) (Lines 38-44)
    for (int i=0; i<10; i++) {
     Z += CircuitPlayground.motionZ();
      delay(1);
  }
  Z /= 10;
  accel = Z;

  Serial.print("Accel: ");
  Serial.println(accel);
  delay(200);

    if(accel > 20){
      count++;
      Serial.print(" Count: ");
      Serial.println(count);
    }
    else if(accel < -20){
      count++;
      Serial.print(" Count: ");
      Serial.println(count);
    }
    else{
      Serial.print(" Count: ");
      Serial.println(count);
    }
     if(level = 2 && delay_5s.isExpired() && count < 8){
      Serial.print("            Game Over :( ");
      CircuitPlayground.speaker.say(spGAMES);
      CircuitPlayground.speaker.say(spOVER);
      lose(50);
      buttonFlagA = 0;
      level = 1;
    }
    if(level = 2 && count >= 8){
      Serial.print("                    You Win!!");
      sparkleLevel2(50);
      buttonFlagA = 0; //turns game completely off
      level = 1;
    }
 }//Level 2 while loop
 


 }//button if
} //for loop



void pressedA(){
  buttonFlagA = 1;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

void sparkleLevel1(int flashTime)
{
  // for(int i = 0; i < 10; i++){
  //   CircuitPlayground.setPixelColor(i, 0, 0, 255);
  // }
  for(int i = 0; i<20; i++){
  int LED_num = random(10);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 255);
  delay(flashTime);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 0);
  delay(flashTime);
  }
   for(int i = 0; i < sizeof(winSong) / sizeof(winSong[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[winSong[i][0]], winSong[i][1]);
    Serial.println(midi[winSong[i][0]]);
    delay(1);
  }
  CircuitPlayground.clearPixels();
}

void sparkleLevel2(int flashTime)
{
  for(int i = 0; i<20; i++){
  int LED_num = random(10);
  CircuitPlayground.setPixelColor(LED_num, 0, 255, 0);
  delay(flashTime);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 0);
  delay(flashTime);
  }
   for(int i = 0; i < sizeof(winSong) / sizeof(winSong[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
    CircuitPlayground.playTone(midi[winSong[i][0]], winSong[i][1]);
    Serial.println(midi[winSong[i][0]]);
    delay(1);
  }
  CircuitPlayground.clearPixels();
}


void lose(int flashTime){
  for(int i = 0; i < 10; i++){
  CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
    CircuitPlayground.playTone(midi[72],200);
    delay(1);
    CircuitPlayground.playTone(midi[71], 200);
    delay(1);
    CircuitPlayground.playTone(midi[67], 200);
    delay(1);
    CircuitPlayground.clearPixels();
  }

