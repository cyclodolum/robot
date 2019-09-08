#include <IRremote.h>
int ENA=5;//connected to Arduino's port 5(output pwm)
int IN1=2;//connected to Arduino's port 2
int IN2=3;//connected to Arduino's port 3
int ENB=6;//connected to Arduino's port 6(output pwm)
int IN3=4;//connected to Arduino's port 4
int IN4=7;//connected to Arduino's port 7
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long ir_val;
int left_speed = 200;
int right_speed = 200;
int incv=12;
bool revers = false;
void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
  
 pinMode(ENA,OUTPUT);//output
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);

// ускорение от нуля до максимального значения

for (int i = 0; i < 256; i++)

{

//analogWrite(ENA, i);
//analogWrite(ENB, i);
//delay(20);

}

// торможение от максимального значения к минимальному

for (int i = 255; i >= 0; --i)
{

//analogWrite(ENA, i);
//analogWrite(ENB, i);
//delay(20);

}

// теперь отключаем моторы

//digitalWrite(IN1, LOW);
//digitalWrite(IN2, LOW);
//digitalWrite(IN3, LOW);
//digitalWrite(IN4, LOW);
pinMode(13, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);
analogWrite(ENA, 0);
analogWrite(ENB, 0);
}

//0: FF6897

//+: FFA857
//-: FFE01F
//1: FF30CF
//2: FF18E7
//3: FF7A85
//+100: FF9867
//+200 FFB04F

//5: FF38C7

int no_sig_cnt=0;
int no_sig_cnt_max=20;
void loop() {

//setup();
//delay(1000);

  if (irrecv.decode(&results)) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    if (results.value != 0xFFFFFFFF) {
      ir_val = results.value;  
      Serial.println("------ Change key -------");
    }
  }
  else {
    ir_val = 0;
    no_sig_cnt++;
    if (no_sig_cnt > no_sig_cnt_max) {
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      Serial.println("------ No signal -------");
      no_sig_cnt=0;
    }
  }
  if (ir_val == 0xFFA857) { //+
      left_speed += incv;
      right_speed += incv;
    }
    else if (ir_val == 0xFFE01F) { //-
      left_speed -= incv;
      right_speed -= incv;
    }
    else if (ir_val == 0xFF6897) { //0
      left_speed = 0;
      right_speed = 0;
    }
    else if (ir_val == 0xFF30CF) { //1
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);

    }
    else if (ir_val == 0xFF18E7) { //2
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }
    else if (ir_val == 0xFF7A85) { //3
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
 

    }
    else if (ir_val == 0xFF9867) { //+100
      left_speed = 200;
      right_speed = 200;
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      
    }
    else if (ir_val == 0xFFB04F) { //+200
      if (revers) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }
      else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }
      revers = !revers;
      Serial.println("Revers");
      
    }
    else if (ir_val == 0xFF38C7) { //5
      analogWrite(ENA, left_speed);
      analogWrite(ENB, right_speed);
      Serial.println("->5");
    }
    else if (ir_val == 0xFF10EF) { //4
      analogWrite(ENA, left_speed);
      analogWrite(ENB, 0);
      Serial.println("->5");
       
    }
    else if (ir_val == 0xFF5AA5) { //6
      analogWrite(ENA, 0);
      analogWrite(ENB, left_speed);
      Serial.println("->5");
       
    }

    

    
    else {
      
      
    }
    //Serial.println(ir_val);
    delay(70);
    digitalWrite(LED_BUILTIN, LOW);


  


}
