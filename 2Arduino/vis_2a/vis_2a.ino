//updated 2020.05.04
//This code communicate with visual_grating_drifting_pin.py, gives 1/0 from arduino digitalPin and control the psychopy to generate visuasl stimulus accordingly


int inPin_h = 7;    // input from digital pin 7
int inPin_v = 23;
int val_h = 0;      // variable to store the read value
int val_v = 0;      // variable to store the read value


void setup() {
  pinMode(inPin_h, INPUT);    // sets the digital pin 7 as input
  pinMode(inPin_v, INPUT);
  Serial.begin(9600);
}

void loop() {
  val_h = digitalRead(inPin_h);   // read the input pin
  val_v = digitalRead(inPin_v);
//  Serial.print(val_h);
//  Serial.println(val_v);
  
  if(val_h == 1){
    Serial.println(inPin_h);
    val_h == 0;
    delay(1000);
    }
  else if(val_v == 1){
    Serial.println(inPin_v);
    val_v == 0;
    delay(1000);
    }
  
}
