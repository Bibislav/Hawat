//#**********************TIN BIRSIC**************************#//
//---------------------------------------------- VERSION --------------
// Add modify settings in continius mode
String Version = "ver 2.4.3";

// Impr_1 -> Promjeni sve konstante u macro #define (low prio)
// Impr_6 -> promjeni imena funkcija i varijabli...they are horrible (low prio)
// Impr_7 -> Smanji globalne varijable (low prio)
// Impr_10 -> Dodati odbrojavanje do kraja graviranja i okretanja. (low prio)
// Impr_16 -> Dodati scroll bar
// Impr_17 -> Uredit Main menu
// Impr_18 -> Kada se vraca u mai menu iz continus/bypass modea pitati da li da obrise
//            part ili da ga sacuva (HIGH PRIO)

// Updates:
// 3. Napravi da je brzina i akceleracija postotak, a ne vrijednost (low prio)
// ******************************************************************************************************************
// 4. Statistics
//   4.1 Prikazati na ekranu vrijeme iznmedu dva graviranja
//   4.2 Prikazati na ekranu vrijeme zamjene i strelicu koja bi oznacavala jesi iznad ili ispod
//       prosjeka
//   4.3 Dodati na ekran broj izgraviranih komad i mogucnost da se upise rucno broj komada
//   4.4 Dodati tipku na ekranu STAT na koju kad bi pritisnuo, otvorio bi se meni sa svom statistikkom
//       npr. vrijeme graviranja = prosjecno vrijeme +- pogreska, najbrze graviranje, najsporije, broj komada
//   4.5 Dodati mogucnost set_time() unutar continius modea 
// ******************************************************************************************************************
// X. Mozda promjenit nacin vracanja u main meni. S tipkom na rotary encoderu (Low prio) 
// X. Contrast da s ne kontrolira potenciometrom nego iz arduina (Low prio) - mozda za Hawat 3.0

//---------------------------------------------- DEBOUNCE -------------
#include <Bounce2.h>
Bounce RotaryEncoderDeb = Bounce();
Bounce footDebContinius = Bounce();
Bounce footDebContiniusOut = Bounce();
Bounce footDebContiniusStep1 = Bounce();
Bounce footDebBypass = Bounce();
//---------------------------------------------- LCD ------------------
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const short int col = 20;
const short int row = 4;
uint8_t down[] = {
        0b00000,
        0b00100,
        0b00100,
        0b00100,
        0b10101,
        0b01110,
        0b00100,
        0b00000
    };
uint8_t up[] = {
        0b00000,
        0b00100,
        0b01110,
        0b10101,
        0b00100,
        0b00100,
        0b00100,
        0b00000
    };
uint8_t left[] = {
        0b00000,
        0b00100,
        0b01000,
        0b11111,
        0b01000,
        0b00100,
        0b00000,
        0b00000
    };
uint8_t right[] = {
        0b00000,
        0b00100,
        0b00010,
        0b11111,
        0b00010,
        0b00100,
        0b00000,
        0b00000
    };
//---------------------------------------------- PAUSE SWITCH ---------
const short int pause_switch = 14;
bool pause_state = false;
//---------------------------------------------- FOOT SWITCH ----------
const short int foot_switch = 16;
//---------------------------------------------- ROTARY ENCODER -------
unsigned long currentTime;
unsigned long loopTime;
const short int pin_A = 5;  
const short int pin_B = 6;  
const short int pin_Button = 4;
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;
//---------------------------------------------- STEPPER --------------
#include <AccelStepper.h>
#define STEP 400
const short int PUL = 3;
const short int DIR = 2;
unsigned int MAX_SPEED = 1000000;
unsigned int ACCEL = 10000;
AccelStepper stepp(1, PUL, DIR);
float pos = 0.25;
//---------------------------------------------- CHANGE SETTINGS ------
bool mod = false;
bool enable = true;
bool state = false;
int encoder_pos = 1;
unsigned short int passedTimeToGoBack = 0;
long duration;
unsigned int timeToGoBack = 3000;
//---------------------------------------------- SETTINGS -------------
String menuItem1 = "1) Continius mode";
String menuItem2 = "2) Bypass mode";
String menuItem3 = "3) Fine Adjust";

int speed_val = 0;
int acceleration_val = 0;

