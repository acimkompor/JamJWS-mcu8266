void textCenter(int y,String Msg) {
  
  int center = int((Disp.width()-Disp.textWidth(Msg)) / 2);
  Disp.drawText(center,y,Msg);
  
}

void textCenter1PKanan(int y,String Msg) {
  
  int center = ((Disp.width()-Disp.textWidth(Msg)) / 2) + (Disp.width() / 4);
  Disp.drawText(center,y,Msg);
  
}

//----------------------------------------------------------------------
// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void alarmSholat() {

   int hours, minutes, seconds;

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configJWS.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {

    tipealarm = 1;
    detikbeep = 0;
    tmpiqmh = 4;
    Disp.clear();
    
  }


  // Dzuhur
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + configJWS.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0 && rHar != 5) {
    
    tipealarm = 2;
    detikbeep = 0;
    tmpiqmh = 4;
    Disp.clear();

  } else if (rJam == hours && rMen == minutes && rDet == 0 && rHar == 5) {
    //Jika Hari Jumat tidak ada Iqomah
    tipealarm = 3;
    detikbeep = 0;
    tmpiqmh = 5;
    Disp.clear();

  }


  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + configJWS.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 4;
    detikbeep = 0;
    tmpiqmh = 4;
    Disp.clear();
    
  }

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + configJWS.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 5;
    detikbeep = 0;
    tmpiqmh = 4;
    Disp.clear();
    
  }

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + configJWS.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 6;
    detikbeep = 0;
    tmpiqmh = 4;
    Disp.clear();  
  }
}


//----------------------------------------------------------------------
// TAMPILAN ADZAN

void TampilAdzan() {

  BunyiBeep(2,6);
  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint16_t det;
  
  if (tipealarm == 1) {
  
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "SUBUH");
      
    durasimenit = configJWS.iqmhs;
    duralarm = 7;
  }
  
  if (tipealarm == 2) {
    
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "DZUHUR");
    
    durasimenit = configJWS.iqmhd;
    duralarm = 7;
  }
  
  if (tipealarm == 3) {
    
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "JUM'AT");
    
  }
  
  if (tipealarm == 4) {
  
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "ASHAR");
    
    durasimenit = configJWS.iqmha;
    duralarm = 7;
  }
  
  if (tipealarm == 5) {
  
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "MAGHRIB");
    
    durasimenit = configJWS.iqmhm; 
    duralarm = 7;
  } 
  
  if (tipealarm == 6) {
  
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, "ADZAN");
    textCenter(8, "ISYA");
    
    durasimenit = configJWS.iqmhi;
    duralarm = 7;  
  }  

  if (cM-pM >= 1000) {
    
    det++;   

    if (tipealarm == 0) {      
      
      if (det == 60) {
        Disp.clear();
        det = 0;
        detikbeep = 0;
        tmpiqmh = 0;
      }
      
    }

    
    if (tipealarm == 3) {
    
      if (det == configJWS.durasiadzan * 60) {
        Disp.clear();
        delay(configJWS.delayjumat * 1000);
        det = 0;
        detikbeep = 0;
        tmpiqmh = 0;
      }
      
    }
    
    
    if (tipealarm == 1 or tipealarm == 2 or tipealarm == 4 or tipealarm == 5 or tipealarm == 6) {
          
      if (det == configJWS.durasiadzan * 60) {
        Disp.clear();
        det = 0;
        detikbeep = 0;
        tmpiqmh = 1;
      }
      
    }
    
    pM = cM;
    
  }  
  
}

//----------------------------------------------------------------------
// TAMPILAN SAAT SHOLAT

void TampilSaatSholat() {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t durasi = 240; // Detik
  static uint32_t det;

  Disp.clear();

  if (cM - pM >= 1000) {
    pM = cM;
    det++;

    if (durasi == det) {
      Disp.clear();
      detikbeep = 0;
      det = 0;
      tmpinfo = 0;
      tmpiqmh = 0;
    }
  }  
  
}


void teksBerjalan() {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(configJWS.namamasjid) + width;
  Disp.setFont(ElektronMart6x8);
  textCenter(0,"#");
  Disp.drawRect(0,6,Disp.width(),6,1,1);
  
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > 75) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      Disp.drawRect(0,0, 64, 15, 0, 0);
      tmpinfo = 0;
      
    }
    Disp.drawText(width - x, 8, configJWS.namamasjid);
  }
 
}


void hitungMundurIqomah(){
  static uint32_t pM;
  uint32_t cM = millis();
  static boolean beep;
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

    if(durasimenit == 0 && durasidetik == duralarm){   
      beep = !beep;
      duralarm--;
      if (beep) {
        digitalWrite(buzzer, HIGH);
      } else {
        digitalWrite(buzzer, LOW);
      }
      if(durasidetik == 0){
        digitalWrite(buzzer, LOW);
        Disp.clear();
        durasidetik = 59;
        tmpiqmh = 2;
      }
    }
  }

  sprintf(iqomah, "%02d:%02d", durasimenit, durasidetik); 
  Disp.setFont(SystemFont5x7Ramping);
  textCenter(8, iqomah);
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

