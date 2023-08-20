

#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

#include <sstream>    
#include <math.h>
using namespace std;

  

class Golomb {
    
    private:

    string toBinary(int n){
        string r;
        while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
        return r;
    }

    string toBinary2(int n,int size){
        int a[size], i;  
        string fim;
        for(i=0; n>0; i++)    
        {
            a[i]=n%2;    
            n= n/2;  
        }    
        for(i=i-1 ;i>=0 ;i--)    
        {    
        fim = fim + to_string(a[i]);    
        }    
        return fim;
    }

    int binaryToDecimal(string n)
    {
    string num = n;
    int dec_value = 0;
 
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
    }
    

        
    public:
    Golomb() {

    }
    string encodeInt(int n,int m){

    int q = abs(n)/m;
    int r = abs(n)%m;
    string final = "";
    for(int i=0;i<q;i++){
        final = final + '0';
    }
    final = final + '1';
        

       
    if (m>4){
        int resto = m%4;
        int tabela_aux = 0;
        vector<string> tabela1;
        tabela_aux = (m-resto)/4; 
        vector<string> tabela(tabela_aux*4);
        
        int max_bits = (toBinary(m)).size();
        
        for(int i=0;i<tabela.size();i++){
            string aux_bin = toBinary2(i,tabela.size());
            if(aux_bin.size() < max_bits){
                for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                    aux_bin = "0" + aux_bin;
                }
            }

            tabela[i]=aux_bin;
        }
        
        

        
        tabela1 = tabela; 
        
        vector<string> tabela_novos((m-tabela1.size())*2);
        int count = 0;
        int tamanho_novos = 0;

        
        for(int i = tabela1.size()-1; i>=tabela1.size()-resto; i--){
        
            tabela_novos[tamanho_novos] = tabela1[i] + '1';
            tamanho_novos++;
            tabela_novos[tamanho_novos] = tabela1[i] + '0';
            tamanho_novos++;
            count++;
        }

        for (int i=0;i<resto;i++){
            tabela1.pop_back();
        }
        
        for(int i=tabela_novos.size()-1;i>=0;i--){
            tabela1.push_back(tabela_novos[i]);
        }   


        max_bits = tabela1.back().size();
            // cout << "max_bits: " << max_bits << endl;

		for(auto i=0;i<tabela1.size();++i){
			for (int j= 0; j<max_bits-1;j++){
				if(tabela1[i].size()< max_bits-1){
					tabela1[i] = "0" + tabela1[i];
				}

			}
		}
        // tabela1[0] = "0" + tabela1[0];

        // for(auto i=0;i<tabela1.size();++i){
        //     cout << tabela1[i] << endl;
        // }
        if (n >= 0){      
            return final + tabela1[r] + '0';
        }
        else{
            
            return final + tabela1[r] +'1';
        }
        
    }
    else{
        
        if (m>2){
            int resto = m%2;
            int tabela_aux = 0;
            vector<string> tabela1;

            tabela_aux = (m-resto)/2; 
            vector<string> tabela(tabela_aux*2);
            
            int max_bits = (toBinary(m)).size();
            
            for(int i=0;i<tabela.size();i++){
                string aux_bin = toBinary2(i,tabela.size());
                if(aux_bin.size() < max_bits){
                    for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                        aux_bin = "0" + aux_bin;
                    }
                }

                tabela[i]=aux_bin;
            }
        
        

            
            tabela1 = tabela; 
            
            vector<string> tabela_novos((m-tabela1.size())*2);
            int count = 0;
            int tamanho_novos = 0;

            
            for(int i = tabela1.size()-1; i>=tabela1.size()-resto; i--){
            
                tabela_novos[tamanho_novos] = tabela1[i] + '1';
                tamanho_novos++;
                tabela_novos[tamanho_novos] = tabela1[i] + '0';
                tamanho_novos++;
                count++;
            }

            for (int i=0;i<resto;i++){
                tabela1.pop_back();
            }
            
            for(int i=tabela_novos.size()-1;i>=0;i--){
                tabela1.push_back(tabela_novos[i]);
            }   
            
            for(auto i=0;i<tabela1.size();++i){
                for (int j= 0; j<max_bits-1;j++){
                    if(tabela1[i].size()< max_bits-1){
                        tabela1[i] = "0" + tabela1[i];
                    }
                
                }
            }
            

            for(auto i=0;i<tabela1.size();++i){
              
            }
                if (n >= 0){
                return final + tabela1[r] + '0';
            }
            else{
                
                return final + tabela1[r] +'1';
            }
        }
        else{
            if (m==2){
                int resto = m%2;
                int tabela_aux = 0;
                vector<string> tabela1;

                tabela_aux = (m-resto)/2; 
                vector<string> tabela(tabela_aux*2);
                
                int max_bits = (toBinary(m)).size();
                
                for(int i=0;i<tabela.size();i++){
                    string aux_bin = toBinary2(i,tabela.size());
                    if(aux_bin.size() < max_bits){
                        for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                            aux_bin = "0" + aux_bin;
                        }
                    }

                    tabela[i]=aux_bin;
                }
            
            
                tabela1 = tabela; 
                // for(auto i=0;i<tabela1.size();++i){
                //     cout << tabela1[i] << endl;
                // }
                // cout << n << endl;     
                if (n >= 0){
                    
                    return final + tabela1[r] + '0';
                }
                else{
                    
                    return final + tabela1[r] +'1';
                }
                        
            }
        }
                
    }


            
            
}

        


    
    int decodeString(string bits, int m){
        int flag = 0;
        int q = 0;
        string aux = "";
        for (size_t i = 0; i < bits.length(); i++) {
            if (flag == 0){
                if (bits[i] == '1'){
                    flag =1;
                }
                else{
                    q++;
                }
            }
            else{
                aux = aux + bits[i];
            }
        }
        int r = 0;
        if (m>4){
            int resto = m%4;
            int tabela_aux = 0;
            vector<string> tabela1;
            tabela_aux = (m-resto)/4; 
            vector<string> tabela(tabela_aux*4);
        

        
            int max_bits = (toBinary(m)).size();
            
            for(int i=0;i<tabela.size();i++){
                string aux_bin = toBinary2(i,tabela.size());
                if(aux_bin.size() < max_bits){
                    for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                        aux_bin = "0" + aux_bin;
                    }
                }

                tabela[i]=aux_bin;
            }
            
            

            
            tabela1 = tabela; 
            
            vector<string> tabela_novos((m-tabela1.size())*2);
            int count = 0;
            int tamanho_novos = 0;

            
            for(int i = tabela1.size()-1; i>=tabela1.size()-resto; i--){
            
                tabela_novos[tamanho_novos] = tabela1[i] + '1';
                tamanho_novos++;
                tabela_novos[tamanho_novos] = tabela1[i] + '0';
                tamanho_novos++;
                count++;
            }

            for (int i=0;i<resto;i++){
                tabela1.pop_back();
            }
            
            for(int i=tabela_novos.size()-1;i>=0;i--){
                tabela1.push_back(tabela_novos[i]);
            }   


            max_bits = tabela1.back().size();
            // cout << "max_bits: " << max_bits << endl;

            for(auto i=0;i<tabela1.size();++i){
                for (int j= 0; j<max_bits-1;j++){
                    if(tabela1[i].size()< max_bits-1){
                        tabela1[i] = "0" + tabela1[i];
                    }

                }
            }

            // for(auto i=0;i<tabela1.size();++i){
            //     cout << tabela1[i] << endl;

                
            // }
        
            int menor_num_bits = tabela1[0].size();
            string aux1 = aux.substr(0,menor_num_bits);
        
            int posicao = 0;
            int posicao2 = 0;
            for(auto i=0;i<tabela1.size();++i){
                if (aux1 == tabela1[i]){
                    posicao = i;
                }
            }

            if (posicao == 0){
                string aux2 = aux.substr(0,menor_num_bits+1);
            
                for(auto i=0;i<tabela1.size();++i){
                    if (aux2 == tabela1[i]){
                        posicao2 = i;
                    }
                }
            }
            int num_bits=0;
            
            if (posicao !=0 ){
                num_bits = menor_num_bits;
                r = posicao;
            }
            else{
                num_bits = menor_num_bits+1;
                r = posicao2;
            }
            // cout << "R:" << r << endl;
        }
        else{
            if (m>2){
                int resto = m%2;
                int tabela_aux = 0;
                vector<string> tabela1;

                tabela_aux = (m-resto)/2; 
                vector<string> tabela(tabela_aux*2);
                
                int max_bits = (toBinary(m)).size();
                
                for(int i=0;i<tabela.size();i++){
                    string aux_bin = toBinary2(i,tabela.size());
                    if(aux_bin.size() < max_bits){
                        for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                            aux_bin = "0" + aux_bin;
                        }
                    }

                    tabela[i]=aux_bin;
                }
            
            

                
                tabela1 = tabela; 
                
                vector<string> tabela_novos((m-tabela1.size())*2);
                int count = 0;
                int tamanho_novos = 0;

                
                for(int i = tabela1.size()-1; i>=tabela1.size()-resto; i--){
                
                    tabela_novos[tamanho_novos] = tabela1[i] + '1';
                    tamanho_novos++;
                    tabela_novos[tamanho_novos] = tabela1[i] + '0';
                    tamanho_novos++;
                    count++;
                }

                for (int i=0;i<resto;i++){
                    tabela1.pop_back();
                }
                
                for(int i=tabela_novos.size()-1;i>=0;i--){
                    tabela1.push_back(tabela_novos[i]);
                }   
                
                for(auto i=0;i<tabela1.size();++i){
                    for (int j= 0; j<max_bits-1;j++){
                        if(tabela1[i].size()< max_bits-1){
                            tabela1[i] = "0" + tabela1[i];
                        }
                    
                    }
                }

                int menor_num_bits = tabela1[0].size();
                string aux1 = aux.substr(0,menor_num_bits);
            
                int posicao = 0;
                int posicao2 = 0;
                for(auto i=0;i<tabela1.size();++i){
                    // cout << tabela1[i]<< endl;
                    if (aux1 == tabela1[i]){
                        posicao = i;
                    }
                    
                }

                if (posicao == 0){
                    string aux2 = aux.substr(0,menor_num_bits+1);
                
                    for(auto i=0;i<tabela1.size();++i){
                        if (aux2 == tabela1[i]){
                            posicao2 = i;
                        }
                    }
                }
                int num_bits=0;
                
                if (posicao !=0 ){
                    num_bits = menor_num_bits;
                    r = posicao;
                }
                else{
                    num_bits = menor_num_bits+1;
                    r = posicao2;
                }
                // cout << "R:" << r << endl;
            }  
            else{
                if (m==2){
                    int resto = m%2;
                    int tabela_aux = 0;
                    vector<string> tabela1;

                    tabela_aux = (m-resto)/2; 
                    vector<string> tabela(tabela_aux*2);
                    
                    int max_bits = (toBinary(m)).size();
                    
                    for(int i=0;i<tabela.size();i++){
                        string aux_bin = toBinary2(i,tabela.size());
                        if(aux_bin.size() < max_bits){
                            for(int j = 0; j<max_bits-(aux_bin.size())-1;j++){
                                aux_bin = "0" + aux_bin;
                            }
                        }

                        tabela[i]=aux_bin;
                    }
                
                
                    tabela1 = tabela; 

                    int menor_num_bits = tabela1[0].size();
                   
                    string aux1 = aux.substr(0,menor_num_bits);
                
                    int posicao = 0;
                    int posicao2 = 0;
                    for(auto i=0;i<tabela1.size();++i){
                       
                        if (aux1 == tabela1[i]){
                            posicao = i;
                           
                        }
                        
                    }
                   

                    int num_bits=0;
                 
                
                    num_bits = menor_num_bits;
                    r = posicao;
                    // cout << "R:" << r << endl;
                    
                   

                }
            }



        }

        // cout << "R2:" << r << endl;
        int n = q * m + r;

        if (bits[bits.length() -1] == '1'){
            n = n * -1;
        }
        return n;
    }



};
