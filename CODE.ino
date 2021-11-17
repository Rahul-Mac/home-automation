#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <ESP8266WiFi.h>

const char* ssid = "abc";
const char* password = "abcdefabc";
WiFiServer server(80);
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
int white = 15;//D8
int green = 13;//D7
int orange = 12;//D6

void setup()
{
  pinMode(white, OUTPUT);
  digitalWrite(white, LOW);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  pinMode(orange, OUTPUT);
  digitalWrite(orange, LOW);
Wire.begin(D2, D1); 
lcd.begin();
lcd.backlight(); 
lcd.clear();
lcd.setCursor(0, 0); 
    lcd.print("WELCOME");delay(5000);
WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    lcd.setCursor(0, 0); 
    lcd.print("CONNECTING...");
    delay(500);
    }
    lcd.clear();
    
lcd.setCursor(0, 0); 
lcd.print("CONNECTED");
lcd.setCursor(0, 1); 
lcd.print(WiFi.localIP());
  server.begin();

}

void loop()

{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  while(!client.available())
  {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  if(request.indexOf("/LED=ONW") != -1)
  {
    digitalWrite(white, HIGH); 
  }
  if(request.indexOf("/LED=OFFW") != -1)
  {
    digitalWrite(white, LOW); 
  }
  if(request.indexOf("/LED=ONG") != -1)
  {
    digitalWrite(green, HIGH); 
  }
  if(request.indexOf("/LED=OFFG") != -1)
  {
    digitalWrite(green, LOW); 
  }
  if(request.indexOf("/LED=ONO") != -1)
  {
    digitalWrite(orange, HIGH); 
  }
  if(request.indexOf("/LED=OFFO") != -1)
  {
    digitalWrite(orange, LOW); 
  }
  if(request.indexOf("/LED=ONA") != -1)
  {
    digitalWrite(white, HIGH); 
    digitalWrite(green, HIGH); 
    digitalWrite(orange, HIGH); 
  }
  if(request.indexOf("/LED=OFFA") != -1)
  {
    digitalWrite(white, LOW);
    digitalWrite(green, LOW);
    digitalWrite(orange, LOW); 
  }

/*------------------HTML Page Creation---------------------*/

  client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<h1>HOME AUTOMATION SYSTEM</h1>");
  client.println("<h2>WHITE</h2>");
  client.println("<h3><a href=\"/LED=ONW\"\"><button>ON</button></a></h3>");
  client.println("<h3><a href=\"/LED=OFFW\"\"><button>OFF</button></a></h3><br />");
  client.println("<h2>GREEN</h2>");
  client.println("<h3><a href=\"/LED=ONG\"\"><button>ON</button></a></h3>");
  client.println("<h3><a href=\"/LED=OFFG\"\"><button>OFF</button></a></h3><br />");
  client.println("<h2>ORANGE</h2>");
  client.println("<h3><a href=\"/LED=ONO\"\"><button>ON</button></a></h3>");
  client.println("<h3><a href=\"/LED=OFFO\"\"><button>OFF</button></a></h3><br />");
  client.println("<h2>ALL</h2>");
  client.println("<h3><a href=\"/LED=ONA\"\"><button>ON</button></a></h3>");
  client.println("<h3><a href=\"/LED=OFFA\"\"><button>OFF</button></a></h3><br />");
  
  client.println("</html>");
}
