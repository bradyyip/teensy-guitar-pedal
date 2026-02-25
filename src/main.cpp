#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//sine volume control var
float vol;
bool button_state = false;
bool fx_on = false;

//testing out the fx
AudioEffectReverb reverb1;
AudioEffectChorus chorus1;

//establish mixer to change around the fx chain
AudioMixer4 mixer1;

//testing output and dac
AudioSynthWaveformSine sine1;
AudioOutputI2S i2s1;
AudioConnection patchCord1(sine1, 0, mixer1, 0);
AudioConnection patchCord2(sine1, chorus1);
AudioConnection patchCord3(chorus1, 0, mixer1, 1);
AudioConnection patchCord4(sine1, reverb1);
AudioConnection patchCord5(reverb1, 0, mixer1, 2);
AudioConnection patchCord6(mixer1, 0, i2s1, 0);

// AudioConnection patchCord1(sine1, chorus1);
// AudioConnection patchCord2(chorus1, flange1);
// AudioConnection patchCord3(flange1, 0, i2s1, 0);
// AudioConnection patchCord4(flange1, 0, i2s1, 1);

//toggle reverb func


void setup() {
  //serial monitor for debugging
  Serial.begin(9600);

  AudioMemory(200);
  sine1.frequency(440);
  sine1.amplitude(0.2);

  reverb1.reverbTime(0.01);

  //enable chorus
  short chorusBuffer[2048];
  chorus1.begin(chorusBuffer, 2048, 2);

  //reverb control
  pinMode(11, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  //read the button state
  button_state = digitalRead(11);

  //if the button is pressed, turn on the fx
  if (button_state == HIGH) {
    Serial.println("Button Pressed");
    chorus1.voices(5);
  } else {
    chorus1.voices(0);
  }
  
}
