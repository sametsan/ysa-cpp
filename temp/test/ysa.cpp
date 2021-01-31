
#include "ysa.hpp"

using namespace json11;
using namespace std;

ysa::ysa(string model_file){

	model_load(model_file);
	allocation();
	network_reset();
}	


void ysa::allocation(){

	input = (float*) calloc(sizeof(float),model.inputsize);
	output_target = (float*) calloc(sizeof(float),model.outputsize);
	node_output = (float*) calloc(sizeof(float),model.nodesize);
	output = (float*) calloc(sizeof(float),model.outputsize);
	errors.eo = (float*) calloc(sizeof(float),model.outputsize);
	errors.e = (float*) calloc(sizeof(float),model.nodesize);

	network.w = (float**) calloc(sizeof(float*),model.nodesize);
	for(int i=0;i<model.nodesize;i++)
		network.w[i] = (float*) calloc(sizeof(float),model.inputsize);

	network.wo = (float**) calloc(sizeof(float*),model.outputsize);
	for(int i=0;i<model.outputsize;i++)
		network.wo[i] = (float*) calloc(sizeof(float),model.nodesize);

}

void ysa::network_reset(){
	
	// Ağ ağırlıkları tanımlama
	for(int i=0;i<model.nodesize;i++){
		for(int j=0;j<model.inputsize;j++){
			network.w[i][j]=model.start_weight;
			//printf("%f\n",network.w[i][j] );
		}
	}


	for(int i=0;i<model.outputsize;i++){
		for(int j=0;j<model.nodesize;j++){
			network.wo[i][j]=model.start_weight;
		}	
	}

	result.error=0.5;

	memset(output_target,0,model.outputsize*sizeof(float));
	memset(input,0,model.inputsize*sizeof(float));
	memset(node_output,0,model.nodesize*sizeof(float));
	memset(output,0,model.outputsize*sizeof(float));
	memset(errors.eo,0,model.outputsize*sizeof(float));
	memset(errors.e,0,model.nodesize*sizeof(float));
	memset(network.name,0,sizeof(network.name));
}

ysa::~ysa(){

	free(input);
	free(output_target);
	free(node_output);
	free(output);
	free(errors.e);
	free(errors.eo);

	for(int i=0;i<model.nodesize;i++)
		free(network.w[i]); 

	for(int i=0;i<model.outputsize;i++)
		free(network.wo[i]); 

	free(network.w);
	free(network.wo);

}

void ysa::output_set(int id){
	// ID nolu çıkışı öntanımlı değeri ver.
	output_target[id]=model.output_target_value;
	cout<<id<<" çıkış değeri "<<output_target[id]<<" yapıldı."<<endl;
}


float ysa::calcE(float value,float error,float weight){
	// Hata değeri hesapla.
	// value : Çıkış değeri 
	// error : hata değeri
	// weight : ağırlık
	return  value * (1 - value) * weight * error ;
}

float ysa::calcEo(float value,float b){
	// Çıkış katı hata değeri hesaplama
	// value : çıkış değeri
	// b = Beklenen değer.
	float y;
	float e = -1*(b - value);

	if(model.activation == "sigmoid"){
		y = value * (1- value) *e;
	}
	else if(model.activation == "leaky_relu"){
		if(value<0) y=0;  else y=1; // Leakly RELU
	}
	else if(model.activation == "relu"){
		 y=0;   //  RELU
	}
	else{
		cout<<"Hata fonksiyonu seçilemedi!"<<endl;
		exit(0);
	}

	return y;
}

float ysa::calcNewW(float value,float error,float weight){
	//Ağın yeni ağırlığını hesaplama
	// value : giriş değeri
	// error : hata değeri
	// weight : ağırlık
	return weight - (0.5 * error * value);
}

float ysa::total(float *i,float* w,int len){
	// Bir düğüme gelen bağlantıların değerini toplama
	// i : bağlantı değerleri (dizi)
	// w : ağırlıklar (dizi)
	// len : Bağlantı adedi
	float s=0;	
	for(int j=0;j<len;j++){
		s = s+(i[j]*w[j]);
		//cout<<w[j]<<"|";
	}
	//cout<<endl;
	return s;
}

float ysa::func(float x){

	// Aktivasyon fonksiyonları
	float y;

	if(model.activation == "relu"){
		if(x<=0) y=0;  else y=1; // Leakly RELU
	}
	else if(model.activation == "leaky_relu"){
		if(x<0) y=0.001;  else y=x; // Leakly RELU
	}
	else if(model.activation == "swish"){
    	y= 2*x*(1/(1+exp(-1*x))); // Swish 
	}
	else if(model.activation == "sigmoid"){
    	y= (1/(1+exp(-1*x))); // Sigmoid 
	}
	else if(model.activation == "hyperbolic"){
		y = (exp(x) - exp(-1*x)) / (exp(x) + exp(-1*x)) ; // hyperbolic
	}
	else {
		cout<<"Aktivasyon fonksiyonu seçilemedi. [relu][leaky_relu][sigmoid][swish][hyperbolic]"<<endl;
		exit(0);
	}

	return y;
}


void ysa::ImageToInput(image *img){

	int index =0;

	for(int i=0;i<img->height;i++){
		for(int j=0;j<img->width;j++){
			index = (i*img->height)+j;
			input[index] =func((float)(img->matrix[i][j])); 
			//cout<<input[index]<<"|";
		}
	}


}


void ysa::run(){

	// Giriş katı  hesapla
	for(int i=0;i<model.nodesize;i++){
		node_output[i] = func(total(input,network.w[i],model.inputsize));
		//printf("Node output %f => %f  \n",total(input,network.w[i],model.inputsize),node_output[i]);
	}



	// Çıkış katı hesapla
	for(int i=0;i<model.outputsize;i++){
		output[i] = func(total(node_output,network.wo[i],model.nodesize));
		//printf("Output %d => %f  \n",i,o[i]);
	}

}


