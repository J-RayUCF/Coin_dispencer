#include <Keypad.h>
#include <Servo.h>
#define QUARTER_VAL 25
#define DIME_VAL 10
#define NICKLE_VAL 5
#define PENNY_VAL 1


//create turn functions and number of coin for turn function
//void counterTurn();//counter clockwisse turn of servo with return to original porition
//void clockTurn();//clockwise turn of servo with return to original porition
//int calcNumCoins(int, int, void *f());//calculates the number of coins of each kind and calls servo

//define row and colm in matrix keypad
const byte ROWS = 4;
const byte COLMS = 4;
char keys[ROWS][COLMS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9};//initialize what pins each row is set too
byte colmPins[COLMS] = {8, 7, 6, 5};//initialize what pin each colum is set too

//create servo object
Servo myservo1;
Servo myservo2;
int pos = 0;
 
//create a keypad from the setup above for the arduino to recognize
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colmPins, ROWS, COLMS);

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  myservo1.attach(3);
  myservo2.attach(13);
}

// put your main code here, to run repeatedly:
void loop() {//variables with a one behinf them are for the ones place of the total number (example: 10, 1 in the tens place, 0 in the ones place)
  char key, key1;
  int flag = 1;
  int superFlag = 1;
  int total, KeY, KeY1;

  while(flag != 0){
    key = keypad.getKey();
    if (key){//if you do not have this the code will not wait for a press
      if (key != '*') {
        KeY = key - 48; // converts character too correct integer
        Serial.print(KeY);//prints integer value

        //Used soley for debugging (next 3 lines)
        //Serial.println(key);
        //Serial.println("key");//seeing which kaypad i am checking
        //counterTurn();//run of the servo function
        
        flag = 0;
     }
    }
 }

  while(superFlag != 0){
    key1 = keypad.getKey();
    if(key1){//if you do not have this the code will not wait for a press
      if (key1!= '*') {
        KeY1 = key1 - 48;// converts character too correct integer
        Serial.println(KeY1);//prints integer value

        //Used soley for debugging (next 3 lines)
        //Serial.println(key);
        //Serial.println("key1");//seeing which kaypad i am checking
        //clockTurn(); //run of the servo function
        
        superFlag = 0;
      }
    }
  }
  total = (10 * KeY) + KeY1;//stitches the values together(KeY is in tens place KeY1 is in ones place)
  
  total = calcNumCoins (QUARTER_VAL, total, clockTurn1);//calculate new total minus quarters and turn the correct servor the correct way
    
  total = calcNumCoins (DIME_VAL, total, counterTurn1);//calculate new total minus quarters and dimes and turn the correct servor the correct way
   
  total = calcNumCoins (NICKLE_VAL, total, clockTurn2);//calculate new total minus quarters,dimes, and nickles and turn the correct servor the correct way 
   
  total = calcNumCoins (PENNY_VAL, total, counterTurn2);//calculate new total minus all the coins which should always be 0
}
void counterTurn1(){
    myservo1.write(-270);
    delay(150);

    myservo1.write(90);
    delay(150);
  
}
void clockTurn1(){
    myservo1.write(270);
    delay(150);

    myservo1.write(90);
    delay(150);
  
}
void clockTurn2(){
    myservo2.write(270);
    delay(150);

    myservo2.write(90);
    delay(150);
 
}
void counterTurn2(){
    myservo2.write(-270);
    delay(150);

    myservo2.write(90);
    delay(150);
  }
int calcNumCoins (int coin_Val, int total, void *servoTurn()){
    if (total / coin_Val >= 1 ){
    int coin;
    coin = total / coin_Val;
    Serial.println(coin, DEC);
    for (int i = 1; i <= coin; i++){
      servoTurn(); //run of the servo function
     }
     total = total - (coin * coin_Val);
      //Serial.println(total, DEC);//Used so I can check the math of total
      return(total);
    }
  }
