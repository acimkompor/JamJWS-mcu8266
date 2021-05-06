
#include <DMDESP.h>

#include <fonts/ElektronMart6x8.h>
#include <fonts/ElektronMart6x16.h>
#include <fonts/ElektronMart5x6.h>
#include <fonts/ElektronMartArabic6x16.h>
#include <fonts/ElektronMartArabic5x6.h>
#include <fonts/Mono5x7.h>
#include <fonts/angka6x13.h>




//SETUP DMDESP
//--------------------------------------------------

#define DISPLAY_WIDE 2
#define DISPLAY_HIGH 1
DMDESP Disp(DISPLAY_WIDE, DISPLAY_HIGH); // Jumlah panel P10 yang digunakan


void setup() {
  Serial.begin(9600);

  //DMD
  Disp.start();
  Disp.setBrightness(40);

}

void loop() {
  Disp.loop();
  Disp.setFont(Mono5x7);
  Disp.drawText(1,0, "HASYIM");
  Disp.drawText(1,8, "Arkana");
  delay(1000);
  Disp.clear();
  Disp.setFont(angka6x13);
  Disp.drawText(1,0, "12-35:47");
  delay(2000);
  Disp.clear();

}
