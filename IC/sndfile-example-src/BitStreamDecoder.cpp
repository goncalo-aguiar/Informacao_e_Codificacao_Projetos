#include "BitStream.cpp"

int main(int argc, char *argv[]) {

    BitStream bitstream{"ficheiro_descodificado","w"};

    
    
    ifstream f("ficheiro_codificado",ios::binary | ios::in);
    char c;
    int bit;
    while(f.get(c)){
        bit = c - '0';
        bitstream.writeBit(bit);
    }

    
   
    
}