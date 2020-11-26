

//ECG sensor test
  
char auth[] = "688eff00841e481fbbac27213a37164b";
const int heartPin = A2;
void setup() {
   Serial.begin(9600);
}
 void loop() { 
 int heartValue = analogRead(heartPin);
 Serial.println(heartValue);
 delay(5);
 }
