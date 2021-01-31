#include "ysa.hpp"


namespace yz{

	void printv(vector<float> v){
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			cout<<v[i]<<"|";
		}
		cout<<endl;
	}


	ysa::ysa(vector<int> katman_yapisi,DUGUM_ISLEV islev,int cikis_no,float cikis_hedef){
		cout<<"Katmanlar tanımlanıyor"<<endl;

		this->cikis_adet = katman_yapisi.back();
		this->giris_adet = katman_yapisi.front();

		this->katman_yapisi = katman_yapisi;

		this->cikis_hedef.resize(this->cikis_adet);
		this->cikis_deger.resize(this->cikis_adet);
		this->giris_deger.resize(this->giris_adet);

		this->cikis_deger.assign(cikis_adet,0);
		this->cikis_deger[cikis_no] = cikis_hedef;


		for(unsigned int i=0;i<katman_yapisi.size();i++)
		{			
			cout<<"Katman "<<i<<endl;
			this->katmanlar.push_back(katman(katman_yapisi[i==0?0:i-1],katman_yapisi[i],islev));
			cout<<"----------"<<endl;
		}

		this->katmanlar.front().giris_yap();
		this->katmanlar.back().cikis_yap();

	}

	ysa::~ysa(){


	}


	vector<float> ysa::calistir(vector<float> deger){

		if(deger.size() != this->giris_adet){
			cout<<"Giriş sayısı aynı değil"<<deger.size()<<"-"<<this->giris_adet<<endl;
			exit(0);
		}

		this->giris_deger = deger;

		for(unsigned int i=0;i<this->katmanlar.size();i++)
		{
			//printv(deger);
			cout<<"Katman "<<i<<" ";
			deger = this->katmanlar.at(i).hesapla(deger);
		}	

		printv(deger);
		this->cikis_deger = deger;
		return this->cikis_deger;
	}

	void ysa::egit(){

		unsigned int size;
		float cikis_hata;

		for(int i=0;i<this->katmanlar.back().dugumler.size();i++){
			this->katmanlar.back().dugumler[i].ag_cikis_hatasi(this->cikis_hedef[i]);
			cikis_hata = this->katmanlar.back().dugumler[i].cikis_hata;

			for(int k=this->katmanlar.size()-1; k>0;k++){
				size = this->katmanlar.at(k).dugumler.size();
				for(unsigned int d=0; d<size;d--){
				

				}
			}



		}



		



	}

	

}



