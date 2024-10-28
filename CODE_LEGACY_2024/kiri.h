int cek = 0;

void followDindingKanan(int jarak, int lebar) {
  int toleransi = 5;
  int lamanya = 5;
  int selisihKanan = lid1 - lid2;  // 15-20 = -5
  int selisihPositif = toleransi;
  int selisihNegatif = -1 * toleransi;
  int batasMendekatkan = jarak + toleransi;
  int batasMenjauhkan = jarak - toleransi;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak)) {
    for (int i = 0; i < lamanya; i++) passData(4);  // kanan
    Serial.println("serong tapi jauh");
  }

  while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak)) {
    for (int i = 0; i < lamanya; i++) passData(4);  // kanan
    Serial.println("serong tapi jauh");
  }

  while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak)) {
    for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
    Serial.println("serongkanan - 1");
  }

  while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak)) {
    for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
    Serial.println("serongKiri - 1");
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  while ((lid2 > batasMendekatkan) && (lid1 > batasMendekatkan)) {
    while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(4);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(4);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak)) {
      for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
      Serial.println("serongkanan - 1");
    }

    while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak)) {
      for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
      Serial.println("serongKiri - 1");
    }

    for (int i = 0; i < lamanya; i++) passData(4);  // langkah kanan
    Serial.println("kekiri");
  }

  while ((lid2 < batasMenjauhkan) && (lid1 < batasMenjauhkan)) {
    while (((selisihKanan < selisihNegatif) && (lid2 > jarak)) && (lid1 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(4);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan > selisihPositif) && (lid2 > jarak)) && (lid1 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(4);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan < selisihNegatif) && (lid2 >= jarak)) && (lid1 <= jarak)) {
      for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
      Serial.println("serongkanan - 1");
    }

    while (((selisihKanan > selisihPositif) && (lid2 <= jarak)) && (lid1 >= jarak)) {
      for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
      Serial.println("serongKiri - 1");
    }

    for (int i = 0; i < lamanya; i++) passData(2);  // langkah kiri
    Serial.println("kekanan");
  }

  lebarLangkah = 40;
}

void followDindingKiri(int jarak, int lebar) {
  int toleransi = 3;
  int lamanya = 5;
  int selisihKanan = lid2 - lid1;  // 15-20 = -5
  int selisihPositif = toleransi;
  int selisihNegatif = -1 * toleransi;
  int batasMendekatkan = jarak + toleransi;
  int batasMenjauhkan = jarak - toleransi;

  while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 > jarak)) {
    for (int i = 0; i < lamanya; i++) passData(2);  // kanan
    Serial.println("serong tapi jauh");
  }

  while (((selisihKanan > selisihPositif) && (lid1 > jarak)) && (lid2 > jarak)) {
    for (int i = 0; i < lamanya; i++) passData(2);  // kanan
    Serial.println("serong tapi jauh");
  }

  while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 < jarak)) {
    lebarLangkah = lebar;
    for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
    Serial.println("serongKiri");
  }

  while (((selisihKanan > selisihPositif) && (lid1 < jarak)) && (lid2 > jarak)) {
    lebarLangkah = lebar;
    for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
    Serial.println("serongkanan");
  }

  while ((lid1 > batasMendekatkan) && (lid2 > batasMendekatkan)) {
    while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(2);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan > selisihPositif) && (lid1 > jarak)) && (lid2 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(2);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 < jarak)) {
      lebarLangkah = lebar;
      for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
      Serial.println("serongKiri");
    }

    while (((selisihKanan > selisihPositif) && (lid1 < jarak)) && (lid2 > jarak)) {
      lebarLangkah = lebar;
      for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
      Serial.println("serongkanan");
    }

    lebarLangkah = 40;
    for (int i = 0; i < 20; i++) passData(2);  // langkah kiri
    Serial.println("kekiri");
  }

  while ((lid1 < batasMenjauhkan) && (lid2 < batasMenjauhkan)) {
    while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(2);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan > selisihPositif) && (lid1 > jarak)) && (lid2 > jarak)) {
      for (int i = 0; i < lamanya; i++) passData(2);  // kanan
      Serial.println("serong tapi jauh");
    }

    while (((selisihKanan < selisihNegatif) && (lid1 > jarak)) && (lid2 < jarak)) {
      lebarLangkah = lebar;
      for (int i = 0; i < lamanya; i++) passData(5);  // pivot kiri
      Serial.println("serongKiri");
    }

    while (((selisihKanan > selisihPositif) && (lid1 < jarak)) && (lid2 > jarak)) {
      lebarLangkah = lebar;
      for (int i = 0; i < lamanya; i++) passData(6);  // pivot kanan
      Serial.println("serongkanan");
    }

    lebarLangkah = 40;
    for (int i = 0; i < lamanya; i++) passData(4);  // langkah kanan
    Serial.println("kekanan");
  }

  lebarLangkah = 40;
}



//========================Menuju Korban 1=============================================
void menujuKorban1() {
  // Gerak maju sampai jarak lidar memenuhi syarat
  while (lid0 < 25) {
    followDindingKanan(14, 20);
    for (int i = 0; i < 5; i++) passData(1);  // Gerak maju
  }
}

//========================ambil korban 1================================
void ambilKorban1() {
  while (true) {
    int yaw = bacaKompas();
    if (yaw > 95 && yaw < 105) {
      break;  // Sudah berada pada sudut yang diinginkan
    }
    passData(5);  // Putar robot sampai sudut tercapai
  }
  delay(100);
}

//=========================Menuju Safe Zone 1============================
void menujuSz1() {
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
  passData(0);  // Berhenti setelah mencapai sudut
}
