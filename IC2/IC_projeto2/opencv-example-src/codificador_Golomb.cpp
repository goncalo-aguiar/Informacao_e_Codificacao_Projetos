#include "Golomb.cpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.cpp"

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

short quantize(short code,int quant){
	return (code >> quant);
}
int main(int argc, char *argv[]) {

  bool verbose { false };

	
	SndfileHandle sfhIn { argv[1] };
	if(sfhIn.error()) {
		cerr << "Error: invalid input file\n";
		return 1;
    }

	fstream my_file;
	my_file.open("ficheiro_codificado", ios::out);
	my_file.close();

    Golomb golomb{};
	BitStream bitstream{"ficheiro_codificado","w"};

	ofstream myfile;
	myfile.open ("aux",std::ios_base::app);
	
	int m = stoi(argv[3]);
	if (sfhIn.channels() == 2){

		
		
			SNDFILE *infile;
			SF_INFO sfinfo;
			int readcount;
			short ch[2];
			
			if (! (infile = sf_open (argv[1], SFM_READ, &sfinfo))) {
				cout << "File doesn't exists" << endl;
			exit(EXIT_FAILURE);
			}

			cout << "Encoding Header..." << endl;
			bitstream.writeNBits(golomb.encodeInt(int(sfhIn.format()),m));
			bitstream.writeNBits(golomb.encodeInt(int(sfhIn.channels()),m));
			bitstream.writeNBits(golomb.encodeInt(int(sfhIn.samplerate()),m));
			cout << "Ended encoding Header..." << endl;

			cout << "Starting encoding sound..." << endl;
			short guardar_mid_anterior = 0;
			short guardar_side_anterior = 0;
			while ((readcount = (int) sf_readf_short (infile, ch, 1)) > 0) {
				short aux;
				if (stoi(argv[2]) != 0){
					
					aux = quantize((ch[0] + ch[1])/2,stoi(argv[2]));
				}
				else{
					aux = (ch[0] + ch[1])/2;
				}
				short residual_left = aux - guardar_mid_anterior ;
				guardar_mid_anterior = aux;
				string codified = golomb.encodeInt(int(residual_left),m); 

				if (stoi(argv[2]) != 0){
					aux = quantize((ch[0] - ch[1]),stoi(argv[2]));
				}
				else{
					aux = (ch[0] - ch[1]);
				}
				short residual_right = aux- guardar_side_anterior;
				guardar_side_anterior = aux;
				codified = codified +  golomb.encodeInt(int(residual_right),m); 

				bitstream.writeNBits(codified);
			}
			cout << "Ended encoding sound..." << endl;
			
			sf_close (infile) ;  
		
	}
	else if (sfhIn.channels() == 1){
		SNDFILE *infile;
		SF_INFO sfinfo;
		int readcount;
		short ch[1];
		
		if (! (infile = sf_open (argv[1], SFM_READ, &sfinfo))) {
        	cout << "File doesn't exists" << endl;
        exit(EXIT_FAILURE);
		}
		string codified;
		short ch_anterior=0;
		cout << "Encoding Header..." << endl;
		bitstream.writeNBits(golomb.encodeInt(int(sfhIn.format()),m));
		bitstream.writeNBits(golomb.encodeInt(int(sfhIn.channels()),m));
		bitstream.writeNBits(golomb.encodeInt(int(sfhIn.samplerate()),m));
		cout << "Ended encoding Header..." << endl;

		cout << "Starting encoding sound..." << endl;
		while ((readcount = (int) sf_readf_short (infile, ch, 1)) > 0) {
			
			short aux;
			if (stoi(argv[2]) != 0){
				aux = ch[0] - ch_anterior;
				ch_anterior = ch[0];
				codified = golomb.encodeInt(int(quantize(aux,stoi(argv[2]))),m); 
			}
			else{
				aux = ch[0] - ch_anterior;
				ch_anterior =  ch[0];
				codified = golomb.encodeInt(int(aux),m); 
			}
			bitstream.writeNBits(codified);

			
		}
		cout << "Ended encoding sound" << endl;
		sf_close (infile) ;  
	}
}


