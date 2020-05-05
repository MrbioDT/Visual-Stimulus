// this is the code Paul sent to me, annotated by Yang with notes and questions
// modified to delete auditory and include visual cues
// updated 2020.05.02

//Q. run the code and see how it works?
//Q. why functions are defined at bottom? running sequence?


//part1. define session //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <toneAC.h>   //Q. what is this? how auditory cues are played
#define encoder_a 2
#define encoder_b 3
#define water 4
#define air 5
#define touch 18
#define voice1 11
#define voice2 12
#define camera 41
#define opto 31

long encoder = 0;
long counter = 0;
char inputString;
boolean stringComplete = false;
boolean cueAON = false;
long pre_low = 0;
int grad = 0;
boolean cueBON = false;
long pre_high = 0;
int sound = 0;
boolean habAOn = false;
boolean habBOn = false;
boolean conAOn = false;
boolean conBOn = false;
boolean trialON = false;
long sounddur=10000;
long itidur=30000;
long soundvar=0;
long itivar=0;
long pretrial=30000;
long posttrial=30000;
long prea = 0;
long pret = 0;
long preh = 0;
long preS = 0;
boolean command = false;
int pair = 0;
boolean airOn = false;
int reward = 0;
volatile boolean sta = false;
int stage=1;
int vis = 51; // dt-tag, the pin used to trigger visual stimulus

//part2. define session //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(encoder_a, INPUT_PULLUP);
pinMode(encoder_b, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoder_a), encoderPinChangeA, CHANGE);
attachInterrupt(digitalPinToInterrupt(encoder_b), encoderPinChangeB, CHANGE);
pinMode(water, OUTPUT);
pinMode(air, OUTPUT);
pinMode(opto,OUTPUT);
pinMode(touch, INPUT);
attachInterrupt(digitalPinToInterrupt(touch), blin, CHANGE);
randomSeed(analogRead(0));
digitalWrite(opto,LOW);
digitalWrite(air,LOW);
pinMode(vis,OUTPUT); //dt-tag
digitalWrite(vis,LOW); //dt-tag
}

//part3. implementation  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

///////////////part3.1 updated the serial monitor
String statusreport = String(millis(),DEC) + ';' + String(encoder,DEC) + ';' + sta + ';'+ String(sound,DEC) + ';' +String(reward,DEC)+ ';' +String(trialON,DEC);
// millis() Returns the number of milliseconds passed since the Arduino board began running the current program
Serial.println(statusreport);  

///////////////part3.2 ??? lick for what???
//Lick = water
if (counter >= 8){
   reward = 1;
   digitalWrite(water,HIGH);
   counter = 0;
   pret = millis();  // millis() Returns the number of milliseconds passed since the Arduino board began running the current program
}
//Lick = water end 


///////////////part3.3 ??? what is this millis and prexxx session for???
if (millis()>pret + 10)
{
  digitalWrite(water,LOW);
  if (reward == 1){
    reward = 0;
  }
}

if (millis()>prea + 400)
{
  digitalWrite(air,LOW);
  if (reward == 2){
    reward = 0;
  }
}

if (millis()>prea + 2400)
{
  digitalWrite(opto,LOW);
  if (reward == 2){
    reward = 0;
  }
}


