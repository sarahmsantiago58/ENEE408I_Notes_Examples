const unsigned int VCC_SENSE = 27;
const float ADC_COUNTS_TO_VOLTS = (2.4 + 1.0) / 1.0 * 3.3 / 4095.0;


void setup() {
  pinMode(VCC_SENSE, INPUT);
  Serial.begin(115200);
}

void loop() {
  while(1) { 
    int counts = analogRead(VCC_SENSE);
    Serial.print("ADC: ");
    Serial.print(counts);
    Serial.print(" Volts: ");
    Serial.println(ADC_COUNTS_TO_VOLTS * counts);
  }
}
