#include <AsyncTCP.h>
#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include <TFT_eSPI.h>
#include "drows.h"
#include "drowsiness_alert_system.h"
#include "teleg.h"
#include "streamurl.h"

TFT_eSPI   tft = TFT_eSPI();

const char* WIFI_SSID = "Cylo";
const char* WIFI_PASS = "cyliaaaaa";
int value = 0;

int incomingByte;
int i = 0;

 
WebServer server(80);

 
 
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(640, 480);
static auto hiRes = esp32cam::Resolution::find(1024, 768);
void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));
 
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}
 
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgMid()
{
  if (!esp32cam::Camera.changeResolution(midRes)) {
    Serial.println("SET-MID-RES FAIL");
  }
  serveJpg();
}
  //delay(200);
void drowsn()
{
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(10, 10, 219, 211, drows);
  delay(1000);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(10, 10, 220, 189, streamurl);
  }
void switching()
{
   tft.fillScreen(TFT_BLACK);
   tft.pushImage(10, 10, 220, 189, streamurl);
  }
 
void  setup(){
  // pinMode(4, OUTPUT);
   // digitalWrite(4, LOW);
  Serial.begin(115200);
  Serial.println();
  {
    using namespace esp32cam;
    
    Config cfg;
    cfg.setPins(pins::AiThinker);
    
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
 
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("  /cam-lo.jpg");
  Serial.println("  /cam-hi.jpg");
  Serial.println("  /cam-mid.jpg");
    Serial.println("  /streamurl");
 
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam-mid.jpg", handleJpgMid);
  server.on("/drowsn", drowsn);
  server.on("/switching", switching);
 
  server.begin();

  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(10, 10, 227, 189, drowsiness_alert_system);

  delay(2000);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(10, 10, 230, 190, teleg);
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(10, 10, 220, 189, streamurl);
  

}
void loop()
{
  server.handleClient();
   /*if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'A') {
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(10, 10, 227, 189, drowsiness_alert_system);
    }
    if (incomingByte == 'T') {
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(10, 10, 230, 190, teleg);
    }
    if (incomingByte == 'S') {
      tft.fillScreen(TFT_BLACK);
    tft.pushImage(10, 10, 220, 189, streamurl);
    }
    if (incomingByte == 'D') {
      tft.fillScreen(TFT_BLACK);
    tft.pushImage(10, 10, 219, 211, drows);
    }
    }
    //Serial.println(i);*/
  }
