#include <stdio.h>
#include <string.h>
#define MAX_SORULAR 100
#define MAX_SECENEKLER 5
#define MAX_SINAVLAR 10

int sistemSecimi();

//----------------Structlar ve Degişkenler----------------//
struct Soru {
    char icerik[200];
    char secenekler[5][100];
    int counter;
} yeniSoru;

struct duyrular {
    char duyru[100][20];
    int duyruSayisi;
    int duyruCounter;
} duyrular;


struct Sinav {
    char sinavAdi[100];
    char sinavSoruIcerik[200];
    char sinavSecenekler[MAX_SECENEKLER][100];
    char dogruSecenek;
};

struct Sinav sinavlar[MAX_SINAVLAR][MAX_SORULAR];
int sinavSoruSayisi[MAX_SINAVLAR];
int sinavCounter = 0;

char dSecenek[10];
char ogrSecenek[10];
int alistirmaCounter;
struct Soru sorular[100];
int soruSayisi = 0;

//----------------Dizayn Metodu----------------//

void printHeader(const char* title) {
    int length = strlen(title) + 4; 
    char border[length + 1];
    memset(border, '=', length);
    border[length] = '\0';

    printf("%s\n", border);
    printf("| %s |\n", title);
    printf("%s\n", border);
}

//----------------Ekran Temizleme Metodu----------------//

void ekranTemizle() {
    printf("\033[H\033[J");
    fflush(stdout);
}

//----------------Alıştırma ekleyen metodu----------------//

void soruEkle() {
    ekranTemizle();
    printHeader("Yeni Soru Ekle");
    printf("Sorunun içeriği: ");
    scanf("%199[^\n]", yeniSoru.icerik);
    printf("Seçenekleri girin:\n");
    for (int i = 0; i < 5; i++) {
        printf("%c) ", 'A' + i);
        scanf(" %99[^\n]", yeniSoru.secenekler[i]);
    }

    printf("Doğru seçenek giriniz (A, B, C, D, veya E): ");
    scanf(" %c", &dSecenek[soruSayisi]);
    sorular[soruSayisi++] = yeniSoru;
    yeniSoru.counter++;
    ekranTemizle();
}

//----------------Öğrenciye alıştırmayı gösteren metodu----------------//

void sorulariGoster() {
    ekranTemizle();
    printHeader("Alıştırmalar");

    if (soruSayisi > 0) {
        for (int i = 0; i < soruSayisi; ++i) {
            printf("Soru %d:\n", i + 1);
            printf("%s\n", sorular[i].icerik);
            printf("Seçenekler:\n");
            for (int j = 0; j < 5; ++j) {
                printf("%c) %s\n", 'A' + j, sorular[i].secenekler[j]);
            }

            printf("\nCevabınız: ");
            scanf(" %c", &ogrSecenek[i]);
            if (ogrSecenek[i] == dSecenek[i]) { 
                printf("Tebrikler! Doğru bir cevap girdiniz!\n\n");
            } else {
                printf("Maalesef yanlış bir cevap girdiniz, doğru cevap %c'dır.\n\n", dSecenek[i]);
            }
        }
        soruSayisi = 0;
        memset(sorular, 0, sizeof(sorular));
        memset(dSecenek, 0, sizeof(dSecenek));
    } else {
        printf("Henüz mevcut bir Alıştırma bulunmamaktadır.\n\n");
    }
}


//----------------Sınav ekleyen metodu----------------//

