// include the library code:
#include <LiquidCrystal.h>

#define SW1 2
#define SW2 3
#define SW3 13

boolean page_1 = HIGH;

boolean change_1 = LOW;
boolean change_2 = LOW;
boolean change_3 = LOW;

boolean enable_s1 = HIGH;
boolean enable_s2 = HIGH;
boolean enable_s3 = HIGH;
boolean enable_s4 = HIGH;

boolean masked = HIGH;
boolean passed = LOW;
boolean auth = LOW

int s1, s2, s3, s4;

int col = 0;

int i;

// those hold the last 10 readings AKA 5 seconds
int values_1[10];
int values_2[10];
int values_3[10];

String password;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);


void setup()
{
  Serial.begin(115200);
  
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.print("Welcome Dr.Tamer!");
  delay(1000);
  lcd.clear();

  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
}

void loop()
{
  while(!(passed))
  {
    change_1 = digitalRead(SW1);
    change_2 = digitalRead(SW2);
    change_3 = digitalRead(SW3);
    
    if(change_1 == LOW)
    {
      lcd.setCursor(col, 1);
      if (masked)
        lcd.print('*');     // password masking

      else
        lcd.print('a');

        
      col++;

      password+= 'a';

      //Serial.println(password);
      
      while(digitalRead(SW1) == LOW);
      delay(50); // debounce

      if(password == "aaaaa")
      {
        delay(1000);
        passed = HIGH;

        lcd.clear();

        lcd.setCursor(3, 0);
        lcd.print("Authorized");
        lcd.setCursor(5, 1);
        lcd.print("Access");
        delay(3000);
        lcd.clear();
      }
    }

    if(change_2 == LOW)
    {
      if (password.length() > 0)
      {
        col--;
        lcd.setCursor(col, 1);
        lcd.print(' ');
          
        password = password.substring(0, (password.length() - 1));
        //Serial.println(password);
      }
      
      while(digitalRead(SW2) == LOW);
      delay(50); // debounce
    }

    if(change_3 == LOW)
    {
      if(masked)
      {
        lcd.setCursor(0,0);
        lcd.print("Enter Password:");

        lcd.setCursor(0, 1);
        lcd.print(password);

        masked = LOW;
      }

      else if(!(masked))
      {
        lcd.setCursor(0,0);
        lcd.print("Enter Password:");

        lcd.setCursor(0, 1);
        
        for(i=0; i < password.length(); i++)
        {
          lcd.print('*');
        }

        masked = HIGH;
      }
      
      while(digitalRead(SW3) == LOW);
      delay(50); // debounce
    }
  }



  
  while(passed)
  {
    change_1 = digitalRead(SW1);
    change_2 = digitalRead(SW2);
    
    if(change_1 == LOW)
    {
      page_1 = !(page_1);
      
      while(digitalRead(SW1) == LOW);
  
      lcd.clear();
    }
  
  
    if((change_2 == LOW) && (!(page_1)))
    {
      enable_s1 = !(enable_s1);
      
      while(digitalRead(SW2) == LOW);
    }
  
    if((change_2 == LOW) && (page_1))
    {
      if (enable_s1)
      {
        s1++;
      }
      
      while(digitalRead(SW2) == LOW);
  
      lcd.clear();
    }
    
    if(page_1)
    {
      lcd.setCursor(0, 0);
      
      if (enable_s1 == HIGH)
        lcd.print(s1);
  
      else if (enable_s1 == LOW)
        lcd.print("DIS");
  
      lcd.setCursor(14, 0);
      lcd.print("S2");
  
      lcd.setCursor(0, 1);
      lcd.print("S3");
  
      lcd.setCursor(14, 1);
      lcd.print("S4");
    }
  
    else if(!(page_1))
    {
      lcd.setCursor(0, 0);
  
      if (enable_s1 == HIGH)
        lcd.print("EN1 ");
  
      else if (enable_s1 == LOW)
        lcd.print("DIS1");
  
      lcd.setCursor(13, 0);
      lcd.print("EN2");
  
      lcd.setCursor(0, 1);
      lcd.print("EN3");
  
      lcd.setCursor(13, 1);
      lcd.print("EN4");
    }
  }
}
