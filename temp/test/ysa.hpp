#ifndef YSA_HPP
#define YSA_HPP

#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include "image.hpp"
#include "config.hpp"
#include <iostream>
#include "json11.hpp"

using namespace std;

class ysa{


private:

	typedef struct{
		int inputsize;
		int outputsize;
		int nodesize;
		int offset=0;
		float error_tolerance;
		float output_target_value;
		string activation;
		string data_file;
		float start_weight;
		int epoch_limit;
	}__model;


	typedef struct 
	{
		int id;
		char name[30];
		float **w;
		float **wo;
	}__network;

	typedef struct {
		// Errors
		float *eo;
		float *e;
	}__errors;

	typedef struct
	{
		float error;
		int  id;
		char name[30];
		
	}__result;

	void data_create();
	float calcE(float value,float errorX,float weight);
	float calcEo(float value,float b);
	float calcNewW(float value,float error,float weight);
	float total(float *i,float* w,int len);
	float func(float x);
	void   allocation();
public:

	float *input;
	float *output;
	float *node_output;
	float *output_target;

	__network 	network;
	__model		model;
	__errors 	errors;
	__result	result;

	ysa(string);
	~ysa();
	void run();
	int isOk();
	void training();

	void network_reset();
	void output_set(int id);
	void data_add(int id,char *name);
	int data_load();
	void ImageToInput(image *img);
	void model_load(string);
};




#endif