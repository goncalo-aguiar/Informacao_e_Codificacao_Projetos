#include "fcm_novo.cpp"

int main(int argc, char** argv)
{
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./lang <textfile> <textfile>" << endl;
        return 0; 
    }

    //Context order and alpha
    int k = -1;
    float a = 0;
    char l ='a';


    
    while(k <= 0){
        cout << "Insert context order (k): ";
        cin >> k;
    }
    while(a <= 0){
        cout << "Insert alpha (a): ";
        cin >> a;
    }
    

    //Load model and processing it
    fcm f = fcm(k, a);
    map<string, map<char, int>> model;
    cout << "Begin processing..." << endl;
   
    f.getModelo(model, argv[1]);
  
        
    cout << "Model loaded sucessfully!" << endl;

    //estimated number of bits required to compress second file
    f.estimate(model, argv[2]);
    cout << "Estimated number of bits to compress file: " << f.dist<< endl;
    cout << "Estimated number of bits per character: " << f.dist/f.num_letras << endl;

    
    return 0;
}