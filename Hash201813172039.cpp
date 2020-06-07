// Bu kod DevC++ ile çalýþtýrýlmýþtýr.  


// Yiðitalp Dikmen 201813172039 2.Öðretim 2.Sýnýf Bilgisayar Mühendisliði

// Projemi GitHub Üzerinden de görüntüleyebilirsiniz : 

// https://github.com/YigitalpDikmen/C-Just-Hash-Table 


#include <iostream>
#include<locale.h> 
using namespace std;
static const int MAX = 10;

/* --------------------Burasý Çýrpýlama Hash Tablosu için Ana menüdeki 5 numaralý kýsýmýn Baþlangýcý --------------------------   */   

// constantýmý en üste koydum 10 olarak. 

class Dugum { // class tanýmlýyoruz 
public: // herkese açýk yapýyoruz 

//-------------------- Node düðüm yapýmýz ------------

    int Anahtar; //önceden veri diyorduk þimdi anahtar olarak adlandýrýyoruz. Çünkü bu veriye ulaþýrsak devamýnda barýndýrdýðý verilere de ulaþacaðýz. 
    Dugum* pSonraki; // bir sonraki düðümün verisini iþaret eden iþaretçi.  
    
//-------------------- Node düðüm yapýmýz ------------    
    
	Dugum(int Anahtar) // Constructorumuz 
    {
        this->Anahtar = Anahtar; // deðiþkenlerin karýþmamasý adýna this kullandýk. 
        pSonraki = NULL; // ilk baþta herhangi bir yeri iþaret etmiycek.  
    }
    
};
class HashTable { // Hash Tablosu için gerekli sýnýf. 
public: // Herkese açýk yaptýk. 
    Dugum* Veri[MAX]; //pointer dizisi. yani dizi adres tutacak
    HashTable(); //kurucu fonksiyon
    void Ekle(int Anahtar); //baðlý listelerde eklememe iþlemi pek yok, o yüzden void
    Dugum* Bul(int Anahtar);//düðümü komple getirecek.düðümün olmadýðýný Null ile anlayacaðýz
    void Sil(int Anahtar); // Silmek için kullanacaðýmýz fonksiyonu sýnýf içi tanýmladýk. 
};

HashTable::HashTable() // Constructorumuz 
{
    for (int i = 0; i < MAX; i++) // Max = 10 ise 0-9 arasý 10 tane slotumuz var ve bu slotlardaki tüm veriler birbiriyle baðlantýlý. En baþtaki null olursa devamý da null olur. 
        Veri[i] = NULL; // dolayýsýyla bu kýsým ile program ilk çalýþtýðýnda tüm tabloyu boþaltmýþ olacak. 
}


void HashTable::Ekle(int Anahtar) // Eleman ekleyici Hash fonksiyonu 
{
    Dugum* pYeni = new Dugum(Anahtar); // yeni düðüm
    int mod = Anahtar % MAX; // mod deðeri burada girilen elemanýn Max deðerine göre modu alýndýktan sonra çýkan sonuca göre diziye yerleþecek indexin deðeri oluyor. 
    if (!Veri[mod]) //ilgili hücrede bir adres var mý
    {//eðer varsa oaryaa baðlý bir baðlý liste var demektir
        Veri[mod] = pYeni;
        return;
    }
    //buraya geldiysek baðlý liste var:
    Dugum* pTemp = Veri[mod];//ilgili indisteki adres bilgisini pTemp'e atacaðýz.
    while (pTemp->pSonraki != NULL)
    {//son elemana kadar gideceðiz. Liste konusunda görmüþtük
        pTemp = pTemp->pSonraki;
    }
    pTemp->pSonraki = pYeni;//son düðüme yeni düðümü ekleyebiliriz.
}
Dugum* HashTable::Bul(int Anahtar)
{
    int mod = Anahtar % MAX;
    Dugum* pTemp = Veri[mod];
    while (pTemp != NULL)
    {//döngü burada düðümün kendisini kontrol edecek
        if (pTemp->Anahtar == Anahtar)//aradýðýmýz anahtar buysa adres dönecek
            return pTemp;
        pTemp = pTemp->pSonraki;
    }
    //listede aradýðýmýzý bulamadýk
    return NULL;
}

