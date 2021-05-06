int durasimenit;
int durasidetik;
uint8_t tmpinfo;
uint8_t tmpiqmh;
uint8_t tipealarm;
int duralarm;

struct ConfigJWS {
  uint8_t iqmhs; // menit
  uint8_t iqmhd; // menit
  uint8_t iqmha; // menit
  uint8_t iqmhm; // menit
  uint8_t iqmhi; // menit

  int kecerahan; // default 30
  uint8_t durasiadzan; //Menit
  uint8_t delayjumat; //Menit
  uint8_t ihti; //koreksi Waktu jam sholat
  float latitude;
  float longitude;
  int8_t zonawaktu;
  uint8_t hilal;
  char textstliqomah[512];
  char namamasjid[512];
};

const char *fileConfigJws = "/configjws.json";
ConfigJWS configJWS; 

String message, XML;

// -------------------------------------------
// Membuat file config JWS JSON di File Sistem

void membuatDataAwal() {

  String dataawal = "{\"iqmhs\":\"12\",\"iqmhd\":\"8\",\"iqmha\":\"6\",\"iqmhm\":\"5\",\"iqmhi\":\"5\",\"durasiadzan\":\"3\",\"ihti\":\"2\",\"latitude\":\"-1.2603995106966508\",\"longitude\":\"116.89451868938446\",\"zonawaktu\":\"8\",\"hilal\":\"0\",\"namamasjid\":\"Mushollah Al-Muddatsir Rt. 8\",\"textstliqomah\":\"Matikan HP, Luruskan dan Rapatkan Shaf\",\"kecerahan\":\"30\",\"delayjumat\":\"30\"}";
//    String dataawal = "{\"iqmhs\":\"12\",\"iqmhd\":\"8\",\"iqmha\":\"6\",\"iqmhm\":\"5\",\"iqmhi\":\"5\",\"durasiadzan\":\"4\",\"ihti\":\"2\",\"latitude\":\"-6.16\",\"longitude\":\"106.61\",\"zonawaktu\":\"7\",\"hilal\":\"0\",\"namamasjid\":\"UNTUK 1000 MASJID - ELEKTRONMART.COM - 2020\"}";

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, dataawal);

  File configFileJws = LittleFS.open(fileConfigJws, "w");
  
  if (!configFileJws) {
    Serial.println("Gagal membuat file configjws.json untuk ditulis mungkin partisi belum dibuat");
    return;
  }
  
  serializeJson(doc, configFileJws);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileJws.close();
    Serial.println("Berhasil membuat file configjws.json");
  
  }  

}

// -------------------------------------------
// Membaca file config JWS JSON di File Sistem

void loadJwsConfig(const char *fileconfigjws, ConfigJWS &configjws) {  

  File configFileJws = LittleFS.open(fileconfigjws, "r");

  if (!configFileJws) {
    
    Serial.println("Gagal membuka file configjws.json untuk dibaca");
    membuatDataAwal();
    Serial.println("Sistem restart...");
    ESP.restart();
    
  }

  size_t size = configFileJws.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileJws.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());  

  if (error) {
    Serial.println("Gagal parse fileconfigjws");
    return;
  }
  
  configJWS.iqmhs = doc["iqmhs"];
  configJWS.iqmhd = doc["iqmhd"];
  configJWS.iqmha = doc["iqmha"];
  configJWS.iqmhm = doc["iqmhm"];
  configJWS.iqmhi = doc["iqmhi"];
  configJWS.kecerahan = doc["kecerahan"];
  configJWS.delayjumat = doc["delayjumat"];
  configJWS.durasiadzan = doc["durasiadzan"];
  configJWS.ihti = doc["ihti"];
  configJWS.latitude = doc["latitude"];
  configJWS.longitude = doc["longitude"];
  configJWS.zonawaktu = doc["zonawaktu"];
  configJWS.hilal = doc["hilal"];
  strlcpy(configJWS.namamasjid, doc["namamasjid"] | "", sizeof(configJWS.namamasjid));
  strlcpy(configJWS.textstliqomah, doc["textstliqomah"] | "", sizeof(configJWS.textstliqomah));
  configFileJws.close(); 

}

// -------------------------------------------
// MEMBACA PARAMETER YANG TERSIMPAN

void bacaParameter() {

  Serial.println(" ");
  Serial.println("PARAMETER TERSIMPAN");
  Serial.print("Iqomah Subuh   : "); Serial.println(configJWS.iqmhs);
  Serial.print("Iqomah Dzuhur  : "); Serial.println(configJWS.iqmhd);
  Serial.print("Iqomah Ashar   : "); Serial.println(configJWS.iqmha);
  Serial.print("Iqomah Maghrib : "); Serial.println(configJWS.iqmhm);
  Serial.print("Iqomah Isya    : "); Serial.println(configJWS.iqmhi);
  Serial.print("Kecerahan      : "); Serial.println(configJWS.kecerahan);
  Serial.print("Delayjumat     : "); Serial.println(configJWS.delayjumat);
  Serial.print("Durasi Adzan   : "); Serial.println(configJWS.durasiadzan);
  Serial.print("Ihtiyati       : "); Serial.println(configJWS.ihti);
  Serial.print("Latitude       : "); Serial.println(configJWS.latitude);
  Serial.print("Longitude      : "); Serial.println(configJWS.longitude);
  Serial.print("Zona Waktu     : "); Serial.println(configJWS.zonawaktu);
  Serial.print("Derajat Hilal  : "); Serial.println(configJWS.hilal);
  Serial.print("Nama Masjid    : "); Serial.println(configJWS.namamasjid);
  Serial.print("Text Setelah   : "); Serial.println(configJWS.textstliqomah);
  Serial.println(" ");
  
}

