// this program take serial command which specify the orientation and control the psychopy to generate visual grating
// updated 2020.04.27


//part1. initialize variables
char orientation = 'Z';     // this variable temporarily store the command from serial monitor
char command = 'Z';   // this variable stores the command from serial monitor


//part2. set up
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


//part3. execution
void loop() {
  // put your main code here, to run repeatedly:
 
 //part3.1 take the serial input
 if(Serial.available()>0){
    orientation = Serial.read();
     
    //part3.2 store the serial monitor input if it's a command
    //part3.2.1 take command A, 45degree
    if(orientation=='A'){
      command = orientation;
      // say what you got:
      Serial.println();
      Serial.println("now the updated command is: ");
      Serial.println(command);
      orientation = 'Z';
      } //if(orientation=='A'), part3.2.1 take command A, 45degree

    //part3.2.2 take command B, 135degree
    if(orientation=='B'){
      command = orientation;
      // say what you got:
      Serial.println();
      Serial.println("now the updated command is: ");
      Serial.println(command);
      orientation = 'Z';
      } //if(orientation=='B'), part3.2.2 take command B, 135degree
      
  } //if(Serial.available()>0), part3.1 take the serial input

 //part3.2 send the serial input to psychopy
 Serial.print(command);
 delay(2000);  // wait 2000ms before updating serial port again

}//Void loop
