#ifndef		YSA_HPP
#define		YSA_HPP

#include <iostream>
#include <stdlib.h>
#include "dugum.hpp"
#include <vector>
#include "katman.hpp"


using namespace std;


namespace yz{

	
	class ysa{

	public:	
		ysa(vector<int>,DUGUM_ISLEV,int,float);					//ag({3,54,75,56},DUGUM_ISLEV.SIGMOID);
		~ysa();
		vector<float>						giris_deger;
		vector<float>						cikis_deger;
		float 								cikis_hatasi;
		unsigned int 						cikis_adet;
		unsigned int 						giris_adet;
		unsigned int 						cikis_no;
		vector<float> 						cikis_hedef;
		katman								*giris_katman; 
		katman								*cikis_katman; 
		vector<katman>						katmanlar; 
		vector<int>							katman_yapisi;
		vector<float>						calistir(vector<float>);
		void 								egit();

	};


}


#endif