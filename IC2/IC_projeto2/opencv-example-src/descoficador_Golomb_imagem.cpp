
#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.cpp"


#include <iostream>
#include <opencv2/opencv.hpp>
#include "Golomb.cpp"
using namespace cv;
using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;
int num_max = 0;
int num_min = 0;
int count_header = 0;
int cols = 0;
int rows = 0;


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

    
  
    int m = stoi(argv[2]);
    vector<string> tabela= getTabela(m);
	// for(int i=0;i<tabela.size();i++){
	// 	cout << tabela[i] << endl;
	// }
    num_min = tabela[0].size();
    num_max = tabela[tabela.size()-1].size();
  
	Golomb golomb{};
    BitStream bitstream{"ficheiro_codificado_imagem","r"};
    int bit;
    string codified = "";
    string codified2 = "";
    int flag_primeiro_1 = 0;
    int flag_aux = 0;
    int contador= 0;
    int posicao = 0;
    int flag_acabou = 1;

    
    int contador_rgb= 0;
    int contador_i = 0;
    int contador_j=0;
	cout << "Starting decoding header..." << endl;
	// while para header
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
                    // cout << endl;
                    
                    int numero = golomb.decodeString(codified,m);

					if (count_header==0){
						rows = numero;
						count_header++;
					} else if (count_header ==1){

						cols = numero;
						count_header++;
					}

					flag_acabou=1;
					flag_primeiro_1 = 0;
					contador =-1;
					
					codified = "";
					codified2 = "";

                }
            }
			if (count_header==2){
				break;	
			}

        }

        else if (contador==num_max+1 && flag_primeiro_1 == 1){
            codified2 = codified.substr(posicao,num_max);
            
            
            for (int i=0; i < tabela.size();i++){
                

                if(tabela[i]==codified2){
                    
                    int numero = golomb.decodeString(codified,m);
                    
					if (count_header==0){
						rows = numero;
						count_header++;
					} else if (count_header ==1){
						cols = numero;
						count_header++;
					}
                   

					flag_acabou=1;
					flag_primeiro_1 = 0;
					contador =-1;
					
					
					codified = "";
					codified2 = "";

					
                    
                }

            }
			if (count_header==2){
				break;	
			}
            
            
        }
        
        contador++;
        

    }

	cout << "Ended decoding header:" << endl;
	cout << "Starting decoding rest of the file..." << endl;


	Mat img2(rows, cols, CV_8UC3, Scalar(0, 0, 0));
	int a,b,c;
	int x =0;

	// while fora do header
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
		
        
		//se for o mais pequeno na tabela
        if (contador==num_min+1 && flag_primeiro_1 == 1){
            codified2 = codified.substr(posicao,num_min);
            
            
            for (int i=0; i < tabela.size();i++){

				// primeria linha e coluna
                if(tabela[i]==codified2 && count_header>=2){
                    
                    
                    int numero = golomb.decodeString(codified,m); 	// numero -> oque vem do ficheiro (predictor)
																	// oque vem da imagem (Xn)

					if (contador_i == 0 || contador_j == 0){
						// RED
						if (contador_rgb== 0){

							img2.at<Vec3b>(contador_i, contador_j)[0] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// GREEN
						else if(contador_rgb== 1){
							img2.at<Vec3b>(contador_i, contador_j)[1] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// BLUE
						else if(contador_rgb== 2){
							img2.at<Vec3b>(contador_i, contador_j)[2] = saturate_cast<uchar>(numero + x);
							contador_rgb=0;
							if (contador_j == cols -1){
								contador_j=0;
								contador_i++;
							}
							else{
								contador_j++;
							}

							
						}


					// sem ser primeira linha e coluna
					} else {

						// RED
						if (contador_rgb== 0){

							a = img2.at<Vec3b>(contador_i, contador_j-1)[0];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[0];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[0];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;

							img2.at<Vec3b>(contador_i, contador_j)[0] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// GREEN
						else if(contador_rgb== 1){
							a = img2.at<Vec3b>(contador_i, contador_j-1)[1];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[1];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[1];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;

							img2.at<Vec3b>(contador_i, contador_j)[1] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// BLUE
						else if(contador_rgb== 2){
							a = img2.at<Vec3b>(contador_i, contador_j-1)[2];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[2];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[2];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;

							img2.at<Vec3b>(contador_i, contador_j)[2] = saturate_cast<uchar>(numero + x);

							contador_rgb=0;
							if (contador_j == cols -1){
								contador_j=0;
								contador_i++;
							}
							else{
								contador_j++;
							}	
						}
					}

					flag_acabou=1;
					flag_primeiro_1 = 0;
					contador =-1;
					
					codified = "";
					codified2 = "";
                }
            }
        }
		// quando foi o maior da tabela
        else if (contador==num_max+1 && flag_primeiro_1 == 1){
            codified2 = codified.substr(posicao,num_max);
            
            
            for (int i=0; i < tabela.size();i++){
                

                // primeria linha e coluna
                if(tabela[i]==codified2 && count_header>=2){
                    
                    
                    int numero = golomb.decodeString(codified,m); 	// numero -> oque vem do ficheiro (predictor)
																	// oque vem da imagem (Xn)

					if (contador_i == 0 || contador_j == 0){
						// RED
						if (contador_rgb== 0){

							img2.at<Vec3b>(contador_i, contador_j)[0] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// GREEN
						else if(contador_rgb== 1){
							img2.at<Vec3b>(contador_i, contador_j)[1] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// BLUE
						else if(contador_rgb== 2){
							img2.at<Vec3b>(contador_i, contador_j)[2] = saturate_cast<uchar>(numero + x);
							contador_rgb=0;
							if (contador_j == cols -1){
								contador_j=0;
								contador_i++;
							}
							else{
								contador_j++;
							}

							
						}


					// sem ser primeira linha e coluna
					} else {

						// RED
						if (contador_rgb== 0){

							a = img2.at<Vec3b>(contador_i, contador_j-1)[0];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[0];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[0];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;
							//cout << "R" << numero + x << endl;
							img2.at<Vec3b>(contador_i, contador_j)[0] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// GREEN
						else if(contador_rgb== 1){
							a = img2.at<Vec3b>(contador_i, contador_j-1)[1];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[1];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[1];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;

							//cout << "G" << numero + x << endl;
							img2.at<Vec3b>(contador_i, contador_j)[1] = saturate_cast<uchar>(numero + x);
							contador_rgb++;
						}
						// BLUE
						else if(contador_rgb== 2){
							a = img2.at<Vec3b>(contador_i, contador_j-1)[2];
							b = img2.at<Vec3b>(contador_i-1, contador_j)[2];
							c = img2.at<Vec3b>(contador_i-1, contador_j-1)[2];

							if (c >= max(a, b))
								x = min(a, b);
							else if (c < min(a, b))
								x = max(a, b);
							else
								x = a + b - c;

							//cout << "B" << numero + x << endl;
							img2.at<Vec3b>(contador_i, contador_j)[2] = saturate_cast<uchar>(numero + x);

							contador_rgb=0;
							if (contador_j == cols -1){
								contador_j=0;
								contador_i++;
							}
							else{
								contador_j++;
							}	
						}
					}

					flag_acabou=1;
					flag_primeiro_1 = 0;
					contador =-1;
					
					codified = "";
					codified2 = "";
                }
            }
            
            
        }
        
        contador++;
        if (contador_j == cols -1 && contador_i == rows -1  ){
           
            break;
            
        }
        
    }
	cout << "Ended decoding rest of the file..." << endl;
    imwrite(argv[1],img2);
    
}