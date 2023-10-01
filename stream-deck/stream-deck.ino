#define VOL A1
#define MUT 7         

int  lastVolume  = 0;
bool lastMuteMic = false;

void setup() 
{    
  pinMode(MUT, INPUT_PULLUP);
  pinMode(VOL, INPUT);

  lastVolume  = analogRead(VOL);
  lastMuteMic = !digitalRead(MUT);
  Serial.begin(9600);
}

void loop() 
{
  sendSliderValues();
  delay(50); 
}

void sendVolumeBody(int volume) {
  float volumeConverted = (float) volume / 1024;

  Serial.println(String("{\"volume\":") + String(volumeConverted) + String("}"));
}

void sendMuteMicBody(bool muteMic) {
  if (!muteMic) return;

  Serial.println(String("{\"muteMic\":") + String(muteMic) + String("}"));
}

void sendSliderValues() { 
  int volume = analogRead(VOL);
  bool muteMic = !digitalRead(MUT);

  if (volume != lastVolume) {
    sendVolumeBody(volume);
    lastVolume = volume;
  }

  if (muteMic != lastMuteMic) {
    sendMuteMicBody(muteMic);
    lastMuteMic = muteMic;
  }
}