///////////////part3.4 serial input command!
//////////////////////////////////Serial input control////////////////////////////////////////
if (stringComplete){
    if (inputString == '1'){
      cueAON = !cueAON;       //tag. Q. cueAON later would effect????
      pre_low = millis();     //tag. Q. where would pre_low go?
      }
    else if (inputString == '2'){
      cueBON = !cueBON;
      pre_high = millis();
      }
    else if (inputString == '3'){
      digitalWrite(water,HIGH);
      reward = 1;
      pret = millis();
      }
    else if (inputString == '4'){
      digitalWrite(air,HIGH);
      digitalWrite(opto,HIGH);
      reward = 2;
      prea = millis();
      }
    else if (inputString == '5'){
      habAOn = !habAOn;
      preh = millis();
      }
    else if (inputString == '6'){
      habBOn = !habBOn;
      preh = millis();
      }
    else if (inputString == '7'){
      conAOn = !conAOn;
      preh = millis();
      }
    else if (inputString == '8'){
      conBOn = !conBOn;
      preh = millis();
      }
    else if (inputString == '9'){ //dt-tag, created by Yang
      digitalWrite(vis,HIGH);
      prea = millis(); //Q. what is this prea for???
      delay(1000);
      digitalWrite(vis,LOW);
      }
      
inputString = '0';
stringComplete = false;
}
//////////////////////////////////////End of Serial input control////////////////////////////

///////////////part3.5 auditory cues session
//Auditory cueB module
if (cueBON == true){
  sound = 2;
//delay(50);
  if (millis()>pre_high){
  toneAC(12000);
  }
  if (millis()>pre_high+250){
    noToneAC();
    pre_high=pre_high+500;
  }
}
if (cueBON == false){
  if(sound==2) {sound = 0; noToneAC();}
}
//cueB module end

//Auditory cueA module
if (cueAON == true){
  sound = 1;
//delay(50);
  if (grad==0){
    toneAC(4000);
      if (millis()>pre_low + 500){
        pre_low = millis();
        grad = 1;
      }
  }
  if (grad==1){
    toneAC(5000);
      if (millis()>pre_low + 500){
        pre_low = millis();
        grad = 2;
      }
  }
  if (grad==2){
    toneAC(6000);
      if (millis()>pre_low + 500){
        pre_low = millis();
        grad = 3;
      }
  }
  if (grad==3){
    toneAC(6500);
      if (millis()>pre_low + 500){
        pre_low = millis();
        grad = 0;
      }
  }  
}
if (cueAON == false){
  if(sound==1) {sound = 0; noToneAC();}
}
//cueA module end


