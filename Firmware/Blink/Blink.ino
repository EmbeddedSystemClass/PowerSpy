int LED_RED = 25;
int LED_GREEN = 26;
int LED_BLUE = 27;

void setup() {  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);
  delay(1000);

  Serial.println("TESTE");
}
