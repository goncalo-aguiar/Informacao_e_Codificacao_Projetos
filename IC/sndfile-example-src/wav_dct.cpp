#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.cpp"



using namespace std;



int main(int argc, char *argv[]) {

	bool verbose { false };
	size_t bs { 1024 };
	double dctFrac { 0.2 };

	if(argc < 3) {
		cerr << "Usage: wav_dct [ -v (verbose) ]\n";
		cerr << "               [ -bs blockSize (def 1024) ]\n";
		cerr << "               [ -frac dctFraction (def 0.2) ]\n";
		cerr << "               wavFileIn wavFileOut\n";
		return 1;
	}

	for(int n = 1 ; n < argc ; n++)
		if(string(argv[n]) == "-v") {
			verbose = true;
			break;
		}

	for(int n = 1 ; n < argc ; n++)
		if(string(argv[n]) == "-bs") {
			bs = atoi(argv[n+1]);
			break;
		}

	for(int n = 1 ; n < argc ; n++)
		if(string(argv[n]) == "-frac") {
			dctFrac = atof(argv[n+1]);
			break;
		}

	SndfileHandle sfhIn { argv[argc-2] };
	if(sfhIn.error()) {
		cerr << "Error: invalid input file\n";
		return 1;
    }

	if((sfhIn.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
		cerr << "Error: file is not in WAV format\n";
		return 1;
	}

	if((sfhIn.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
		cerr << "Error: file is not in PCM_16 format\n";
		return 1;
	}

	SndfileHandle sfhOut { argv[argc-1], SFM_WRITE, sfhIn.format(),
	  sfhIn.channels(), sfhIn.samplerate() };
	if(sfhOut.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }

	if(verbose) {
		cout << "Input file has:\n";
		cout << '\t' << sfhIn.frames() << " frames\n";
		cout << '\t' << sfhIn.samplerate() << " samples per second\n";
		cout << '\t' << sfhIn.channels() << " channels\n";
	}

	size_t nChannels { static_cast<size_t>(sfhIn.channels()) };
	size_t nFrames { static_cast<size_t>(sfhIn.frames()) };

	// Read all samples: c1 c2 ... cn c1 c2 ... cn ...
	// Note: A frame is a group c1 c2 ... cn
	vector<short> samples(nChannels * nFrames);
	sfhIn.readf(samples.data(), nFrames);

	size_t nBlocks { static_cast<size_t>(ceil(static_cast<double>(nFrames) / bs)) };

	// Do zero padding, if necessary
	samples.resize(nBlocks * bs * nChannels);

	// Vector for holding all DCT coefficients, channel by channel
	vector<vector<double>> x_dct(nChannels, vector<double>(nBlocks * bs));

	// Vector for holding DCT computations
	vector<double> x(bs);

	// Direct DCT
	
	fftw_plan plan_d = fftw_plan_r2r_1d(bs, x.data(), x.data(), FFTW_REDFT10, FFTW_ESTIMATE);
	for(size_t n = 0 ; n < nBlocks ; n++)
		for(size_t c = 0 ; c < nChannels ; c++) {
			for(size_t k = 0 ; k < bs ; k++)
				x[k] = samples[(n * bs + k) * nChannels + c];

			fftw_execute(plan_d);
			// Keep only "dctFrac" of the "low frequency" coefficients
			for(size_t k = 0 ; k < bs * dctFrac ; k++)
				x_dct[c][n * bs + k] = x[k] / (bs << 1);
				
		}
	BitStream bitstream{"escrever_dct","w"};
	string auxiliar1;
	string final = "";
	ofstream myfile;
	ofstream myfile2;
	myfile2.open ("escrever_dct_0");
	myfile2<<"";
	myfile2.close();
    myfile.open ("escrever_dct_0",fstream::app);


	ofstream myfile1;
	myfile1.open ("dct_codificado_0");

	ofstream myfile1_1;
	myfile1_1.open ("dct_codificado_1");


	ofstream myfile_1;
	ofstream myfile2_1;
	myfile2_1.open ("escrever_dct_1");
	myfile2_1<<"";
	myfile2_1.close();
    myfile_1.open ("escrever_dct_1",fstream::app);

	
	
    int bits;
	
	int contador = 0;


	vector<string> buffer_escrever;
	
	for(size_t c = 0 ; c < nChannels ; c++) {
		buffer_escrever.clear();
		for (int i=0; i < x_dct[c].size();i++ ){
			if (c == 0){
				if (int(x_dct[c][i])> 0){
				auxiliar1 = "+" + to_string(int(x_dct[c][i]));
				
				}
				else if (int(x_dct[c][i])==0){
					auxiliar1 = "+" + to_string(int(x_dct[c][i]));
					
				}
				else{
					auxiliar1 = to_string(int(x_dct[c][i]));
					
				}
				
				buffer_escrever.push_back(auxiliar1);
				
				if (buffer_escrever.size()==2048){
					
					for (auto x:buffer_escrever){
						// cout << x;
						myfile<<x;
					}
					buffer_escrever.clear();

					BitStream bitstream{"escrever_dct_0","r"};
					
					int bit;
					while((bit = bitstream.readBit()) != EOF){
						myfile1 << bit;
						
					}
					ofstream myfile2;
					myfile2.open ("escrever_dct_0",std::ios::trunc);
					myfile2.close();
					
				
				}
			}
			else{
				if (int(x_dct[c][i])> 0){
					auxiliar1 = "+" + to_string(int(x_dct[c][i]));
				
				}
				else if (int(x_dct[c][i])==0){
					auxiliar1 = "+" + to_string(int(x_dct[c][i]));
					
				}
				else{
					auxiliar1 = to_string(int(x_dct[c][i]));
					
				}
				
				buffer_escrever.push_back(auxiliar1);
				
				if (buffer_escrever.size()==2048){
					
					for (auto x:buffer_escrever){
						// cout << x;
						myfile_1<<x;
					}
					buffer_escrever.clear();

					BitStream bitstream1{"escrever_dct_1","r"};
					
					int bit;
					while((bit = bitstream1.readBit()) != EOF){
						myfile1_1 << bit;
						
					}
					

					ofstream myfile2_1;
					myfile2_1.open ("escrever_dct_1",std::ios::trunc);
					myfile2_1.close();
				}
				
					
					
			}
			
		}
	}	

	BitStream bitstream2{"dct_descodificado_0","w"};
    ifstream f("dct_codificado_0",ios::binary | ios::in);
    char c;
    int bit;
    while(f.get(c)){
        bit = c - '0';
        bitstream2.writeBit(bit); 
    }	


	BitStream bitstream3{"dct_descodificado_1","w"};
    ifstream f1("dct_codificado_1",ios::binary | ios::in);
    
	char c1;
    int bit1;
    while(f1.get(c1)){
        bit1 = c1 - '0';
        bitstream3.writeBit(bit1);
    }	

	vector<vector<double>> x_dct1(nChannels, vector<double>(nBlocks * bs));



	ifstream f323("dct_descodificado_0");
	char c11;
    int numero;
	string auxiliar = "";
	char last_signal = ' ';
	bool flag = false;
	
    while(f323.get(c11)){
		if (auxiliar == "" && last_signal == ' '){
			last_signal = c11;
			flag = true;
		}
		auxiliar = auxiliar + c11;
		
        if (c11 == '+' && auxiliar != "" ){
			auxiliar.pop_back();
			
			if (flag == false and c11 != '\n'){
				try{
					numero = stoi(auxiliar);
				}
				catch(...){
					
				}
			}
				
			if (last_signal == '-'){
				numero = numero *-1;
			}
			last_signal = '+';
			auxiliar ="";
			x_dct1[0].push_back(numero);
			flag = false;
			
		}
		else if (c11 == '-' && auxiliar != ""){
			auxiliar.pop_back();
			
			if (flag == false and c11 != '\n'){
				try{
					numero = stoi(auxiliar);
				}
				catch(...){
					
				}
			}
				
			if (last_signal == '-'){
				numero = numero *-1;
			}
			last_signal = '-';
			auxiliar = "";
			x_dct1[0].push_back(numero);
			flag = false;
		}
    }	


	ifstream f3232("dct_descodificado_1");
	char c12;
    int numero1;
	string auxiliar11 = "";
	char last_signal1 = ' ';
	bool flag1 = false;
	
    while(f3232.get(c12)){
		if (auxiliar11 == "" && last_signal1 == ' '){
			last_signal1 = c12;
			flag1 = true;
		}
		auxiliar11 = auxiliar11 + c12;
		
        if (c12 == '+' && auxiliar11 != "" ){
			auxiliar11.pop_back();
			
			if (flag1 == false and c12 != '\n'){
				try{
					numero1 = stoi(auxiliar11);
				}
				catch(...){
					
				}
			}
				
			if (last_signal1 == '-'){
				numero1 = numero1 *-1;
			}
			last_signal1 = '+';
			auxiliar11 ="";
			x_dct1[1].push_back(numero1);
			flag1 = false;
			
		}
		else if (c12 == '-' && auxiliar11 != ""){
			auxiliar11.pop_back();
			
			if (flag1 == false and c12 != '\n'){
				try{
					numero1 = stoi(auxiliar11);
				}
				catch(...){
					
				}
			}
				
			if (last_signal1 == '-'){
				numero1 = numero1 *-1;
			}
			last_signal1 = '-';
			auxiliar11 = "";
			x_dct1[1].push_back(numero1);
			flag1 = false;
		}
    }	
	
	x_dct[0] = x_dct1[0];
	x_dct[1] = x_dct1[1];

	for (int i=0;i < x_dct1[0].size();i++){
		x_dct[0][i] = double(x_dct1[0][i]);
	}

	for (int i=0;i < x_dct1[1].size();i++){
		x_dct[1][i] = double(x_dct1[1][i]);
	}
	
	
	// Inverse DCT
	fftw_plan plan_i = fftw_plan_r2r_1d(bs, x.data(), x.data(), FFTW_REDFT01, FFTW_ESTIMATE);
	for(size_t n = 0 ; n < nBlocks ; n++)
		for(size_t c = 0 ; c < nChannels ; c++) {
			for(size_t k = 0 ; k < bs ; k++)
				x[k] = x_dct[c][n * bs + k];

			fftw_execute(plan_i);
			for(size_t k = 0 ; k < bs ; k++)
				samples[(n * bs + k) * nChannels + c] = static_cast<short>(round(x[k]));

		}

	sfhOut.writef(samples.data(), sfhIn.frames());
	return 0;
}




