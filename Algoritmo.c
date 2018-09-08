#include <stdio.h>
#include <math.h>	
#include <stdlib.h>
#include <string.h>
//Desenvolvido por Gabriel Felix e Matheus Lima em 07/09/2018
//github.com/geflx
//github.com/MatheusAL
//Algoritmo: Google's PageRank
struct PageRank{  //Struct do page rank
    double valorAtual;
	int IndicedaPagina;
    double valorAntigo;
    int n_SaiDeMim;  //número dos links que "Saem" da página
    int *LigaEmMim; //páginas que "Chegam"
    int n_LigaEmMim; //número de páginas que "Chegam"
};	

int E(struct PageRank *minhaAmostra, int numeroPaginas){ //Funcao atrelada ao Termino do Calculo.
	double somatorio=0;
	int i=0;
	for(i=0;i<numeroPaginas;i++){
		somatorio+= (minhaAmostra[i].valorAtual - minhaAmostra[i].valorAntigo) * (minhaAmostra[i].valorAtual - minhaAmostra[i].valorAntigo);
	}
	if (sqrt(somatorio)< 0.000001)
		return 1; //terminar o calculo!
	else
		return 0; //ainda não acabou...
}
double somatorioDosQueLigamEmMim(struct PageRank *minhaAmostra, int indice){ //Funcao usada dentro do Calculo, a do Somatorio.
	double somatorio=0;
	int i=0;
	for(i=0;i<minhaAmostra[indice].n_LigaEmMim;i++){  //Fazendo o calculo do Somatorio, utilizando as Paginas que chegam ate a Pagina[indice]
		int indiceDoQueLiga= minhaAmostra[indice].LigaEmMim[i];
		somatorio+=(minhaAmostra[indiceDoQueLiga].valorAntigo) / ((double)minhaAmostra[indiceDoQueLiga].n_SaiDeMim);
	}
	return somatorio;
}

int comparaPR(const void * a, const void *b){ //Funçao para comparacao

	if((*(struct PageRank*)a).valorAtual == (*(struct PageRank*)b).valorAtual){// Quando os dois valores do PageRank forem iguais
		return 0;
	}
	if((*(struct PageRank*)a).valorAtual>(*(struct PageRank*)b).valorAtual) // Quando o primeiro valor do PageRank for maior
		return -1;
	else	//Quando o segundo valor de PageRank e maior
		return 1;
}

