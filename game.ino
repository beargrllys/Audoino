#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define joystick_x A2
#define joystick_y A1
#define joystick_sw A0
Servo servo;
int Buzzer1 = 6;
int Buzzer2 = 8;
boolean intro = false;
boolean level = false;
int harddelay = 250;
int easydelay = 500;
int easyanswer[15][15] = {0};
int youranw[15][15]={0};
int times =0;

void intro1(){
  int i=0;
  while(i<3){
  digitalWrite(Buzzer1,HIGH);
  digitalWrite(Buzzer2,HIGH);
  if(i==0){
    lcd.print("   WELCOME!");
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
  }
  else if(i==1){
    lcd.print("  MEMORY SOUND");
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(13,HIGH);
    digitalWrite(9,HIGH);
    }
  else if (i==2){
    lcd.print("     ENJOY!");
    digitalWrite(13,LOW);
    digitalWrite(9,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(2,HIGH);
    }
  delay(500);
  digitalWrite(Buzzer1,LOW);
  digitalWrite(Buzzer2,LOW);
  delay(500);
  lcd.clear();
  i++;
  }
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
  }
  //lcd.setCursor(0,1);
int levels(){
  lcd.clear();
  int level = 0;//0 is hard 1 is easy
  lcd.print("  HARD    EASY  ");
  lcd.setCursor(0,1);
  lcd.print("========");
  while(true){
  if(analogRead(joystick_y)<=20){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  HARD    EASY  ");
    lcd.setCursor(0,1);
    lcd.print("        ========");
    level = 1;
    }
  else if(analogRead(joystick_y)>=1000){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  HARD    EASY  ");
    lcd.setCursor(0,1);
    lcd.print("========");
    level = 0;
    }
  if(analogRead(joystick_x)<=20){
    lcd.clear();
    return level;
    }
  }
  }

void gamesetting(){
  int i=1;
  int j=0;
  int temp=0;
  while(i<=15){
    while(j<i){
        temp = random(300);
        easyanswer[i-1][j]=(temp%2+1);
        j++;
      }
      i++;
      j=0;
    }
  }

int yourlistlenght(int y){
  int len =0;
  int i=0;
  while(i<15){
    if(youranw[y][i]!=0){
      len+=1;
      }
      i++;
    }
    return len;
  }

boolean easyjudge(int y){
  int i=0;
  int score = 0;
  while(i<15){
    if(youranw[y-1][i]!=0 && easyanswer[y-1][i]!=0 && youranw[y-1][i]==easyanswer[y-1][i]){
      score += 1;
      }
    i+=1;
    }
  lcd.clear();
  lcd.print("score: ");
  lcd.setCursor(7,0);
  lcd.print(score);
  lcd.setCursor(13,0);
  lcd.print("/");
  lcd.setCursor(15,0);
  lcd.print(y);
  delay(2000);
  if(y==score){
    return true;
    }
  else{
    return false;
    }
  
  }

void cleanarray(){
  int i=0;
  int j=0;
  while(i<15){
      while(j<15){
        easyanswer[i][j]=0;
        j++;
      }
      i++;
      j=0;
    }
  i=0;
  j=0;
  while(i<15){
      while(j<15){
        youranw[i][j]=0;
        j++;
      }
      j=0;
      i++;
    }
  }

void easygame(int whatgame){
  int score = 0;
  int i=1;
  int j=0;
  int k=0;
  boolean joytime=false;
  gamesetting();
  while(i<=15){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     LV.");
    lcd.setCursor(8,0);
    lcd.print(i);
    delay(2000);
    j=0;
    while(j<3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("       ");
      lcd.setCursor(7,0);
      lcd.print((3-j));
      digitalWrite(12-j,HIGH);
      delay(1000);
      digitalWrite(12-j,LOW);
      j++;
      }
    lcd.clear();
    lcd.print("  LISTEN IT");
    lcd.setCursor(0,1);
    lcd.print("<-L   ::    R->");
    j=0;
    while(j<i+1){
      if(easyanswer[i-1][j] == 1){
        digitalWrite(Buzzer1,HIGH);
        if(whatgame == 1){
          delay(easydelay);
          }
        if(whatgame == 0){
          delay(harddelay);
          }
        digitalWrite(Buzzer1,LOW);
        }
      if(easyanswer[i-1][j] == 2){
        digitalWrite(Buzzer2,HIGH);
        if(whatgame == 1){
          delay(easydelay);
          }
        if(whatgame == 0){
          delay(harddelay);
          }
        digitalWrite(Buzzer2,LOW);
        }
      j+=1;
      delay(200);
      }
    k=0;
    times=0;
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    lcd.clear();
    lcd.print("  WHERE SOUND?");
    lcd.setCursor(0,1);
    lcd.print("<-L   ::    R->");
    while((yourlistlenght(i-1) < i) && times<=6000){
      if(times >= 2000){
        digitalWrite(12,LOW);
        }
      if(times >= 4000){
        digitalWrite(11,LOW);
        }
      if(times >= 6000){
        digitalWrite(10,LOW);
        break;
        }
      if(k!=0){
          lcd.clear();
          lcd.print("      AND?");
          }
      if(analogRead(joystick_y)>=900){
        youranw[i-1][k]=1;
        digitalWrite(2,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("      GOT IT");
        k+=1;
        delay(300);
      }
      if(analogRead(joystick_y)<=120){
        youranw[i-1][k]=2;
        digitalWrite(3,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("       OK...");
        k+=1;
        delay(300);
       }
     delay(20);
     times+=20;
     digitalWrite(3,LOW);
     digitalWrite(2,LOW);
    }
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    
    if(easyjudge(i) == true){
      lcd.clear();
      lcd.print("    GOOD JOB!");
      digitalWrite(9,HIGH);
      delay(1000);
      digitalWrite(9,LOW);
      if(i==16){
        break;
        }
      }
    else{
      lcd.clear();
      lcd.print("    YOU WRONG!");
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      break;
      }
      i+=1;
      }
      
  }


  
void setup() {
  lcd.begin();
  lcd.backlight();//lcd셋업
  Serial.begin(9600);
  pinMode(13,OUTPUT);//오답 LED
  pinMode(12,OUTPUT);//카운트 다운 3
  pinMode(11,OUTPUT);//카운트 다운 2
  pinMode(10,OUTPUT);//카운트 다운 1
  pinMode(9,OUTPUT); //정답 LED
  pinMode(3,OUTPUT);// 왼쪽 LED
  pinMode(1,OUTPUT);//오른쪽 LED
  pinMode(joystick_x, INPUT);//조이스틱 상하
  pinMode(joystick_y, INPUT);//조이스틱 좌우
  pinMode(joystick_sw, INPUT);
  pinMode(Buzzer1, OUTPUT);//왼쪽
  pinMode(Buzzer2, OUTPUT);//오른쪽
  servo.attach(7);//서보준비
  
  randomSeed(analogRead(0));
}


void loop() {
  int whatgame;
  if(intro == false){
    intro1();
    intro = true;
    }
  while(true){
    setup();
    level = false;
    harddelay = 250;
    easydelay = 500;
    cleanarray();
    
    if(level == false){
      whatgame = levels();
      level = true;
      }
    easygame(whatgame);
      level = false;
    }
   
  
  

}
