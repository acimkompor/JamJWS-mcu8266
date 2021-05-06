/*
 * JADWAL WAKTU SHOLAT MENGGUNAKAN NODEMCU ESP8266, LED P10, RTC DS3231, BUZZER
 * FITUR :  JADWAL SHOLAT 5 WAKTU DAN TANBIH IMSAK, JAM BESAR, TANGGAL, SUHU, ALARAM ADZAN DAN TANBIH IMSAK,
 *          DAN HITUNG MUNDUR IQOMAH DAN UBAH WAKTU LEWAT WIFI DENGAN BROWSER.
 * 

Pin on  DMD P10     GPIO      NODEMCU               Pin on  DS3231      NODEMCU                   Pin on  Buzzer       NODEMCU
        2  A        GPIO16    D0                            SCL         D1 (GPIO 5)                       +            RX (GPIO 3)
        4  B        GPIO12    D6                            SDA         D2 (GPIO 4)                       -            GND
        8  CLK      GPIO14    D5                            VCC         3V
        10 SCK      GPIO0     D3                            GND         GND
        12 R        GPIO13    D7
        1  NOE      GPIO15    D8
        3  GND      GND       GND

Catatan : 
o Perlu Power Eksternal 5V ke LED P10.
o Saat Flashing (upload program) cabut sementara pin untuk buzzer.

Project Git
- https://github.com/busel7/Arduino

Eksternal Library
- HJS589(DMD3 porting for ESP8266 by Ahmad Herman) 
  < DMD3 by Azis Kurosaki 
  < DMD2(https://github.com/freetronics/DMD2) 
  < DMD (https://github.com/freetronics/DMD)
- PrayerTime : https://github.com/asmaklad/Arduino-Prayer-Times
- RTC DS3231 : https://github.com/Makuna/Rtc
- ArduinoJson V6 : https://github.com/bblanchon/ArduinoJson

Diskusi Grup Untuk1000Masjid : https://www.facebook.com/groups/761058907424496/

www.grobak.net - www.elektronmart.com

Updated : 24 September 2019
*/

#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);

//#include <HJS589.h>
#include <DMDESP.h>

#include <fonts/ElektronMart6x8.h>
#include <fonts/ElektronMart6x16.h>
#include <fonts/ElektronMart5x6.h>
#include <fonts/ElektronMartArabic6x16.h>
#include <fonts/ElektronMartArabic5x6.h>
#include <fonts/SystemFont5x7Ramping.h>
#include <fonts/angka6x13.h>
#include <fonts/arab6x13.h>
#include <fonts/AllahMuhammad.h>
#include <fonts/Mono5x7.h>

//PrayerTimes
#include <PrayerTimes.h>
double times[sizeof(TimeName)/sizeof(char*)];

// BUZZER
const int buzzer = 3; //Pin GP10 Buzzer - RX

int ihti = 2;

static uint16_t d;
String nama1 = {"Luruskan, Rapatkan Shaf dan Matikan HP"};

int durasimenit;
int durasidetik;


//----------------------------
// SETUP DMD HJS589

#define DISPLAYS_WIDE 2 
#define DISPLAYS_HIGH 1
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)



//----------------------------------------------------------------------
// HJS589 P10 FUNGSI TAMBAHAN UNTUK NODEMCU ESP8266

void ICACHE_RAM_ATTR refresh() { 
  
  Disp.refresh();
  timer0_write(ESP.getCycleCount() + 80000);  

}

void Disp_init() {
  
  Disp.start();
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(refresh);
  timer0_write(ESP.getCycleCount() + 80000);
  interrupts();
  Disp.clear();
  
}


//SETUP RTC
//year, month, date, hour, min, sec and week-day(Senin 0 sampai Ahad 6)
//DateTime dt(2018, 12, 20, 16, 30, 0, 3);
RtcDateTime now;
char weekDay[][7] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu", "Ahad"}; // array hari, dihitung mulai dari senin, hari senin angka nya =0,
char monthYear[][4] = { "DES", "JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGU", "SEP", "OKT", "NOV", "DES" };




//----------------------------------------------------------------------
// SETUP