int main(){

	///////////////////////////// Início da Leitura!  ////////////////////////////
    int numeroPaginas=-1; //Verifica se estamos no primeiro laco da leitura, lendo o numeroPaginas (n)
    struct PageRank *minhaAmostra;
    int jaAlocou=0; //variavel utilizada para verificar se ja alocamos a memória para as paginas
	while(1){ 

		if((numeroPaginas!=-1) &&(jaAlocou==0)){ //Verificando se ja lemos o numero de paginas para assim alocar a memoria!
			minhaAmostra=calloc(numeroPaginas, sizeof(struct PageRank));
			int k=0;
			jaAlocou=1; //Opa, agora não alocaremos mais.
		}
		int bytes_lidos;
		int nbytes=10;
        char *buffer;
		buffer = (char *) malloc (nbytes + 1);
		bytes_lidos = getline (&buffer, &nbytes, stdin); //Buffer fazendo seu trabalho de ler a linha
		if (bytes_lidos == -1){
               free(buffer);
               break;
        }
        char *quebra;
        quebra = strtok (buffer,":,"); //Utilizando a funco strtok para capturar os índices
        int indicePaginaMestre=-1; //Página Mestre: página que tem link para outras
        int indicePaginaComum; //Páginas Comuns: páginas que são "linkadas" pela Pagina Mestre
        while (quebra != NULL) {
        	if (numeroPaginas==-1){ //Capturando o numero de paginas na primeira linha da entrada.
            	numeroPaginas=atoi(quebra);
            	quebra = strtok (NULL, ":,");
            }else if(indicePaginaMestre==-1){ //Capturando qual e' a Pagina Mestre da linha digitada.
            	indicePaginaMestre=atoi(quebra);
            	quebra = strtok (NULL, ":,");
        	}else{
        		//Aqui lemos as Paginas Comuns e anotamos nelas que a Pagina Mestre tem link chegando ate elas.
            	indicePaginaComum=atoi(quebra); //Iremos ate o struct da Pagina que recebe link, e anotaremos a Pagina Mestre
				minhaAmostra[indicePaginaComum].n_LigaEmMim++;
            	minhaAmostra[indicePaginaComum].LigaEmMim=(int *)realloc(minhaAmostra[indicePaginaComum].LigaEmMim, (minhaAmostra[indicePaginaComum].n_LigaEmMim)* sizeof(int));
				minhaAmostra[indicePaginaComum].LigaEmMim[(minhaAmostra[indicePaginaComum].n_LigaEmMim)-1]= indicePaginaMestre;
				minhaAmostra[indicePaginaMestre].n_SaiDeMim++;
            	quebra = strtok (NULL, ":,");
        	}
        }
    	free(buffer);
    }
    ////////////////////////////  Fim da Leitura! /////////////////////////////////////


    /////////////////Inicializaçao dos valores!////////////////
    int i=0;
    for(i=0;i<numeroPaginas;i++){ //Passo Um
		minhaAmostra[i].IndicedaPagina=i; //Atribuindo o indice da pagina a uma variavel
    	minhaAmostra[i].valorAntigo= (1/(double)numeroPaginas);
    }
    /////////////////Fim da Inicializacao ////////////////////


    
    //////////////////Calculo do PageRank ///////////////////
    int aindaNaoAcabou = 0;
    double constanteUm = (1-0.85)/(double)numeroPaginas; //Duas variaveis para deixar receber os valores constantes descritos no trabalho.
	double constanteDois = 0.85;
    while(aindaNaoAcabou == 0){  //Enquanto E(k) > ε
    	for(i=0;i<numeroPaginas;i++){
    		if (minhaAmostra[i].n_SaiDeMim == 0){  //Tipo de pagina 1: Pagina que nao tem link para ninguem
    			double temp= minhaAmostra[i].valorAtual;
    			minhaAmostra[i].valorAtual= constanteUm + constanteDois * minhaAmostra[i].valorAntigo + constanteDois * somatorioDosQueLigamEmMim(minhaAmostra,i);
    			minhaAmostra[i].valorAntigo= temp;
    		}else{	
    			//Tipo de pagina 2: Pagina que tem link para alguem
    			double temp= minhaAmostra[i].valorAtual;
    			minhaAmostra[i].valorAtual= constanteUm + constanteDois * somatorioDosQueLigamEmMim(minhaAmostra,i);
    			minhaAmostra[i].valorAntigo= temp;
    		}
    	}

    	if(E(minhaAmostra,numeroPaginas) ==1){
    		aindaNaoAcabou=1; // Agora como E(k) < ε , fim!
    	}
    }
    ///////////////// Fim do Calculo /////////////////////



    /////////////// Ordenacao dos valores /////////////////
	qsort(minhaAmostra, numeroPaginas,sizeof(struct PageRank),comparaPR);

	//////////////////////////Fim da ordenaçao//////////////////////////

	////////////////Imprimindo as paginas apos ordenaçao
	for(int cont=0;cont<numeroPaginas;cont++){
		printf("%d \n",minhaAmostra[cont].IndicedaPagina);
	}



    ////////////Liberando os dados das paginas////////////
    for(i=0;i<numeroPaginas;i++){
    	free(minhaAmostra[i].LigaEmMim);
    }
    free(minhaAmostra);
    ///////////////Fim da liberaçao de memoria! >:-) /////////////////
	
	return 0;
}
