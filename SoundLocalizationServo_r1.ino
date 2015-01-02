//ECE4572 - Microcomputer-based Control Systems
//


#include <Servo.h>

Servo myservo;

int leftPin = A1;    
int rightPin = A0;
int leftSensor = 0;
int rightSensor = 0;

int offset_right = 61;
int offset_left = 58;

int sample_size =2;

void setup() {
  
  analogReference(EXTERNAL);
  //Serial.begin(115200);
  myservo.attach(9);
}

void loop() {
 
  leftSensor = 0;
  rightSensor = 0;

  sample_sensors();
  
  int difference = leftSensor - rightSensor;
  
  if(abs(difference) >50)
  {
    //Sped of motor is controlled by the difference
    //between sensors
    myservo.write(map(difference, -512, 512, 0, 180));
  }
  else{
    myservo.write(90);
  }

/*Uncomment for debug
if(abs(difference) > 0)
  {   
    Serial.print(leftSensor, DEC);
    Serial.print(",");
    Serial.println(rightSensor, DEC);
  }
*/            
}

void sample_sensors()
{
    for(int i = 0; i < sample_size; i++)
  {
  leftSensor =+ (analogRead(leftPin) - offset_left);    
  rightSensor =+ (analogRead(rightPin) - offset_right);
  }
  leftSensor = leftSensor/sample_size;
  rightSensor = rightSensor/sample_size;
}
