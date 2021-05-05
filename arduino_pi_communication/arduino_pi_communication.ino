
#define LIGHT_DELAY 1
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  for(int postivePin = 0; postivePin < 16; postivePin++){
    int physicalPin = positivePinToPhysicalPin(postivePin);
    pinMode(physicalPin, OUTPUT);  
  }
  for(int negativePin = 0; negativePin < 32; negativePin++){
    int physicalPin = negativePinToPhysicalPin(negativePin);
    pinMode(physicalPin, OUTPUT); 
  }

  setAllLights(false);
  Serial.begin(57600);
}

String checkIfNewInstruction(){
  if(Serial.available() > 0){
    return "";
  }
  String data = Serial.readStringUntil('\n');
  Serial.print("You sent me: ");
  Serial.println(data);
  return data;
  delay(500);
}

void setAllLights(bool onOrOff){
  for(int postivePin = 0; postivePin < 16; postivePin++){
    for(int negativePin = 0; negativePin < 32; negativePin++){
      setLight(postivePin, negativePin, onOrOff); 
    }
  }
}

int logicalPinToPhysicalPin(int logicalPin){
  // Mega board doesn't have all pins going in order so this
  // flips the first 13 to make then go in order
  if(logicalPin > 13){
    return logicalPin;
  }
  return 13 - logicalPin;
}

int positivePinToPhysicalPin(int positivePin){
  // Positive pins are pins 0-15
  return logicalPinToPhysicalPin(positivePin);
}

int negativePinToPhysicalPin(int negativePin){
  // Negative pins are pins 16-47
  return logicalPinToPhysicalPin(negativePin + 16); 
}

void setLight(int postivePin, int negativePin, bool on){
  int physicalPosPin = positivePinToPhysicalPin(postivePin);
  int physicalNegPin = negativePinToPhysicalPin(negativePin);
  if(on){
    digitalWrite(physicalPosPin, HIGH);
    digitalWrite(physicalNegPin, LOW);
  }else{
    digitalWrite(physicalPosPin, LOW);
    digitalWrite(physicalNegPin, HIGH);
  }

}

void displayPattern(String pattern, int iterations){

  Serial.println("displayPattern");
  for(int iteration = 0; iteration < iterations; iteration++){
    int positivePin = 0;
    int negativePin = 0;
    for(int i = 0; i < pattern.length(); i++){
      // increment where we are in the 2D array
      if(pattern[i] == ':'){
        positivePin++;
        negativePin = 0;
        continue;
        //don't handle lights on separator
      }
      if(pattern[i] != '0'){
        setLight(positivePin, negativePin, true);
        delay(LIGHT_DELAY);
        setLight(positivePin, negativePin, false);
      }
      negativePin++; 
    }
  }
}

void loop() {
  
  String basicPattern = "11:11";
  displayPattern(basicPattern, 500);
  delay(1000);

  basicPattern = "10:10";
  displayPattern(basicPattern, 500);
  delay(1000);
  
  //String command = checkIfNewInstruction();
  //if(command != ""){
  //}
}