void setup() {

  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(50);

  //RTC D3231

  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Serial.println(F("SDA data line held low"));
    }
  } else { // bus clear, re-enable Wire, now can start Wire Arduino master
    Wire.begin();
  }
  
  Rtc.Begin();

  if (!Rtc.GetIsRunning()) {
    
    Rtc.SetIsRunning(true);
    
  }
  
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 
  // Set Jam RTC
//    Rtc.SetDateTime(RtcDateTime(2021,4,3,11,7,0));
  Serial.println("Setup RTC selesai");
  

//  //DMD
//  Disp_init();
//  
//  Disp.setBrightness(40);

  // DMDESP Setup
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(20); // Tingkat kecerahan

  
}




//----------------------------------------------------------------------
// LOOP

uint8_t tmpinfo;
uint8_t tmpiqmh;

void loop() {
  Disp.loop(); // Jalankan Disp loop untuk refresh LED
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
    teksBerjalanKananKiri(nama1, 4, 75);
    break;
  } 
}


void tampilInfo() {
  switch(tmpinfo){
    case 0:
      tampilLogo();
      alarmSholat();
      break;

    case 1:
      JamBesar2(0);
      tampilJadwalSholat();
      alarmSholat();
      break;

    case 2:
      tampilTanggal();
      alarmSholat();
      break;

     case 3:
      TampilJamKecil();
      teksBerjalan();
      alarmSholat();
      break;
  }
}

void teksBerjalanKananKiri(String teks, uint8_t y, uint8_t kecepatan) {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(teks) + width;
  
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > kecepatan) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      Disp.drawRect(0,0, 64, 15, 0, 0); 
      delay(1000 * 60 * 3);
      tmpiqmh = 0;     
    }
    Disp.drawText(width - x, y, teks + " ");
  }
}

void hitungMundurIqomah(){
  static uint32_t pM;
  uint32_t cM = millis();
  char iqomah[7];

  Disp.setFont(SystemFont5x7Ramping);
  textCenter(0, "Iqomah");

  if(durasidetik == 60){
    durasidetik = 0;
  }

  if(durasidetik < 0){
    durasidetik = 59;
    durasimenit--;
  }
    
  if(cM - pM > 1000){
    pM = cM;
    durasidetik--;

    if(durasimenit == 0 && durasidetik == 0){
      Disp.clear();
      buzzerPanjang();
      durasidetik = 59;
      Disp.clear();
      tmpiqmh = 2;
    }
  }

  sprintf(iqomah, "%02d:%02d", durasimenit, durasidetik); 
  Disp.setFont(SystemFont5x7Ramping);
  textCenter(8, iqomah);
}

//----------------------------------------------------------------------
// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void alarmSholat() {
   RtcDateTime now = Rtc.GetDateTime();
   int Hari = now.DayOfWeek();
   int Hor = now.Hour();
   int Min = now.Minute();
   int Sec = now.Second();
   int durasiadzan = 3 * 60000;

   jadwalSholat();

   int hours, minutes, seconds;

   // Tanbih Imsak
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;

  if (minutes < 10) {
    
    minutes = 60 - minutes;
    hours --;
    
  } else {
    
    minutes = minutes - 10 ;
    
  }

  if (Hor == hours && Min == minutes) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "TANBIH");
    textCenter(8, "IMSAK");
    delay(durasiadzan);
    Disp.clear();

  }

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (Hor == hours && Min == minutes) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "SUBUH");
    delay(durasiadzan);
    durasimenit = 12;
    tmpiqmh = 1;
    Disp.clear();
    
  }


  // Dzuhur
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (Hor == hours && Min == minutes && Hari != 5) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "DZUHUR");
    delay(durasiadzan);   
    durasimenit = 7;
    tmpiqmh = 1;
    Disp.clear();

  } else if (Hor == hours && Min == minutes && Hari == 5) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "JUM'AT");
    delay(durasiadzan);

  }


  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (Hor == hours && Min == minutes) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "ASHAR");
    delay(durasiadzan);   
    durasimenit = 5;
    tmpiqmh = 1;
    Disp.clear();
    
  }

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (Hor == hours && Min == minutes) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "MAGHRIB");
    delay(durasiadzan);    
    durasimenit = 5;
    tmpiqmh = 1;
    Disp.clear();
    
  }

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (Hor == hours && Min == minutes) {
    
    buzzerPanjang();
    Disp.clear();
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "ISYA'");
    delay(durasiadzan);   
    durasimenit = 5;
    tmpiqmh = 1;
    Disp.clear();
    
  }
}