int menuItem1_Dval = MAX_SPEED;
int menuItem2_Dval = ACCEL;
//-----------------------------------------------ENGRAVING -------------
unsigned int time_milis= 2000;
const short int mark_switch = 15;
//-----------------------------------------------STATISTIC -------------
unsigned int part = 0;
unsigned long t = 0;
unsigned long t_last = 0;
unsigned long t_press = 0;
//-----------------------------------------------FUNCTIONS -------------
void setup() {
  pinMode(mark_switch, OUTPUT);
  digitalWrite(mark_switch, HIGH);
  
  pinMode(pause_switch, INPUT);
  
  pinMode(foot_switch, INPUT_PULLUP);
  footDebContinius.attach(foot_switch);
  footDebContinius.interval(5);
  footDebContiniusOut.attach(foot_switch);
  footDebContiniusOut.interval(5);
  footDebContiniusStep1.attach(foot_switch);
  footDebContiniusStep1.interval(5);
  footDebBypass.attach(foot_switch);
  footDebBypass.interval(5);
    
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  pinMode(pin_Button, INPUT_PULLUP);
  RotaryEncoderDeb.attach(pin_Button);
  RotaryEncoderDeb.interval(5);
  currentTime = millis();
  loopTime = currentTime;

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(PUL, LOW);
  
  lcd.begin(col, row);
  lcd.clear();
  lcd.createChar (1, down);
  lcd.createChar (2, up);
  lcd.createChar (3, left);
  lcd.createChar (4, right);
  
  hello_screen();
  delay(2500);
  settings(1);
}
void loop() {
  currentTime = millis();
  if(currentTime >= (loopTime + 5)){ 
    encoder_A = digitalRead(pin_A);    
    encoder_B = digitalRead(pin_B);   
    
    if((!encoder_A) && (encoder_A_prev)){
      if(encoder_B) {
        encoder_pos++;               
        } else {
        encoder_pos--;               
        }
      
      if(encoder_pos > 3){
        encoder_pos = encoder_pos - 3;
        } else if(encoder_pos < 1){
        encoder_pos = 3 - encoder_pos;
        }   
      settings(encoder_pos);
    }   
    encoder_A_prev = encoder_A;    
    loopTime = currentTime;  
  }

  RotaryEncoderDeb.update();
  state = RotaryEncoderDeb.read();
  if((state == false)&&(enable == true)){
    mod = true;
    enable = false;
  } else if(state == true) enable = true;


  if(mod == true){
    change_settings(encoder_pos);
    settings(encoder_pos);    
  }
}
void printStatistics() {
  unsigned short int row = 3;
  String rowString = "P=" + String(part);
  
  unsigned short int digits = 0;
  unsigned int num = part;
  // ------------------------------------- Part ------------------------
  do {
    num /= 10;
    digits++;
    } while (num != 0);
  for(unsigned short int i = 1+digits; i < 19; i++) rowString += " ";
  // -------------------------------------------------------------------  
  
  lcd.setCursor(0,row);
  lcd.print(rowString);
}
void bypassMode() {
  bool foot_state = true;
  bool out = true;

  bool pressOnlyOnce = true;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>>>>BYPASS MODE<<<<");
    
  while(out == true) {
    pause_state = digitalRead(pause_switch);

    switch (pause_state) {
      case false:
        footDebBypass.update();
        foot_state = footDebBypass.read();

        passedTimeToGoBack = 0;
        lcd.setCursor(0,2);
        lcd.print("-----ENGRAVING!-----");
        
        if(foot_state == false) {
          digitalWrite(mark_switch, LOW);
          if(pressOnlyOnce == true) {
            part++;
//          t_press = millis();
//          t = t_press - t_last;
//          printStatistics();
//          t_last = t_press;
            pressOnlyOnce = false;
            
          }
        }
        else if(foot_state == true) {
          digitalWrite(mark_switch, HIGH);
          pressOnlyOnce = true;
          }
        
        break;

      case true:
        lcd.setCursor(0,2);
        lcd.print("-------PAUSE!-------");
        
        footDebBypass.update();
        foot_state = footDebBypass.read();
        
        if(foot_state == false) {
          lcd.setCursor(0,3);
          lcd.print("Back to main menu ");
          if( ((timeToGoBack - passedTimeToGoBack) % 1000 ) == 0) {
            lcd.setCursor(18,3);
            lcd.print((timeToGoBack - passedTimeToGoBack) / 1000);
            lcd.setCursor(19,3);
            lcd.print(" ");
            }
      
          delay(100);
          passedTimeToGoBack = passedTimeToGoBack + 100;

          if (passedTimeToGoBack == timeToGoBack) {
            passedTimeToGoBack = 0;
            mod = false;
            return;
          }
        }
        else if(foot_state == true) {
          lcd.setCursor(0,3);
          lcd.print("                    ");
//        printStatistics();
          passedTimeToGoBack = 0;
        }
        
        break;
    }
  }
  return;
}
void continiusMode() {
  bool foot_state = true;
  bool out = true;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>>CONTINIUS MODE<<<");
  continiusMode_step1();
  continiusMode_step2();
  
  delay(250);
  start(true, pos);
  pos += 0.25;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>>CONTINIUS MODE<<<");

  while(out == true) {
    pause_state = digitalRead(pause_switch);
    switch(pause_state) {
      case true:
        lcd.setCursor(0,2);
        lcd.print("-------PAUSE!-------");
        
        footDebContiniusOut.update();
        foot_state = footDebContiniusOut.read();
        
        if(foot_state == false) {
          lcd.setCursor(0,3);
          lcd.print("Back to main menu ");
          if( ((timeToGoBack - passedTimeToGoBack) % 1000 ) == 0) {
            lcd.setCursor(18,3);
            lcd.print((timeToGoBack - passedTimeToGoBack) / 1000);
            }
      
          delay(100);
          passedTimeToGoBack = passedTimeToGoBack + 100;

          if (passedTimeToGoBack == timeToGoBack) {
            passedTimeToGoBack = 0;
            mod = false;
            out = false;
            // TODO ask if you want to save P or not (save?())
          }
        }
        else if(foot_state == true) {
          printStatistics();
          passedTimeToGoBack = 0;
        }
        
        break;
      
      case false:
        lcd.setCursor(0,2);
        lcd.print("-----ENGRAVING!-----"); 
      
        footDebContinius.update();
        foot_state = footDebContinius.read();

        printStatistics();
        
        if(foot_state == false) {
          digitalWrite(mark_switch, LOW);
          delay(time_milis-250);
          digitalWrite(mark_switch,HIGH);            
          delay(250);
          
          part++;
          
//        t_press = millis();
//        t = t_press - t_last;
          printStatistics();
//        t_last = t_press;
          
          start(true, pos);
          pos = pos + 0.25;
          footDebContinius.update();
          foot_state = footDebContinius.read();
        }
        break;
    }
  }
}
void continiusMode_step1() {
  lcd.setCursor(0,1);
  lcd.print("Set up:             ");
  lcd.setCursor(0,2);
  lcd.print("Input time:         ");
  set_time();
}
void continiusMode_step2() {
  lcd.setCursor(0,1);
  lcd.print("Set up:             ");
  lcd.setCursor(0,2);
  lcd.print("Input part:         ");
  set_part();
}
void start(bool dir, float n){
  if(dir == false) n = n * STEP;
  else if(dir == true) n = n * STEP * -1; 

  stepp.moveTo(n);
  stepp.setMaxSpeed(MAX_SPEED);
  stepp.setAcceleration(ACCEL); 

   while (stepp.distanceToGo() != 0) stepp.run();

  return;
}
void set_time(){  
  lcd.setCursor(0,3);
  lcd.print("(Push to accept)    ");  
  bool ena = true;
  bool ok = true;
  bool check = false;
  float time_sec = 2;

  unsigned short int digits;
  unsigned short int num;  
  
  while(ena == true){
      currentTime = millis();
      if(currentTime >= (loopTime + 5)){ 
        encoder_A = digitalRead(pin_A);    
        encoder_B = digitalRead(pin_B);   
        if((!encoder_A) && (encoder_A_prev)){
          if(encoder_B) {
            time_sec = time_sec + 0.05;               
           } else {
            time_sec = time_sec - 0.05;               
            }   
      } 
      encoder_A_prev = encoder_A;    
      loopTime = currentTime; 
      if(time_sec < 0.05) time_sec = 0.05;
      if(time_sec > 99.9) time_sec = 99.9;

      digits = 0;
      num = time_sec;
      do {
        num /= 10;
        digits++;
      } while (num != 0);
      if (digits == 1){
        lcd.setCursor(12,2);
        lcd.print(time_sec);
        lcd.setCursor(16,2);
        lcd.print(" [s]");
      }
      else if (digits == 2){
        lcd.setCursor(12,2);
        lcd.print(time_sec);
        lcd.setCursor(17,2);
        lcd.print(" [s");
      }      
      
      RotaryEncoderDeb.update();
      ok = RotaryEncoderDeb.read();
      if((ok == false)&&(check == true)){
        ena = false;
      } else if (ok == true){
        ena = true;
        check = true;
      }
      }
      
     }
     time_milis = (time_sec*1000) + 200;
     
}
void set_part() {
  lcd.setCursor(0,3);
  lcd.print("(Push to accept)    ");  
  bool ena = true;
  bool ok = true;
  bool check = false;

  String inputPartRow;

  unsigned short int digits;
  unsigned short int num;  
  
  while(ena == true){
      currentTime = millis();
      if(currentTime >= (loopTime + 5)){ 
        encoder_A = digitalRead(pin_A);    
        encoder_B = digitalRead(pin_B);   
        if((!encoder_A) && (encoder_A_prev)){
          if(encoder_B) {
            part = part + 1;               
           } else {
            part = part - 1;               
            }   
      } 
      encoder_A_prev = encoder_A;    
      loopTime = currentTime; 
      //if(part < 1) part = 1;
      
      digits = 0;
      num = part;
      do {
        num /= 10;
        digits++;
      } while (num != 0);
      inputPartRow = String(part);
      for(unsigned short int i = 11+digits; i < 19; i++) inputPartRow += " ";
      lcd.setCursor(12,2);
      lcd.print(inputPartRow);
      
      RotaryEncoderDeb.update();
      ok = RotaryEncoderDeb.read();
      if((ok == false)&&(check == true)){
        ena = false;
      } else if (ok == true){
        ena = true;
        check = true;
        }
      }
      
     }
     
}
void fine_adjust(){
  int stepsPer = 50;
  unsigned int timePer = 5000; 
  while(stepsPer >= 1){
    if(stepsPer < 10){
      lcd.setCursor(18, 3);
      lcd.print(" ");
      lcd.setCursor(16, 3);
      lcd.print(">");
      lcd.setCursor(17, 3);
      lcd.print(stepsPer);
    }
    lcd.setCursor(16, 3);
    lcd.print(">");
    lcd.setCursor(17, 3);
    lcd.print(stepsPer);
    
    currentTime = millis();
    if(currentTime >= (loopTime + 5)){ 
      encoder_A = digitalRead(pin_A);    
      encoder_B = digitalRead(pin_B);   
      
      if((!encoder_A) && (encoder_A_prev)){
        if(encoder_B) {
          digitalWrite(DIR, LOW);
          for(int i = 0; i < stepsPer; i++){
              digitalWrite(PUL, HIGH);
              delayMicroseconds(timePer);
              digitalWrite(PUL, LOW);             
            }
          } else {
          digitalWrite(DIR, HIGH); 
          for(int i = 0; i < stepsPer; i++){
              digitalWrite(PUL, HIGH);
              delayMicroseconds(timePer);
              digitalWrite(PUL, LOW);             
            }             
            }
          }   
      encoder_A_prev = encoder_A;    
      loopTime = currentTime;  
    }
  
    RotaryEncoderDeb.update();
    state = RotaryEncoderDeb.read();
    if((state == false)&&(enable == true)){
    stepsPer = stepsPer / 2;
    timePer = timePer * 2;
    enable = false;
  } else if(state == true) enable = true;
  }
  mod = false;
  return;
}
void resetStatistics() {
  part = 0;
  t = 0;
  t_last = 0;
  t_press = 0;
}
void change_settings(short int num_select){
  if(num_select == 1) continiusMode();
  if(num_select == 2) bypassMode();
  if(num_select == 3) fine_adjust();
}
void settings(short int num_select){
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(">>>>>Main Menu:<<<<<");
  lcd.setCursor(0, 1);
  lcd.print(" ");  
  lcd.setCursor(0, 2);
  lcd.print("*");
  lcd.setCursor(0, 3);
  lcd.print("*");
  
  display_menuItem(num_select);
}
void display_menuItem(short int num_select){

  if(num_select == 1){
    
    lcd.setCursor(0, 2);
    lcd.print(">");
    
    lcd.setCursor(1, 2);
    lcd.print(menuItem1);
  
    lcd.setCursor(1, 3);
    lcd.print(menuItem2);
    
    lcd.setCursor(19, 3);
    lcd.print((char) 0x01);
    
  }

  if(num_select == 2){
    
    lcd.setCursor(0, 3);
    lcd.print(">");
    
    lcd.setCursor(1, 2);
    lcd.print(menuItem1);
  
    lcd.setCursor(1, 3);
    lcd.print(menuItem2);
    
    lcd.setCursor(19, 3);
    lcd.print((char) 0x01);
  }

  if(num_select == 3) {
         
    lcd.setCursor(0, 3);
    lcd.print(">");
    
    lcd.setCursor(1, 2);
    lcd.print(menuItem2);
  
    lcd.setCursor(1, 3);
    lcd.print(menuItem3);
  }
}
void hello_screen(){

  lcd.clear();
  
  for(int thisCol = 1; thisCol < col - 1; thisCol++){
    lcd.setCursor(thisCol, 0);
    lcd.write("X");

    lcd.setCursor(thisCol, 3);
    lcd.write("X");
  }

  for(int thisRow = 0; thisRow < row; thisRow++){
    lcd.setCursor(0, thisRow);
    lcd.write("X");
    lcd.setCursor(1, thisRow);
    lcd.write("X");
   
    lcd.setCursor(18, thisRow);
    lcd.write("X");
    lcd.setCursor(19, thisRow);
    lcd.write("X");        
  }

    lcd.setCursor(6, 1);
    lcd.write("-Hawat-");
    lcd.setCursor(5, 2);
    lcd.print(Version);

}
