void setup() {
  Serial.begin(9600);       //UART para menu
  pinMode(2,OUTPUT);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("wenas");
  digitalWrite(2,1);
  delay(1000);
  digitalWrite(2,0);
  delay(1000);
}
