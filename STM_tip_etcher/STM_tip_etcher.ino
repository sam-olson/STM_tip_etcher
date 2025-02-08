int readPin = 3;          // pin reading Vout of voltage divider formed with electrodes
int basePin = 8;          // pin that activates transistor switch that controls delivery of power to electrodes 
int ledPin = 7;           // pin that activates LED indicator

// threshold variables
float v_threshold = 0.2;  // voltage threshold, below which power to electrodes is shut off
float t_threshold = 0.5;  // time threshold in minutes below hich power to electrodes will not be shut off even if voltage threshold is reached

// variables for storing data
float voltage;
int N = 0;
float sum_v = 0.0;
float average = 0.0;

/* Cuts voltage to electrodes until Arduino is restarted */
void cut_voltage()
{
  digitalWrite(basePin, LOW);
  digitalWrite(ledPin, HIGH);
  Serial.println("Etching stopped");
  while (1)
  {
    continue;
  }
}

/* Converts milliseconds to minutes */
float milli_to_min(unsigned long t)
{
  return t / 60000.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(basePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(basePin, HIGH);
  digitalWrite(ledPin, LOW);

}

void loop() {
  voltage = 5.0 * (analogRead(readPin) / 1023.0);

  sum_v += voltage;
  N++;

  // Average every 50 cycles to smooth out transient spikes
  if (N == 50)
  {
    Serial.print(milli_to_min(millis()), 4);
    Serial.print(",");
    Serial.println(average);
    average = sum_v / N;
    
    sum_v = 0;
    N = 0;
  }

  // if you are past the time threshold...
  if (milli_to_min(millis()) >= t_threshold)
  {
    // if you are below the voltage threshold...
    if (average <= v_threshold) 
    {
      Serial.print(milli_to_min(millis()), 4);
      Serial.print(",");
      Serial.println(average);

      // cut voltage to the electrodes to stop etching of the tip
      cut_voltage();
    }
  }
  delay(10);
}
