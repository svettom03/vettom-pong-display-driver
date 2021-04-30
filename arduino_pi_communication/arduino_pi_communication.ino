#define LED_1_PIN 9

bool priorValue = true;

void setup() {
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
}

void activateLight(bool on){
  if(on){
    digitalWrite(LED_1_PIN, HIGH);
  }else{
    digitalWrite(LED_1_PIN, LOW);
  }

}

void loop() {
  String command = checkIfNewInstruction();
  if(command != ""){
    if(command == "on"){
      activateLight(true);
    }else{
      activateLight(false);
    }
  }
}