void tampilJadwalSholat(){

  static uint8_t i;
  static uint32_t pM;
  uint32_t cM = millis();

  char sholat[7];
  char jam[5];
  char TimeName[][8] = {"Subuh","Terbit","Dzuhur","Ashar","TRBNM","Magrib","Isya"};
  int hours, minutes;

  if(cM - pM >= 5000) {
    pM = cM;
    Disp.drawRect(32,0, 64, 15, 0, 0);

    if(i == 1) {i = 2;} //Abaikan Terbit
    if(i == 4) {i = 5;} //Abaikan Terbenam

    get_float_time_parts(times[i], hours, minutes);
    minutes = minutes + configJWS.ihti;

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


void tampilTanggalMasehi() {

//  char hari[8];
  char tanggal[28]; // 19 Desember 2021

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t x;

//  sprintf(hari, "%s", namaHari[rHar]);
  sprintf(tanggal, "%s, %02d %s %d", namaHari[rHar], rTgl, namaBulan[rBul], rTah);
  
  int width = Disp.width();
  int fullScroll = Disp.textWidth(tanggal) + width;
  
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > 75) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      Disp.drawRect(0, 0, 64, 15, 0, 0);  
      tmpinfo = 4;
      }    
    }
    Disp.drawText(width - x, 8, tanggal);
}

//----------------------------------------------------------------------
//TAMPILKAN TANGGAL HIJRIAH

void tampilTanggalHijriah() {

  char hari[8];
  char tanggal[36]; // 19 Romadhan 1442 H

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t x;

//  sprintf(hari, "%s", hariHijriah[rHar]);
  sprintf(tanggal, "%s, %d %s %d H", hariHijriah[rHar], Hjr_Date, (char*)&strNamaBulanHijriah[Hjr_Month -1], Hjr_Year);
//  sprintf(tanggal, "%s, %d %s %d H", hariHijriah[rHar], Hjr_Date, bulanHijriah[Hjr_Month], Hjr_Year);
  int width = Disp.width();
  int fullScroll = Disp.textWidth(tanggal) + width;
  
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > 75) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      Disp.drawRect(0, 8, 64, 15, 0, 0); 
      tmpinfo = 3;
      }    
    }
    Disp.drawText(width - x, 8, tanggal);

}

void JamBesar2(uint16_t x) {

  char jam[3];
  char menit[3];

  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

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

void JamBesarCenter(uint16_t x, int durasi) {

  char jam[3];
  char menit[3];

  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

  static boolean huruf;

  static uint8_t y;
  static uint8_t d;           
  static uint32_t pM;
  static uint32_t pMBuz;
  static boolean dtk;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t flag;

  if (cM - pMPulse >= 1000) { 
    pMPulse = cM;
    dtk = !dtk;
    flag++;
  }

  if(flag >= durasi){
    flag = 0;
    Disp.clear();
    tmpiqmh = 0;
    tmpinfo = 0;
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

  if(cM - pM > 15000 and y == 20) {
    d=1;
  }

  if(y == 20) {  
    
      if(dtk) {
        Disp.drawRect(15+x, 4, 16+x, 10, 0, 0);
      } else {
        Disp.drawRect(15+x, 4, 16+x, 5, 1, 1);
        Disp.drawRect(15+x, 9, 16+x, 10, 1, 1);
      }   
  }

  if(y < 20) {
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


void TampilJamKecil() {

  static uint32_t pM;
  static uint32_t pMJam;
  uint32_t cM = millis();
  
  char jam[9];
  
  if (cM - pMJam >= 1000) {
   
    pMJam = cM;
    
    //JAM
    sprintf(jam,"%02d:%02d:%02d", rJam, rMen, rDet);
    Disp.setFont(SystemFont5x7Ramping);
    textCenter(0, jam);     
  }
}

void teksBerjalanKananKiri(String teks, uint8_t y, uint8_t kecepatan) {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t x;
  static uint8_t flag;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(teks) + width;
  
  Disp.setFont(SystemFont5x7Ramping);
  if(cM - pM > kecepatan) {
    pM = cM;
    if(x < fullScroll) {
      ++x;   
    } else {
      x = 0;
      flag++;
      if (flag >= 2) {
        Disp.drawRect(0,0, 64, 15, 0, 0); 
//        delay(1000 * 60 * 3);
        flag = 0;
        tmpiqmh = 5;
      }    
      Serial.println(flag);
    }
    Disp.drawText(width - x, y, teks + " ");
  }
}
