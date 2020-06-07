// Bu kod DevC++ ile �al��t�r�lm��t�r.  


// Yi�italp Dikmen 201813172039 2.��retim 2.S�n�f Bilgisayar M�hendisli�i

// Projemi GitHub �zerinden de g�r�nt�leyebilirsiniz : 

// https://github.com/YigitalpDikmen/C-Just-Hash-Table 


#include <iostream>
#include<locale.h> 
using namespace std;
static const int MAX = 10;

/* --------------------Buras� ��rp�lama Hash Tablosu i�in Ana men�deki 5 numaral� k�s�m�n Ba�lang�c� --------------------------   */   

// constant�m� en �ste koydum 10 olarak. 

class Dugum { // class tan�ml�yoruz 
public: // herkese a��k yap�yoruz 

//-------------------- Node d���m yap�m�z ------------

    int Anahtar; //�nceden veri diyorduk �imdi anahtar olarak adland�r�yoruz. ��nk� bu veriye ula��rsak devam�nda bar�nd�rd��� verilere de ula�aca��z. 
    Dugum* pSonraki; // bir sonraki d���m�n verisini i�aret eden i�aret�i.  
    
//-------------------- Node d���m yap�m�z ------------    
    
	Dugum(int Anahtar) // Constructorumuz 
    {
        this->Anahtar = Anahtar; // de�i�kenlerin kar��mamas� ad�na this kulland�k. 
        pSonraki = NULL; // ilk ba�ta herhangi bir yeri i�aret etmiycek.  
    }
    
};
class HashTable { // Hash Tablosu i�in gerekli s�n�f. 
public: // Herkese a��k yapt�k. 
    Dugum* Veri[MAX]; //pointer dizisi. yani dizi adres tutacak
    HashTable(); //kurucu fonksiyon
    void Ekle(int Anahtar); //ba�l� listelerde eklememe i�lemi pek yok, o y�zden void
    Dugum* Bul(int Anahtar);//d���m� komple getirecek.d���m�n olmad���n� Null ile anlayaca��z
    void Sil(int Anahtar); // Silmek i�in kullanaca��m�z fonksiyonu s�n�f i�i tan�mlad�k. 
};

HashTable::HashTable() // Constructorumuz 
{
    for (int i = 0; i < MAX; i++) // Max = 10 ise 0-9 aras� 10 tane slotumuz var ve bu slotlardaki t�m veriler birbiriyle ba�lant�l�. En ba�taki null olursa devam� da null olur. 
        Veri[i] = NULL; // dolay�s�yla bu k�s�m ile program ilk �al��t���nda t�m tabloyu bo�altm�� olacak. 
}


void HashTable::Ekle(int Anahtar) // Eleman ekleyici Hash fonksiyonu 
{
    Dugum* pYeni = new Dugum(Anahtar); // yeni d���m
    int mod = Anahtar % MAX; // mod de�eri burada girilen eleman�n Max de�erine g�re modu al�nd�ktan sonra ��kan sonuca g�re diziye yerle�ecek indexin de�eri oluyor. 
    if (!Veri[mod]) //ilgili h�crede bir adres var m�
    {//e�er varsa oaryaa ba�l� bir ba�l� liste var demektir
        Veri[mod] = pYeni;
        return;
    }
    //buraya geldiysek ba�l� liste var:
    Dugum* pTemp = Veri[mod];//ilgili indisteki adres bilgisini pTemp'e ataca��z.
    while (pTemp->pSonraki != NULL)
    {//son elemana kadar gidece�iz. Liste konusunda g�rm��t�k
        pTemp = pTemp->pSonraki;
    }
    pTemp->pSonraki = pYeni;//son d���me yeni d���m� ekleyebiliriz.
}
Dugum* HashTable::Bul(int Anahtar)
{
    int mod = Anahtar % MAX;
    Dugum* pTemp = Veri[mod];
    while (pTemp != NULL)
    {//d�ng� burada d���m�n kendisini kontrol edecek
        if (pTemp->Anahtar == Anahtar)//arad���m�z anahtar buysa adres d�necek
            return pTemp;
        pTemp = pTemp->pSonraki;
    }
    //listede arad���m�z� bulamad�k
    return NULL;
}

