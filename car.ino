//L298N Bağlantısı   
  const int motorA1  = 3;  // L298N'in IN3 Girişi
  const int motorA2  = 6;  // L298N'in IN1 Girişi
  const int motorB1  = 5; // L298N'in IN2 Girişi
  const int motorB2  = 2;  // L298N'in IN4 Girişi
  int state;               // Bluetooth cihazından gelecek sinyalin değişkeni
  int vSpeed=255;          // Standart Hız, 0-255 arası bir değer alabilir

void setup() {             // Pinlerimizi belirleyelim
                           
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);    
   
    Serial.begin(9600);    // 9600 baud hızında bir seri port açalım
}
 
void loop() {              //Gelen veriyi 'state' değişkenine kaydet
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
     
  //Gelen veri 'W' ise araba ileri gider.
    if (state == 'W') {
      analogWrite(motorA1, vSpeed); 
      analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);      
        analogWrite(motorB2, 0); 
    }
  
  //Gelen veri 'Q' ise araba ileri sol(çapraz) gider.
    else if (state == 'Q') {
     
      analogWrite(motorA1,vSpeed ); 
      analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);    
        analogWrite(motorB2, 0); 
    }

  //Gelen veri 'E' ise araba ileri sağ(çapraz) gider.
    else if (state == 'E') {
        analogWrite(motorA1, 100); 
        analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);      
        analogWrite(motorB2, 0); 
    }

  //Gelen veri 'X' ise araba geri gider.
    else if (state == 'X') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   
        analogWrite(motorB2, vSpeed); 
    }
  
  //Gelen veri 'Z' ise araba geri sol(çapraz) gider
    else if (state == 'Z') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); 
        analogWrite(motorB2, vSpeed); 
    }

  //Gelen veri 'C' ise araba geri sağ(çapraz) gider
    else if (state == 'C') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   
        analogWrite(motorB2, 100); 
    }

  //Gelen veri 'A' ise araba sola gider.
    else if (state == 'A') {
      analogWrite(motorA1, vSpeed);   
      analogWrite(motorA2, 150); 
        analogWrite(motorB1, 0); 
        analogWrite(motorB2, 0); 
    }
 
  //Gelen veri 'D' ise araba sağa gider
    else if (state == 'D') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);   
        analogWrite(motorB2, 150);     
    }
  

  //Gelen veri 'S' ise arabayı durdur.
    else if (state == 'S'){
        analogWrite(motorA1, 0);  
        analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  
        analogWrite(motorB2, 0);
    }  
}
