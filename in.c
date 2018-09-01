#include <stdio.h>

int main()
{
    while(1){ //O while rodará enquanto a entrada não terminar (while getline!= -1)
        int bytes_lidos;
        int nbytes = 12;
        char *minha_str;
        minha_str = (char *) malloc (nbytes + 1);
        bytes_lidos = getline (&minha_str, &nbytes, stdin); //Lendo a linha de entrada
         if (bytes_read == -1){
                puts ("Arquivo de entrada terminou!");
               break;
        }else{
                puts ("Você digitou:");
                puts (minha_str);
        }
    }


    return 0;
}
