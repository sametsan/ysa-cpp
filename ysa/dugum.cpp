
#include "dugum.hpp"

using namespace std;

namespace yz{

	dugum::dugum(int giris_adet,DUGUM_ISLEV islev){
		this->islev_tipi = islev;
		this->giris_adet = giris_adet;
		this->giris_deger.resize(giris_adet);
		this->agirliklar.assign(giris_adet,0.001);
	}

	dugum::~dugum(){


	}

	float dugum::islev(float deger){
		if(this->islev_tipi == SIGMOID){
			cout<<"Sigmoid"<<"->";
    		return (1/(1+exp(-1*deger))); // Sigmoid 
		}
		else if(this->islev_tipi == RELU){
			cout<<"Relu"<<endl;
			if(deger<=0) return 0;  else return 1; // RELU
		}
		else if(this->islev_tipi == LRELU){
			cout<<"Leakly Relu"<<endl;
			if(deger<0) return 0.001;  else return deger; // Leakly RELU
		}
		else{
			cout<<"Aktivasyon fonksiyonu seçilemedi."<<endl;
			exit(1);
		}
	}

	float dugum::turev(float deger){

		if(this->islev_tipi == SIGMOID){
			cout<<"Sigmoid"<<endl;
    		return 	deger * (1- deger); // Sigmoid 
		}
		else if(this->islev_tipi == RELU){
			cout<<"Relu"<<endl;
			return 0; // RELU
		}
		else if(this->islev_tipi == LRELU){
			cout<<"Leakly Relu"<<endl;
			if(deger<0) return 0;  else return 1; // Leakly RELU
		}
		else{
			cout<<"Aktivasyon fonksiyonu seçilemedi."<<endl;
			exit(1);
		}
	}

	float dugum::ag_cikis_hatasi(float cikis_hedef){
		this->cikis_hata = (cikis_hedef - this->sonuc) * this->sonuc * (1 - this->sonuc);
	}

	float dugum::katman_cikis_hatasi(float ag_cikis_hatasi,float cikis_agirlik){
		this->cikis_hata =  (ag_cikis_hatasi * cikis_agirlik) * this->sonuc * (1 - this->sonuc );
	}

	float dugum::ag_cikis_agirlik_hatasi(float ag_cikis_hatasi){
		for(int i=0;i<giris_deger.size();i++)
			this->agirlik_hata[i] = ag_cikis_hatasi * this-> giris_deger[i];
	}

	float dugum::katman_cikis_agirlik_hatasi(){
		for(int i=0;i<giris_deger.size();i++)
			this->agirlik_hata[i] = this->cikis_hata * this-> giris_deger[i];
	}

	float dugum::yeni_agirlik_degeri(float katman_dugum_cikis,float ag_cikis_hatasi){
		for(int i=0;i< agirliklar.size();i++)
			this->agirliklar[i] =this->agirliklar[i] * this->agirlik_hata[i];
	}

	float dugum::topla(){
		float s=0;	
		for(int j=0;j<this->giris_adet;j++){
			s = s+(this->giris_deger[j] * this->agirliklar[j]);
		}
		return s;
	}

	float dugum::hesapla(vector<float> giris_deger){
		this->giris_deger = giris_deger;
		cout<<"Giriş ";
		for(int i=0;i<giris_adet;i++)
			cout<<giris_deger[i]<<"|";
		this->toplam = this->topla();
		cout<<"Toplam "<<this->toplam<<"->";
		this->sonuc = this->islev(toplam);
		cout<<"Çıkış "<<this->sonuc<<endl;
	 	return this->sonuc;
	}

	float dugum::hesapla(float giris_deger){
		cout<<"Giriş "<<giris_deger<<"->";
	 	this->sonuc =  this->islev(giris_deger);
		cout<<"Çıkış "<<this->sonuc<<endl;
	 	return this->sonuc;
	}

	void dugum::egit(){

	}

}


