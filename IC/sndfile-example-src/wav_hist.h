#ifndef WAVHIST_H
#define WAVHIST_H

#include <iostream>
#include <vector>
#include <map>
#include <sndfile.hh>
#include <fstream>

class WAVHist {
  private:
	std::vector<std::map<short, size_t>> counts;
	std::map<short, size_t> counts_mid;
	std::map<short, size_t> counts_side;

  public:
	WAVHist(const SndfileHandle& sfh) {
		counts.resize(sfh.channels());
	}

	void update(const std::vector<short>& samples) {
		size_t n { };
		for(auto s : samples){
			counts[n++ % counts.size()][s]++;
			//std::cout << s << std::endl;
		}
		
	}
	void update_mid(const std::vector<short>& samples) {
		size_t n { };
		int i =0;
		int aux ;
		for(auto s : samples){
			if (i%2==0){
				aux = s;
			}
			else{
				aux = (aux + s)/2;
				counts_mid[aux]++;
			}
			i++;
		}
		
	}

	void update_side(const std::vector<short>& samples) {
		size_t n { };
		int i =0;
		int aux ;
		for(auto s : samples){
			if (i%2==0){
				aux = s;
			}
			else{
				aux = (aux - s)/2;
				counts_side[aux]++;
			}
		
			i++;
		}
		
	}


	void dump(const size_t channel) const {
		for(auto [value, counter] : counts[channel])
			std::cout << value << '\t' << counter << '\n';
	}

	void dump_mid() {
		std::ofstream MyFile("MID.txt");
		for (auto [x ,y]: counts_mid){
			printf("%d %d\n",x,y);	
			MyFile << x << ' ' << y << '\n';
		}	
		MyFile.close();
	}

	void dump_side() {
		std::ofstream MyFile("SIDE.txt");
		for (auto [x ,y]: counts_side){
			printf("%d %d\n",x,y);	
			MyFile << x << ' ' << y << '\n';
		}
		MyFile.close();
			
	}

	

	
};

#endif

