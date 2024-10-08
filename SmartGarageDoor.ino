#include <Ultrasonic.h> //Ultrasonic Simple - Prints the distance 
read by an ultrasonic sensor in centimeters
Ultrasonic ultrasonic(8,9); //Pass as a parameter the trigger and 
echo pin
int bolt = 2; //Reads the status of the pin connected to the 
bolt module
int enable = 3; //Enable pin of LM293D motor driver
int in1 = 4; //input pin 1 and 2 of LM293D motor driver
int in2 = 5;
int buz = 6; // connected to the buzzer
int old_state = 0; //variable to hold the previous state value of 
the pin connected to bolt. It is initialized to 0. Change in state 
indicates that the garage door is opened or closed.
int new_state; // variable to hold the new state value
int distance; // holds the distance between the vehicle and 
the garage wall
void setup()
{
 //set bolt pin as input, motor pins as output, buzzer pin as 
output
 pinMode(bolt,INPUT); 
 pinMode(enable, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(buz, OUTPUT);
 //start serial communication with a baud rate of 9600
 Serial.begin(9600);
 //keep the motor off initially
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
}
void loop()
{
 new_state = digitalRead(bolt); //read the new state value from 
the pin conncted to bolt wifi module
 if (new_state != old_state) //checking for change in state
 {
 if (new_state == 0) //new state value is 0 indicates 
that the garage door should be closed
 {
 digitalWrite(buz,LOW); //buzzer need not be ON when the 
garage is closed
 Serial.println("Closing Garage"); 
 analogWrite(enable,255); //rotate the motor in order to 
close the garage door
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 delay(4000);
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
 Serial.println("Garage Closed");
 }
 else if(new_state == 1)
 {
 Serial.println("Opening Garage");
 analogWrite(enable,255); //rotate the motor in opposite 
direction to open the garage door
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 delay(4000);
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
 Serial.println("Garage Opened");
 }
 }
 old_state = new_state; //assign new state value to old state 
for the next cycle of the loop
 if (new_state == 1) //checking if the garage door is open
 {
 //trigger the ultrasonic sensor if the garage door is open
 distance = ultrasonic.read();
 Serial.print("Distance in CM: ");
 Serial.println(distance);
 if (distance < 30) 
 {
 Serial.println("STOP!"); 
 digitalWrite(buz,HIGH); //if the distance between the 
vehicle and garage wall is less than 30cms turn ON the buzzer
 }
 else
 {
 digitalWrite(buz,LOW); 
 }
 
 }
 
 delay(5000); //repeat for every 5 seconds (5000ms)
}