void sinavAt() {
    ekranTemizle();
    printHeader("Yeni Sınav At ");
    int soruSayisi;
    printf("Sınav Adı Giriniz: ");
    fgets(sinavlar[sinavCounter][0].sinavAdi, sizeof(sinavlar[sinavCounter][0].sinavAdi), stdin);
    strtok(sinavlar[sinavCounter][0].sinavAdi, "\n"); 

    printf("Soru Sayisi Giriniz: ");
    scanf("%d", &soruSayisi);
    getchar(); 

    for (int i = 0; i < soruSayisi; i++) {
        ekranTemizle();
        printf("%d. Sorunun içeriği: ", i + 1);
        fgets(sinavlar[sinavCounter][i].sinavSoruIcerik, sizeof(sinavlar[sinavCounter][i].sinavSoruIcerik), stdin);
        strtok(sinavlar[sinavCounter][i].sinavSoruIcerik, "\n"); 

        printf("Seçenekleri girin:\n");
        for (int j = 0; j < MAX_SECENEKLER; j++) {
            printf("%c) ", 'A' + j);
            fgets(sinavlar[sinavCounter][i].sinavSecenekler[j], sizeof(sinavlar[sinavCounter][i].sinavSecenekler[j]), stdin);
            strtok(sinavlar[sinavCounter][i].sinavSecenekler[j], "\n"); 
        }

        printf("Doğru seçenek giriniz (A, B, C, D, veya E): ");
        scanf(" %c", &sinavlar[sinavCounter][i].dogruSecenek);
        getchar(); 

        sinavSoruSayisi[sinavCounter]++;
    }
    sinavCounter++;
    ekranTemizle();
}

//----------------eklenen sınavı/sınavları gösteriyor----------------//

void sinavGoster(int sinavIndex) {
    printHeader("Başarılar (:1");
    for (int i = 0; i < sinavSoruSayisi[sinavIndex]; ++i) {
        printf("Soru %d: ", i + 1);
        printf("%s\n", sinavlar[sinavIndex][i].sinavSoruIcerik);
        printf("Seçenekler:\n");
        for (int j = 0; j < MAX_SECENEKLER; ++j) {
            printf("%c) %s\n", 'A' + j, sinavlar[sinavIndex][i].sinavSecenekler[j]);
        }

        char ogrSecenek;
        printf("\nCevabınız: ");
        scanf(" %c", &ogrSecenek);
        ekranTemizle();
        getchar();
    }

    for (int i = sinavIndex; i < sinavCounter - 1; ++i) {
        sinavSoruSayisi[i] = sinavSoruSayisi[i + 1];
        memcpy(sinavlar[i], sinavlar[i + 1], sizeof(sinavlar[i]));
    }
    sinavSoruSayisi[sinavCounter - 1] = 0;
    memset(sinavlar[sinavCounter - 1], 0, sizeof(sinavlar[sinavCounter - 1]));
    sinavCounter--;
}

//----------------Duyru atan metodu----------------//

void duyruAt() {
    ekranTemizle();
    printHeader("Yeni Duyuru At");
    printf("Konu: ");
    scanf("%s", duyrular.duyru[duyrular.duyruSayisi]);
    duyrular.duyruSayisi++;
    ekranTemizle();
    printf("Duyru gönderildi.✅\n\n");
    duyrular.duyruCounter++;
}

//----------------Gonderilen duyru/duyrular gösteren metodu----------------//

void duyruGoster() {
    ekranTemizle();
    printHeader("Duyurular");
    if (duyrular.duyruSayisi > 0) {
        for (int i = 0; i < duyrular.duyruSayisi; i++) {
            printf("Duyuru %d:\n", i + 1);
            printf("Konu: %s\n", duyrular.duyru[i]);
            printf("==============\n");
        }
    } else {
        printf("Henüz duyuru bulunmamaktadır.\n");
    }
}

//----------------Hoca menusu yazdıran metodu----------------//

void hanaMenuYazdir() {
    printHeader("Menü");
    printf("1. Alıştırma At\n");
    printf("2. Duyuru at\n");
    printf("3. Sınav At\n");
    printf("4. Çıkış\n");
    printf("Seçiminizi yapın: ");
}

//----------------Hoca metodları çalıştıran metod----------------//

int hAnaMenu() {
    int secim;
    do {
        hanaMenuYazdir();
        scanf("%d", &secim);
        getchar(); // Yeni satırı oku

        switch (secim) {
            case 1:
                soruEkle();
                break;
            case 2:
                duyruAt();
                break;
            case 3:
                sinavAt();
                break;
            default:
                girdiDogrula(1,4);
                break;
        }
    } while (secim != 4);
    ekranTemizle();
    sistemSecimi();

    return 0;
}
