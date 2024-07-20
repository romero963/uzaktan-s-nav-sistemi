#ifndef SOURCE_CPP
#define SOURCE_CPP
#define SCREEN_WIDTH 120

#include <stdio.h>
#include <string.h>
#include "kayit.cpp"
#include <unistd.h>

// --------------Structlar ve değişkenler-------------- //

struct destek {
    char konular[100][20];
    char kategoriler[100][20];
    char detaylar[100][10000];
    int talepSayisi;
} destekTalepleri;

int secim;

// --------------Ana menu Metodu-------------- //

void anaMenuYazdir() {
    printf("==========================================================\n");
    printf("|                         Ana Menü                       |\n");
    printf("==========================================================\n");
    printf("1. Sınavlarım\n");
    printf("2. Duyrular\n");
    printf("3. Destek Masası\n");
    printf("4. Alıştırmalar\n");
    printf("5. Çıkış\n\n");
    printf("Seçiminizi girin: ");
}

// --------------Girilecek sayi kontrol yapan metod-------------- //

int girdiDogrula(int min, int max) {
    int girdi;
    scanf("%d", &girdi);
    while (girdi < min || girdi > max) {
        printf("Geçersiz giriş. Lütfen %d ve %d arasında bir sayı girin: ", min, max);
        scanf("%d", &girdi);
    }
    return girdi;
}

// --------------Destek Talepi oluşturan metodu-------------- //

void destekTalebiOlustur() {
    ekranTemizle();
    printf("==========================================================\n");
    printf("|                  Destek Talebi Oluştur                 |\n");
    printf("==========================================================\n");
    printf("Konu Başlığı: ");
    scanf("%s", destekTalepleri.konular[destekTalepleri.talepSayisi]);
    printf("Kategori: ");
    scanf("%s", destekTalepleri.kategoriler[destekTalepleri.talepSayisi]);
    printf("Detaylar: ");
    scanf("%s", destekTalepleri.detaylar[destekTalepleri.talepSayisi]);
    destekTalepleri.talepSayisi++;
    ekranTemizle();
    printf("Destek talebiniz gönderildi ✅. Destek ekibi kısa süre içinde sizinle iletişime geçecek.\n\n");
}

// --------------Destek talepleri gösteren metodu-------------- //

void destekTaleplerim() {
    ekranTemizle();
    printf("========================================================\n");
    printf("|                  Destek Taleplerim                   |\n");
    printf("========================================================\n");
    if (destekTalepleri.talepSayisi > 0) {
        for (int i = 0; i < destekTalepleri.talepSayisi; i++) {
            printf("Talep %d:\n", i + 1);
            printf("Konu Başlığı: %s\n", destekTalepleri.konular[i]);
            printf("Kategori: %s\n", destekTalepleri.kategoriler[i]);
            printf("Detaylar: %s\n", destekTalepleri.detaylar[i]);
            printf("=============\n\n");
        }
    } else {
        printf("Henüz mevcut bir destek talebiniz bulunmamaktadır.\n\n");
    }
}

// --------------yayınlanan sınavlar gösteren metodu-------------- //

void sinavlarim() {
    ekranTemizle();
    printf("==================================================\n");
    printf("|                   Sınavlarım                   |\n");
    printf("==================================================\n");

    if (sinavCounter > 0) {
        for (int i = 0; i < sinavCounter; ++i) {
            printf("%d. Sınav: %s\n", i + 1, sinavlar[i][0].sinavAdi);
        }
        printf("==================================================\n");
        printf("Sınavı başlatmak ister misiniz? Evet ise sınav numarasını girin, hayır ise 0'a basın: ");
        int secim;
        scanf("%d", &secim);
        getchar(); 

        if (secim > 0 && secim <= sinavCounter) {
            ekranTemizle();
            sinavGoster(secim - 1);
        } else if (secim == 0) {
            ekranTemizle();
            printf("Sınav başlatılmadı.\n");
        } else {
            printf("Geçersiz seçim!\n");
        }
    } else {
        printf("Henüz planlanmış bir sınavınız yok.\n\n");
    }
}

// --------------Duyrular gösteren metodu-------------- //

void duyrularim() {
    ekranTemizle();
    printf("==================================================\n");
    printf("|                   Duyrular                     |\n");
    printf("==================================================\n");
    if (duyrular.duyruCounter > 0) {
        duyruGoster();
    } else {
        printf("Henüz duyuru bulunmamaktadır.\n\n");
    }
}

// --------------Girilen alıştırmaları gösteren metodu-------------- //

void testSorulari() {
    ekranTemizle();
    printf("==================================================\n");
    printf("|                 Alıştırmalar                   |\n");
    printf("==================================================\n");
    if (yeniSoru.counter > 0) {
        sorulariGoster();
    }
    else {
        printf("Henüz Alıştırma bulunmamaktadır.\n\n");
    }
}

// --------------öğrenci menusu gösteren metodu-------------- //

int anaMenu() {
    do {
        anaMenuYazdir();
        secim = girdiDogrula(1, 5);

        switch (secim) {
        case 1:
            sinavlarim();
            break;
        case 2:
            duyrularim();
            break;
        case 3:
            ekranTemizle();
            printHeader("Destek Masası ");
            printf("1. Destek Taleplerim\n");
            printf("2. Destek Talebi Oluştur\n");
            printf("3. Ana Menü\n\n");
            printf("Seçiminizi girin: ");
            secim = girdiDogrula(1, 3);

            switch (secim) {
            case 1:
                destekTaleplerim();
                break;
            case 2:
                destekTalebiOlustur();
                break;
            case 3:
            ekranTemizle();
                break;
            }
            break;
        case 4:
            testSorulari();
            break;
        }
    } while (secim != 5);
    ekranTemizle();
    sistemSecimi();

    return 0;
}

// --------------Animation metodlari ve main metodu(Kullanıcı karşılama metodu)-------------- //

void printAnimatedText(const char *text, int delay) {
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay);
    }
}

void printCenteredText(const char *text, int delay) {
    int len = strlen(text);
    if (len < SCREEN_WIDTH) {
        int spaces = (SCREEN_WIDTH - len) / 2;
        for (int i = 0; i < spaces; i++) {
            printf(" ");
        }
    }
    printAnimatedText(text, delay);
}



void printWelcomeMessage() {
    const char *lines[] = {
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",
        "=-                                                     -=\n",
        "=-                                                     -=\n",
        " =-                   Sınav Sistemine                 -=\n",
        "  =-                   Hoş Geldiniz!                 -=\n",
        " =-                                                   -=\n",
        "=-                                                     -=\n",
        "=-                                                     -=\n",
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n"
    };
    int numLines = sizeof(lines) / sizeof(lines[0]);
    int delay = 20000; 

    for (int i = 0; i < numLines; i++) {
        printCenteredText(lines[i], delay); 
    }
}

void girisBasarili() {
    const char *lines[] = {
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",
        "     |    Giriş başarılı, Hoş geldiniz !       |\n",
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",
    };
    int numLines = sizeof(lines) / sizeof(lines[0]);
    int delay = 20000; 

    for (int i = 0; i < numLines; i++) {
        printCenteredText(lines[i], delay); 
    }
}

int main() {
    ekranTemizle();           
    printWelcomeMessage();   
    sleep(1);                
    ekranTemizle();
    sistemSecimi();

    return 0;
}

#endif
