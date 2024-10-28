#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include "controlSystem.h"
#include "module.h"
#include "bodyKinematics.h"
#include "kaki.h"
#include "kompas.h"
#include "komponen.h"
// #include "prog.h"
bool bag = 0;  // set robot pada bagian 0 = kiri dan 1 = kanan

int j, k, l, m, n, o, p;
char keyInput;

#define pb 30
#define SERIAL_PORT Serial1  // Menggunakan Serial1 (RX1/TX1 pada pin 19/18)
#define buf_length 11        // Panjang buffer data yang dikirim oleh sensor

byte RxBuff[buf_length];     // Buffer untuk menyimpan data
float AngleZ = 0;            // Data sudut (angle) Z (yaw)
int dataIndex = 0;           // Menyimpan index buffer
bool startFrame = false;  


// Fungsi untuk membaca data kompas CMP10A dan mengembalikan nilai yaw
int bacaKompas() {
  unsigned long startTime = millis();  // Waktu mulai untuk timeout

  while (millis() - startTime < 1000) {  // Timeout setelah 1000 ms (1 detik)
    if (SERIAL_PORT.available()) {
      byte inputData = SERIAL_PORT.read();  // Baca byte dari sensor

      // Mendeteksi awal frame (0x55)
      if (inputData == 0x55 && !startFrame) {
        startFrame = true;
        dataIndex = 0;  // Reset index buffer
        RxBuff[dataIndex++] = inputData;
      } else if (startFrame) {
        // Masukkan data ke dalam buffer
        RxBuff[dataIndex++] = inputData;

        // Jika buffer sudah penuh, proses data
        if (dataIndex == buf_length) {
          startFrame = false;  // Reset flag frame

          // Memproses data sudut (angle) yang diterima
          if (RxBuff[1] == 0x53) {  // Data sudut (angle)
            // Mendapatkan nilai sudut Z (yaw)
            int16_t rawAngleZ = (int16_t)(RxBuff[7] << 8 | RxBuff[6]);
            AngleZ = rawAngleZ / 32768.0 * 180;  // Konversi ke derajat (-180 hingga 180)

            // Mengonversi nilai sudut ke rentang 0 - 360 derajat
            if (AngleZ < 0) {
              AngleZ = 360 + AngleZ;
            }

            return AngleZ;  // Mengembalikan nilai sudut Z (yaw)
          }
        }
      }
    }
  }

  // Jika tidak ada data yang valid dalam waktu 1 detik, kembalikan -1
  return -1;
}

// Fungsi untuk menampilkan nilai kompas di layar OLED (DIPINDAHKAN KE FILE .INO)
void tampilkanKompas(int yaw) {
  display.clearDisplay();  // Bersihkan layar OLED
  display.setTextSize(1);  // Set ukuran teks
  display.setTextColor(SSD1306_WHITE);  // Set warna teks

  // Tampilkan judul "Kompas"
  display.setCursor(0, 0);
  display.println(F("Kompas CMP10A"));

  // Tampilkan nilai sudut Z (Yaw)
  display.setCursor(0, 16);
  display.print(F("Yaw (Z): "));
  display.print(yaw);  // Tampilkan nilai yaw

  display.display();  // Perbarui tampilan OLED
}

void bacaLidar() {
  Serial.print("lid0 : ");
  Serial.print(lid0);
  Serial.print("   lid1 : ");
  Serial.print(lid1);
  Serial.print("   lid2 : ");
  Serial.print(lid2);
  Serial.print("   lid3 : ");
  Serial.print(lid3);
  Serial.print("   lid4 : ");
  Serial.print(lid4);
  Serial.print("   lid5 : ");
  Serial.println(lid5);
}

void tungguTombolStartDanPrintNilaiSensor() {
  while (digitalRead(pb) == 1) {
    passData(0);
  }
}

