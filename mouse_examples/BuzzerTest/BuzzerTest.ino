const unsigned int BUZZ = 10;

void setup() {
}

void loop() {
  for (int i = 0; i < 10; i++) {
    tone(BUZZ, 3000+(i*200), 100);
    delay(100);
  }
}
