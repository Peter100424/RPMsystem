

#include <Ethernet.h>
// the sensor communicates using SPI, so include the library:
#include <SPI.h>


// assign a MAC address for the Ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// assign an IP address for the controller:
IPAddress ip(192, 168, 56, 20);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);


int ThermistorPin = 2;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  // put your setup code here, to run once:
  SPI.begin();

  Ethernet.begin(mac, ip);
  server.begin();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;

  // uncomment this to get temperature in farenhite
  Serial.print("TEMPRATURE = ");
  Serial.print(Tc);
  Serial.print("*C");
  Serial.println();
  delay(1000);

  // listen for incoming Ethernet connections:
  // listenForEthernetClients();
}

void listenForEthernetClients() {
  //val = analogRead(tempPin);
 // float mv = ( val / 1024.0) * 5000;
 // float cel = mv / 100;
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Got a client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          // print the current readings, in HTML format:
          client.print("Temperature: ");
          client.print(Tc);
          client.print(" degrees C");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