void followDindingKanan(int jarak, int lebar) {
  int toleransi = 5;
  int lamanya = 5;
  int selisihKanan = lid1 - lid2;  //15-20 = -5
  int selisihPositif = toleransi;
  int selisihNegatif = -1 * toleransi;
  int batasMendekatkan = jarak + toleransi;
  int batasMenjauhkan = jarak - toleransi;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  {
    for (int i = 0; i < lamanya; i++) passData(4);  //kanan
    Serial.println("serong tapi jauh");
  }
  while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  {
    for (int i = 0; i < lamanya; i++) passData(4);  //kanan
    Serial.println("serong tapi jauh");
  }
  while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  {
    for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
    Serial.println("serongkanan - 1");
  }
  // while (((selisihKanan < selisihNegatif) && (lid5 < jarak)) && (lid4 < jarak) && set == 0)  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  // {
  //   for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
  //   Serial.println("serongkanan - 2");
  // }
  while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  {
    for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
    Serial.println("serongKiri - 1");
  }
  // while (((selisihKanan > selisihPositif) && (lid5 < jarak)) && (lid4 < jarak) && set == 0)  // && (kanan0<batasDekat) && (kanan1<batasDekat))
  // {
  //   for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
  //   Serial.println("serongKiri - 2");
  // }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  while ((lid2 > batasMendekatkan) && (lid1 > batasMendekatkan))  /////
  {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(4);  //kanan
      Serial.println("serong tapi jauh");
    }
    while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(4);  //kanan
      Serial.println("serong tapi jauh");
    }
    while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
      Serial.println("serongkanan - 1");
    }
    // while (((selisihKanan < selisihNegatif) && (lid5 < jarak)) && (lid4 < jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    // {
    //   for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
    //   Serial.println("serongkanan - 2");
    // }
    while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
      Serial.println("serongKiri - 1");
    }
    // while (((selisihKanan > selisihPositif) && (lid5 < jarak)) && (lid4 < jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    // {
    //   for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
    //   Serial.println("serongKiri - 2");
    // }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < lamanya; i++) passData(4);  //langkah kanan
    Serial.println("kekiri");
  }
  while ((lid2 < batasMenjauhkan) && (lid1 < batasMenjauhkan)) {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(4);  //kanan
      Serial.println("serong tapi jauh");
    }
    while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(4);  //kanan
      Serial.println("serong tapi jauh");
    }
    while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
      Serial.println("serongkanan - 1");
    }
    // while (((selisihKanan < selisihNegatif) && (lid5 < jarak)) && (lid4 < jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    // {
    //   for (int i = 0; i < lamanya; i++) passData(6);  //pivot kanan
    //   Serial.println("serongkanan - 2");
    // }
    while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
      Serial.println("serongKiri - 1");
    }
    // while (((selisihKanan > selisihPositif) && (lid5 < jarak)) && (lid4 < jarak))  // && (kanan0<batasDekat) && (kanan1<batasDekat))
    // {
    //   for (int i = 0; i < lamanya; i++) passData(5);  //pivot kiri
    //   Serial.println("serongKiri - 2");
    // }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < lamanya; i++) passData(2);  //langkah kiri
    Serial.println("kekanan");
  }
  lebarLangkah = 40;
}
void tampilkanData(String label, float value) {
  display.clearDisplay();  // Bersihkan layar OLED
  display.setTextSize(1);  // Set ukuran teks
  display.setTextColor(SSD1306_WHITE);  // Set warna teks

  // Tampilkan label data
  display.setCursor(0, 0);
  display.print(label);  // Tampilkan label (misalnya: "Suhu")

  // Tampilkan nilai data
  display.setCursor(0, 16);
  display.print("Value: ");
  display.print(value, 2);  // Tampilkan nilai variabel dengan 2 angka di belakang koma

  display.display();  // Perbarui tampilan OLED
}

void menujuKorban1() {
  // Gerak maju sampai jarak lidar memenuhi syarat
  while (lid0 < 25) {
    followDindingKanan(14, 20);
    for (int i = 0; i < 5; i++) passData(1);  // Gerak maju
  }

  // Mengontrol arah berdasarkan kompas dengan toleransi
  while (true) {
    int yaw = bacaKompas();
    if (yaw > 95 && yaw < 105) {
      break;  // Sudah berada pada sudut yang diinginkan
    }
    passData(5);  // Putar robot sampai sudut tercapai
  }
  delay(100);
  while (true) {
    int yaw = bacaKompas();
    if (yaw > 330 && yaw < 340) {
      break;  // Sudah berada pada sudut yang diinginkan
    }
    passData(6);  // Putar robot sampai sudut tercapai
  }
  while (lid3 > 30) {
    followDindingKanan(14, 20);
    for (int i = 0; i < 8; i++) passData(1);  // Gerak maju
  }
  //  for (int i = 0; i < 20; i++) passData(1);
  passData(0);  // Berhenti setelah mencapai sudut
}

void setup() {
  Serial.begin(9600);
  pinMode(pb, INPUT_PULLUP);
  SERIAL_PORT.begin(9600);       

  // Inisialisasi OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.display();
  display.clearDisplay();
  setupSensor();
  setupKaki();
  setupBody();
  servo_park_home();
  passData(0);
  Serial.print("halo");
}

void loop() {
  if (digitalRead(pb) == 0) {
    menujuKorban1();
  }
  // Serial.println(lid5);
//  tampilkanData("lid", lid2);
 
}
  // if (digitalRead(pb) == 0) {
  //   menujuKorban1();
  // }