int ysa::isOk(){
	int OK;
	for(int i=0;i<model.outputsize;i++){
		OK=1;
		if((output[i] < (output_target[i] - model.error_tolerance ) )  ||  (output[i] > (output_target[i] + model.error_tolerance ))   ){
			OK=0;
			break;
		}

	}

	return OK;
}


void ysa::training(){

	cout<<"Eğitiliyor..."<<endl;
	int a=0;
	while(a < model.epoch_limit){

		run();

		cout<<"Epoch "<<a<<endl;

		for(int j=0;j<model.outputsize;j++){
			cout<<output_target[j]<<"/"<<output[j]<<endl; 
		}	

		printf("\033[%dA",model.outputsize+1); 

		for(int io=0;io<model.outputsize;io++){
			errors.eo[io] = calcEo(output[io],output_target[io]);
			for(int ic=0;ic<model.nodesize;ic++){
				network.wo[io][ic] = calcNewW(node_output[ic],errors.eo[io],network.wo[io][ic]);
				//printf("%d => %d : %f | ",ic,io,network.wo[io][ic]);
				for(int ii=0;ii<model.inputsize;ii++){
					errors.e[ic] = calcE(node_output[ic],errors.eo[io],network.w[ic][ii]); 
					network.w[ic][ii]=calcNewW(input[ii],errors.e[ic],network.w[ic][ii]);
					//printf("%d => %d : %f | ",ii,ic,network.w[ic][ii] );
				}
			}

		}

		if(isOk()){
		
			printf("Çıkış : ");
/*
			for(int i=0;i<model.nodesize;i++){
				for(int j=0;j<model.inputsize;j++){
					printf("%f|",network.w[i][j] ); 
				}
			}	
			printf("------------\n");
			for(int i=0;i<model.outputsize;i++){
				for(int j=0;j<model.nodesize;j++){
					printf("%f|",network.wo[i][j] ); 
				}
			}		
*/		
			return;
		} 	

		a++;
	}

}


int ysa::data_load(){

	ifstream fp(model.data_file,ifstream::binary);

	cout<<model.data_file<<" açılıyor..."<<endl;

	if(!fp.is_open()){
		cout<<model.data_file<<" açılamadı."<<endl;
		return  false;
	}

	fp.seekg(model.offset);

	cout<<"Konum "<<fp.tellg()<<endl;

	fp.read((char*)&network.id,sizeof(int));
	fp.read(network.name,sizeof(network.name));

	cout<<"["<<sizeof(network.name)<<"]"<<network.name<<" okunuyor..."<<endl;

	for(int i=0;i<(model.nodesize);i++)
		fp.read((char*)network.w[i],model.inputsize*sizeof(float));
	for(int i=0;i<(model.outputsize);i++)
		fp.read((char*)network.wo[i],model.nodesize*sizeof(float));

	model.offset = fp.tellg();

	cout<<network.name<<" okundu..."<<"Son konum "<<model.offset<<endl;

	if(fp.eof()) return  false;
	fp.close();

	return true;
}


void ysa::data_add(int id,char *name){

	network.id=id;
	strncpy(network.name,name,sizeof(network.name));

	cout<<"Open file"<<model.data_file<<"->"<<network.name<<endl;

	ofstream fp(model.data_file,ios::binary | ios::app);
	fp.seekp(ios::end);

	fp.write((char*)&network.id,sizeof(int));
	fp.write(network.name,sizeof(network.name));


	for(int i=0;i<(model.nodesize);i++)
		fp.write((char*)network.w[i],model.inputsize*sizeof(float));
	for(int i=0;i<(model.outputsize);i++)
		fp.write((char*)network.wo[i],model.nodesize*sizeof(float));

	fp.close();

}


void ysa::model_load(string model_file){

	ifstream t;
	Json json;
	string line,data;
	t.open(model_file);   

	if(!t.is_open()){
		cout<<"Model dosyası bulunamadı."<<endl;
		return;
	}

	while(!t.eof()){
		getline(t, line);
		data.append(line);
	}
	t.close(); 

    string inputError;
    auto y = json.parse(data, inputError,JsonParse::COMMENTS);

    if(inputError.length()!=0){
    	cout<<"Parse Error : "<<inputError<<endl;
    }

    cout<<"Model is loading..."<<endl;
  	model.inputsize = y["inputsize"].int_value();
  	model.outputsize = y["outputsize"].int_value();
  	model.nodesize = y["nodesize"].int_value();
  	model.offset = y["offset"].int_value();
  	model.output_target_value = y["output_target_value"].number_value();
  	model.error_tolerance = y["error_tolerance"].number_value();
  	model.activation = y["activation"].string_value();
  	model.data_file = y["data_file"].string_value();
  	model.start_weight = y["start_weight"].number_value();
  	model.epoch_limit = y["epoch_limit"].int_value();

  	cout<<"Input: "<<model.inputsize<<endl;
  	cout<<"Node: "<<model.nodesize<<endl;
  	cout<<"Output: "<<model.outputsize<<endl;
  	cout<<"Offset: "<<model.offset<<endl;
	cout<<"Activation Function: "<<model.activation<<endl;
	cout<<"Error Tolerance: "<<model.error_tolerance<<endl;
	cout<<"Data File: "<<model.data_file<<endl;	
	cout<<"Start Weight: "<<model.start_weight<<endl;	
	cout<<"Epoch Limit: "<<model.epoch_limit<<endl;	
}
