
#include "baglanti.hpp"

namespace ysa{


	baglanti::baglanti(float agirlik){
		this->agirlik = agirlik;
	}

	baglanti::~baglanti(){

	}

	float	baglanti::hesapla(float deger){
		return this->agirlik * deger;
	}

}