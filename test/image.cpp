#include "image.hpp"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>


using namespace std;

image::image(string adres){

	file_path = adres;
	//strcpy(file_path,adres);
	read();
}

image::~image(){

	free(matrix);
	free(data);
}


void image::read(){

	BMPHeader header;
	char info[56];

	ifstream fp(file_path,ios::binary);

	if(!fp.good()){
		cout<<"HATA : Resim dosyası bulunamadı."<<endl;
		exit(0) ;
	}

	cout<<"dosya açılıyor "<<file_path<<endl;

	//FILE* f = fopen(file_path, "rb");

	fp.read(&info[2],54);
	//fread(&info[2], sizeof(unsigned char), 54, f); // read the 54-byte header

	memcpy(&header,info,56);

	this->width = header.width_px;
	this->height = header.height_px;
	this->datasize = header.image_size_bytes;

	printf("Görüntü genişlik %d yükseklik %d kayıt başlangıcı %d boyut %d \n",this->width,this->height,header.offset,this->datasize);
/*
	fseek(f,header.offset,SEEK_SET);
	data = (unsigned char*)calloc(datasize,sizeof(unsigned char)); // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), datasize, f); // read the rest of the data at once
	fclose(f);*/

	this->data = (unsigned char*)calloc(this->datasize,sizeof(unsigned char));
	fp.seekg(header.offset,ios::beg);
	fp.read((char*)data,this->datasize);
	fp.close();


}


void image::to_matrix(){

	printf("Görüntü griye çevriliyor...\n");
	int R,G,B,C,A;

	this->matrix = (unsigned char**) calloc(height,sizeof(unsigned char*));
	for(int i=0;i<width;i++)
		this->matrix[i] = (unsigned char*) calloc(width,sizeof(unsigned char));

	int a=0;

	for(int i=this->height-1;i>=0 ;i--){
		for(int j=0;j<this->width;j++){

			B = 0.0722 * (int)data[a]; a++; 
			G = 0.7152 * (int)data[a]; a++; 
			R = 0.2126 * (int)data[a]; a++; 
			A = 0 * (int)data[a]; a++;

			C = R + G + B + A;

			if(C < (255/2))
				this->matrix[i][j]=255-C;
			
			else
				this->matrix[i][j]=255-C;


		}
	}
}


void image::trim(){

	int total;
	int top,left,right,bottom;


	for(int i=0;i< height;i++){
		total=0;
		for(int j=0;j< width;j++){
			total+= this->matrix[i][j];
		}

		if((total%width)!=0){
			top=i;
			break;
		}

	}


	for(int i=height-1 ;i >=0 ;i--){
		total=0;
		for(int j=0;j< width;j++){
			total+= this->matrix[i][j];
		}

		if((total%width)!=0){
			bottom=i;
			break;
		}

	}

	for(int i=0;i< width;i++){
		total=0;
		for(int j=0;j<height;j++){
			total+= this->matrix[j][i];
		}


		if((total%height)!=0){
			left = i;
			break;
		}

	}

	for(int i=width-1;i>=0;i--){
		total=0;
		for(int j=0;j<height;j++){
			total+= this->matrix[j][i];
		}

		if((total%height)!=0){
			right = i;
			break;
		}

	}

	int trim_width = right- left;
	int trim_height = bottom - top;

	unsigned char trim_matrix[trim_height][trim_width];

	for(int i=0; i <trim_height; i++){
		for(int j=0;j< trim_width;j++){

			trim_matrix[i][j] = this->matrix[i+top][j+left];
		}
	}

	unsigned char temp[this->height][this->width];
	
	float oranH = this->height / (float)trim_height;
	float oranW = this->width / (float)trim_width;
	int h,w;

	for(int i=0; i < height; i++){
		for(int j=0;j< width;j++){

			if((h=i/oranH) >= this->height) break;
			if((w=j/oranW) >= this->width) break;
			temp[i][j]= trim_matrix[h][w];
		}	
	}


	for(int i=0; i < height; i++){
		memcpy(this->matrix[i],temp[i],width);
	}


	for(int i=0;i< height;i++){

		for(int j=0;j<width;j++){

			printf("%d|", this->matrix[i][j]);			
		}	printf("\n");
	}



	//printf("\033[%d;%dH", (y), (x));


}




