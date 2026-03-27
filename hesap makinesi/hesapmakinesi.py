"""
bir hesap makinesi
kullanıcı istediği sayıları işareti girer ve sonucu alır 
sonuc diğer işlemin birinci sayısı olarak tanımlanır ve 
üstüne işlem yapılmaya devam eder
eğer alınan sonuctan sonra işlem yerine = yazılır enter 
yapılırsa sonucunuz ... dır şeklinde cıktı versin
yapılcaklar:
    sonsuz döngü içinde 
    kullanıcıdan bi sayı alınır(1.sayı)
    ardından bir işaret alınır(*,/,+,-,=)
    5 if le hheangi işaret olduğuna bakılır(= ise işlem sonlanır)
    sonra bir sayı daha alınır(2.sayı)
    işaret sorgusu yapılır eşittirse sonuc gösterilir ve 
    1.sayıya atanır
    değilse sonuc gösterilmeden 1. sayıya atanır ve
    onun üstüne işlem yapılır
    ikinci sayı işaretten sonra tekrar girilir ve 
    sonuc ekrandayken sıradaki işlem = olana kadar bu 
    işlem devam eder
"""
islem=","
sonuc=0
sayi1=int(input("sayı giriniz:"))
islem=input("işleminiz nedir:")
while islem !="=":
    if(islem=="*"):
        sayi2=int(input("sayı giriniz:"))
        sonuc=sayi1*sayi2
    elif(islem=="**"):
        sonuc=sayi1**2
    elif(islem=="/"):
        sayi2=int(input("sayı giriniz:"))
        if (sayi1>sayi2):
            try:
                sonuc=sayi1/sayi2
            except ZeroDivisionError as hata:
                print("hatalı islem")
                print(hata)
                sonuc=sayi1
        else:
            sonuc=sayi1/sayi2
            print("sayınız birden küçüktür")
                
    elif(islem=="+"):
        sayi2=int(input("sayı giriniz:"))
        sonuc=sayi1+sayi2
    elif(islem=="-"):
        sayi2=int(input("sayı giriniz:"))
        sonuc=sayi1-sayi2
        if (sayi1>sayi2):
            sonuc=sayi1-sayi2
        else:
            print("sayınız negatiftir ")
            sonuc=sayi1-sayi2
    else:
        print("hatalı işlem girdiniz!!")
        islem="="
    print(f"sonucunuz={sonuc}")
    islem=input("sıradaki işleminiz nedir:")
    sayi1=sonuc  
    print(f"sonucunuz={sonuc}",)
    