#include <Key.h>
#include <Keypad.h>

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; // variable to store the servo position
boolean done = true;
String password = "5A789#";
String pass = "";
boolean openClose = false;
int button = 10;
const int buzzer = 12;
char button2000khz [12] = {'1','2','3','4','5','6','7','8','9','0','*','#'};
char button1000khz [4] = {'A','B','C'};
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// connect the pins from right to left to pin 2, 3, 4, 5,6,7,8,9
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo.write(30);
  
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
  //pinMode(button,OUTPUT);
  digitalWrite(button,HIGH);
  Serial.begin(9600); 
}

void loop() {
  char key = keypad.getKey();
  //just print the pressed key

  if (key){
  for (unsigned int keyNow = 0; keyNow < sizeof(button2000khz); keyNow++){
    //if (button2000khz[key] != '') 
    if (button2000khz[keyNow] == key){
      //Serial.println(button2000khz[keyNow]);
      int range = (10 - 0) + 1;
      int randomer = range * (rand() / (RAND_MAX + 1.0));
      tone(buzzer, 2000 + keyNow * randomer); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    }
   }
   for (unsigned int keySpecial = 0; keySpecial < sizeof(button1000khz); keySpecial++){
    //if (button2000khz[key] != '') 
    if (button1000khz[keySpecial] == key){
      int range = (10 - 0) + 1;
      int randomer = range * (rand() / (RAND_MAX + 1.0));
      //Serial.println(button1000khz[keySpecial]);
      tone(buzzer, 1000 + randomer * 50); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    }
   }
  }
  /*
   if (key){
      tone(buzzer, 2000); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
   }*/

   
   if (key == 'C'){
    pass = ""; 
   }

  if (digitalRead(button) == HIGH){
    Serial.println("ok input");
    if (openClose == false){
      openClose = true;
      tone(buzzer, 4000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      myservo.write(140);
      delay(500);
      myservo.write(127);
      delay(500);
    } else if(openClose == true){
      openClose = false;
      tone(buzzer, 4000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      myservo.write(30);
      delay(500);
      myservo.write(35);
      delay(500);
    }
  }


  //if password was right loc out
  if ((pass == password) && (key == 'D') && (key) && (!openClose)){
      //Serial.println("done");
      openClose = true;
      tone(buzzer, 4000); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      myservo.write(140);
      delay(500);
      myservo.write(125);
      pass = ""; 
      delay(2000);
    } else if ((key == 'B') && (openClose)){
      //Serial.println("how");
      openClose = false;
      pass = ""; 
      myservo.write(30);
      delay(500);
      myservo.write(35);
   }

   if ((pass != password) && (key == 'D') && (openClose != true)){
      tone(buzzer, 500); // Send 1KHz sound signal...
      delay(500);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    } else if ((key == 'D') && (openClose = true)){
      tone(buzzer, 2000); // Send 1KHz sound signal...
      delay(50);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(50);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    }
   
   if ((key != 'D') && (key != 'C') && (key != 'B') && (key)){
    pass += key;
   }

   /*if (key){
   Serial.print("Key ");
   Serial.print(key);
   Serial.println(" is pressed"); 
   Serial.println(pass); */ 
   


/*
 // if (done == true){
  for (pos = 30; pos <= 140; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  //}
  //done = false;
  
  for (pos = 140; pos >= 30; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  */
}
