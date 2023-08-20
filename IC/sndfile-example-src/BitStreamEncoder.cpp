
#include "BitStream.cpp"

int main(int argc, char *argv[]) {

    BitStream bitstream{"ficheiro_inicial","r"};
    

    ofstream myfile;
    myfile.open ("ficheiro_codificado",std::ios_base::app);

    int bit;
    while((bit = bitstream.readBit()) != EOF){
       myfile << bit;
    }
    


    
}