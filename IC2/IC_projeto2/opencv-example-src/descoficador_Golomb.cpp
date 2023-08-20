#include "Golomb.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.cpp"

constexpr size_t FRAMES_BUFFER_SIZE = 65536;
int num_max = 0;
int num_min = 0;

short quantize(short code,int quant){
	return (code << quant);
}
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


		max_bits = tabela1.back().size();
            // cout << "max_bits: " << max_bits << endl;

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


    Golomb golomb{};

	BitStream bitstream{"ficheiro_codificado","r"};
	int bit_;
	string codified_= "";
	string codified2_= "";
	int contador2_=0;
	int posicao_=0;
	int flag_acabou_=1;
	int flag_primeiro_1_=0;
	vector <int> header_(3);
	int contador_header_ =0;
	int m = stoi(argv[3]);
	int contador_ =0;
	vector<string> tabela= getTabela(m);
    num_min = tabela[0].size();
    num_max = tabela[tabela.size()-1].size();
	cout << "Starting Decoding Header..." << endl;
	while((bit_ = bitstream.readBit()) != EOF){
		// cout <<"Contador header:" << contador_header_<< endl ;
		// cout <<"min:" << num_min<< endl ;
		// cout <<"max:" << num_max<< endl ;
		// cout <<"contador:" << contador_<< endl ;
		if (bit_ == 0){
			codified_ = codified_ + '0';
		}
		else if(bit_ == 1){
			codified_ = codified_ + '1';
			if (flag_primeiro_1_ ==0 && flag_acabou_ ==1){
				flag_primeiro_1_ = 1;
				
				posicao_ = contador_+1;
			
				contador_ = 0;
			}
		}
		
		if (contador_==num_min+1 && flag_primeiro_1_ == 1){
			codified2_ = codified_.substr(posicao_,num_min);
			
			for (int i=0; i < tabela.size();i++){
				if(tabela[i]==codified2_){
					
					int numero = golomb.decodeString(codified_,m);
					header_[contador_header_] = numero;
					contador_header_++;
					
			
					flag_acabou_=1;
					flag_primeiro_1_ = 0;
					contador_ =-1;
					codified_ = "";
					codified2_ = "";

					
					
				}
			}
		}
		else if (contador_==num_max+1 && flag_primeiro_1_ == 1){
			codified2_ = codified_.substr(posicao_,num_max);
			
			for (int i=0; i < tabela.size();i++){
				if(tabela[i]==codified2_){
					
					int numero = golomb.decodeString(codified_,m);
					header_[contador_header_] = numero;
					contador_header_++;

					
					
					
					flag_acabou_=1;
					flag_primeiro_1_ = 0;
					contador_ =-1;
					
					
					codified_ = "";
					codified2_ = "";

					
					

				}
			}
			
			
		}
		if (contador_header_ >= 3){
			break;
		}
		
		contador_++;
	}
	cout << "Header Decoded" << endl;
	cout << "Starting Decoding rest of the file..." << endl;
	SndfileHandle sfhOut { argv[1], SFM_WRITE, header_[0],
	  header_[1], header_[2] };
	if(sfhOut.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }
    
   
   
    int contador=0;

    ofstream myfile;
	myfile.open ("aux2",std::ios_base::app);

    vector<short> samples(2);
	vector<short> samples_anteriores= {0,0};
	
	if (header_[1] == 2){
        
        int bit;
        string codified = "";
        string codified2 = "";
        int flag_primeiro_1 = 0;
        int flag_aux = 0;
        int contador= 0;
        int posicao = 0;
        int flag_acabou = 1;
		int contador2= 0;

		int palavras =0;
        while((bit = bitstream.readBit()) != EOF){
            if (bit == 0){
                codified = codified + '0';
            }
            else if(bit == 1){
                codified = codified + '1';
                if (flag_primeiro_1 ==0 && flag_acabou ==1){
                    flag_primeiro_1 = 1;
                    
                    posicao = contador+1;
                
                    contador = 0;
                }
            }
            
            if (contador==num_min+1 && flag_primeiro_1 == 1){
                codified2 = codified.substr(posicao,num_min);
               
                for (int i=0; i < tabela.size();i++){
                    if(tabela[i]==codified2){
                       
                        int numero = golomb.decodeString(codified,m);
						if (stoi(argv[2]) > 0){
							numero = quantize(numero,stoi(argv[2]));
						}
						
                      
                        if (contador2==1){
							short side = numero + samples_anteriores[1];

							
							short right = (2*samples[0] - side)/2;
							short left = side + right;
							
							vector<short> left_right= {left,right};
							samples[contador2] = (short)side;
							
							sfhOut.writef(left_right.data(), samples.size()/2);
							samples_anteriores = samples;
							contador2=0;
							palavras++;
							
						}
						else if(contador2==0){
							short mid = numero + samples_anteriores[0];
							
							samples[contador2] = (short)mid;

							contador2++;
						}
						
                        flag_acabou=1;
                        flag_primeiro_1 = 0;
                        contador =-1;
                        codified = "";
                        codified2 = "";

						
						
                    }
                }
            }
            else if (contador==num_max+1 && flag_primeiro_1 == 1){
                codified2 = codified.substr(posicao,num_max);
                
                for (int i=0; i < tabela.size();i++){
                    if(tabela[i]==codified2){
                       
                        int numero = golomb.decodeString(codified,m);
                        if (stoi(argv[2]) > 0){
							numero = quantize(numero,stoi(argv[2]));
						}

						if (contador2==1){
							short side = numero + samples_anteriores[1];

							
							short right = (2*samples[0] - side)/2;
							short left = side + right;
							
							vector<short> left_right= {left,right};
							samples[contador2] = (short)side;
							
							sfhOut.writef(left_right.data(), samples.size()/2);
							samples_anteriores = samples;
							contador2=0;
							palavras++;
							
						}
						else if(contador2==0){
							short mid = numero + samples_anteriores[0];
							
							samples[contador2] = (short)mid;

							contador2++;
							
						}
							
                       
                       
                        flag_acabou=1;
                        flag_primeiro_1 = 0;
                        contador =-1;
                        myfile << numero  << " ";
                      
                        codified = "";
                        codified2 = "";

                    }
                }
                
                
            }
            
            contador++;
			


        }
		cout << "Ended Decoding..." << endl;
         
        
	}
	else if (header_[1]  == 1){
		
		int bit;
        string codified = "";
        string codified2 = "";
        int flag_primeiro_1 = 0;
        int flag_aux = 0;
        int contador= 0;
        int posicao = 0;
        int flag_acabou = 1;
		int contador2= 0;

		short ch_anterior = 0;

		int palavras =0;
        while((bit = bitstream.readBit()) != EOF){
            if (bit == 0){
                codified = codified + '0';
            }
            else if(bit == 1){
                codified = codified + '1';
                if (flag_primeiro_1 ==0 && flag_acabou ==1){
                    flag_primeiro_1 = 1;
                    
                    posicao = contador+1;
                
                    contador = 0;
                }
            }
            
            if (contador==num_min+1 && flag_primeiro_1 == 1){
                codified2 = codified.substr(posicao,num_min);
               
                for (int i=0; i < tabela.size();i++){
                    if(tabela[i]==codified2){
                       
                        int numero = golomb.decodeString(codified,m);
						if (stoi(argv[2]) > 0){
							numero = quantize(numero,stoi(argv[2]));
						}
						
						short aux = numero + ch_anterior;
						vector<short> ch = {aux};
						ch_anterior = ch[0];
						sfhOut.writef(ch.data(), samples.size()/2);
						samples_anteriores = samples;
						
						
							
					
						
                        flag_acabou=1;
                        flag_primeiro_1 = 0;
                        contador =-1;
                        codified = "";
                        codified2 = "";

						
						
                    }
                }
            }
            else if (contador==num_max+1 && flag_primeiro_1 == 1){
                codified2 = codified.substr(posicao,num_max);
                
                for (int i=0; i < tabela.size();i++){
                    if(tabela[i]==codified2){
                       
                        int numero = golomb.decodeString(codified,m);
                        if (stoi(argv[2]) > 0){
							numero = quantize(numero,stoi(argv[2]));
						}
						
						short aux = numero + ch_anterior;
						vector<short> ch = {aux};
						ch_anterior = ch[0];
						sfhOut.writef(ch.data(), samples.size()/2);
						samples_anteriores = samples;
							
                       
                       
                        flag_acabou=1;
                        flag_primeiro_1 = 0;
                        contador =-1;
                        myfile << numero  << " ";
                      
                        codified = "";
                        codified2 = "";

                    }
                }
                
                
            }
            
            contador++;
			


        }
		cout << "Ended Decoding..." << endl;
         


	}

	


}


