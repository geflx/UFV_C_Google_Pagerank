#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    while(1){ //O while rodará enquanto a entrada não terminar (while getline!= -1)
        int bytes_lidos;
        int nbytes = 12;
        char *minha_str;
        minha_str = (char *) malloc (nbytes + 1);
        bytes_lidos = getline (&minha_str, &nbytes, stdin); //Lendo a linha de entrada
         if (bytes_lidos == -1){
                puts ("Arquivo de entrada terminou!");
               break;
        }else{
                puts ("Você digitou:");
                puts (minha_str);
        }
        printf("Minha str é: %s",minha_str);
        char * pch;
        int i=0;
        int *numeros_lidos = calloc(1,sizeof(int)); //Vetor para armazenar os numeros lidos, comeca com 1 espaço
        pch = strtok (minha_str,":,");
        while (pch != NULL) {
            (numeros_lidos[i]) = (*pch - '0'); //Armazenando o inteiro lido ao vetor
            i++;
            numeros_lidos = (int *)realloc(numeros_lidos, 1*sizeof(int)); //Realocando o vetor para caber mais inteiros lidos
            printf ("%s\n",pch);
            pch = strtok (NULL, ":,");
        }
        int j=0;
        for(j=0;j<i;j++){
            printf("%d ",*(numeros_lidos+j)); //Imprimindo os inteiros lidos
        }
        printf("\n");
        free(pch);
        free(numeros_lidos);
    }


    return 0;
}
