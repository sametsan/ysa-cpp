#include "katman.hpp"

using namespace std;


namespace yz{


	katman::katman(int giris_adet,int dugum_adet,DUGUM_ISLEV islev){

		this->cikis_deger.resize(dugum_adet);
		this->giris_adet = giris_adet;
		
		for(int i=0;i<dugum_adet;i++){
			cout<<"Düğüm "<<i<<"| İslev : "<<islev<<endl;
			this->dugumler.push_back(dugum(giris_adet,islev));
		}
	}

	katman::~katman(){


	}

	vector<float> katman::hesapla(vector<float> giris_deger){
		this->giris_deger = giris_deger;

		for(unsigned int i=0;i< this->dugumler.size();i++){
			cout<<"Düğüm "<<i<<" ";
			if(tipi == KATMAN_GIRIS)
				this->cikis_deger[i] = this->dugumler[i].hesapla(giris_deger[i]);
			else
				this->cikis_deger[i] = this->dugumler[i].hesapla(giris_deger);
		}

		return this->cikis_deger;

	}

	void katman::cikis_hatasi(){

		for(unsigned int i=0;i< this->dugumler.size();i++){
			cout<<"Düğüm "<<i<<" ";
			if(tipi == KATMAN_CIKIS)
				this->cikis_deger[i] = this->dugumler[i].ag_cikis_hatasi(giris_deger[i]);
			else
				this->cikis_deger[i] = this->dugumler[i].katman_cikis_hatasi(giris_deger);
		}
	}


	void katman::cikis_hatasi(){

		for(unsigned int i=0;i< this->dugumler.size();i++){
			cout<<"Düğüm "<<i<<" ";
			if(tipi == KATMAN_CIKIS)
				this->cikis_deger[i] = this->dugumler[i].ag_cikis_hatasi(giris_deger[i]);
			else
				this->cikis_deger[i] = this->dugumler[i].katman_cikis_hatasi(giris_deger);
		}
	}



	void katman::giris_yap(){
		this->tipi = KATMAN_GIRIS;
	}

	void katman::cikis_yap(){
		this->tipi = KATMAN_CIKIS;
	}



}