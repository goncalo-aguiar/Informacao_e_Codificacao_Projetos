#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

#include <sstream>    

using namespace std;


class BitStream {
    
    private:
        string filename;
        string tipo_stream;
        int contador_ler;
        int contador_ler_n;
        int contador_escrever;
        vector<int> aux;
        vector<int> buffer_escrever;

        
    public:
        BitStream(string filename1,string tipo) {
        if (tipo == "r"){
            tipo_stream = tipo;
            filename = filename1;

            
            contador_ler = 0;
            contador_ler_n = 0;
            
            
            ifstream f(filename,ios::binary | ios::in);
            char c;
            
            int auxiliar;
            while(f.get(c)){
                for (int i=7;i>=0;i--){
                auxiliar = ((c >> i) & 1);
                aux.push_back(auxiliar);
                }
            }

            
            aux.push_back(-1);
        }
        else if(tipo =="w"){
            filename = filename1;
            tipo_stream = tipo;
            contador_escrever = 0;
        }
           
            
         
	}
   
    int readBit(){
        if (tipo_stream != "r"){
            cerr << "Erro: Para usar funções de leitura o BitStream precisa de ser de leitura. BitStream(,\"r\")\n";
        }
        int a = aux[contador_ler];
        contador_ler++;
        if(a == -1){
            contador_ler=0;
        }
        return a;
    }

    string readNBits(int num_bits){
        if (tipo_stream != "r"){
            cerr << "Erro: Para usar funções de leitura o BitStream precisa de ser de leitura. BitStream(,\"r\")\n";
        }
        stringstream a;
        string auxx;
        string fim;
         if (contador_ler_n +  num_bits > aux.size()-1 ){
           cout << "Erro: Tamanho inserido superior ao tamanho do ficheiro" << endl;
           cout << "Tamanho do ficheiro:" << aux.size()-1 << endl;
           contador_ler_n=0; 
           return fim;
        }
        for (int i=0;i< num_bits;i++){
            auxx ="";
            a << readBit();
            auxx =  a.str();
            fim =   auxx;  
        }
        return fim;
    }

    void writeBit(int val){
        if (tipo_stream != "w"){
            cerr << "Erro: Para usar funções de escrita o BitStream precisa de ser de escrita. BitStream(,\"w\")\n";
        }

        ofstream myfile;
        myfile.open (filename,std::ios_base::app);
        
        if (contador_escrever <= 7){
            buffer_escrever.push_back(val);
            contador_escrever++;  
             
        }
        if (contador_escrever==8)
        {
            stringstream a;
            string auxx;
            string fim;
            for (int i = 0; i< 8; i++){
                auxx ="";
                a << buffer_escrever[i];
                auxx =  a.str();
                fim =   auxx;   
            }

           
            // cout<< fim<< endl;
            fim  = setStringtoASCII(fim);
            // cout << fim<< endl;

            myfile  << fim;
            contador_escrever = 0;
            buffer_escrever.clear();
        }
        myfile.close();
    }

    void writeNBits(string bits){
        if (tipo_stream != "w"){
            cerr << "Erro: Para usar funções de escrita o BitStream precisa de ser de escrita. BitStream(,\"w\")\n";
        }
        for (char bit : bits){
            if (bit == '1'){
                writeBit(1);
            }
            else if(bit == '0'){
                writeBit(0);
            } 
                
        }
    }

    int binaryToDecimal(string n)
    {
        string num = n;
    
        // Stores the decimal value
        int dec_value = 0;
    
        // Initializing base value to 1
        int base = 1;
    
        int len = num.length();
        for (int i = len - 1; i >= 0; i--) {
    
            // If the current bit is 1
            if (num[i] == '1')
                dec_value += base;
            base = base * 2;
        }
    
        // Return answer
        return dec_value;
    }
    string setStringtoASCII(string str)
    {
        // To store size of s
        int N = int(str.size());
    
        // If given string is not a
        // valid string
        if (N % 8 != 0) {
            return "Not Possible!";
        }
    
        // To store final answer
        string res = "";
    
        // Loop to iterate through string
        for (int i = 0; i < N; i += 8) {
            int decimal_value
                = binaryToDecimal((str.substr(i, 8)));
    
            // Apprend the ASCII character
            // equivalent to current value
            res += char(decimal_value);
        }
    
        // Return Answer
        return res;
}

};


