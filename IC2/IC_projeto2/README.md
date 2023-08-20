to build: 
  make
 
To test:
	exercícios 1: 
	
    ../opencv-example-bin/cp_image boat.ppm copy.jpeg // onde boat.ppm é o ficheiro original, copy.png é a cópia
    
    ../opencv-example-bin/cp_effects boat.ppm neg.png vert.png hor.png rot.png more.png less.png // onde boat.ppm é o ficheiro original, copy.png é a cópia
    neg.jpeg é a versão negativa, vert.jpeg é o espelho vertical, hor.jpeg é o espelho horizontal, rot.jpeg é a imagem rodade, more.jpeg é a imagem com mais luz e less.jpeg a imagem com menos luz.
    
    
    
    ./codificador_Golomb sample.wav 0 999 (som origem, quantos bits perdidos , m)
    ./decoficador_Golomb out.wav 0 999 (som final, quantos bits perdidos , m)
    
    ./codificador_Golomb_imagem download.jpeg 0 67  (imagem origem, quantos bits perdidos , m)
    ./descoficador_Golomb_imagem download_pred.jpeg 0 67 (imagem final, quantos bits perdidos , m)

     Para calcular o SNR e o erro absoluto: 
    ../opencv-example-bin/wav_cmp sample.wav out.wav // sample.wav é a amostra original e out.wav o ficheiro após passar pelo codec

