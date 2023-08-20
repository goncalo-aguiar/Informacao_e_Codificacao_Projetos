#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <cmath>
#include <math.h>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading/writing frames

int main(int argc, char *argv[]) {

	bool verbose { false };

	if(argc < 3) {
		cerr << "Usage: wav_cp [ -v (verbose) ]\n";
		cerr << "              wavFileIn wavFileOut\n";
		return 1;
	}

	for(int n = 1 ; n < argc ; n++)
		if(string(argv[n]) == "-v") {
			verbose = true;
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

    SndfileHandle sfhIn2 { argv[argc-1] };
    

	if(verbose) {
		cout << "Input file has:\n";
		cout << '\t' << sfhIn.frames() << " frames\n";
		cout << '\t' << sfhIn.samplerate() << " samples per second\n";
		cout << '\t' << sfhIn.channels() << " channels\n";
	}

   
	
	double somatorio_amostra_original = 0;
    double somatorio_amostra_alterada = 0;
	int erro = 0;
	int aux=0;
	size_t nFrames;
	vector<short> samples(FRAMES_BUFFER_SIZE * sfhIn.channels());
    size_t nFrames1;
	vector<short> samples1(FRAMES_BUFFER_SIZE * sfhIn2.channels());
	
    SndfileHandle outFile { "reduced.wav", SFM_WRITE, sfhIn.format(), sfhIn.channels(),sfhIn.samplerate()};
	while((nFrames = sfhIn.readf(samples.data(), FRAMES_BUFFER_SIZE))){
        nFrames1 = sfhIn2.readf(samples1.data(), FRAMES_BUFFER_SIZE);
        for (int i = 0;i<samples.size();i++){
			somatorio_amostra_original = somatorio_amostra_original + pow(abs(samples[i]),2);
            somatorio_amostra_alterada = somatorio_amostra_alterada + pow(abs(samples[i]-samples1[i]),2);
			aux = samples[i]-samples1[i];
			if (aux > erro){
				erro = aux;
			}

			
		}
		
		outFile.writef(samples1.data(), nFrames);
	}

	
    
    double resultado = 10 * log10((double)somatorio_amostra_original/somatorio_amostra_alterada);
    // cout << "\n " << somatorio_amostra_original <<endl;
    // cout  << "\n " << somatorio_amostra_alterada << endl;
    // cout  << "\n " << resultado << endl;

    printf("\nSNR = %f",resultado);
	printf("\nErro absoluto máximo por amostra = %d",erro);
	return 0;
}