#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//sine volume control var
float vol;
bool button_state = false;
bool fx_on = false;

//fx on and off var
bool chorus_on = false;
bool delay_on = false;
bool reverb_on = false;
bool btcrsh_on = false;

//after designing pcb fx control read pins will be decided
int btcrsh_enable_pin;
int chorus_enable_pin;
int delay_enable_pin;
int reverb_enable_pin;

//testing out the fx
AudioEffectFreeverb reverb;
AudioEffectChorus chorus;
AudioEffectChorus delay;
AudioEffectChorus biquad;
AudioEffectBitcrusher btcrsh;

//establish mixer to change around the fx chain
AudioMixer4 btcrsh_mix;
AudioMixer4 chorus_mix;
AudioMixer4 delay_mix;
AudioMixer4 reverb_mix;

//testing output and dac

//signal chain 1
AudioSynthWaveformSine sine1;

AudioInputI2S i2s1_in; 

//each fx has a mxr after it to control off and on or to mix the dry and wet signal
//mxr ch 1 is wet and ch 0 is dry
//btcrsh mix
AudioConnection patchCord1(i2s1_in, 0, btcrsh, 0);
AudioConnection patchCord2(i2s1_in, 0, btcrsh_mix, 0);
AudioConnection patchCord3(btcrsh, 0, btcrsh_mix, 1);

//chorus mix
AudioConnection patchCord4(btcrsh_mix, 0, chorus, 0);
AudioConnection patchCord5(btcrsh_mix, 0, chorus_mix, 0);
AudioConnection patchCord6(chorus, 0, chorus_mix, 1);

//delay mix
AudioConnection patchCord7(chorus_mix, 0, delay, 0);
AudioConnection patchCord8(chorus_mix, 0, delay_mix, 0);
AudioConnection patchCord9(delay, 0, delay_mix, 1);

//reverb mix
AudioConnection patchCord10(delay_mix, 0, reverb, 0);
AudioConnection patchCord11(delay_mix, 0, reverb_mix, 0);
AudioConnection patchCord12(reverb, 0, reverb_mix, 1);

//final output
AudioConnection patchCord13(reverb_mix, 0, i2s1_out, 0);

AudioOutputI2S i2s1_out;

//functions to enable or disable fx

//read the btcrsh enable pin
bool btcrsh_enable_read(int btcrsh_enable_pin) {

  if (digitalRead(btcrsh_enable_pin) == HIGH) {
    btcrsh_on = true;
  } else {
    btcrsh_on = false;
  }

  return btcrsh_on;
}

//read chorus enable pin
bool chorus_enable_read(int chorus_enable_pin) {

  if (digitalRead(chorus_enable_pin) == HIGH) {
    chorus_on = true;
  } else {
    chorus_on = false;
  }

  return chorus_on;
}

//read delay enable pin
bool delay_enable_read(int delay_enable_pin) {

  if (digitalRead(delay_enable_pin) == HIGH) {
    delay_on = true;
  } else {
    delay_on = false;
  }

  return delay_on;
}

//read reverb enable pin
bool reverb_enable_read(int reverb_enable_pin) {

  if (digitalRead(reverb_enable_pin) == HIGH) {
    reverb_on = true;
  } else {
    reverb_on = false;
  }

  return reverb_on;
}

//fx control functions




void setup() {
  //serial monitor for debugging
  Serial.begin(9600);

  AudioMemory(200);
  sine1.frequency(440);
  sine1.amplitude(0.2);

  reverb.roomsize(0.5);

  //enable chorus
  short chorusBuffer[2048];
  chorus.begin(chorusBuffer, 2048, 2);

  //btcrsh enable 
  pinMode(btcrsh_enable_pin, INPUT);

  //chorus enable
  pinMode(chorus_enable_pin, INPUT);

  //delay enable
  pinMode(delay_enable_pin, INPUT);

  //reverb enable
  pinMode(reverb_enable_pin, INPUT);
}

void loop() {

  //check if fx are on

  
}
