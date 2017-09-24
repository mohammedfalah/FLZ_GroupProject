#define dirPin 4
#define stepPin 3
#define rightbutton 5
#define leftbutton 8
#define StepDelay 25
#define ButtonDelay 400

const int MinSpeed=1;
const int MaxSpeed=100;
const int MinDelay=25;
const int MaxDelay=250;
const int BAUD_RATE = 9600;

char Command = 'X';
int Displacement = 0; //By Meter
int Steps = 0; 
int Tspeed ;
int DelayConstant = 25;


void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(rightbutton,INPUT_PULLUP);
  pinMode(leftbutton,INPUT_PULLUP);  
}

void loop() {
  if( digitalRead(rightbutton)==LOW ){
    delay(ButtonDelay);
    RightDirection() ;
  }else if (digitalRead(leftbutton)==LOW){
    delay(ButtonDelay);
    LeftDirection () ;
  }else {
    digitalWrite(stepPin, HIGH);
  }
  
  if(Serial.available() > 0){
    Command = Serial.read();
  
    if( Command == 'L'){
      Displacement = Serial.parseInt();
      Steps=Displacement/1.8;
      Serial.print("Displacement :");
      Serial.println(Displacement); 
      Serial.print("steps :");
      Serial.println(Steps);
          
      if (Steps>0){
        digitalWrite(dirPin,HIGH);
      }
      else if (Steps<0){
        digitalWrite(dirPin,LOW);
        Steps = abs(Steps);
      }
      for (int x=0 ; x<=Steps ; x++){
        digitalWrite(stepPin, LOW);
        delay(StepDelay);
        digitalWrite(stepPin, HIGH);
        delay(DelayConstant);
      }
    }
      else if( Command == 'V' ){
        Tspeed = Serial.parseInt();
        DelayConstant=map(Tspeed,MinSpeed,MaxSpeed,MaxDelay,MinDelay);
        Serial.print("speed ");
        Serial.println(Tspeed);
        Serial.print("Delay Constant ");
        Serial.println(DelayConstant);
      
    }
   Command = 'X';
  }
  
}