static String nama = ("Mushollah Al-Muddatsir Rt. 8");

void teksBerjalan() {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t kecepatan = 75;
  static uint8_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(nama) + width;
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > kecepatan) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      Disp.drawRect(0,0, 64, 15, 0, 0);
      tmpinfo = 0;
      delay(1000);
      
    }
    Disp.drawText(width - x, 8, nama + " ");
  }
 
}



void tampilLogo() {

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t kecepatan = 40;
  static uint8_t x, s;

   if (cM - pM > kecepatan) {
    if (s == 0 and x < 31) {
      pM = cM;
      x++;
    }
   
    if (s == 1 and x > 0) {
      pM = cM;
      x--;
    }  
  }

  if (cM - pM > 7000 and x == 31) { 
    s = 1;    
  }

  if (x == 0 and s == 1) {
    Disp.clear();
    s = 0;
    tmpinfo = 1;
  }

  int width = Disp.width();
  Disp.setFont(AllahMuhammad);
  Disp.drawText(width - x, 0, "!"); //Allah
  Disp.drawText(x - (width / 2), 0, "\""); //Muhammad
  
}


void jadwalSholat(){
   RtcDateTime now = Rtc.GetDateTime();
   int tahun = now.Year();
   int bulan = now.Month();
   int tanggal = now.Day();
   float latitude = -1.2603995106966508;
   float longitude = 116.89451868938446;
   int zonawaktu = 8;

   set_calc_method(Karachi);
   set_asr_method(Shafii);
   set_high_lats_adjust_method(AngleBased);
   set_fajr_angle(20);
   set_isha_angle(18);

   get_prayer_times(tahun, bulan, tanggal, latitude, longitude, zonawaktu, times);
}

void tampilJadwalSholat(){
  jadwalSholat();

  static uint8_t i;
  static uint32_t pM;
  uint32_t cM = millis();

  char sholat[7];
  char jam[5];
  char TimeName[][8] = {"SUBUH","TERBIT","DZUHUR","ASHAR","TRBNM","MAGRIB","ISYA"};
  int hours, minutes;

  if(cM - pM >= 5000) {
    pM = cM;
    Disp.drawRect(32,0, 64, 15, 0, 0);

    if(i == 1) {i = 2;} //Abaikan Terbit
    if(i == 4) {i = 5;} //Abaikan Terbenam

    get_float_time_parts(times[i], hours, minutes);
    minutes = minutes + ihti;

    if (minutes >= 60) {
      minutes = minutes - 60;
      hours ++;
    }

    String sholat = TimeName[i];
    sprintf(jam, "%02d:%02d", hours, minutes);
    
    Disp.setFont(SystemFont5x7Ramping);
    textCenter1PKanan(0, sholat);
    textCenter1PKanan(8, jam);

    i++;

    if (i > 7 ) {
      i = 0;
//      d = 1;
      Disp.drawRect(0,0, 64, 15, 0, 0);
      tmpinfo = 2;
    }
  }
  
}

void tampilTanggal() {
  
  static uint8_t flag;
  char hari[8];
  char tanggal[13]; //10 MAR 2021
  
  RtcDateTime now = Rtc.GetDateTime();

  static uint32_t pM;
  uint32_t cM = millis();
  if(cM - pM > 4000) {
    pM = cM;
    flag++;
    sprintf(hari, "%s", weekDay[now.DayOfWeek()]);
    sprintf(tanggal, "%02d %s %d", now.Day(), monthYear[now.Month()], now.Year());
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, hari);
    textCenter(8, tanggal);

    if(flag >= 2){
      flag = 0;
      Disp.drawRect(0,0, 64, 15, 0, 0);
      tmpinfo = 3;
    }
  }
//  tmpinfo = 0;
  
  
}

