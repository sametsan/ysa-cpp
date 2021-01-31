#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "image.hpp"
#include "ysa.hpp"
#include <dirent.h>
#include <iostream>

using namespace std;

char data_file[50];

int main(int argc,char **args){

	// Başlıyoruz
	cout<<"Başlıyoruz..."<<endl;

	if(argc < 3){
		cout<<"HATA : Bir bmp dosyası adresi ve model adresi girin. \n Örnek : "<<args[0]<<" model.json example/1.bmp"<<endl;
		return 0;
	}

	char name[5];

	cout<<"Resim okunuyor..."<<endl;
	image img(args[2]);

	cout<<"Ağ oluşturuluyor..."<<endl;
	ysa ys(args[1]);

	// Resim hash işlemi
	printf("Matris oluşturmaya başlıyor...\n");
	img.to_matrix();
	img.trim();

	// Image hash convert to input data
	printf("Resim giriş olarak ayarlanıyor...\n");
	ys.ImageToInput(&img);

   //	dir = opendir (data_folder);

	float k;

	printf("Ağ çalışıyor...\n");
  	while(ys.data_load()==true){

		ys.run();

		for(int j=0;j<ys.model.outputsize;j++){
			cout<<ys.output[j]<<"|"; 
		}	cout<<endl;

		for(int j=0;j<ys.model.outputsize;j++){
			k = (ys.model.output_target_value - ys.model.error_tolerance ) - ys.output[j];
			if(k < 0) k = k * -1;
			if(k <  ys.result.error) { strcpy(ys.result.name,ys.network.name); ys.result.error=k; ys.result.id = ys.network.id; cout<<"----"<<endl;}

		}
   	}



   	printf("------------------------------------------------\n");
    cout<< img.file_path<<" dosyasındaki sayı : "<<ys.result.name<<endl;
    cout<<"Hata payı : "<<ys.result.error<<endl;

    cout<<"Sonuç doğru ise (E). Yanlış ise (H)ye basın."<<endl;
    char res = getchar();

    int id=ys.result.id;

    if(res!='E' && res!='e'){
    	cout<<"Bir isim giriniz : ";
    	cin>>name;
    	id++;
    }

	ys.output_set(id);
	ys.training();
	ys.data_add(id,name);

	return 0;
}