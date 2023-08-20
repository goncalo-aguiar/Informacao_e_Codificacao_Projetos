#include "Golomb.cpp"
#include "BitStream.cpp"


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

vector<string> getTabela(int m){
	int flag = 0;
	int q = 0;
	string aux = "";
	int r = 0;

    vector<string> tabela_final;
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

        tabela_final = tabela1;
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

             tabela_final = tabela1;
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
					// cout << "AUX "<<aux << endl;
					// cout << "TAB" <<tabela1[i] << endl;

					if (aux == tabela1[i]){
						posicao = i;
					
					}
					
				}
				//  cout << "pos:" << posicao << endl;

				int num_bits=0;
			
			
				num_bits = menor_num_bits;
				r = posicao;
                 tabela_final = tabela1;
				// cout << "R:" << r << endl;
				
			

			}
		}   


        
	}
    return tabela_final;
}
int main(int argc, char *argv[]) {


   

    // Golomb golomb{};

    // string codified = golomb.encodeInt(1,2); 
    // cout << codified << endl;


    // cout << "DECODER" << endl;
    // int numero = golomb.decodeString(codified,2);

    // cout << numero << endl;
    // vector<string> tabela= getTabela(2);
    // for (int i=0; i < tabela.size();i++){
    //     cout << tabela[i] << endl;
    // }
    
    ifstream f("aux2",ios::binary | ios::in);
    char c;
    int bit;
    while(f.get(c)){
       cout << c;
    }

}