#include <iostream>
#include <vector>
#include <sndfile.hh>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading/writing frames
vector<short> aux(0);
vector<short> aux1(0);
size_t frames;

void add(const vector<short>& sampless){
	for (short s: sampless){
		aux.push_back(s);
		
	}
}
int main(int argc, char *argv[]) {
	bool verbose { false };
	for(int n = 1 ; n < argc ; n++)
		if(string(argv[n]) == "-v") {
			verbose = true;
			break;
		}
	SndfileHandle sfhIn { argv[argc-1] };
	SndfileHandle effect { argv[argc-2], SFM_WRITE, sfhIn.format(),sfhIn.channels(), sfhIn.samplerate() };

	if(verbose) {
		cout << "Input file has:\n";
		cout << '\t' << sfhIn.frames() << " frames\n";
		cout << '\t' << sfhIn.samplerate() << " samples per second\n";
		cout << '\t' << sfhIn.channels() << " channels\n";
	}
	size_t nFrames;
	vector<short> samples(FRAMES_BUFFER_SIZE * sfhIn.channels());
	while((nFrames = sfhIn.readf(samples.data(), FRAMES_BUFFER_SIZE))){
		add(samples);
		frames = frames + nFrames;
	}
	vector<short> samples1= aux;
	for (int i=0;i<100000;i++){
		aux.insert(aux.begin(),0);
	}
	vector<short> final(0);


	//simple echo
	SndfileHandle simple { argv[argc-3], SFM_WRITE, sfhIn.format(),sfhIn.channels(), sfhIn.samplerate() };
	if(simple.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }
	for (size_t i=0;i<samples1.size();i++){
		final.push_back(((samples1[i] + 0.9 *aux[i])/(1+0.9)) );	
	}
	simple.writef(final.data(), frames);
	cout << final.size()<<endl;

	 
	
	
	SndfileHandle sfhOut1 { argv[argc-1], SFM_WRITE, sfhIn.format(),
	  sfhIn.channels(), sfhIn.samplerate() };
	if(sfhOut1.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }
	final.clear();
	for (size_t i=0;i<samples1.size();i++){
		final.push_back(((samples1[i] + 0.9 *final[i-1])) );	
	}
	sfhOut1.writef(final.data(), frames);
	cout << final.size();


	//reverse
	SndfileHandle reverse { argv[argc-1], SFM_WRITE, sfhIn.format(),sfhIn.channels(), sfhIn.samplerate() };
	if(reverse.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }
	vector<short> reversevec(0);
	for (size_t i=0;i<samples1.size();i++){
		reversevec.push_back(samples1[samples1.size()-i-1]);
	}	
	reverse.writef(reversevec.data(), frames);	

	return 0;   

}
	

	







