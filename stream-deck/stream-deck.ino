// LED
#define A   13 
#define B   12 
#define C   11 
#define D   5  
#define E   4  
#define F   3  
#define G   2  

//Input
#define VOL A1
#define MUT 7         

int  lastVolume  = 0;
bool lastMuteMic = false;
bool lastLed     = true;

void setup() 
{    
  pinMode(A,   OUTPUT);
  pinMode(B,   OUTPUT);
  pinMode(C,   OUTPUT);
  pinMode(D,   OUTPUT);
  pinMode(E,   OUTPUT);
  pinMode(F,   OUTPUT);
  pinMode(G,   OUTPUT);
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
  setLed();
}

void setLed() {
  int ledStatus = lastLed ? HIGH : LOW;

  digitalWrite(A, ledStatus);
  digitalWrite(B, ledStatus);
  digitalWrite(C, ledStatus);
  digitalWrite(D, ledStatus);
  digitalWrite(E, ledStatus);
  digitalWrite(F, ledStatus);
  digitalWrite(G, ledStatus);

  lastLed = !lastLed;
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