void jadwalSholat(){
  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting

    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi

    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night

    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  
  */
  

   set_calc_method(Karachi);
   set_asr_method(Shafii);
   set_high_lats_adjust_method(AngleBased);
   set_fajr_angle(20);
   set_isha_angle(18);

   get_prayer_times(rTah, rBul, rTgl, configJWS.latitude, configJWS.longitude, configJWS.zonawaktu, times);
}


// ------------------------------
// UPDATE HISAB TANGGAL

void TanggalHijriah() {

  HisabTanggal.setLocationOnEarth(configJWS.latitude, configJWS.longitude); //clatitude clongitude TANGERANG
  
  //Set Imkan Rukyah ... Visibility Factor
  // Muhammadiah      ==> 0 derajat
  // Nahdatul Ulama   ==> 2 derajat
  HisabTanggal.setHilalVisibilityFactor(configJWS.hilal);
  HisabTanggal.Greg2HijrDate(rTgl, rBul, rTah, Hjr_Date, Hjr_Month, Hjr_Year);

}


void updateWaktu() {

  static long pM;
  static uint16_t d;
  

  if (millis() - pM > 1000) {
    d++;
    if (d < 2) {
      BacaRTC();
      jadwalSholat();
      TanggalHijriah();
    } else if (d < 60) {
      rDet++;
      if (rDet > 59) {
        rMen++;
        rDet=0;
        if (rMen > 59) {
          rJam++;
          rMen = 0;
        }
      }
    } else {
      d = 0; 
    }
    pM = millis();    
  }
}

//----------------------------------------------------------------------
// XML UNTUK JEMBATAN DATA MESIN DENGAN WEB

void XMLWaktu(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";
  
    XML+="<Tahun>";
    XML+=rTah;
    XML+="</Tahun>";
    XML+="<Bulan>";
    XML+=rBul;
    XML+="</Bulan>";
    XML+="<Tanggal>";
    XML+=rTgl;
    XML+="</Tanggal>";
    XML+="<Jam>";
      if(rJam<10){
        XML+="0";
        XML+=rJam;
      }else{XML+=rJam;}
    XML+="</Jam>";
    XML+="<Menit>";
      if(rMen<10){
        XML+="0";
        XML+=rMen;
      }else{XML+=rMen;}
    XML+="</Menit>";
    XML+="<Detik>";
      if(rDet<10){
        XML+="0";
        XML+=rDet;
      }else{XML+=rDet;}
    XML+="</Detik>";
    XML+="<Suhu>";
    XML+= celcius - 5;
    XML+="</Suhu>";
    
  XML+="</t>"; 
}


void XMLDataJWS(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";

    XML+="<IqomahSubuh>";
    XML+= configJWS.iqmhs;
    XML+="</IqomahSubuh>";
    XML+="<IqomahDzuhur>";
    XML+= configJWS.iqmhd;
    XML+="</IqomahDzuhur>";
    XML+="<IqomahAshar>";
    XML+= configJWS.iqmha;
    XML+="</IqomahAshar>";
    XML+="<IqomahMaghrib>";
    XML+= configJWS.iqmhm;
    XML+="</IqomahMaghrib>";
    XML+="<IqomahIsya>";
    XML+= configJWS.iqmhi;
    XML+="</IqomahIsya>";
    XML+="<Kecerahan>";
    XML+= configJWS.kecerahan;
    XML+="</Kecerahan>";
    XML+="<DelayJumat>";
    XML+= configJWS.delayjumat;
    XML+="</DelayJumat>";
    XML+="<DurasiAdzan>";
    XML+= configJWS.durasiadzan;
    XML+="</DurasiAdzan>";
    XML+="<Ihtiyati>";
    XML+= configJWS.ihti;
    XML+="</Ihtiyati>";
    XML+="<Latitude>";
    XML+= configJWS.latitude;
    XML+="</Latitude>";
    XML+="<Longitude>";
    XML+= configJWS.longitude;
    XML+="</Longitude>";
    XML+="<ZonaWaktu>";
    XML+= configJWS.zonawaktu;
    XML+="</ZonaWaktu>";
    XML+="<Hilal>";
    XML+= configJWS.hilal;
    XML+="</Hilal>";
    XML+="<NamaMasjid>";
    XML+= configJWS.namamasjid;
    XML+="</NamaMasjid>";
    XML+="<TextStliqomah>";
    XML+= configJWS.textstliqomah;
    XML+="</TextStliqomah>";
    
  XML+="</t>"; 
}
