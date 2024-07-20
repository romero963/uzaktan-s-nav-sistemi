#ifndef KAYIT_CPP
#define KAYIT_CPP
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Source.cpp"
#include "hocasistemi.cpp"

//----------------Structlar ve Değikenler----------------//

int anaMenu();
int ogrGiris();
void ogretmenGiris();
void girisBasarili();


struct giris {
    char kullaniciAdi[20];
    char sifre[20];
} kullanici;

struct ogrenciGiris {
    char saklananKullaniciAdi[5][20];
    char saklananSifre[5][20]; 
} oGirisBilgisi = {{ "Muhammed", "Ahmed", "Abdulhadi", "Abdullah", "Kutaiba" }, { "pass1", "pass2", "pass3", "pass4", "pass5" }};

struct hocaGiris {
    char hSaklananKullaniciAdi[5][20];
    char hSaklananSifre[5][20];
} hGirisBilgisi = { { "Bilal", "Ahmet", "Ihsan", "Fatih", "Recep" }, { "pass1", "pass2", "pass3", "pass4", "pass5" } };

//----------------Sistemi Seçen metodu----------------//

int sistemSecimi() {
    int islem;
    printHeader("Sistem Seçimi ");
    printf("1. Hoca sistemi\n");
    printf("2. Ogrenci Sistemi\n");
    printf("3. Çıkış\n\n");
    printf("Secenek gir: ");
    scanf("%d", &islem);

    if (islem == 1) {
        ekranTemizle();
        ogretmenGiris();
    } else if (islem == 2) {
        ekranTemizle();
        ogrGiris();
    } else if (islem == 3) {
        printf("Çıkış Yapılıyor...");
        return 0;
    } else {
        printf("Seçtiğiniz seçenek geçersiz.\n\n");
        sistemSecimi();
    }
    return 0;
}

//----------------oğrenci giriş yaptıran metodu----------------//

int ogrGiris() {
    int secim;

    printHeader("Öğrenci Girişi   ");
    printf("1. Giriş Yap\n");
    printf("2. Çıkış\n");
    printf("Lütfen bir seçenek girin: ");
    scanf("%d", &secim);

    if (secim == 1) { // giris yapmak icin
    ekranTemizle();
        printf("Kullanıcı Adı: ");
        scanf("%s", kullanici.kullaniciAdi);
        printf("Şifre: ");
        scanf("%s", kullanici.sifre);

        for (int i = 0; i < 5; i++) {
            if (strcmp(kullanici.kullaniciAdi, oGirisBilgisi.saklananKullaniciAdi[i]) == 0 && strcmp(kullanici.sifre, oGirisBilgisi.saklananSifre[i]) == 0) {
                ekranTemizle();
                girisBasarili();
                ekranTemizle();
                anaMenu();
                return 0;
            }
        }

        printf("Giriş başarısız! Lütfen kullanıcı adı ve şifreyi kontrol edin.\n\n");
        ogrGiris();


    }  
    
    else if (secim == 2) {
        ekranTemizle();
        sistemSecimi();
    } 
    
    else {
        printf("Seçtiğiniz seçenek geçersiz.\n");
        ogrGiris();
    }
    return 0;
}

//----------------Öğretmen giriş yaptıran metodu----------------//

void ogretmenGiris() {
    do
    {
        int secim;
        printHeader("Öğretmen Girişi   ");
        printf("1. Giriş Yap\n");
        printf("2. Çıkış\n\n");
        printf("Seçim Yapınız: ");
        scanf("%d", &secim);

        if (secim == 1) {
            ekranTemizle();
            printf("Kullanıcı Adı: ");
            scanf("%s", kullanici.kullaniciAdi);
            printf("Şifre: ");
            scanf("%s", kullanici.sifre);

            for (int i = 0; i < 5; i++) {
                if (strcmp(kullanici.kullaniciAdi, hGirisBilgisi.hSaklananKullaniciAdi[i]) == 0 && strcmp(kullanici.sifre, hGirisBilgisi.hSaklananSifre[i]) == 0) {
                    ekranTemizle();
                    girisBasarili();
                    ekranTemizle();
                    hAnaMenu();
                    return;
                }
            }
            printf("Giriş başarısız! Lütfen kullanıcı adı ve şifreyi kontrol edin.\n\n");
        }
        else if (secim == 2) {
            ekranTemizle();
            sistemSecimi();
        }
    } while (true);

}

#endif 
