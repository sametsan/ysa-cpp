#ifndef		DUGUM_HPP
#define		DUGUM_HPP

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

namespace yz{

	enum DUGUM_ISLEV{SIGMOID,RELU,LRELU};

	class dugum{

	public:
		dugum(int,DUGUM_ISLEV);
		~dugum();
		float			hesapla(vector<float>);
		float			hesapla(float);
		float			islev(float);
		float			topla();
		float 			turev(float);
		void 			egit();
		float 			ag_cikis_hatasi(float);
		float 			katman_cikis_hatasi(float,float);
		float 			ag_cikis_agirlik_hatasi(float);
		float 			katman_cikis_agirlik_hatasi();
		float 			yeni_agirlik_degeri(float,float);
		float			cikis_hata;
		vector<float>	giris_deger;
		vector<float>	agirliklar;
		vector<float>	agirlik_hata;
		int				giris_adet;
		DUGUM_ISLEV		islev_tipi;
		float			sonuc;
		float			toplam;
	};


}


#endif