void JamBesar2(uint16_t x) {

  RtcDateTime now = Rtc.GetDateTime();

  char jam[3];
  char menit[3];

  sprintf(jam, "%02d", now.Hour());
  sprintf(menit, "%02d", now.Minute());

  static boolean huruf;

  static uint8_t y;
  static uint8_t d;           
  static uint32_t pM;
  static uint32_t pMBuz;
  static boolean dtk;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 1000) { 
    pMPulse = cM;
    dtk = !dtk;
    pulse++;
  }

  if (pulse > 8) {
    pulse=0;
  }

  if(cM - pM > 35) { 
    
    if(d == 0 and y < 20) {
      pM = cM;
      y++;
    }
    
    if(d  == 1 and y > 0) {
      pM = cM;      
      y--;
    }
  }

  if(cM - pM > 10000 and y == 20) {
    d=1;
  }

  if(y == 20) {
//    Disp.drawRect(x+14, 3+pulse, x+17, 11-pulse, 0, 1);  
    
      if(dtk) {
        Disp.drawRect(15, 4, 16, 10, 0, 0);
      } else {
        Disp.drawRect(15, 4, 16, 5, 1, 1);
        Disp.drawRect(15, 9, 16, 10, 1, 1);
      }   
  }

  if(y < 20) {
//    Disp.drawRect(x+14, 3, x+18, 17, 0, 0);
    Disp.drawRect(15, 4, 16, 10, 0, 0);
  }

  if(y == 0 and d == 1) {
    d=0;
    huruf = !huruf;
  }

  //JAM
  if (huruf) {
    Disp.setFont(angka6x13);
  } else {
    Disp.setFont(arab6x13);
  }  
  Disp.drawText(x+1, y - 20, jam);


  //MENIT
  if (huruf) {
    Disp.setFont(angka6x13);
  } else {
    Disp.setFont(arab6x13);
  }  
  Disp.drawText(x+18, y - 20, menit);  
}

void jamBesar(){
  RtcDateTime now = Rtc.GetDateTime();
  Disp.drawRect(0,0, 31, 15, 0, 0);
  char jam[3];
  char menit[3];
  static uint32_t pMBuz, pM;
  uint32_t cM = millis();
  static boolean dtk;

  sprintf(jam, "%02d", now.Hour());
  sprintf(menit, "%02d", now.Minute());
  
  Disp.setFont(angka6x13);
  Disp.drawText(1, 0, jam);
  Disp.drawText(18, 0, menit);
  

  if(cM - pMBuz >= 1000) {
    pMBuz = cM;
    dtk = !dtk;
  }

  if(dtk) {
    Disp.drawRect(15, 4, 16, 10, 0, 0);
  } else {
    Disp.drawRect(15, 4, 16, 5, 1, 1);
    Disp.drawRect(15, 9, 16, 10, 1, 1);
  }
}

void buzzerPanjang(){
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
}

void buzzerPendek(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
}

void bunyiBeep(){
  static uint32_t pMBuz;
  uint32_t cM = millis();
  static boolean beep;

  if(cM - pMBuz >= 1000) {
    pMBuz = cM;
    beep = !beep;
  }

  if(beep) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}


void TampilJamKecil() {

  static uint32_t pM;
  static uint32_t pMJam;
  uint32_t cM = millis();
  
  RtcDateTime now = Rtc.GetDateTime();
  char jam[9];
  
  if (cM - pMJam >= 1000) {
   
    pMJam = cM;
    
    //JAM
    sprintf(jam,"%02d:%02d:%02d", now.Hour(), now.Minute(), now.Second());
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, jam);
        
  }
 
}


void textCenter(int y,String Msg) {
  
  int center = int((Disp.width()-Disp.textWidth(Msg)) / 2);
  Disp.drawText(center,y,Msg);
  
}

void textCenter1PKanan(int y,String Msg) {
  
  int center = ((Disp.width()-Disp.textWidth(Msg)) / 2) + (Disp.width() / 4);
  Disp.drawText(center,y,Msg);
  
}


//----------------------------------------------------------------------
// I2C_ClearBus menghindari gagal baca RTC (nilai 00 atau 165)

int I2C_ClearBus() {
  
#if defined(TWCR) && defined(TWEN)
  TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
#endif

  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master. 
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok
}
