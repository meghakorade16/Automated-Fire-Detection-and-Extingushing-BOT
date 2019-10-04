const int   sensorMin = 0;    // sensor minimum
const int sensorMax = 1024;  // sensor maximum
const int trigPin = 12;
const int echoPin = 13;
int motora1=2;          
int motora2=3;          
int motorb1=4;          
int motorb2=5; 
int motorc1=6;          
int motorc2=7;          
int motord1=8;          
int motord2=9;      
int sortValues[5];
int flag=0;       
int ir1,ir2,ir3,ir4,ir5,ir6,range,range1,distance,mnir,starttime,endtime;
long duration;

void setup() {
pinMode(A0,INPUT);//flame sensors
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(trigPin, OUTPUT);//ultrasonic
pinMode(echoPin, INPUT); 
pinMode(motora1,OUTPUT);  //wheels
pinMode(motora2,OUTPUT);  
pinMode(motorb1,OUTPUT);  
pinMode(motorb2,OUTPUT);         
digitalWrite(motora1,HIGH);         
digitalWrite(motora2,HIGH);          
digitalWrite(motorb1,HIGH);         
digitalWrite(motorb2,HIGH);
pinMode(motorc1,OUTPUT);  //vertical motor and solenoid valve
pinMode(motorc2,OUTPUT);  
pinMode(motord1,OUTPUT);  
pinMode(motord2,OUTPUT);         
digitalWrite(motorc1,HIGH);         
digitalWrite(motorc2,HIGH);          
digitalWrite(motord1,HIGH);         
digitalWrite(motord2,HIGH);
 
pinMode(30,OUTPUT);
pinMode(32,OUTPUT);
pinMode(34,OUTPUT);
pinMode(40,OUTPUT);
pinMode(42,OUTPUT);
pinMode(44,OUTPUT);
pinMode(31,OUTPUT);
pinMode(33,OUTPUT);
pinMode(35,OUTPUT); 
pinMode(41,OUTPUT);
pinMode(43,OUTPUT);
pinMode(45,OUTPUT);
digitalWrite(30,HIGH);//IR sensors vcc    
digitalWrite(32,HIGH);   
digitalWrite(34,HIGH);   
digitalWrite(40,HIGH);    
digitalWrite(42,HIGH);   
digitalWrite(44,HIGH);   
digitalWrite(31,LOW); // IR sensors GND  
digitalWrite(33,LOW);   
digitalWrite(35,LOW);   
digitalWrite(41,LOW);   
digitalWrite(43,LOW);   
digitalWrite(45,LOW);

pinMode(26,OUTPUT);
pinMode(27,OUTPUT);
digitalWrite(26,LOW);   
digitalWrite(27,LOW);  
//pinMode(52,OUTPUT);
//digitalWrite(52,HIGH);   
pinMode(11,OUTPUT);
digitalWrite(11,HIGH); //ultasonic vcc  
Serial.begin(9600);

}
int findRange(int ir)
  {
    range = map(ir, sensorMin, sensorMax, 0, 4);
    return range;
  }
void rotate()
{
  digitalWrite(motora1,HIGH);
  digitalWrite(motora2,LOW);
  digitalWrite(motorb1,LOW);
  digitalWrite(motorb2,HIGH);
   
}
void forward()
{
    digitalWrite(motora1,HIGH);
    digitalWrite(motora2,LOW);
    digitalWrite(motorb1,HIGH);
    digitalWrite(motorb2,LOW);
    
}
void backward()
{
    digitalWrite(motora1,LOW);
    digitalWrite(motora2,HIGH);
    digitalWrite(motorb1,LOW);
    digitalWrite(motorb2,HIGH);    
}
void left()                             
  {
    digitalWrite(motora1,LOW);
      digitalWrite(motora2,HIGH);
      digitalWrite(motorb1,HIGH);
      digitalWrite(motorb2,LOW);
  }
void brake()
{
  digitalWrite(motora2,HIGH);
      digitalWrite(motora1,HIGH);
      digitalWrite(motorb1,HIGH);
      digitalWrite(motorb2,HIGH);
  }
  
void sort(int a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

void up()
{
    Serial.print("up");
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <=180000) // rotates shaft for 3 mins
    {
          digitalWrite(motorc1,HIGH);
          digitalWrite(motorc2,LOW);
          endtime = millis();      
    }
 }
 int readval()
{
    while ((endtime - starttime) <=12) // continuous check for upper sensor
      {     ir6=analogRead(A6);
            endtime = millis();     
      }
    return ir6;
 }
