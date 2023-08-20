#include<fstream>
#include<string>
#include<iostream>
#include<cmath>
#include<sstream>
#include<map>
#include<string>
#include<vector>
#include<iterator>
#include<numeric>
using namespace std;

#define ALPHABETH_SIZE 27




class fcm {
    
    private:
        int k;
        double alpha;

        
    public:
        fcm(int k,double alpha) {
            this->k= k;
            this->alpha= alpha;
        }

        double dist;
        double m_entropy;
        double e_entropy;
        int num_letras;
    
        void getEntropy(map<string, map<char, int>> &modelo){
        
        
            int aux;
            int entradas = 0;
            map<string, int> num_contexto;
            for(std::map<string,std::map<char,int>>::iterator it = modelo.begin(); it != modelo.end(); ++it){
                map<char, int> &mapa_novo = modelo[it->first];
                aux = 0;
                std::vector<int> value;
                for(std::map<char,int>::iterator it = mapa_novo.begin(); it != mapa_novo.end(); ++it){
                    value.push_back(it->second);
                }
                int aux = std::accumulate(value.begin(), value.end(), 0);

                num_contexto[it->first] = aux;
                entradas = entradas + aux;
                
            }
           
            double contexto_prob, prob, contexto_entropia, H;
            int total;

            for(std::map<string,std::map<char,int>>::iterator it = modelo.begin(); it != modelo.end(); ++it){
                map<char, int> &mapa_novo = modelo[it->first];

                total = num_contexto[it->first];
                contexto_prob = (double)total / entradas;

               
                contexto_entropia = 0;
                
                for(std::map<char,int>::iterator it = mapa_novo.begin(); it != mapa_novo.end(); ++it) {
                    prob = (double) it->second / total;
                    contexto_entropia = contexto_entropia - prob * log2(prob);
                }
                
                H = H + contexto_entropia * contexto_prob;
                
            }
            m_entropy = H;
        }


        void estimate(map<string, map<char, int>> &modelo, char *filename){      
            ifstream ifs(filename, std::ios::in);      

            string contexto;
            char aux;
            for (int i = 0; i < k; i++){
                readChar(ifs, &aux);
                contexto = contexto + aux;
            }                                                                   // contexto fica com o primeiro conjunto de chars com tamanho k

            int n, total_n;
            double sumH = 0;
            int count = 0;

            while(!ifs.eof()){
                readChar(ifs, &aux);
                count++;

                total_n = 0;
                
                if(modelo.find(contexto) == modelo.end()){
                    n = 0;
                    total_n = 0;
                    
                }else{ 
                    map<char, int> &mapa_novo = modelo[contexto];
                    
                    // if(mapa_novo.count(aux) > 0){  
                    //     n = mapa_novo[aux];
                    // }else{ // não tem
                    //     n = 0;
                    // }
                    n = mapa_novo[aux];
                
                    std::vector<int> value;
                    for(std::map<char,int>::iterator it = mapa_novo.begin(); it != mapa_novo.end(); ++it){
                        value.push_back(it->second);
                    }
                    total_n = std::accumulate(value.begin(), value.end(), 0);
             
                }
                
                
                sumH = sumH + (-log2((n + alpha) / (total_n + (alpha * ALPHABETH_SIZE))));

                contexto = contexto.substr(1,contexto.size() -1);
                contexto = contexto + aux;
            }

            dist = sumH;
            e_entropy = sumH / count;
            num_letras = count;
        }

void getModelo(map<string, map<char, int>> &modelo, char *filename){
    ifstream ifs(filename, std::ios::in);
    string contexto, aux_s;
    char aux;
    for (int i = 0; i < k; i++){
        readChar(ifs, &aux);
        contexto = contexto + aux;                
    }
    while(!ifs.eof()){
        readChar(ifs, &aux);
        if(modelo.find(contexto) == modelo.end()){
            map<char, int> empty;           
            modelo[contexto] = empty;             
            modelo[contexto][aux]++;
        }else{
            modelo[contexto][aux]++;              
        }        
        contexto = contexto.substr(1,contexto.size() -1);
        contexto = contexto + aux;                
    };

    // NOME DO FICHEIRO
    string fich_destino = "";
    string flag = "";
    
    for (int i = string(filename).size(); i-- > 0;){
        if( filename[i] == '.'){
            flag = "1";
        }
        if(flag == "1"){
            fich_destino = filename[i] + fich_destino;
        }
    }
    fich_destino = "." + fich_destino.substr(1,fich_destino.size() -2) + "modelo.txt";
    cout << "created file path: " << fich_destino << endl;   
   
       

    ofstream myfile;
    myfile.open (fich_destino);
    myfile << k << "\t" << alpha << endl;                           // escreve no ficheiro o alpha e k que usamos                         
    
    for(std::map<string,std::map<char,int>>::iterator it = modelo.begin(); it != modelo.end(); ++it) {
        map<char, int> &mapa_novo = modelo[it->first];
        myfile << it->first;                                          // i.first tem as k letras que tamos a ver
        
        for(std::map<char,int>::iterator it = mapa_novo.begin(); it != mapa_novo.end(); ++it){
            myfile << '\t' << it->first << '\t' << it->second;          // j.first é letra que vem a seguir e j.second é o numero de vezes em q aparece 
        }
        myfile << endl;
    }                                                               // este for serve para escrever oque está no mapa para o ficheiro
    myfile.close();
}



void readChar(ifstream &ifs, char *c){
    char s;
    do{
        ifs.get(s);
        if(!(s == '\n'| s == '\t')) {
            *c = s;
        }
    }while((*c == '\n'|*c == '\t') && !ifs.eof());
}
           
   
};