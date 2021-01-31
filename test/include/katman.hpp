#ifndef		KATMAN_HPP
#define 	KATMAN_HPP

#include <vector>
#include "dugum.hpp"

using namespace std;

namespace yz{

	enum KATMAN_TIPI{KATMAN_GIZLI,KATMAN_GIRIS,KATMAN_CIKIS};

	class katman{

	public:
		vector<dugum>	dugumler;
		katman(int,int,DUGUM_ISLEV);
		~katman();
		vector<float>	hesapla(vector<float>);
		vector<float>	giris_deger;
		vector<float>	cikis_deger;
		int 			giris_adet;
		KATMAN_TIPI 	tipi = KATMAN_GIZLI;
		void 			giris_yap();
		void 			cikis_yap();
	};


}


#endif