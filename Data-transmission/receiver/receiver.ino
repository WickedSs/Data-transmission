#include <LiquidCrystal_I2C.h>

int R_clock = 3;
int R_data = 2;


char message[16];
volatile byte r_bytes = 0;
volatile int bit_pos = 0;
volatile bool update_lcd = true;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup() {
  pinMode(R_data, INPUT);
  strcpy(message, "");
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(R_clock), onClock, RISING);
  
}

void onClock() {
  bool r_bite = digitalRead(R_data);

  if(bit_pos == 8) {
    r_bytes = 0;
    bit_pos = 0;
  }

  if (r_bite) {
    r_bytes |= (0x80 >> bit_pos);
  }

  bit_pos += 1;

  if (bit_pos == 8) {
    strncat(message, &r_bytes, 1);
  }

  update_lcd = true;
  
}


void loop() {
  if (update_lcd) {
    update_lcd = false;


    lcd.noCursor();
    lcd.setCursor(0, 0);
    lcd.print(message);
    lcd.setCursor(0, 1);
    
    for (int i = 0; i < 8; i += 1) {
      if (i < bit_pos) {
        lcd.print(r_bytes & (0x80 >> i) ? "1" : "0");
      } else {
        lcd.print(" ");
      }
    }

    lcd.setCursor(strlen(message), 0);
    lcd.cursor();
  }
}




