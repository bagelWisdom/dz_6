
#include <Wire.h>

const int sampleWindow = 50;
unsigned int sample;
 
#define SENSOR_PIN_D 14
#define SENSOR_PIN_A 4
#define DIOD_PIN 2
 
void setup(){
  pinMode(SENSOR_PIN_D, INPUT); 
  pinMode(SENSOR_PIN_A, INPUT); 
  pinMode(DIOD_PIN, OUTPUT);
  Serial.begin(115200);

}
 
void loop()
{
  unsigned long startMillis = millis();                  
  float peakToPeak = 0;                                  
  unsigned int signalMax = 0;                            
  unsigned int signalMin = 1024;                         
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(SENSOR_PIN_A);
    if (sample < 1024)                                  
    {
      if (sample > signalMax)
      {
        signalMax = sample;                          
      }
      else if (sample < signalMin)
      {
        signalMin = sample;                           
      }
    }
  }
  peakToPeak = signalMax - signalMin;                    
  int db = map(peakToPeak, 0, 900, 49, 90);         
  Serial.print("\t");
  Serial.println(db);
  
  if (db <= 55)
  {
    Serial.print("Level:Quite");
     // digitalWrite(DIOD_PIN, HIGH);
      delay(1000);
     // digitalWrite(DIOD_PIN, LOW);
  }
  else if (db > 60 && db < 85)
  {
    Serial.print("Level:Moderate");
    digitalWrite(DIOD_PIN, HIGH);
    delay(2000);
    digitalWrite(DIOD_PIN, LOW);
  }
  else if (db >= 85 && db <= 90)
  {
    Serial.print("Level:High");
    digitalWrite(DIOD_PIN, HIGH);
    delay(3000);
    digitalWrite(DIOD_PIN, LOW);
  }
  else
  {
    digitalWrite(DIOD_PIN, LOW);
    Serial.print("NO_SOUND");
  }
  delay(200);
}