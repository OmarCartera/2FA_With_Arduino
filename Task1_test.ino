/*************************
* Gear shift indicator + *
*    quick shifter       *
*    By: Omar Gamal      *
* c.omargamal@gmail.com  *
*                        *
*       17/4/2016        *
**************************/


// let power-button-resistor-ground and take the output at
// button and resistor mutual pin


// defining constants for shift up/down buttons
#define upButton 11
#define downButton 2


//6 speed gearbox
#define maxShifts 6
#define minShifts 0


//defining boolean variables to save last button press
boolean lastUpButton = LOW;
boolean lastDownButton = LOW;
boolean eeh = HIGH;

// the number of gear we're in
int i=0;

// counter el 7oroof
int _7arf = 0;

// time el maska
unsigned long int wa2t = 0;

//a function that shifts up
void upShift()
{
  if(digitalRead(upButton) == lastUpButton)
    {
      wa2t = millis();
      _7arf++;
    }
}


void setup()
{
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  
  Serial.begin(9600);
  Serial.println('N');
}


void loop()
{
  lastUpButton = digitalRead(upButton);
  lastDownButton = digitalRead(downButton);

  wa2t = millis();
  _7arf = 0;
  
  //if upshift button is pressed
  while((lastUpButton == HIGH) && (eeh == HIGH))
  {
    if(digitalRead(upButton) == lastUpButton)
      {
        wa2t = millis();
        _7arf++;
      }    
    while(digitalRead(upButton) == HIGH)
    {
      //it stays here until you release the button
    }
  
    //to prevent shifting more than once
    delay(50);
    
    if ((millis() - wa2t) > 300)
    {      
      if (_7arf == 1)
      {
        Serial.print('o');
      }
      
      if (_7arf == 2)
      {
        Serial.print('m');
      }

      if (_7arf == 3)
      {
        Serial.print('a');
      }
      
      wa2t = 0;
      _7arf = 0;
      
      break;
    }
  }


  //if upshift button is pressed
  while((lastDownButton == HIGH) && (eeh == HIGH))
  {
    if(digitalRead(downButton) == lastDownButton)
      {
        wa2t = millis();
        _7arf++;
      }    
    while(digitalRead(downButton) == HIGH)
    {
      //it stays here until you release the button
    }
  
    //to prevent shifting more than once
    delay(50);
    
    if ((millis() - wa2t) > 300)
    {      
      if (_7arf == 1)
      {
        Serial.print('a');
      }
      
      if (_7arf == 2)
      {
        Serial.print('b');
      }

      if (_7arf == 3)
      {
        Serial.print('c');
      }
      
      wa2t = 0;
      _7arf = 0;
      
      break;
    }
  }
}
