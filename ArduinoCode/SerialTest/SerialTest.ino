void setup()  
 {  
  Serial.begin(9600); 
  pinMode(13,OUTPUT); 
 }  
 char c;
 void loop()  
 {  
  if(Serial.available()>0)  
  { 
     c = Serial.read();
     Serial.print(c);
  }  
 }  