void down()
{   
    flag=1;
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <=160000) // rotates shaft for 2 mins
    {
          digitalWrite(motorc1,LOW);
          digitalWrite(motorc2,HIGH);
          endtime = millis();
          ir6=readval();
          //Serial.print(ir6);
          if(ir6<500)
          {
            spray();
            //Serial.print(ir6);
            Serial.print("Spray");
            break;
          }
    }
}
void spray()
{
  while ((endtime - starttime) <=1000) // spray for 1 sec
    {
          digitalWrite(motord1,HIGH);
          digitalWrite(motord2,LOW);
          endtime = millis();
          
    }
    digitalWrite(motord1,HIGH);
          digitalWrite(motord2,HIGH);
}
void loop()
{
  delay(1000);
  ir1=analogRead(A0);
  ir2=analogRead(A1);
  ir3=analogRead(A2);   
  ir4=analogRead(A3);
  ir5=analogRead(A4);
  sortValues[0]=ir1;
  sortValues[1]=ir2;
  sortValues[2]=ir3;
  sortValues[3]=ir4;
  sortValues[4]=ir5;

if((ir1<500)||(ir2<500)||(ir3<500)||(ir4<500)||(ir5<500))
{

  sort(sortValues,5);
  mnir=sortValues[0];
     if(ir1==mnir) 
        {
          Serial.println("TOP-LEFT"); 
          //range1=findRange(ir1);
          do{
            
            left();
             ir2=analogRead(A2);
            }while(ir2>500);
            brake();
        }
     else if(ir2==mnir) 
        {
          Serial.println("MIDDLE");
          //range1=findRange(ir2);
 //         forward();
          Serial.println(range1);
        }
     else if(ir3==mnir) 
        {
          Serial.println("TOP-RIGHT");
          //range1=findRange(ir3);
          do{
            rotate();
            ir2=analogRead(A2);
            }while(ir2>500);
          brake();
        }
        
      else if(ir4==mnir) 
        {
          Serial.println("BOTTOM-RIGHT");
          //range1=findRange(ir4);
          do{
            rotate();
            ir2=analogRead(A2);
            }while(ir2>500);
          brake();
        }
        
     else if(ir5==mnir) 
        {
          Serial.println("BOTTOM-LEFT");
          //range1=findRange(ir5);
          do{
            left();
            ir2=analogRead(A2);
            }while(ir2>500);
          brake();
        }
        
range1=findRange(ir2);
Serial.print("Rnage of focused sensor");
Serial.println(range1);

    switch (range1) 
      {
        case 0:    // 
           { 
             if(flag==0)
               {down();}
                delay(5000);
                ir5=analogRead(A5);
                if(ir5>500)
                 up();
                Serial.println("** Spray **");
             
           }
           break;
        case 1:    // 
          {
            Serial.println("** Close Fire **");
            do
            {
              digitalWrite(trigPin, LOW);
              delayMicroseconds(2);
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              
              duration = pulseIn(echoPin, HIGH);
              distance= duration*0.034/2;
              Serial.print("Distance: ");
              Serial.println(distance);
              
              if (distance < 15)/*if there's an obstacle 25 centimers, ahead, do the following: */ 
                {   
                  Serial.println ("Close Obstacle detected!" );
                  Serial.print ("Distance From Robot is " );
                  Serial.print ( distance);
                  Serial.print ( " CM!");
                  Serial.println (" Turning !");
                  backward();
                  rotate();
                  delay(15);
                }
              else 
                {
                  Serial.println ("No obstacle detected. going forward");
                  delay (15);
                  forward(); 
                }  
                delay(100);
              ir2=analogRead(A2);
              range1=findRange(ir2);
              }while(range1!=0);
              brake();        
          }
          break;
        case 2:
              {
                Serial.println("** Distant Fire **");
                
                do
                  {
                    digitalWrite(trigPin, LOW);
                    delayMicroseconds(2);
                    digitalWrite(trigPin, HIGH);
                    delayMicroseconds(10);
                    digitalWrite(trigPin, LOW);
                    
                    duration = pulseIn(echoPin, HIGH);
                    distance= duration*0.034/2;
                    Serial.print("Distance: ");
                    Serial.println(distance);
                   
                    if (distance <15)/*if there's an obstacle 25 centimers, ahead, do the following: */ 
                      {   
                        Serial.println ("Close Obstacle detected!" );
                        Serial.print ("Distance From Robot is " );
                        Serial.print ( distance);
                        Serial.print ( " CM!");
                        Serial.println (" Turning !");
                        backward();                
                        rotate();
                        delay(15);
                      }
                    else 
                      {
                       Serial.println ("No obstacle detected. going forward");                 
                       forward();
                       delay(15);
                      }  
                      delay(100);
                      ir2=analogRead(A2);
                      range1=findRange(ir2);                  
                    }while(range1!=0);
                  brake();
            
               }
               break;
        case 3:
               Serial.println("** No Fire **");
               break;  
         }
  }//eo if           
}
 
