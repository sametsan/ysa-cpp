#include <stdio.h>
#include <string.h>
#include "include/ysa.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace yz;


int main(int argc,char **args){

	vector<float> cikis;
	vector<float> giris;
	vector<int> yapi;

	cout<<"Önyüklemeler"<<endl;

	giris.push_back(0.34);
	giris.push_back(2.18);
	giris.push_back(0.78);
	giris.push_back(0.448);
	giris.push_back(0.965);
	giris.push_back(5.3134);
	giris.push_back(0.15558);
	giris.push_back(6.4348);
	giris.push_back(0.44458);
	giris.push_back(0.965);


	yapi.push_back(10);
	yapi.push_back(5);
	yapi.push_back(1);

	cout<<"Ağ oluşuyor.."<<endl;
	ysa ys(yapi,SIGMOID,1,1);

	cout<<"Ağ çalışıyor.."<<endl;
	cikis = ys.calistir(giris);


	cout<<"Çıkış"<<endl;
	for (unsigned int i = 0; i < cikis.size(); ++i)
	{
		cout<<cikis[i]<<endl;
	}


	ys.egit();
	
	return 0;
}