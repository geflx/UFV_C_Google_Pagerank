#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PG{  //Struct do page rank
    double PR;
    int n_sai;
    int *entra;
    int n_entra;
};
int main()
{
    struct PG *p;
    int n_paginas; //numero de paginas na entrada
    scanf("%d",&n_paginas);
    p=malloc(n_paginas * sizeof(struct PG)); 
    //Temporario: inicialziando com 0 o num de paginas que entram e saem de cada uma
    int zera=0; 
    for(zera=0;zera<n_paginas;zera++){
        p[zera].n_sai=0;
        p[zera].n_entra=0;
    }

    while(1){ //O while rodará enquanto a entrada não terminar (while getline!= -1)
        int bytes_lidos;
        int nbytes = 12;
        char *minha_str;
        minha_str = (char *) malloc (nbytes + 1);
        bytes_lidos = getline (&minha_str, &nbytes, stdin); //Lendo a linha de entrada
         if (bytes_lidos == -1){
               free(minha_str);
               printf("Arquivo de entrada terminou!\n");
               break;
        }else{
            /*
                printf ("Você digitou:\n");
                printf ("%s\n",minha_str);
            */
        }
        printf("Minha str é: %s",minha_str);
         
        
        char * pch;
        int i=0;
        int *numeros_lidos = calloc(1,sizeof(int)); //Vetor para armazenar os numeros lidos, comeca com 1 espaço
        pch = strtok (minha_str,":,");
        while (pch != NULL) {
            (numeros_lidos[i]) = (*pch - '0'); //Armazenando o inteiro lido ao vetor
            i++;
            numeros_lidos = (int *)realloc(numeros_lidos, 1*sizeof(int));//Realocando o vetor para caber mais inteiros lidos
            printf ("%s\n",pch);
            pch = strtok (NULL, ":,");
        }
        free(minha_str); //Liberando a memoria alocada para a entrada de minha_str
        int j=0;
        for(j=0;j<i;j++){
            printf("%d ",*(numeros_lidos+j)); //Imprimindo os inteiros lidos
            if(j>0){
                   //Nesta parte estamos indo na pagina que sai o link e colocando nela que o link da pagina em questao entra.          
                p[*(numeros_lidos+j)].entra=(int *) realloc( p[*(numeros_lidos+j)].entra , 1*sizeof(int)); //Alocando +1 pro passo abaixo
                p[*(numeros_lidos+j)].entra[p[*(numeros_lidos+j)].n_entra]=(*(numeros_lidos)); //Anotando na pagina a pagina que leva ate ela
                p[*(numeros_lidos+j)].n_entra++; //Aumentando o cont numero de paginas que leva ate ela
                
            }
        }
        //Tratando os dados lidos na linha atual da entrada:
        p[*(numeros_lidos)].n_sai= j-1; //Armazenando na pagina[i] o número de links que saem dela

        free(numeros_lidos);
        free(pch);
        printf("\n");
    }

    //Temporario: imprimindo os valores armazenados para verificar a entrada. ///////////////////////////////////
    int cont=0;
    int cont2=0;
    for (cont=0;cont<n_paginas;cont++){
        //printf("%d ",p[cont].n_sai);
        printf("Ola sou a pagina de indice %d! As paginas que tem link para mim sao:  ",cont);
        if(p[cont].n_entra==0){
            printf("nenhuma");
        }else{
            for(cont2=0;cont2<p[cont].n_entra;cont2++){
                printf("%d ",p[cont].entra[cont2]);
            }
        }
        printf("\n");
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    free(p);

    return 0;
}
