#include <mbed.h>

rtos::Thread t1;
rtos::Thread t2;

rtos::Mutex led_on_mutex;
bool led_on = false;

void blinkIndicator(void) {
  while(true) {
    digitalWrite(13, HIGH);

    // Use a mutex else either thread can
    // get interrupted while reading and writing
    led_on_mutex.lock();
    led_on = true;
    led_on_mutex.unlock();

    // Sleep 500 ms (print can run)
    rtos::ThisThread::sleep_for(500);
    digitalWrite(13, LOW);

    led_on_mutex.lock();
    led_on = false;
    led_on_mutex.unlock();

    rtos::ThisThread::sleep_for(500);
  }
}

void printBlinkStatus(void) {
  while(true) {
    Serial.print("Led status ");

    led_on_mutex.lock();
    Serial.println(led_on);
    led_on_mutex.unlock();

    // Sleep 100 ms (print runs faster than led)
    rtos::ThisThread::sleep_for(100);
  }
}

void setup()
{
  Serial.begin(115200);
  
  t1.start(mbed::callback(blinkIndicator));
  t2.start(mbed::callback(printBlinkStatus));
}

void loop()
{ 
    rtos::ThisThread::sleep_for(1000); // Do nothing in the main thread
}
