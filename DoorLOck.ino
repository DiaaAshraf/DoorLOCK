//**************************************************************************//
//  Name          : Electronic Door Lock                               
//  Author        : Turyn                                 
//  Version       : 3.0                                             
//  Notes         : An electronic door lock using a matrix keypad and lcd
//                : display that controls an electric door strike                         
//**************************************************************************//

// Adding the necessary libraries to operate the keypad,lcd and Fingerprint sensor--//
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <SimpleTimer.h>
SimpleTimer timer;
//include definitions for The LED pins--------------------------------------//

//#define greenPin 5
//#define redPin 6


SoftwareSerial mySerial(2,3);      // pin #10 is IN from sensor (GREEN wire) and pin #9 is OUT from arduino (WHITE wire)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display


int user;
Servo myservo;
Servo myservo2;
int getFingerprintIDez();

#define Password_Lenght 7

char Data[Password_Lenght]; // بعرف مصفوفه عشان تشيل الباسورد بتاعي

char Master[Password_Lenght] = "154808"; // mosaad
char Master1[Password_Lenght] = "154768"; // ده khaled
char Master2[Password_Lenght] = "222222"; // gelany
char Master3[Password_Lenght] = "333333"; // sedik
char Master4[Password_Lenght] = "444444"; // bha2
char Master5[Password_Lenght] = "555555"; // haliem
char Master6[Password_Lenght] = "666666"; // esmaeel
char Master7[Password_Lenght] = "777777"; // amr hamza
char Master8[Password_Lenght] = "111111"; // Gen.DR.Mohammed



byte data_count = 0, master_count = 0; // ده عداد عشان يعمل مسح لكل عناصر المصفوفه بتاعتي ويقارنها ب الباسورد الي هيخش لي

bool Pass_is_good; // ده متغير يا اما صح يا اما غلط عشان يحدد ان الباسورد بتاعي صح

char customKey; // ده متغير بشيل فيه القرايه من الكيباد


const byte ROWS = 4; //عدد الصفوف في الكيباد

const byte COLS = 4; //عدد الاعمده في الكيباد

char keys[ROWS][COLS] = {

  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
//تعريف عناصر الكيباد


//تعريف عناصر الكيباد
byte rowPins[ROWS] = {
   4, 5, 6, 7 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  8, 9, 12,13 }; //connect to the column pinouts of the keypad
// هنا الارجل الي هتتوصل من الكيباد للاردوينو
/*
byte rowPins[ROWS] = {
  41,43,45,47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
 49,51,53}; //connect to the column pinouts of the keypad
// هنا الارجل الي هتتوصل من الكيباد للاردوينو
*/
//---------------------/
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad






                            //initialize variables
int getFingerprintIDez();
int cursorColumn = 0;       //this controls the cursor postition
int menu = 0;               //this controls the menu settings 
int n=0;                    // variable used to point to the bits in the keypad input array
int addr=0;
char pswrdElement=0;
char a='0';                 //variables a,b,c,d are all zero by default and store each digit of the 4 digit passcode
char b='0';
char c='0';
char d='0';

char password[]={5,5,5,5}; //initializing an array called password with variables a,b,c,d that hold the password digits
char input[4];             // an array that will contain the digits that are input




// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{

    lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
    lcd.clear();
lcd.print("welcomeToSector1");
  myservo.attach(10);
    myservo2.attach(11);
  myservo.write(0);
  myservo2.write(0);

  // set the data rate for the sensor serial port
  finger.begin(57600);

}

void loop()                     // run over and over again
{

  customKey = customKeypad.getKey(); //بقرا الباسورد من الكيباد

  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
   lcd.clear();

    lcd.setCursor(0,0);
 lcd.print( "WelcomeToSector1");         // Prints a message to the LCD.

    Data[data_count] = customKey; // store char into data array

    lcd.setCursor(data_count,1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  // هنا بعمل مسح للباسورد الي دخل من الكيباد وبقارنه ب الباسورد بتاعي
  }

  if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    //lcd.print("pass okey");

    if(!strcmp(Data, Master))
    {
    
    lcd.print("Hello mosaad");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
     else if(!strcmp(Data, Master1))
    {
    
    lcd.print("Hello khaled");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
     else if(!strcmp(Data, Master2))
    {
    
    lcd.print("Hello gelany");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
     else if(!strcmp(Data, Master3))
    {
    
    lcd.print("Hello sedik");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
      else if(!strcmp(Data, Master4))
    {
    
    lcd.print("Hello bha2");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
      else if(!strcmp(Data, Master5))
    {
    
    lcd.print("Hello halim");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
      else if(!strcmp(Data, Master6))
    {
    
    lcd.print("Hello esmaell");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    
    }
      else if(!strcmp(Data, Master7))
    {
    
    lcd.print("Hello amr");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
      else if(!strcmp(Data, Master8))
    {
    
    lcd.print("Gen.dr mohammed");
    myservo.write(180);
    delay(5000);
    myservo.write(0);
    }
 else
  {
                lcd.clear();
        lcd.setCursor(0,0);
      lcd.print("Denied");
      myservo2.write(180);
      delay(5000);
       
// في حاله الباسورد غلط بقوله دخولك غير مسموح بيه وبستني 3 ثواني وبعدين اديه فرصه يدخل باسورد تاني
  }
  lcd.clear();
    clearData();
    

// equal to (strcmp(Data, Master) == 0)

   //   lcd.print("Enter Finger");    
 // getFingerprintIDez();
    delay(50);

//في حاله ان الباسورد الي دخلته متطابق مع الباسورد المتخزن عندي بفتح الباب 5 ثواني وبقوله دخولك مسموح
    
   
}
}  
  

void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
// هنا بصفر الباسورد عشان اقرأ باسورد جديد وهكذا
}


void askForCode(){
  lcd.clear();
  lcd.print("Enter your code");  //prints when the user wants to enter the code
}
/*
void fingerCheck(){
  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Found sensor!");
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Did not find fingerprint sensor :(");
    while (1);
  }
  lcd.setCursor(0,1);
  lcd.print("Waiting..."); 
  return ;
}
*/

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) 
  {
  myservo2.write(180);
        lcd.clear();
        lcd.print("wrong finger");
  return -1;


  }  
  // found a match!
  lcd.clear();
    
  lcd.setCursor(0,1);
      if (finger.fingerID==1){
        
        lcd.print("Welcome diaa");
        myservo.write(180);
        delay(5000);
        myservo.write(0);

        }
          else if (finger.fingerID==2){
        lcd.print("Welcome mahmoud");
        myservo.write(180);
         delay(5000);
        myservo.write(0);
          }
          else if (finger.fingerID==3){
        lcd.print("Welcome mosaad");
        
        myservo.write(180);
         delay(5000);
        myservo.write(0);
          }
         
    

  delay(5000);
lcd.clear();
    clearData();
    
  return finger.fingerID; 
    

}

