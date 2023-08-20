#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <string.h>
#include "wav_hist.h"

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading frames

int main(int argc, char *argv[]) {

	if(argc < 3) {
		cerr << "Usage: " << argv[0] << " <input file> <channel>\n";
		return 1;
	}

	SndfileHandle sndFile { argv[argc-2] };
	if(sndFile.error()) {
		cerr << "Error: invalid input file\n";
		return 1;
    }

	if((sndFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
		cerr << "Error: file is not in WAV format\n";
		return 1;
	}

	if((sndFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
		cerr << "Error: file is not in PCM_16 format\n";
		return 1;
	}
	string aux = "MID";
	int aux1 = aux.compare(argv[argc-1]) ;

	string aux2 = "SIDE";
	int aux3 = aux2.compare(argv[argc-1]) ;

	if (aux1==0){
		size_t nFrames;
		vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());
		WAVHist hist { sndFile };
		while((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
			samples.resize(nFrames * sndFile.channels());
			hist.update_mid(samples);
		}
		hist.dump_mid();
	}else if(aux3==0){
		size_t nFrames;
		vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());
		WAVHist hist { sndFile };
		while((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
			samples.resize(nFrames * sndFile.channels());
			hist.update_side(samples);
		}
		hist.dump_side();
	}
	else{
		int channel = stoi(argv[argc-1]) ;
		if(channel >= sndFile.channels()) {
			cerr << "Error: invalid channel requested\n";
			return 1;
		}
		size_t nFrames;
		vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());
		WAVHist hist { sndFile };
		while((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
			samples.resize(nFrames * sndFile.channels());
			hist.update(samples);
		}
		

		hist.dump(channel);
		
	}
	return 0;
	
}

