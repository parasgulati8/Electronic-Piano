/* Play a flute sound when a button is pressed.

   Connect a pushbutton to pin 1 and pots to pins A2 & A3.
   The audio tutorial kit is the intended hardware:
     https://www.pjrc.com/store/audio_tutorial_kit.html

   Without pots connected, this program will play a very
   strange sound due to rapid random fluctuation of the
   pitch and volume!

   Requires Teensy 3.2 or higher.
   Requires Audio Shield: https://www.pjrc.com/store/teensy3_audio.html
*/

#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
#include <SerialFlash.h>
#include <CapacitiveSensor.h>
CapacitiveSensor   Touch1 = CapacitiveSensor(21,20);
CapacitiveSensor   Touch2 = CapacitiveSensor(21,0);
CapacitiveSensor   Touch3 = CapacitiveSensor(21,16);
CapacitiveSensor   Touch4 = CapacitiveSensor(21,17);
#include "Piano_test_samples.h"

AudioSynthWavetable wavetable;
AudioOutputI2S i2s1;
AudioMixer4 mixer;
AudioConnection patchCord1(wavetable, 0, mixer, 0);
AudioConnection          patchCord2(mixer, 0, i2s1, 0);
AudioConnection          patchCord3(mixer, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;

// Bounce objects to read pushbuttons 
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time

void setup() { 
  Serial.begin(115200);
  pinMode(1, INPUT_PULLUP);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  mixer.gain(0, 0.7);
  
  wavetable.setInstrument(Piano_test);
  wavetable.amplitude(1);
}

void loop() {
//  long start = millis();
  //long total1 =  Touch1.capacitiveSensor(30);
  long Touch1_Value =  Touch1.capacitiveSensor(30);
  long Touch2_Value =  Touch2.capacitiveSensor(30);
  long Touch3_Value =  Touch3.capacitiveSensor(30);
  long Touch4_Value =  Touch4.capacitiveSensor(30);
  
  float freq1 = 261.0 ;
  float freq2 = 200.0 ;
  float freq3 = 150.0 ;
  float freq4 = 89.0 ;
  float gain = 0.5;

//  Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(Touch1_Value);     
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(Touch2_Value);
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(Touch3_Value);
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.println(Touch4_Value);         // print sensor output 3
    delay(10);
  if (Touch1_Value > 3000)
  {
      wavetable.playFrequency(freq1);
      wavetable.amplitude(gain);
      delay(500);
      wavetable.stop();
  }
//     delay(10);
//      wavetable.stop();
  if (Touch2_Value > 3000)
  {
      wavetable.playFrequency(freq2);
      wavetable.amplitude(gain);
      delay(500);
      wavetable.stop();
  }
    if (Touch3_Value > 3000)
  {   wavetable.playFrequency(freq3);
      wavetable.amplitude(gain);
      delay(500);
      wavetable.stop();
  }
    if (Touch4_Value > 3000)
   {  wavetable.playFrequency(freq4);
      wavetable.amplitude(gain);
      delay(500);
      wavetable.stop();
   }
      /*wavetable.playFrequency(freq2);
      wavetable.amplitude(gain);
      delay(2000);
      wavetable.playFrequency(freq3);
      wavetable.amplitude(gain);
      delay(2000);
      wavetable.playFrequency(freq4);
      wavetable.amplitude(gain);
      delay(2000);
*/
//  wavetable.amplitude(gain);
//  wavetable.setFrequency(freq1);
}
