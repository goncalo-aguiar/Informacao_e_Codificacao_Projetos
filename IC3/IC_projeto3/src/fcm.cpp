#include<fstream>
#include<string>
#include<iostream>
#include<cmath>
#include <sstream>
#include<map>
#include<string>


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
    
        void getEntropy(map<string, map<char, int>> &model){
        
        
            int aux;
            int totalEntrys = 0;
            map<string, int> totalOccurCtx;
            for(auto i : model){
                map<char, int> &occur = model[i.first];
                aux = 0;
                for(auto i : occur){
                    aux += i.second;
                }
                totalOccurCtx[i.first] = aux;
                totalEntrys += aux;
                
            }
           
            double probCtx, prob, ctxEntropy, H;
            int ctxTotal;

            for(auto i : model){
                map<char, int> &occur = model[i.first];

                ctxTotal = totalOccurCtx[i.first];
                probCtx = (double)ctxTotal / totalEntrys;

               
                ctxEntropy = 0;
                for(auto i : occur){
                    prob = (double) i.second / ctxTotal;
                    ctxEntropy -= prob * log2(prob);       
                }
                H += ctxEntropy * probCtx;
                
            }
            m_entropy = H;
        }


        void estimate(map<string, map<char, int>> &model, char *filename){      
            ifstream ifs(filename, std::ios::in);
            if(!ifs.is_open()){
                throw runtime_error("Error: Could not open file!");
            }

            string ctx;
            char aux;

            for (int i = 0; i < k; i++){
                readChar(ifs, &aux);
                ctx.append(1, aux);
            }
            
            int noccur, totalOccur;
            double sumH = 0;
            int count = 0;

            while(!ifs.eof()){
                readChar(ifs, &aux);
                count++;

                totalOccur = 0;
                // modelo contem contexto
                if(model.count(ctx) > 0){
                    map<char, int> &occur = model[ctx];
                    // contexto tem o char que procuramos
                    if(occur.count(aux) > 0){  
                        noccur = occur[aux];
                    }else{ // não tem
                        noccur = 0;
                    }
                    for(auto i : occur){
                        // contar o número total de entrys para o contexto
                        totalOccur += i.second;
                    }
                }else{  // não contêm
                    noccur = 0;
                    totalOccur = 0;
                }
                
                sumH += -log2((noccur + alpha) / (totalOccur + (alpha * ALPHABETH_SIZE)));

                // update ctx
                ctx.erase(0,1); // removes first character
                ctx.append(1, aux);
            }

            // save estimated dist
            dist = sumH;

            // save estimated entropy
            e_entropy = sumH / count;

            // Update number of characters in the file
            num_letras = count;
            }

void getModelo(map<string, map<char, int>> &model, char *filename){
    ifstream ifs(filename, std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Could not open file!");
    }

    string ctx;
    char aux;
    for (int i = 0; i < k; i++){
        readChar(ifs, &aux);
        ctx.append(1, aux);                 // 4 letras do texto
        
    }

    do{
        readChar(ifs, &aux);
        if (model.count(ctx) > 0){          // model.count() retorna 1 se o se o elemento com key 'ctx' aparece no map model 
            model[ctx][aux]++;              // se o conjutnp de chars está no mapa fazemos aux++ para incrementar o contador para esse conjunto
        }else{
            map<char, int> empty;           // para entrar neste else, é poque este conjunto de chars está a aparecer pela primeira vez no texto
                     
            model[ctx] = empty;             // transformamos o value do mapa model num mapa
            model[ctx][aux]++;              // adiciona um novo conjunto de chars ao mapa
        }
        // update ctx
        ctx.erase(0,1);                     // removes first character in ctx
        ctx.append(1, aux);                 // adiciona proximo caracter a ctx
    }while(!ifs.eof());

    // Filename path to a file were to store the model
    size_t dot = string(filename).find_last_of(".");
    string destFilename = string(filename).substr(0, dot);
    destFilename += "model.txt";
    cout << destFilename << endl;                                   // cria o ficheiro onde vai escrever com o nome como queremos

    ofstream myfile;
    myfile.open (destFilename);
    myfile << k << "\t" << alpha << endl;                           // escreve no ficheiro o alpha e k que usamos                         
    for(auto i : model) {
        map<char, int> &occur = model[i.first];
        myfile << i.first;                                          // i.first tem as k letras que tamos a ver
        
        for(auto j : occur){
            myfile << '\t' << j.first << '\t' << j.second;          // j.first é letra que vem a seguir e j.second é o numero de vezes em q aparece 
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


