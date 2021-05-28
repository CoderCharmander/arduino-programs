typedef unsigned long long u64;

u64 sum = 0;
u64 count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  pinMode(2, INPUT);
  sum = analogRead(5);
  count = 1;
}

bool spiking;
long long lastspike = -1;

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(5)
           // digitalRead(2)
  ;
  float avg = (float)sum / count;
  char log_[64];
  //Serial.println(avg - val);
  if (abs(avg - val) < 20) {
    sum += val;
    ++count;
    spiking = false;
  } else if (!spiking) {
    spiking = true;
    u64 now = millis();
    if (lastspike != -1) {
      Serial.println((unsigned long)(now - lastspike) * 2);
    }
    lastspike = now;
  }
  delay(10);
}
