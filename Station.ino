#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include<SoftwareSerial.h>

SoftwareSerial bluetooth(D7,D6); //RX,TX của ESP
String location = "";
MDNSResponder mdns;
ESP8266WebServer server(80);

#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
String webPage =
{
"  <!DOCTYPE html>"
"<html>"
"<head>"
"	 <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
"	<title>Mobile car</title>"
"	<meta name='viewport' content='width=device-width, initial-scale=1'>"
"	<style>"
"    button{"
"      padding: 15px 30px;"
"      border: none;"
"      font-size: 20px;"
"      background-color: rgb(43, 225, 116);"
"      color: #fff;"
"      border-radius: 15px;"
"      cursor: pointer;"
"    }"
"    h2{"
"      color: rgb(253, 53, 53);"
"      font-family: 'Courier New';"
"    }"
"   .dung{"
"      margin-top: 10px;"
"      background-color: rgb(213, 5, 5);"
"    }"
"	</style>"
"</head>"
"<body>"
"<div style='width: 330px;height: auto;margin: 0 auto;margin-top: 70px'>"
"<h2 align='center'>Điều khiển xe qua Wifi</h2>"
"<div align='center'>"
"  <a href='/tien'><button>Tiến</button></a>"
"</div>"
"<div style='display: flex; justify-content: center; margin: 10px 0;'>"
"  <a href='/trai'><button style='margin-right: 60px;'>Trái</button></a>"
"  <a href='/phai'><button>Phải</button></a>"
"</div>"
"<div align='center'>"
"  <a href='/lui'><button>Lùi</button></a>"
"</div>"
"<div align='center'><a href='/dung'><button class='dung'>Dừng</button></a></div>"
"</div>"
"<div align='center'><a href='/track'><button class='dung'>Track</button></a></div>"
"</div>"
"</body>"
"</html>"
};
void trangChu()
{
  server.send(200, "text/html", webPage);
}
void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.print("Connecting to ");
  WiFi.begin("Mac", "12345678");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP()))
  Serial.println("MDNS responder started");

  server.on("/", trangChu);
  server.on("/tien", tien);
  server.on("/trai", trai);
  server.on("/phai", phai);
  server.on("/lui", lui);
  server.on("/dung", stopp);
  server.on("/track", trackLocation);
  server.begin();
}
void tien(){
  analogWrite(ENA,200);
  analogWrite(ENB,200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("FORWARD");
  server.send(200, "text/html", webPage);
}
/******************************Lui******************************/
void lui(){
  analogWrite(ENA,200);
  analogWrite(ENB,200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("BACKWARD");
  server.send(200, "text/html", webPage);
}
/******************************Re trai******************************/
void trai(){
  analogWrite(ENA,200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("LEFT");
  server.send(200, "text/html", webPage);
}
/******************************Re phai******************************/
void phai(){
  analogWrite(ENB,200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("RIGHT");
  server.send(200, "text/html", webPage);
}
/******************************Dung******************************/
void stopp(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("STOP");
  server.send(200, "text/html", webPage);
}
void trackLocation(){
  while(true){
    if(bluetooth.available()){
      location = bluetooth.readString();
      Serial.println(location);
      break;
    }
  }
  String s = "<!DOCTYPE html>";
  s += "<html>";
  s += "<head>";
  s += "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
  s += "<title>Mobile car</title>";
  s += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  s += "<style>";
  s += "button{";
  s += "padding: 15px 30px;";
  s += "border: none;";
  s += "font-size: 20px;";
  s += "background-color: rgb(43, 225, 116);";
  s += "color: #fff;";
  s += "border-radius: 15px;";
  s += "cursor: pointer;";
  s += "}";
  s += "h2{";
  s += "color: rgb(253, 53, 53);";
  s += "font-family: 'Courier New';";
  s += "}";
  s += ".dung{";
  s += "margin-top: 10px;";
  s += "background-color: rgb(213, 5, 5); margin-bottom: 10px;";
  s += "}";
  s += ".location{font-size: 20px;}";
  s += "</style>";
  s += "</head>";
  s += "<body>";
  s += "<div style='width: 330px;height: auto;margin: 0 auto;margin-top: 70px'>";
  s += "<h2 align='center'>Điều khiển xe qua Wifi</h2>";
  s += "<div align='center'>";
  s += "<a href='/tien'><button>Tiến</button></a>";
  s += "</div>";
  s += "<div style='display: flex; justify-content: center; margin: 10px 0;'>";
  s += "<a href='/trai'><button style='margin-right: 60px;'>Trái</button></a>";
  s += "<a href='/phai'><button>Phải</button></a>";
  s += "</div>";
  s += "<div align='center'>";
  s += "<a href='/lui'><button>Lùi</button></a>";
  s += "</div>";
  s += "<div align='center'><a href='/dung'><button class='dung'>Dừng</button></a></div>";
  s += "<div align='center'><a href='/track'><button>Track</button></a></div></div>";
  s += "</div>";
  s += "<div align='center' id='location' class='location'>"+ location +"</div>";
  s += "<script>";
  s += "let vitri = document.getElementById('location').innerHTML;";
  s += "let arr = vitri.split(' ');";
  s += "vitri = arr[0] + ' ' + arr[1];";
  s += "document.getElementById('location').innerHTML = vitri;";
  s += "</script>";
  s += "</body>";
  s += "</html>";
  server.send(200, "text/html", s);
}
void loop()
{
  server.handleClient();
}