//   // Tampilkan nilai kompas setiap loop
//   int yaw = bacaKompas();
//   if (yaw != -1) {  // Pastikan yaw valid
//     tampilkanKompas(yaw);  // Tampilkan di OLED
//   }

//   delay(100);  // Sedikit delay untuk menghindari refresh terlalu cepat
// }

  // for (int i = 330; i >120 50; i--) passData(5);  //pivot kiri
  // for (int i = 0; i < 50; i++) passData(3);
// }
  // Serial.println(bacaKompas());
  
  // Serial.println(digitalRead(pb));
  // if(digitalRead(pb) == 0){
  //   while(1){
  //     passData(1);
  //     delay(10);
      // tampilkanKompas(bacaKompas());
    
      /*int yaw = bacaKompas();  // Baca nilai yaw
      Serial.println(yaw);  // Tampilkan yaw di Serial Monitor
      tampilkanKompas(yaw);  // Tampilkan yaw di OLED
    
      // Cek kondisi yaw dan lakukan aksi sesuai
      if (yaw <= 340) {
        passData(6);  // Jika yaw kurang dari 340, jalankan passData(6)
      }
      else if (yaw >= 360 || yaw <= 10) {
        passData(5);  // Jika yaw di luar 360-10, jalankan passData(5)
      }
      else {
        passData(1);  // Selain itu, jalankan passData(1)
      }*/

    
  

  //passData(0);

  // Tampilkan nilai kompas di OLED dan Serial Monitor
 
/*

if(digitalRead(pb) == 0) {
  while(1) {
    passData(1);
   
      /*
      int yaw = bacaKompas();  // Baca nilai yaw
      Serial.println(yaw);  // Tampilkan yaw di Serial Monitor
      tampilkanKompas(yaw);  // Tampilkan yaw di OLED

      // Cek kondisi yaw dan lakukan aksi sesuai
      if (yaw < 340) {
        passData(6);  // Jika yaw kurang dari 340, jalankan passData(6)
      }
      else if (yaw > 360 || yaw < 10) {
        passData(5);  // Jika yaw di luar 360-10, jalankan passData(5)
      }
      else {
        passData(1);  // Selain itu, jalankan passData(1)
      }
    }
  }
}

*/

  




 
  /*
  // Tampilkan nilai kompas di OLED
  tampilkanKompas(yaw);

  Serial.print("halo");
  Serial.println(digitalRead(pb));
  
  //tungguTombolStartDanPrintNilaiSensor();
}
*/

  //pasangKaki();
  /*
  //passData(1);
  if (Serial.available() > 0) {
    keyInput = Serial.read();
    Serial.print("keyInput : ");
    Serial.println(keyInput);
    switch (keyInput) {
      case 'a':  //kiri
        input = 2;
        break;
      case 'd':  //kanan
        input = 4;
        break;
      case 'e':  //pivot kanan
        input = 6;
        break; 
      case 'w':  //maju
        input = 1;
        break;
      case 's':  //mundur
        input = 3;
        break; 
      case 'q':  //pivot kiri
        input = 5;
        break;
      case ' ':
        input = 50;
        break;
      }
    passData(input);
  }
   */
//  tungguTombolStartDanPrintNilaiSensor();
 // passData(1);
  /*if (bag == 0) {
    menujuKorban1();
    ambilKorban1();
    menujuSz1();
    taruhKorban1();
    menujuKorban2();
    ambilKorban2();
    menujuSz2();
    taruhKorban2();
    menujuKorban3();
    ambilKorban3();
    menujuKorban4();
    ambilKorban4();
    menujuSz3();
    menujuTangga();
    naikTangga();
    menujuSz4();
    taruhKorban4();
    menujuKorban5();
    ambilKorban5();
    menujuSz5();
    taruhKorban5();
  } else {
    menujuKorban1_1();
    ambilKorban1_1();
    menujuSz1_1();
    taruhKorban1_1();
    menujuKorban2_1();
    ambilKorban2_1();
    menujuSz2_1();
    taruhKorban2_1();
    menujuKorban3_1();
    ambilKorban3_1();
    menujuKorban4_1();
    ambilKorban4_1();
    menujuSz3_1();
    menujuTangga_1();
    naikTangga_1();
    menujuSz4_1();
    taruhKorban4_1();
    menujuKorban5_1();
    ambilKorban5_1();
    menujuSz5_1();
    taruhKorban5_1();*/
  
  // while (1) {
  //   passData(50);
  //   servo_park_home();
  //   Serial.println("sudah");
  // }*/