void HashTable::Sil(int Anahtar)//Kapal� adresleme y�ntemi kullanaca��z
{//Ba�l� listelere benziyor
    int mod = Anahtar % MAX;
    //ilk durum hi� eleman�n(d���m�n) olmad��� durum
    if (!Veri[mod]) //Hi� bir eleman�n olmad��� durum
    {
        return;
    }
    //buraya geldiysek en az 1 d���m var
    //ilk d���m� ��karmaya �al��aca��z:
    if (!Veri[mod]->pSonraki) //tek d���m olma durumudur
    {
        if (Veri[mod]->Anahtar == Anahtar)
        {//tamam 1 d���m var ama bu benim arad���m d���m m�.
        //E�er �yle ise bu tek d���m� silelim
            delete Veri[mod]; //silicem ama yeterli de�il, ��nk� adresini silmedik
            Veri[mod] = NULL; //NULL yapmazsam haf�za hatas�yla kar��la��r�m,
             //��nk� orada d���m var zannedecek
        }
        return; //arad���m�z d���mse veya de�ilse her iki durumda da i�lemi bitiriyoruz
    }
    //buraya geldiysek birden fazla d���m var demektir.
    //Birden fazla eleman�n(d���m�n) olmas� durumu:
    if (Veri[mod]->Anahtar == Anahtar)
    {//birden fazla d���m var ama ilk d���m arad���m�z d���m ve silece�iz
    //ilk d���m silece�iz, dolay�s�yla ba�l� olan sonraki d���me ba�lanmal�y�
        Dugum* pDon = Veri[mod]->pSonraki;//silinen d���me ba�l� olan d���me ula�amazd�k
        delete Veri[mod]; //silinen d���m, �imdi ona ba�l� olan d���me ba�lanal�m:
        Veri[mod] = pDon;
        return;
    }
    //tek bir durum kald�: arad���m�z d���m arada bir yerde
    //Listelerdeki aradan ��karmaya benziyor.
    Dugum* pTemp = Veri[mod];//�ncelikle ilk d���m�n adresini al�yorum pTemp i�erisine.
    while (pTemp->pSonraki != NULL)//son d���me gidecek kadar bir d�ng� yap�yoruz
    {
        if (pTemp->pSonraki->Anahtar == Anahtar)
        {//��karaca��m�z d���mden �nceki d���m�n adresini bilmemiz gerekecek
            Dugum* pDon = pTemp->pSonraki; //d���m�n adresini yedekliyoruz
            pTemp->pSonraki = pDon->pSonraki;//sonraki d���me ba�l�yoruz
            delete pDon;//silmek istedi�imiz d���m� siliyoruz
            return;//silme i�lemi ger�eklendi�ine g�re return
        }//ilk d���m de�ilse while ile sonraki d���me ge�ece�iz:
        pTemp = pTemp->pSonraki;
    }
    //buraya geldiysek silinecek d���m yok demektir.
}

/* --------------------Buras� ��rp�lama Hash Tablosu i�in Ana men�deki 5 numaral� k�s�m�n Sonu --------------------------   */
/* ------------------------------------------------- MA�N FONKS�YONUNA G�R�� !!!!!!!-------------------------------------- */


