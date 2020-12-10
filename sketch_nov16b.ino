#include <PulseSensorPlayground.h>

    #define BLYNK_PRINT Serial   
    #include <SPI.h>
    #include <Ethernet.h>
    #include <BlynkSimpleEthernet.h>
    #include <SimpleTimer.h>
   #include <dht.h>
   #define USE_ARDUINO_INTERRUPTS true
   
   // #define dht_apin A1 // Analog Pin sensor is connected to
 
   
    
    // You should get Auth Token in the Blynk App.
    // Go to the Project Settings (nut icon).
    char auth[] = "db82b7e5d98b4006b07611a6d894ecb4";
    
  
     //temperature variable initialization
    float dht_temp;// variable for temperature value storage
    #define dht_apin A1 // Analog Pin sensor is connected to

    //humidity variable initialization
    float humi;
    #define dht_apin A1 // Analog Pin sensor is connected to



    // ECG variables
    int  heartValue;
    const int heartPin = A2;// ECG analog pin
    
   


    //Pulse sensor variables 
    int Signal;                // Signal value can range from 0-1024
    int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore. 
    int PulseSensorPurplePin = 0;
    int buzzer = 7;



    
    SimpleTimer timer;
     dht DHT;

    void setup()
    {
      Serial.begin(9600); // See the connection status in Serial Monitor
      Blynk.begin(auth);
    
      // Setup a function to be called every second
      timer.setInterval(1000L, sendUptime);

        //void interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
        //analogReference(EXTERNAL); 

      Serial.println("DHT11 temperature Sensor\n\n");
      delay(1000);//Wait before accessing Sensor
    }
    
    // that you define how often to send data to Blynk App.
    void sendUptime()
    {
     // shows the value temp on virtual pin 10
      Blynk.virtualWrite(5, DHT.temperature);
      Blynk.virtualWrite(6, Signal);
      Blynk.virtualWrite(8, DHT.humidity);
      Blynk.virtualWrite(10, heartValue);
     
      
    }
    
    void loop()
    {
      Blynk.run(); // Initiates Blynk
      timer.run(); // Initiates SimpleTimer

      
        DHT.read11(dht_apin);
        //temperature
        Serial.print("temperature = ");
        Serial.print(DHT.temperature);
        Serial.println("C  ");
        //humidity
        Serial.print("Current humidity = ");
        Serial.print(DHT.humidity);
        Serial.print("%  ");

        Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.
        Serial.print("*** Heart-Beat Happened *** ");  //ASCII Art Madness
        Serial.print("BPM: ");
        Serial.print(Signal);
        Serial.print("  ");
      
  


        
        
       //temp = analogRead(tempPin);
      // temp = temp * 0.48828125; 
       

    
      // ECG for heart value
      heartValue = analogRead(heartPin);
      Serial.println(heartValue);
      delay(5);
      // if(temp > 40)
       //{
       // tone(buzzer,1000);
      //  delay(1000);
       // noTone(buzzer);
      //  delay(1000);
      // }   
      // else
       //{
       // noTone(buzzer);
     //  }
       
      
    }
