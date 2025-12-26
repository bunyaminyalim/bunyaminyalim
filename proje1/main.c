#include <stdio.h>
#include <string.h>

#define MAX_KULLANICI 10
#define KITAP_SAYISI 10

char kitaplar[KITAP_SAYISI][50] = {
"k1","k2","k3","k4","k5",
"k6","k7","k8","k9","k10",
};//KÝTAP ÝSÝMLERÝ DEÐÝÞEBÝLÝR VE PDF KISMINDA DEÐÝÞEN KÝTAPLARA GÖRE PDF EKLENEBÝLÝR
struct Kullanici {
    char kullaniciAdi[50];
    char sifre[50];
};
int matris[MAX_KULLANICI][KITAP_SAYISI]={0};

/* -------- ÜYE OL -------- */
void uye_ol(struct Kullanici uyeler[], int *uyeSayisi) {

    char yeniKullaniciAdi[50];
    int i;

    if (*uyeSayisi >= MAX_KULLANICI) {
        printf("Uye limiti dolu!\n");
        return;
    }

    printf("Kullanici adi: ");
    fgets(yeniKullaniciAdi, 50, stdin);
    yeniKullaniciAdi[strcspn(yeniKullaniciAdi, "\n")] = 0;

    for (i = 0; i < *uyeSayisi; i++) {
        if (strcmp(uyeler[i].kullaniciAdi, yeniKullaniciAdi) == 0) {
            printf("Bu kullanici adi zaten var!\n");
            return;
        }
    }

    strcpy(uyeler[*uyeSayisi].kullaniciAdi, yeniKullaniciAdi);

    printf("Sifre: ");
    scanf("%49s", uyeler[*uyeSayisi].sifre);
    getchar();
    
    FILE *dosya = fopen("uyeler.txt", "a");

	if (dosya == NULL) {
	    printf("Dosya acilamadi!\n");
	    return;
	}
	
	fprintf(dosya, "%s %s\n",uyeler[*uyeSayisi].kullaniciAdi,uyeler[*uyeSayisi].sifre);

	fclose(dosya);


    (*uyeSayisi)++;
    printf("Uye olma basarili!\n");
}

/* -------- GÝRÝÞ YAP -------- */
int giris_yap(struct Kullanici uyeler[], int uyeSayisi) {

    char girisKullanici[50];
    char girisSifre[50];
    int i;

    printf("Kullanici adi: ");
    fgets(girisKullanici, 50, stdin);
    girisKullanici[strcspn(girisKullanici, "\n")] = 0;

    printf("Sifre: ");
    scanf("%49s", girisSifre);
    

    for (i = 0; i < uyeSayisi; i++) {
        if (strcmp(uyeler[i].kullaniciAdi, girisKullanici) == 0 &&
            strcmp(uyeler[i].sifre, girisSifre) == 0) {
            printf("Hosgeldin %s\n", girisKullanici);
            return i;
        }
    }

    printf("Giris basarisiz!\n");
    return -1;
}

