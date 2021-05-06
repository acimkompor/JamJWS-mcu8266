
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <F1kM_Hisab.h>

#include <DMDESP.h>

#include <fonts/ElektronMart6x8.h>
#include <fonts/ElektronMartArabic5x6.h>
#include <fonts/SystemFont5x7Ramping.h>
#include <fonts/angka6x13.h>
#include <fonts/arab6x13.h>
#include <fonts/AllahMuhammad.h>
#include <fonts/Mono5x7.h>

// LED Internal
uint8_t pin_led = 2;

//PrayerTimes
#include <PrayerTimes.h>
#include "RTC.h"
#include "FSConfig.h"
#include "WebServer.h"
#include "WebPage.h"
#include "Display.h"
#include "Buzzer.h"
#include "JWS.h"


//----------------------------------------------------------------------
// SETUP

void setup() {

  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(50);

  //RTC
  mulaiRTC();

  //FILE SYSTEM
  LittleFS.begin();
  loadJwsConfig(fileConfigJws, configJWS);
  

  //WIFI

  pinMode(pin_led, OUTPUT);

  wifiConnect();

  server.on("/", []() {
    server.send_P(200, "text/html", setwaktu);

    // Kalau ada perubahan tanggal
    if (server.hasArg("date")) {
    
      uint16_t jam;
      uint8_t menit;
      uint8_t detik;      
      String sd=server.arg("date");
      String lastSd;
      
      jam = ((sd[0]-'0')*1000)+((sd[1]-'0')*100)+((sd[2]-'0')*10)+(sd[3]-'0');
      menit = ((sd[5]-'0')*10)+(sd[6]-'0');
      detik = ((sd[8]-'0')*10)+(sd[9]-'0');
      
      if (sd != lastSd){
        RtcDateTime now = Rtc.GetDateTime();
        uint8_t hour = now.Hour();
        uint8_t minute = now.Minute();
        Rtc.SetDateTime(RtcDateTime(jam, menit, detik, hour, minute, 0));
        lastSd=sd;
      }
      BacaRTC();
      server.send ( 404 ,"text", message );
    
    }

    // Kalau ada perubahaan jam
    if (server.hasArg("time")) {
      
      String st=server.arg("time");
      String lastSt;
      uint8_t jam = ((st[0]-'0')*10)+(st[1]-'0');
      uint8_t menit = ((st[3]-'0')*10)+(st[4]-'0');
      
      if (st != lastSt){
         RtcDateTime now = Rtc.GetDateTime();
         uint16_t year = now.Year();
         uint8_t month = now.Month();
         uint8_t day = now.Day();
         Rtc.SetDateTime(RtcDateTime(year, month, day, jam, menit, 0));
         lastSt=st;
      }
      BacaRTC();
      server.send ( 404 ,"text", message );
  
    }
  });

  server.on("/simpandatajws", HTTP_POST, handleSettingJwsUpdate);

  server.on("/xmlwaktu", handleXMLWaktu); // http://192.168.4.1/xmlwaktu
  server.on("/xmldatajws", handleXMLDataJWS); // http://192.168.4.1/xmldatajws

  httpUpdater.setup(&server);
  server.begin();
  Serial.println("HTTP server started");  

  // Tampilkan Parameter yang tersimpan
  bacaParameter();
  
  //DMD
  Disp.start();
  Disp.setBrightness(configJWS.kecerahan);

  updateWaktu();
}


//----------------------------------------------------------------------
// LOOP
void loop() {
  server.handleClient();
  
//  hitungMundurIqomah();
  switch(tmpiqmh) {
    case 0:
      tampilInfo();
      break;

    case 1:
      hitungMundurIqomah();
      break;

    case 2:
      Disp.clear(); 
      delay(100);  
      tmpiqmh = 3;
      break;

    case 3:
      teksBerjalanKananKiri(configJWS.textstliqomah, 4, 75);
      break;

    case 4 :
      TampilAdzan();
      break;

    case 5 :
      JamBesarCenter(16, 240);
      break;
  } 

  Disp.loop();
  updateWaktu();
  alarmSholat();
}


void tampilInfo() {
  switch(tmpinfo){
    case 0:
      tampilLogo();
      break;

    case 1:
      JamBesar2(0);
      tampilJadwalSholat();
      break;

    case 2:
      TampilJamKecil();
      tampilTanggalHijriah();
      break;

    case 3:
      TampilJamKecil();
      tampilTanggalMasehi(); 
      break;

     case 4:
      teksBerjalan();    
      break;
  }
}
