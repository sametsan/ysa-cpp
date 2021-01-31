#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "image.hpp"
#include "ysa.hpp"
#include <sys/types.h>
#include <dirent.h>

using namespace std;

int main(int argc,char **args){

	if(argc < 2){
		cout<<"HATA : Bir model adresi girin. \n Örnek : "<<args[0]<<" model.json "<<endl;
		return 0;
	}


	ysa ys(args[1]);
	DIR *dp,*rp;
	struct dirent *dc,*rdc;  
	string  raw_folder;

	// Starting 
	cout<<("Liste açılıyor...\n");

	dp = opendir (RAWS_FOLDER);
	int id=0;



	while((dc=readdir(dp))){
		if(strcmp(dc->d_name,".")!=0 && strcmp(dc->d_name,"..")!=0){

			raw_folder = string(RAWS_FOLDER) + dc->d_name +"/" ;

			rp = opendir (raw_folder.c_str());
			while((rdc=readdir(rp))){
				if(strcmp(rdc->d_name,".")!=0 && strcmp(rdc->d_name,"..")!=0){

					//Network reset
					ys.network_reset();

					printf("%d Başlıyoruz...-------------------------------------------\n",id);

					// Image open and read
					printf("Resim okunuyor...\n");
					image img(raw_folder + rdc->d_name);

					// Do Image hash
					printf("Matris oluşturmaya başlıyor...\n");
					img.to_matrix();
					img.trim();
			
					// Image hash convert to input data
					printf("Resim giriş olarak ayarlanıyor...\n");
					ys.ImageToInput(&img);

					// Output set
					ys.output_set(id);

					// network calculating
					printf("Ağ ağırlıkları hesaplanıyor...\n");
					ys.training();
					printf("Ağ eğitimi tamamlandı. \n");

					// YSA data save
					printf("Data kaydediliyor...\n");
					ys.data_add(id,dc->d_name);

				}
			}
			id++;

		}	
	}

	return 0;
}