void HashTable::Sil(int Anahtar)//Kapalý adresleme yöntemi kullanacaðýz
{//Baðlý listelere benziyor
    int mod = Anahtar % MAX;
    //ilk durum hiç elemanýn(düðümün) olmadýðý durum
    if (!Veri[mod]) //Hiç bir elemanýn olmadýðý durum
    {
        return;
    }
    //buraya geldiysek en az 1 düðüm var
    //ilk düðümü çýkarmaya çalýþacaðýz:
    if (!Veri[mod]->pSonraki) //tek düðüm olma durumudur
    {
        if (Veri[mod]->Anahtar == Anahtar)
        {//tamam 1 düðüm var ama bu benim aradýðým düðüm mü.
        //Eðer öyle ise bu tek düðümü silelim
            delete Veri[mod]; //silicem ama yeterli deðil, çünkü adresini silmedik
            Veri[mod] = NULL; //NULL yapmazsam hafýza hatasýyla karþýlaþýrým,
             //çünkü orada düðüm var zannedecek
        }
        return; //aradýðýmýz düðümse veya deðilse her iki durumda da iþlemi bitiriyoruz
    }
    //buraya geldiysek birden fazla düðüm var demektir.
    //Birden fazla elemanýn(düðümün) olmasý durumu:
    if (Veri[mod]->Anahtar == Anahtar)
    {//birden fazla düðüm var ama ilk düðüm aradýðýmýz düðüm ve sileceðiz
    //ilk düðüm sileceðiz, dolayýsýyla baðlý olan sonraki düðüme baðlanmalýyý
        Dugum* pDon = Veri[mod]->pSonraki;//silinen düðüme baðlý olan düðüme ulaþamazdýk
        delete Veri[mod]; //silinen düðüm, þimdi ona baðlý olan düðüme baðlanalým:
        Veri[mod] = pDon;
        return;
    }
    //tek bir durum kaldý: aradýðýmýz düðüm arada bir yerde
    //Listelerdeki aradan çýkarmaya benziyor.
    Dugum* pTemp = Veri[mod];//öncelikle ilk düðümün adresini alýyorum pTemp içerisine.
    while (pTemp->pSonraki != NULL)//son düðüme gidecek kadar bir döngü yapýyoruz
    {
        if (pTemp->pSonraki->Anahtar == Anahtar)
        {//çýkaracaðýmýz düðümden önceki düðümün adresini bilmemiz gerekecek
            Dugum* pDon = pTemp->pSonraki; //düðümün adresini yedekliyoruz
            pTemp->pSonraki = pDon->pSonraki;//sonraki düðüme baðlýyoruz
            delete pDon;//silmek istediðimiz düðümü siliyoruz
            return;//silme iþlemi gerçeklendiðine göre return
        }//ilk düðüm deðilse while ile sonraki düðüme geçeceðiz:
        pTemp = pTemp->pSonraki;
    }
    //buraya geldiysek silinecek düðüm yok demektir.
}

/* --------------------Burasý Çýrpýlama Hash Tablosu için Ana menüdeki 5 numaralý kýsýmýn Sonu --------------------------   */
/* ------------------------------------------------- MAÝN FONKSÝYONUNA GÝRÝÞ !!!!!!!-------------------------------------- */


