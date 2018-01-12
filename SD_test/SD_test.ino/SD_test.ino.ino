/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
 */

#include <SPI.h>
#include <SD.h>

int i=0;

File myFile;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
}

void loop()
{
  i++;
  
  myFile.print(analogRead(A0));
  myFile.print(" ... ");
  myFile.print(analogRead(A1));
  myFile.print(" ... ");
  myFile.print(analogRead(A2));
  myFile.print(" ... ");
  myFile.print(analogRead(A3));
  myFile.print(" ... ");
  myFile.println(millis());

  delay(500);

  if (i == 10)
  {
    myFile.close();
    digitalWrite(13, HIGH);
    while(1);
  }
}