///////////////part3.6 habituation session??? how does this work???
//habituation shcedule A, A*3, B*3, A*2, B*2, A*1, B*1
if (habAOn==true){
   trialON=true;

      if ((stage==1 or stage==2 or stage==3 or stage==7 or stage==8 or stage==11)&&(millis()>preh+pretrial)&&(!command)){
           cueAON=true;
           //soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_low=millis();
           preS=millis();
           command=true;
           }
      if ((stage==1 or stage==2 or stage==3 or stage==7 or stage==8 or stage==11)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueAON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
      if ((stage==4 or stage==5 or stage==6 or stage==9 or stage==10 or stage==12)&&(millis()>preh+pretrial)&&(!command)){
           cueBON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_high=millis();
           preS=millis();
           command=true;
           }       
       if ((stage==4 or stage==5 or stage==6 or stage==9 or stage==10 or stage==12)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueBON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
       if((stage==13)&&(millis()>preh+posttrial)){
           trialON=false;
           habAOn=false;
           }
}  
//END of habituation schedule A

//habituation shcedule B, B*3, A*3, B*2, A*2, B*1, A*1
if (habBOn==true){
   trialON=true;
      if ((stage==1 or stage==2 or stage==3 or stage==7 or stage==8 or stage==11)&& (millis()>preh+pretrial)&&(!command)){
           cueBON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_high=millis();
           preS=millis();
           command=true;
           }
      if ((stage==1 or stage==2 or stage==3 or stage==7 or stage==8 or stage==11)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueBON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
      if ((stage==4 or stage==5 or stage==6 or stage==9 or stage==10 or stage==12)&&(millis()>preh+pretrial)&&(!command)){
           cueAON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_low=millis();
           preS=millis();
           command=true;
           }       
       if ((stage==4 or stage==5 or stage==6 or stage==9 or stage==10 or stage==12)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueAON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
       if((stage==13)&&(millis()>preh+posttrial)){
           trialON=false;
           habBOn=false;
           }
}  
//END of habituation schedule B

///////////////part3.7 conditioning session??? how does this work???
//condition shcedule A, B*4, A*4, B*4, A*4, B*4, A*4
if (conAOn==true){
   trialON=true;
      if ((stage==1 or stage==2 or stage==3 or stage==4 or stage==9 or stage==10 or stage==11 or stage==12 or stage==17 or stage==18 or stage==19 or stage==20)&& (millis()>preh+pretrial)&&(!command)){
           cueBON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_high=millis();
           preS=millis();
           command=true;
           }
      if ((stage==1 or stage==2 or stage==3 or stage==4 or stage==9 or stage==10 or stage==11 or stage==12 or stage==17 or stage==18 or stage==19 or stage==20)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueBON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
      if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(millis()>preh+pretrial)&&(!command)){
           cueAON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_low=millis();
           preS=millis();
           command=true;                    
           }       
       if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(command)){
            if ((millis()>preS+sounddur+soundvar-1500)&&(pair==0)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=1;
            reward=2;
           }
           if ((millis()>preS+sounddur+soundvar-1000)&&(pair==1)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=2;
            reward=2;
           }
           if ((millis()>preS+sounddur+soundvar-500)&&(pair==2)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=0;
            reward=2;
           }
      }  
       if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueAON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
       if((stage==25)&&(millis()>preh+posttrial)){
           trialON=false;
           conAOn=false;
           }
}  
//END of condition schedule A

//condition shcedule B, A*4, B*4, A*4, B*4, A*4, B*4
if (conBOn==true){
   trialON=true;
      if ((stage==1 or stage==2 or stage==3 or stage==4 or stage==9 or stage==10 or stage==11 or stage==12 or stage==17 or stage==18 or stage==19 or stage==20)&& (millis()>preh+pretrial)&&(!command)){
           cueAON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_low=millis();
           preS=millis();
           command=true;
           }
      if ((stage==1 or stage==2 or stage==3 or stage==4 or stage==9 or stage==10 or stage==11 or stage==12 or stage==17 or stage==18 or stage==19 or stage==20)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueAON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
      if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(millis()>preh+pretrial)&&(!command)){
           cueBON=true;
           soundvar=random(-2000,2000);
           itivar=random(-10000,10000);
           pre_high=millis();
           preS=millis();
           command=true;                      
           }
      if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(command)){
            if ((millis()>preS+sounddur+soundvar-1500)&&(pair==0)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=1;
            reward=2;
           }
           if ((millis()>preS+sounddur+soundvar-1000)&&(pair==1)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=2;
            reward=2;
           }
           if ((millis()>preS+sounddur+soundvar-500)&&(pair==2)){
            digitalWrite(air,HIGH);
            digitalWrite(opto,HIGH);
            prea=millis();
            pair=0;
            reward=2;
           }
      }              
       if ((stage==5 or stage==6 or stage==7 or stage==8 or stage==13 or stage==14 or stage==15 or stage==16 or stage==21 or stage==22 or stage==23 or stage==24)&&(millis()>preS+sounddur+soundvar)&&(command)){
           cueBON=false;
           preh=preh+sounddur+itidur+soundvar+itivar;
           stage=stage+1;
           command=false;
           }
       if((stage==25)&&(millis()>preh+posttrial)){
           trialON=false;
           conBOn=false;
           }
}  
//END of condition schedule B

}
////////////void loop() function ends here/////////////////////


//part4. unknown defined functions here  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}

void blin(){
  sta = digitalRead(touch);
  counter++;
}

void serialEvent() {
//  while (Serial.available()) 
    // get the new byte:
    char inChar = Serial.read();
    // add it to the inputString:
    inputString = inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '1' || '2' || '3' || '4' ||'5'||'6'||'7'||'8'||'9'||'0') {
      stringComplete = true;
    }
  
}
