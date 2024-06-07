#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#define LED 13

const char* ssid = "OSobaMask";
const char* password = "123406789";

WebServer server(80);

const int led = 13;

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML>
<html>
    <style>
        #btn-on, #btn-off {
            width: 100%;
            margin-bottom: 30px;
            height: 100px;
            background: yellowgreen;
            font-size: 32px;
        } 
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED control</title>
    <h1>LED Control App</h1>
    <button id="btn-on">On</button>
    <button id="btn-off">off</button>
    <script>
        console.log("hello");
        let btn = document.querySelector("#btn-on");
        btn.addEventListener("click", function() {
            fetch(`http://${window.location.hostname}/led`)
            .then((response) => {return response.json();})
            .then((data) => {console.log(data);});
        });
        let btn1 = document.querySelector("#btn-off");
        btn1.addEventListener("click", function() {
            fetch(`http://${window.location.hostname}/led1`)
            .then((response) => {return response.json();})
            .then((data) => {console.log(data);});
        });
    </script>
</html>
)rawliteral";


void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void ledControl() {
  digitalWrite(LED, HIGH);
  Serial.println("led on");
  server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void ledControl1() {
  digitalWrite(LED, LOW);
  Serial.println("led off");
  server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/led", ledControl);
  server.on("/led1", ledControl1);
  server.on("/aboba", HTTP_GET, [](){
    server.send_P(200, "text/html", index_html);
  });

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
