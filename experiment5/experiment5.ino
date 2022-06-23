
#include "pitches.h" 

// notes in the melody 
int melody1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4}; 
int melody2[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_A3, NOTE_F4, 0, NOTE_B3, NOTE_C4}; 
int melody3[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_D3, NOTE_F4, 0, NOTE_E3, NOTE_D4};
int melody4[] = {NOTE_F1, NOTE_G3, NOTE_C3, NOTE_B3, NOTE_F4, 0, NOTE_G3, NOTE_C4}; 
int melody5[] = {NOTE_F3, NOTE_G3, NOTE_C3, NOTE_A3, NOTE_F4, 0, NOTE_A3, NOTE_E4}; 

// note durations: 4 = quarter note, 8 = eighth note, etc.: 
int noteDurations1[] = {4, 8, 8, 4, 4, 4, 4, 4}; 
int noteDurations2[] = {8, 4, 8, 4, 8, 2, 4, 4}; 
int noteDurations3[] = {8, 4, 8, 4, 8, 2, 2, 4}; 
int noteDurations4[] = {8, 4, 2, 4, 8, 2, 16, 4}; 
int noteDurations5[] = {16, 2, 8, 4, 8, 4, 4, 4}; 

// buz pin 
int tonePin = 7; 

// infrared pin 
int irPin = 8; 

void setup() {
  
pinMode (irPin, INPUT); 

Serial.begin (9600); 
Serial.println ("Remote Controlled melody player"); 
Serial.println ("Press a key from 1 to 5 to play a melody");

} 

// Step 1: Read the duration (of pulses) of key pressed 
//using micros() 

// on the Remote Control and store in an array 
// Step 2: Find out the exact key pressed based on the code

void loop() { 
  
  int bits_len = 24; 
  unsigned int arr[ bits_len ]; 
  unsigned long val = 0; 
  unsigned long startTime, endTime; 
  
  // loop till any key on remote is not pressed 
  // when key is pressed the value is LOW 
  while (digitalRead (irPin) == HIGH) ;
 
  // loop to receive 24 bits of key press on remote control 
  for (int i = 0; i < bits_len; i++) { 
    // loop till a key is pressed 
    while (digitalRead (irPin) == LOW) ; 
    
    // once a key is pressed note the start time 
    startTime = micros(); 
    
    // loop till key is released 
    while (digitalRead (irPin) == HIGH) ; 
    
    // after key is released note the end time 
    endTime = micros(); 
    
    // store the difference in the time interval 
    arr[ i ] = endTime - startTime;
  }

  for (int i = 0; i < bits_len; i++) { 
    // if the time interval more than 1000 microseconds 
    
    if (arr[ i ] > 1000) { 
    // binary to decimal conversion 
    // 1 << i is nothing but 2 raised to the power of i 
    val = val + (1 << i); 
    } 
  }
  Serial.print("value:" );
  Serial.println(val, HEX);
 
  switch (val) { 
    
    // Key 1, channel 1 
    case 0x619F : //proper val that I'm getting 
      Serial.println ("Playing melody-1"); 
      play_melody (melody1, noteDurations1); 
      break; 
      
    // Key 2, channel 2 
    case 0x1FCE : 
      Serial.println ("Playing melody-2"); 
      play_melody (melody2, noteDurations2); 
      break; 
      
    // Key 3, channel 3 
    case 0x1F42 :  
      Serial.println ("Playing melody-3"); 
      play_melody (melody3, noteDurations3); 
      break; 
      
    // Key 4, channel 4 
    case 0x11FE : 
      Serial.println ("Playing melody-4"); 
      play_melody (melody4, noteDurations4); 
      break; 
      
    // Key 5, channel 5 
    case 0x1FC6 : 
      Serial.println ("Playing melody-5"); 
      play_melody (melody5, noteDurations5); 
      break; 
  
    // Key 6, channel 6
    case 0x1F4A : 
      Serial.println ("Key 6"); 
      delay (1000); 
      break; 
  
    // Key 7, channel 7
    case 0x1F7A: 
      Serial.println ("Key 7"); 
      delay (1000); 
      break; 
  
    // Key 8, channel 8
    case 0x1F5A : 
      Serial.println ("Key 8"); 
      delay (1000); 
      break;
  
    // Key 9, channel 9
    case 0xFFFFFF00: 
      Serial.println ("Key 9"); 
      delay (1000); 
      break; 
  
    // Default
    default : 
      Serial.println ("Press any key from 1 to 9"); 
  } 
} 
void play_melody (int melody[], int noteDurations[]) { 

  for (int thisNote = 0; thisNote < 8; thisNote++) { 
    // to calculate the note duration, take one second 
    // divided by the note type 
    // i.e. quarter note = 1000 / 4, eighth note = 1000 / 8, etc. 
    
    int noteDuration = 1000 / noteDurations[ thisNote ]; 
    tone (tonePin, melody[ thisNote ], noteDuration); 
    
    // to distinguish the notes, set a minimum time between them. 
    // the note's duration + 30% work well: 
    
    int pauseBetweenNotes = noteDuration * 1.30; 
    delay (pauseBetweenNotes); 
    
    // stop the tone playing 
    noTone (tonePin); 
  }
}
