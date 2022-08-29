#include <Arduino.h>

// Check platform.ini file to see all libraries
// Have to include the Adafruit libraries even
// if not used or PlatformIO will not build
// (this is the libraries fault)
#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>

#include <Encoder.h>

Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;

const unsigned int ADC_1_CS = 2;
const unsigned int ADC_2_CS = 17;

const unsigned int VCC_SENSE = 27;
const float ADC_COUNTS_TO_VOLTS = (2.4 + 1.0) / 1.0 * 3.3 / 4095.0;

const unsigned int BUZZ = 26;
const unsigned int BUZZ_CHANNEL = 0;

const unsigned int octave = 4;

const unsigned int M1_ENC_A = 39;
const unsigned int M1_ENC_B = 38;
const unsigned int M2_ENC_A = 37;
const unsigned int M2_ENC_B = 36;

const unsigned int M1_IN_1 = 13;
const unsigned int M1_IN_2 = 12;
const unsigned int M2_IN_1 = 25;
const unsigned int M2_IN_2 = 14;

const unsigned int M1_IN_1_CHANNEL = 8;
const unsigned int M1_IN_2_CHANNEL = 9;
const unsigned int M2_IN_1_CHANNEL = 10;
const unsigned int M2_IN_2_CHANNEL = 11;

const unsigned int M1_I_SENSE = 35;
const unsigned int M2_I_SENSE = 34;

const float M_I_COUNTS_TO_A = (3.3 / 1024.0) / 0.120;

const unsigned int PWM_VALUE = 255; // Max PWM given 8 bit resolution

const int freq = 5000;
const int resolution = 8;

Adafruit_MPU6050 mpu;

void M1_backward() {
  ledcWrite(M1_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}

void M1_forward() {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, PWM_VALUE);
}

void M1_stop() {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}

void M2_backward() {
  ledcWrite(M2_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void M2_forward() {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, PWM_VALUE);
}

void M2_stop() {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void print_motor_stats_500_millis(Encoder& enc1, Encoder& enc2) {
    for(int i = 0; i < 500; i++) { 
    int M1_I_counts = analogRead(M1_I_SENSE);
    int M2_I_counts = analogRead(M2_I_SENSE);

    Serial.print("M1 I ");
    Serial.print(M1_I_counts * M_I_COUNTS_TO_A);
    Serial.print("\t M2 I ");
    Serial.print(M2_I_counts * M_I_COUNTS_TO_A);
    Serial.print("\t Enc 1 ");

    Serial.print(enc1.read());
    Serial.print("\t Enc 2 ");
    Serial.print(enc2.read());

    int counts = analogRead(VCC_SENSE);
    Serial.print("\t Bat volts: ");
    Serial.print(ADC_COUNTS_TO_VOLTS * counts);
    
    Serial.println();
    
    delay(1);
  }
}

void print_lightbar_5000_millis() {
  int adc1_buf[8];
  int adc2_buf[8];

  for (int i = 0; i < 500; i++) {
    int t_start = micros();
    for (int i = 0; i < 8; i++) {
      adc1_buf[i] = adc1.readADC(i);
      adc2_buf[i] = adc2.readADC(i);
    }
    int t_end = micros();
  
    for (int i = 0; i < 6; i++) {
      Serial.print(adc1_buf[i]); Serial.print("\t");
      Serial.print(adc2_buf[i]); Serial.print("\t");
    }

    Serial.print(adc1_buf[6]); Serial.print("\t");

    Serial.print(" time to read ");
    Serial.print(t_end - t_start);
    Serial.print(" us");
    Serial.println();
  
    delay(10);
  }
}

void print_imu() {
  for(int i = 0; i < 500; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.print(" m/s^2 \t");

    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.print(" rad/s \t");

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degC");
  }
}

void setup() {
  Serial.begin(115200);

  ledcSetup(M1_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M1_IN_2_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_2_CHANNEL, freq, resolution);

  ledcAttachPin(M1_IN_1, M1_IN_1_CHANNEL);
  ledcAttachPin(M1_IN_2, M1_IN_2_CHANNEL);
  ledcAttachPin(M2_IN_1, M2_IN_1_CHANNEL);
  ledcAttachPin(M2_IN_2, M2_IN_2_CHANNEL);

  pinMode(M1_I_SENSE, INPUT);
  pinMode(M2_I_SENSE, INPUT);

  pinMode(VCC_SENSE, INPUT);

  adc1.begin(ADC_1_CS);  
  adc2.begin(ADC_2_CS);

  digitalWrite(ADC_1_CS, HIGH);
  digitalWrite(ADC_2_CS, HIGH);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);

  ledcAttachPin(BUZZ, BUZZ_CHANNEL);

  for (int j = 0; j < 1; j++) {
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_D, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_F, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_A, octave);
    delay(500);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_B, octave);
    delay(500);
  }

  ledcWrite(BUZZ_CHANNEL, 0);

  Serial.println("Hello");
}

void loop() {
  // Create the encoder objects after the motor has
  // stopped, else some sort exception is triggered
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);

  while (true) {
    M1_stop();
    M2_stop();

    print_imu();

    print_lightbar_5000_millis();
    
    M1_forward();
    M2_forward();

    print_motor_stats_500_millis(enc1, enc2);

    M1_backward();
    M2_backward();
    delay(500);
    print_motor_stats_500_millis(enc1, enc2);
  }
}