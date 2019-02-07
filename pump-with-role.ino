const byte ilkButtonPin = 8; //digital 8,9,10,11
const byte SU_TANK_giris = 33;
const byte SU_TANK_cikis = 32;
const byte FAZ_giris = 31;
const byte FAZ_cikis = 30;
const byte ilkTermikPin_giris = 50;
const byte ilkTermikPin_cikis = 42;
const byte ilkRolePin = 3; // digital 3,4,5,6
const byte ilkGeriBeslemePin = 18; // digital 18,19,20,21
const byte maxButon = 4;
byte RolePin [maxButon];
byte TermikPin_giris [maxButon];
byte TermikPin_cikis [maxButon];
byte ButonPin [maxButon];
byte GeriBeslemePin [maxButon];
byte NewValue;
byte tekdongu ;
int giris_sayac  ;
int cikis_sayac  ;


void onbesdakika_tekli(byte Calisan,int grs_sayisi,int cks_sayisi)// Tek giriş calısınca...
{

  digitalWrite(Calisan, LOW);
  zaman(grs_sayisi,cks_sayisi);
  digitalWrite(Calisan, HIGH);
}
void onbesdakika_ikili(byte Calisan,int grs_sayisi,int cks_sayisi)// 2 giriş calısınca...
{
  byte ikili = Calisan + 1;
  if (ikili > 6) ikili = 3;
  digitalWrite(Calisan, LOW);
  digitalWrite(ikili, LOW);
  zaman(grs_sayisi,cks_sayisi);
  digitalWrite(Calisan, HIGH);
  digitalWrite(ikili, HIGH);
}
void onbesdakika_uclu(byte Calisan,int grs_sayisi,int cks_sayisi)// 3 giris calısınca...
{
  byte ikili = Calisan + 1;
  byte uclu = Calisan + 2;
  if (ikili > 6)
  {
    ikili = 3;
    if (uclu > 6) uclu = 4;
  }
  if (uclu > 6) uclu = 3;
  digitalWrite(Calisan, LOW);
  digitalWrite(ikili, LOW);
  digitalWrite(uclu, LOW);
  zaman(grs_sayisi,cks_sayisi);
  digitalWrite(Calisan, HIGH);
  digitalWrite(ikili, HIGH);
  digitalWrite(uclu, HIGH);
}
int giris_tekrar()
{
  giris_sayac = 0;
  for (int i = 0; i < maxButon; i++)
  {
    NewValue = digitalRead(ButonPin[i]);
    if (NewValue == HIGH)
    {
      giris_sayac++;
    }
  }
  return giris_sayac;
}
int cikis_tekrar()
{
  cikis_sayac = 0;
  for (int i = 0; i < maxButon; i++)
  {
    NewValue = digitalRead(GeriBeslemePin[i]);
    if (NewValue == HIGH)
    {
      cikis_sayac++;
    }
  }
  return cikis_sayac;
}
void termik_atma()
{
  for (int a = 0; a < 4; a++) {
    if (digitalRead(TermikPin_giris[a]) == HIGH && digitalRead(GeriBeslemePin[a]) == LOW) {
      digitalWrite(TermikPin_cikis[a], HIGH );
    } else
    {
      digitalWrite(TermikPin_cikis[a], LOW );
    }
  }
}
void zaman(int grs_sayisi,int cks_sayisi)
{
  unsigned long eskiZaman = 0;
  // unsigned long yeniZaman;
  int sayi = 10;
dakika:
  if (millis() - eskiZaman > 1000) {
    if ( giris_tekrar() != grs_sayisi || cikis_tekrar() != cks_sayisi || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) return;
    if (sayi > 0) {
      sayi = --sayi;
      eskiZaman = millis();

    }
    else
    {
      return;
    }
  }
  goto dakika;

}
void setup () {

  pinMode( SU_TANK_giris , INPUT_PULLUP);
  digitalWrite(SU_TANK_giris, LOW );// buton KAPALI
  pinMode( SU_TANK_cikis , OUTPUT);
  digitalWrite(SU_TANK_cikis, LOW );// buton KAPALI
  pinMode( FAZ_giris , INPUT_PULLUP);
  digitalWrite(FAZ_giris, LOW );// buton KAPALI
  pinMode( FAZ_cikis , OUTPUT);
  digitalWrite(FAZ_cikis, LOW );// buton KAPALI

  for (int i = 0; i < maxButon; i++)
  {
    RolePin[i] = i + ilkRolePin;
    pinMode( RolePin[i] , OUTPUT);
    digitalWrite(RolePin[i], HIGH ); // role KAPALI
    ButonPin[i] = i + ilkButtonPin;
    pinMode( ButonPin[i] , INPUT_PULLUP);
    digitalWrite(ButonPin[i], LOW );// buton KAPALI
    TermikPin_giris[i] = i + ilkTermikPin_giris ;
    pinMode( TermikPin_giris[i] , INPUT_PULLUP);
    digitalWrite(TermikPin_giris[i], LOW );// termik KAPALI
    TermikPin_cikis[i] = i + ilkTermikPin_cikis ;
    pinMode( TermikPin_cikis[i] , OUTPUT);
    digitalWrite(TermikPin_cikis[i], LOW );// termik KAPALI
    GeriBeslemePin[i] = i + ilkGeriBeslemePin;
    pinMode( GeriBeslemePin[i] , INPUT_PULLUP);
    digitalWrite(GeriBeslemePin[i], HIGH );// geri besleme ACIK
  }
  attachInterrupt(5, kesmepin18, LOW);
  attachInterrupt(4, kesmepin19, LOW);
  attachInterrupt(3, kesmepin20, LOW);
  attachInterrupt(2, kesmepin21, LOW);
}
void loop()
{
basla:

  termik_atma();
  if (digitalRead(SU_TANK_giris) == HIGH)
  {
    //EKRANA YAZI YAZILACAK SU TANKI ARIZASI VARDIR DİYE...
    digitalWrite(RolePin[0], HIGH); //1.role KAPALI
    digitalWrite(RolePin[1], HIGH); //2.role KAPALI
    digitalWrite(RolePin[2], HIGH); //3.role KAPALI
    digitalWrite(RolePin[3], HIGH); //4.role KAPALI
    digitalWrite(SU_TANK_cikis, HIGH );
    delay(100);
  } else {
    digitalWrite(SU_TANK_cikis, LOW );
    delay(100);
    if (digitalRead(FAZ_giris) == HIGH)
    {
      //EKRANA YAZI YAZILACAK FAZ ARIZASI VARDIR DİYE...
      digitalWrite(RolePin[0], HIGH); //1.role KAPALI
      digitalWrite(RolePin[1], HIGH); //2.role KAPALI
      digitalWrite(RolePin[2], HIGH); //3.role KAPALI
      digitalWrite(RolePin[3], HIGH); //4.role KAPALI
      digitalWrite(FAZ_cikis, HIGH );
      delay(100);
    } else {
      digitalWrite(FAZ_cikis, LOW );
      delay(100);
      byte geciciikili[2] = {};
      byte geciciuclu[3] = {};
      cikis_sayac = cikis_tekrar();
      switch (cikis_sayac) {
        case 4:
          giris_sayac = giris_tekrar();
          switch (giris_sayac) {
            case 1:
              tekdongu = 0;
              while (tekdongu < maxButon) {
                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if ( giris_sayac != 1 || cikis_sayac != 4 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
                onbesdakika_tekli(RolePin[tekdongu],giris_sayac,cikis_sayac);

                if (digitalRead(RolePin[tekdongu]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= maxButon) {
                    tekdongu = 0;
                  }
                }
              }

            ///////İki giriş çalışınca
            case 2:
              tekdongu = 0;
              while (tekdongu < maxButon) {

                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if (giris_sayac != 2 || cikis_sayac != 4 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;

                onbesdakika_ikili(RolePin[tekdongu],giris_sayac,cikis_sayac);

                if (digitalRead(RolePin[tekdongu]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= maxButon) {
                    tekdongu = 0;
                  }
                }
              }
            //////Üç giriş çalışınca
            case 3:
              tekdongu = 0;
              while (tekdongu < maxButon) {

                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if (giris_sayac != 3 || cikis_sayac != 4 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
                onbesdakika_uclu(RolePin[tekdongu],giris_sayac,cikis_sayac);

                if (digitalRead(RolePin[tekdongu]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= maxButon) {
                    tekdongu = 0;
                  }
                }
              }
            //////Dört giriş çalışınca
            case 4:
don4:
              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if (giris_sayac != 4 || cikis_sayac != 4 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;

              digitalWrite(RolePin[0], LOW); //1.role AÇIK
              digitalWrite(RolePin[1], LOW); //2.role AÇIK
              digitalWrite(RolePin[2], LOW); //3.role AÇIK
              digitalWrite(RolePin[3], LOW); //4.role AÇIK
              goto don4;
            //////Tüm girişler kapalıyken
            default:
              digitalWrite(RolePin[0], HIGH); //1.role KAPALI
              digitalWrite(RolePin[1], HIGH); //2.role KAPALI
              digitalWrite(RolePin[2], HIGH); //3.role KAPALI
              digitalWrite(RolePin[3], HIGH); //4.role KAPALI
          }
        case 3: //uc cikis calisinca...

          for (int i = 0; i < maxButon; i++)
          {
            NewValue = digitalRead(GeriBeslemePin[i]);
            if (NewValue == HIGH)
            {
              if (geciciuclu[0] == NULL) {
                geciciuclu[0] = i;
              }
              else if (geciciuclu[1] == NULL) {
                geciciuclu[1] = i;
              }
              else
              {
                geciciuclu[2] = i;
              }

            }
          }
          giris_sayac = giris_tekrar();
          switch (giris_sayac) {
            case 1:
              tekdongu = 0;
              while (tekdongu < 3) {
                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if ( giris_sayac != 1 || cikis_sayac != 3 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;

                onbesdakika_tekli(RolePin[geciciuclu[tekdongu]],giris_sayac,cikis_sayac);

                if (digitalRead(RolePin[geciciuclu[tekdongu]]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= 3) {
                    tekdongu = 0;
                  }
                }
              }

            case 2:
              tekdongu = 0;
              while (tekdongu < 3) {
                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if ( giris_sayac != 2 || cikis_sayac != 3 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
                byte ikinci = tekdongu + 1;
                if (ikinci > 2) ikinci = 0;
                digitalWrite(RolePin[geciciuclu[tekdongu]], LOW);
                digitalWrite(RolePin[geciciuclu[ikinci]], LOW);
                zaman(giris_sayac,cikis_sayac);
                digitalWrite(RolePin[geciciuclu[tekdongu]], HIGH);
                digitalWrite(RolePin[geciciuclu[ikinci]], HIGH);

                if (digitalRead(RolePin[geciciuclu[tekdongu]]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= 3) {
                    tekdongu = 0;
                  }
                }
              }
            case 3://////Üç giriş çalışınca

              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if ( giris_sayac != 3 || cikis_sayac != 3 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
              digitalWrite(RolePin[geciciuclu[0]], LOW); //1.role AÇIK
              digitalWrite(RolePin[geciciuclu[1]], LOW); //2.role AÇIK
              digitalWrite(RolePin[geciciuclu[2]], LOW); //2.role AÇIK

            case 4://////Dört giriş çalışınca
don3:
              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if ( giris_sayac != 4 || cikis_sayac != 3 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
              digitalWrite(RolePin[geciciuclu[0]], LOW); //1.role AÇIK
              digitalWrite(RolePin[geciciuclu[1]], LOW); //2.role AÇIK
              digitalWrite(RolePin[geciciuclu[2]], LOW); //2.role AÇIK
              goto don3;
            //////Tüm girişler kapalıyken
            default:
              digitalWrite(RolePin[0], HIGH); //1.role KAPALI
              digitalWrite(RolePin[1], HIGH); //2.role KAPALI
              digitalWrite(RolePin[2], HIGH); //3.role KAPALI
              digitalWrite(RolePin[3], HIGH); //4.role KAPALI
          }
        case 2: //iki cikis calisinca...

          for (int i = 0; i < maxButon; i++)
          {
            NewValue = digitalRead(GeriBeslemePin[i]);
            if (NewValue == HIGH)
            {
              if (geciciikili[0] == NULL) {
                geciciikili[0] = i;
              }
              else {
                geciciikili[1] = i;
              }

            }
          }

          giris_sayac = giris_tekrar();
          switch (giris_sayac) {

            case 1:
              tekdongu = 0;
              while (tekdongu < 2) {
                giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
                if ( giris_sayac != 1 || cikis_sayac != 2 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;

                onbesdakika_tekli(RolePin[geciciikili[tekdongu]],giris_sayac,cikis_sayac);

                if (digitalRead(RolePin[geciciikili[tekdongu]]) == HIGH) {
                  tekdongu++;
                  if (tekdongu >= 2) {
                    tekdongu = 0;
                  }
                }
              }

            ///////İki giriş çalışınca
            case 2:

              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if ( giris_sayac != 2 || cikis_sayac != 2 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
              digitalWrite(RolePin[geciciikili[0]], LOW); //1.role AÇIK
              digitalWrite(RolePin[geciciikili[1]], LOW); //2.role AÇIK

            case 3://////Üç giriş çalışınca

              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if ( giris_sayac != 3 || cikis_sayac != 2 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
              digitalWrite(RolePin[geciciikili[0]], LOW); //1.role AÇIK
              digitalWrite(RolePin[geciciikili[1]], LOW); //2.role AÇIK

            case 4://////Dört giriş çalışınca
don2:
              giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
              if ( giris_sayac != 4 || cikis_sayac != 2 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;
              else {
                digitalWrite(RolePin[geciciikili[0]], LOW); //1.role AÇIK
                digitalWrite(RolePin[geciciikili[1]], LOW); //2.role AÇIK
                goto don2;
              }
            default:
              digitalWrite(RolePin[0], HIGH); //1.role KAPALI
              digitalWrite(RolePin[1], HIGH); //2.role KAPALI
              digitalWrite(RolePin[2], HIGH); //3.role KAPALI
              digitalWrite(RolePin[3], HIGH); //4.role KAPALI

          }

        case 1:
          int gecici;
          for (int i = 0; i < maxButon; i++)
          {
            NewValue = digitalRead(GeriBeslemePin[i]);
            if (NewValue == HIGH)
            {
              gecici = i;
            }
          }
don1:
          giris_sayac = giris_tekrar(); cikis_sayac = cikis_tekrar();
          if ( giris_sayac == 0 || cikis_sayac != 1 || digitalRead(FAZ_giris) == HIGH || digitalRead(SU_TANK_giris) == HIGH) goto basla;

          digitalWrite(RolePin[gecici], LOW);
          goto don1;
        default:
          digitalWrite(RolePin[0], HIGH); //1.role KAPALI
          digitalWrite(RolePin[1], HIGH); //2.role KAPALI
          digitalWrite(RolePin[2], HIGH); //3.role KAPALI
          digitalWrite(RolePin[3], HIGH); //4.role KAPALI

      }
    }
  }


}
void kesmepin18()
{
  digitalWrite(RolePin[0], HIGH);//1.role KAPALI
}
void kesmepin19()
{
  digitalWrite(RolePin[1], HIGH);//2.role KAPALI
}
void kesmepin20()
{
  digitalWrite(RolePin[2], HIGH);//3.role KAPALI
}
void kesmepin21()
{
  digitalWrite(RolePin[3], HIGH);//4.role KAPALI
}
