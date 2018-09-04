#include <LiquidCrystal_I2C.h>

int T_clock = 3;
int T_data = 2;

const char *message = "Wicked was Here!";

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


void setup() {
  // configure the pins to output
  pinMode(T_clock, OUTPUT);
  pinMode(T_data, OUTPUT);

  // initialize the lcd 
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print(message);

  for (int bytes = 0; bytes < strlen(message); bytes++ ) {
    char t_bytes = message[bytes]; 
    lcd.noCursor();
    lcd.setCursor(0, 1);
    lcd.print("        ");
    lcd.setCursor(bytes, 0);
    lcd.cursor();
  
    for (int bite = 0; bite < 8; bite++) {
        bool t_bite = t_bytes & (0x80 >> bite);
  
        digitalWrite(T_data, t_bite);
        delay((1000 / 5 ) / 2);    
  
        // udpate the lcd
  
        lcd.noCursor();
        lcd.setCursor(bite, 1);
        lcd.print(t_bite ? "1" : "0");
        lcd.setCursor(bytes, 0);
        lcd.cursor();
  
  
        /// Clock
        digitalWrite(T_clock, HIGH);
        delay( (1000 / 5 ) / 2);
        digitalWrite(T_clock, LOW);
    }
  }

  digitalWrite(T_data, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
