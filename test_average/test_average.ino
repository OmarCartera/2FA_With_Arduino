int value[10] = {0};

int i = 0;

int avg;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  delay(500);

  for(i=9; i>=0; i--)
  {
    value[i] = value[i-1];
  }

  value[0] = analogRead(A5);

  avg = 0;
  
  for(i=0; i<10; i++)
  {
    avg += value[i];
  }
  
  Serial.println(avg/10);
}