int main() {

setlocale(LC_ALL, "Turkish"); // LC_ALL diyerek t�m koddaki t�rk�e karakterleri g�r�nt�lenebilir yapt�k. LC_TIME vb. gibi farkl� kullan�mlar� mevcuttur. 

/* Hash icin global degerler */  int cirpi_secim; int cirpi_dugum_eleman_ekle; int cirpi_dugum_eleman_sil; HashTable h;

   do { // bunlar� yap

                    cout<<" "<<endl;  // aray�z             
                    cout<<"1) Tabloya Eleman Ekle"<<endl; // aray�z 
                    cout<<"2) Tablodan Eleman Sil/��kar"<<endl; // aray�z 
                    cout<<"3) Tabloyu Temizle"<<endl; // aray�z 
                    cout<<"4) Tablodaki Eleman Say�s�n� G�ster"<<endl;  // aray�z 
                    cout<<"5) Tablodaki Elemanlar� G�ster"<<endl; // aray�z 
                    cout<<"6) Programdan ��k�� Yap "<<endl; // aray�z 


                    cout<<" Hash Tablosu Uygulamas�nda Yapmak istedi�iniz i�lemin numaras�n� tu�lay�n�z (1-6 aras�): "<<endl; // aray�z 


      cin>>cirpi_secim; // kullan�c�dan veri giri�i bekleniyor 
      switch(cirpi_secim) { // switch yap�s� 


         case 1: {   // 1'e bas�l�r ise 

			    cout << "Tabloya eklemek istedi�iniz eleman�n de�erini giriniz"<<endl;  // aray�z 
			    cin>>cirpi_dugum_eleman_ekle; // veri giri�i 
			    h.Ekle(cirpi_dugum_eleman_ekle); // eleman ekleme fonksiyonu 
			    
			    cout << "Eleman Eklenmi�tir"<<endl;  // aray�z 


            break;}



         case 2: { // 2'ye bas�l�r ise 

			        cout << "Tablodaki Elemanlar �unlard�r: (indis s�ralamas�na g�redir) "<<endl;  // aray�z 
			   
			   for (int i = 0; i <= 100000; i++) { // Maalesef 100000 e kadar olan elemanlar� bast�rabiliyor. Nas� bast�raca��m� tam olarak kavrayamad�m. 
			    Dugum* pTemp = h.Bul(i); // Constant Max'da ka� indis tan�mlanm�� ise oraya kadar gider. Ve t�m elemanlar� bulur. 
			            //d���mleri yazd�ral�m:
                        while (pTemp != NULL)
                    {
                    	
                    	
                        cout << pTemp->Anahtar << " ";
                        pTemp = pTemp->pSonraki;
                               }
                           } 
                   
				   cout << " "<<endl;         // aray�z 
                   cout << "��kartmak �stedi�iniz Eleman�n de�erini giriniz: "<<endl;    // aray�z 
				   cin>>cirpi_dugum_eleman_sil;     // veri giri�i  
				   h.Sil(cirpi_dugum_eleman_sil); // eleman silici fonksiyon 
				   				   
				   cout << "Eleman ��kart�lm��t�r"<<endl;  // aray�z 


            
            break;}


         case 3: {

			    	
			    for (int i = 0; i <= 100000; i++) {  // her�eyi siliyo 
			    	h.Sil(i); // silici fonksiyon 

                          }
			    	
			    	
			    	cout << "Tablo Temizlenmi�tir"<<endl;  // aray�z 


            
            break;}


         case 4: { // 4'e bas�l�r ise 


			    	
			         int tablo_sayma = 0;
			   
			   for (int i = 0; i <= 100000; i++) {     // i <= MAX; b�yle idi normalde 
			    Dugum* pTemp = h.Bul(i); // Constant Max'da ka� indis tan�mlanm�� ise oraya kadar gider. Ve t�m elemanlar� bulur. 
			    
			            //d���mleri yazd�ral�m:
                        while (pTemp != NULL)
                    {
                        pTemp->Anahtar;

						tablo_sayma++;  
						
                        pTemp = pTemp->pSonraki;
                               }
                               
                               
                           }
                           
                if (tablo_sayma == 0){ // e�er 
                cout << "Tabloda Hi� Eleman Yoktur, Tablodaki Eleman Say�s�: 0 "<<endl; } // aray�z 
                else{ // de�ilse 
                cout << "Tablodaki Eleman Say�s�: " << tablo_sayma <<endl; }   // aray�z  



            
            break; }

        case 5: { // 5'e bas�l�r ise 

     
				if (0){}	
			    	
			    	
			   
			   else{	 
			   cout << "Tablodaki Elemanlar �unlard�r: (indis s�ralamas�na g�redir) "<<endl;  // aray�z 
			   
			   for (int i = 0; i <= 100000; i++) {
			    Dugum* pTemp = h.Bul(i); // Constant Max'da ka� indis tan�mlanm�� ise oraya kadar gider. Ve t�m elemanlar� bulur. 
			    
			            //d���mleri yazd�ral�m: 
                        while (pTemp != NULL) 
                    {
                        cout << pTemp->Anahtar << " ";
                        pTemp = pTemp->pSonraki;
                               }
                           }
                           
                       }
           
            break;}


        case 6: {
            cout<<"��k�� yapt�n�z, konsol ekran�n� kapatmak i�in herhangi bir tu�a bas�n�z "<<endl; // aray�z 
            break; // d�ng�y� k�rar 
         }


        default: {
            cout<<"Yanl�� Numara, L�tfen 1 ile 6 aras�nda bir de�er tu�lay�n�z"<<endl;
         }
      }
   }while(cirpi_secim!=6); // ��k��� buras� sa�l�yo 
      return 0; // main fonksiyonuna 0 yani false de�eri d�n�yor ve uygulama sonlanm�� oluyor.  
}  

/*--------------------------------- Son----------------------------- */     
/* Copyright Yi�italp Dikmen 2020 TM T�m Haklar� Sakl�d�r */ 