/* -------- KÝTAP MENÜSÜ -------- */
void kitap_menu(int uyeID) {

    int secim, pdfSecim, secim2;
    int i;
    char kitap[50];
    char adres[100];

    while (1) {

        printf("\n--- KITAP MENU ---\n");
        printf("1) Kitap ismi gir\n");
        printf("2) Giris ekranina don\n");
        printf("3) Kitaplarim\n");
        printf("Secim: ");
        scanf("%d", &secim);
        getchar();

        if (secim == 1) {

            int kitapIndex = -1;
            int alinanKitapSayisi = 0;

            printf("Kitap adi gir: ");
            fgets(kitap, 50, stdin);
            
            kitap[strcspn(kitap, "\n")] = 0;

            for (i = 0; i < KITAP_SAYISI; i++) {
                if (strcmp(kitap, kitaplar[i]) == 0) {
                    kitapIndex = i;
                    break;
                }
            }

            if (kitapIndex == -1) {
                printf("Bu kitap kutuphanede yok!\n");
                continue;
            }

            

            printf("PDF ister misin? (1=Evet, 2=Hayir): ");
            scanf("%d", &pdfSecim);
            

            if (pdfSecim == 1) {
                printf("PDF acildi.\n");
            }
            else if (pdfSecim == 2) {
            	
            	for (i = 0; i < KITAP_SAYISI; i++) {
                if (matris[uyeID][i] == 1)
                    alinanKitapSayisi++;
            }

            if (alinanKitapSayisi >= 3) {
                printf("AYNI ANDA EN FAZLA 3 KITAP ALABILIRSIN!\n");
                continue;
            }

            if (matris[uyeID][kitapIndex] == 1) {
                printf("Bu kitabi zaten almissin!\n");
                continue;
            }

                printf("Siparis=1, Ayirt=2: ");
                scanf("%d", &secim2);
                

                if (secim2 == 1) {
                    printf("Adres: ");
                    fgets(adres, 100, stdin);
                    adres[strcspn(adres, "\n")] = 0;
                    printf("Adresinize gonderilecek.\n");
                }
                else if (secim2 == 2) {
                    printf("kitap ayrildi.\n");
                }

                matris[uyeID][kitapIndex] = 1;
                printf("kitap basariyla alindi.\n");
            }
        }

        else if (secim == 2) {
            break;
        }

        else if (secim == 3) {
            printf("\n--- KITAPLARIM ---\n");
            int bos = 1;
            for (i = 0; i < KITAP_SAYISI; i++) {
                if (matris[uyeID][i] == 1) {
                    printf("- %s\n", kitaplar[i]);
                    bos = 0;
                }
            }
            if (bos)
                printf("hic kitap Yok.\n");
        }

        else {
            printf("Gecersiz Secim!\n");
        }
    }
}

/* -------- DOSYA ÝÞLEMLERÝ -------- */
void uyeleri_dosyadan_yukle(struct Kullanici uyeler[], int *uyeSayisi) {
    FILE *dosya = fopen("uyeler.txt", "r");

    if (dosya == NULL) {
        return; 
    }

    while (fscanf(dosya, "%49s %49s",
                  uyeler[*uyeSayisi].kullaniciAdi,
                  uyeler[*uyeSayisi].sifre) == 2) {

        (*uyeSayisi)++;

        if (*uyeSayisi >= MAX_KULLANICI)
            break;
    }

    fclose(dosya);
}

void dosya_temizle() {
    FILE *dosya = fopen("uyeler.txt", "w");
    if (dosya != NULL) {
        fclose(dosya);
    }
}

/* -------- MAÝN -------- */
int main() {

    struct Kullanici uyeler[MAX_KULLANICI];
    int uyeSayisi = 0;
    uyeleri_dosyadan_yukle(uyeler, &uyeSayisi);

    int anaSecim;
    

    while (1) {

        printf("\n--- ANA MENU ---\n");
        printf("1) Uye Ol\n");
        printf("2) Giris Yap\n");
        printf("3) Cikis Yap\n");
        printf("Secim: ");
        scanf("%d", &anaSecim);
        getchar();

        if (anaSecim == 1) {

            uye_ol(uyeler, &uyeSayisi);

        } 
        else if (anaSecim == 2) {
			int id = giris_yap(uyeler, uyeSayisi);
            if (id != -1)
                kitap_menu(id);
        } 
        else if (anaSecim == 3) {
        	 int temizle;
   			 printf("cikarken uye kayitlari silinsin mi?\n");
   			 printf("1 = Evet, 2 = Hayir: ");
   			 scanf("%d", &temizle);
   			 

   			 if (temizle == 1) {
    			    dosya_temizle();
    			    printf("dosya temizlendi.\n");
   			 } else {
     			    printf("dosya korunuyor.\n");
    		 }
        	 break;
		}
        else {
        	
            printf("Gecersiz Secim.\n");
        }
    }
}