int main() {

setlocale(LC_ALL, "Turkish"); // LC_ALL diyerek tüm koddaki türkçe karakterleri görüntülenebilir yaptýk. LC_TIME vb. gibi farklý kullanýmlarý mevcuttur. 

/* Hash icin global degerler */  int cirpi_secim; int cirpi_dugum_eleman_ekle; int cirpi_dugum_eleman_sil; HashTable h;

   do { // bunlarý yap

                    cout<<" "<<endl;  // arayüz             
                    cout<<"1) Tabloya Eleman Ekle"<<endl; // arayüz 
                    cout<<"2) Tablodan Eleman Sil/Çýkar"<<endl; // arayüz 
                    cout<<"3) Tabloyu Temizle"<<endl; // arayüz 
                    cout<<"4) Tablodaki Eleman Sayýsýný Göster"<<endl;  // arayüz 
                    cout<<"5) Tablodaki Elemanlarý Göster"<<endl; // arayüz 
                    cout<<"6) Programdan Çýkýþ Yap "<<endl; // arayüz 


                    cout<<" Hash Tablosu Uygulamasýnda Yapmak istediðiniz iþlemin numarasýný tuþlayýnýz (1-6 arasý): "<<endl; // arayüz 


      cin>>cirpi_secim; // kullanýcýdan veri giriþi bekleniyor 
      switch(cirpi_secim) { // switch yapýsý 


         case 1: {   // 1'e basýlýr ise 

			    cout << "Tabloya eklemek istediðiniz elemanýn deðerini giriniz"<<endl;  // arayüz 
			    cin>>cirpi_dugum_eleman_ekle; // veri giriþi 
			    h.Ekle(cirpi_dugum_eleman_ekle); // eleman ekleme fonksiyonu 
			    
			    cout << "Eleman Eklenmiþtir"<<endl;  // arayüz 


            break;}



         case 2: { // 2'ye basýlýr ise 

			        cout << "Tablodaki Elemanlar Þunlardýr: (indis sýralamasýna göredir) "<<endl;  // arayüz 
			   
			   for (int i = 0; i <= 100000; i++) { // Maalesef 100000 e kadar olan elemanlarý bastýrabiliyor. Nasý bastýracaðýmý tam olarak kavrayamadým. 
			    Dugum* pTemp = h.Bul(i); // Constant Max'da kaç indis tanýmlanmýþ ise oraya kadar gider. Ve tüm elemanlarý bulur. 
			            //düðümleri yazdýralým:
                        while (pTemp != NULL)
                    {
                    	
                    	
                        cout << pTemp->Anahtar << " ";
                        pTemp = pTemp->pSonraki;
                               }
                           } 
                   
				   cout << " "<<endl;         // arayüz 
                   cout << "Çýkartmak Ýstediðiniz Elemanýn deðerini giriniz: "<<endl;    // arayüz 
				   cin>>cirpi_dugum_eleman_sil;     // veri giriþi  
				   h.Sil(cirpi_dugum_eleman_sil); // eleman silici fonksiyon 
				   				   
				   cout << "Eleman Çýkartýlmýþtýr"<<endl;  // arayüz 


            
            break;}


         case 3: {

			    	
			    for (int i = 0; i <= 100000; i++) {  // herþeyi siliyo 
			    	h.Sil(i); // silici fonksiyon 

                          }
			    	
			    	
			    	cout << "Tablo Temizlenmiþtir"<<endl;  // arayüz 


            
            break;}


         case 4: { // 4'e basýlýr ise 


			    	
			         int tablo_sayma = 0;
			   
			   for (int i = 0; i <= 100000; i++) {     // i <= MAX; böyle idi normalde 
			    Dugum* pTemp = h.Bul(i); // Constant Max'da kaç indis tanýmlanmýþ ise oraya kadar gider. Ve tüm elemanlarý bulur. 
			    
			            //düðümleri yazdýralým:
                        while (pTemp != NULL)
                    {
                        pTemp->Anahtar;

						tablo_sayma++;  
						
                        pTemp = pTemp->pSonraki;
                               }
                               
                               
                           }
                           
                if (tablo_sayma == 0){ // eðer 
                cout << "Tabloda Hiç Eleman Yoktur, Tablodaki Eleman Sayýsý: 0 "<<endl; } // arayüz 
                else{ // deðilse 
                cout << "Tablodaki Eleman Sayýsý: " << tablo_sayma <<endl; }   // arayüz  



            
            break; }

        case 5: { // 5'e basýlýr ise 

     
				if (0){}	
			    	
			    	
			   
			   else{	 
			   cout << "Tablodaki Elemanlar Þunlardýr: (indis sýralamasýna göredir) "<<endl;  // arayüz 
			   
			   for (int i = 0; i <= 100000; i++) {
			    Dugum* pTemp = h.Bul(i); // Constant Max'da kaç indis tanýmlanmýþ ise oraya kadar gider. Ve tüm elemanlarý bulur. 
			    
			            //düðümleri yazdýralým: 
                        while (pTemp != NULL) 
                    {
                        cout << pTemp->Anahtar << " ";
                        pTemp = pTemp->pSonraki;
                               }
                           }
                           
                       }
           
            break;}


        case 6: {
            cout<<"Çýkýþ yaptýnýz, konsol ekranýný kapatmak için herhangi bir tuþa basýnýz "<<endl; // arayüz 
            break; // döngüyü kýrar 
         }


        default: {
            cout<<"Yanlýþ Numara, Lütfen 1 ile 6 arasýnda bir deðer tuþlayýnýz"<<endl;
         }
      }
   }while(cirpi_secim!=6); // çýkýþý burasý saðlýyo 
      return 0; // main fonksiyonuna 0 yani false deðeri dönüyor ve uygulama sonlanmýþ oluyor.  
}  

/*--------------------------------- Son----------------------------- */     
/* Copyright Yiðitalp Dikmen 2020 TM Tüm Haklarý Saklýdýr */ 


