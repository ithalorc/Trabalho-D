#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

struct candidato
{
	char inscr[10];
	char nome[44];
	int periodo;
	char turno[3];
	int posicao;
	char curso[30];
};
typedef struct candidato Candidato;

void leArquivo();
void criaArquivo(Candidato *vetor, int i);
void zeraVetor(Candidato *vetor, int fim);
Candidato ordenaArquivo(Candidato *vetor, int fim);

FILE *fp;
int num = 0, qtdeArq = -1, final = 0;
float nLeituras = 0, nRegistros = 0;
char vetArquivos[15], arquivos[15], cand[15] = "candidatos.";
clock_t inicio,fim;
double elapsed;

main(){

	/* Verifica quantidade de arquivos */
	do{
		sprintf(arquivos,"%s%03d",cand,num);
		num++;
		qtdeArq++;
	}while(access(arquivos,F_OK) != -1);

	num = 0;		// Para reler os arquivos a partir de "candidatos.000", onde 000 = n
	/* Fim de verificação - Resultado em qtdeArq */

	while(final != 1){
		inicio = clock();
		leArquivo();	// Função para ler 6 arquivos
	}
	fim = clock();

	/* Imprime numero de passos durante a intercalação */
	printf("Numero de leituras = %.0f\nNumero de registros = %.0f\nNumero de passos = %.0f/%.0f = %.02f\n\n",nLeituras,nRegistros,nRegistros,nLeituras,nRegistros/nLeituras);
	
	/* Converte resultado do clock() para tipo double */
	elapsed = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
	
	/* Imprime tempo decorrido durante a intercalação */
	printf("Tempo de intercalação: %.04f\n\n",elapsed);
}

void leArquivo()
{
	int i = 0, ciclos = 0, verif = 1, fim = 0;
	Candidato vetor[2000];
	
	while(verif != 0 && ciclos < 6){
		sprintf(vetArquivos,"%s%03d",cand,num);	
		fp = fopen(vetArquivos,"rb");
		if(fp == NULL){
			printf("Erro ao abrir arquivo.\n");
			verif = 0;
			break;
		}else{
			printf("Aberto arquivo %s\n\n",vetArquivos);
			fim += fread(&vetor[fim],sizeof(Candidato),1000,fp);
			nRegistros += fim;
			nLeituras = fim;
			fclose(fp);
			num++;	// num incrementado para leitura de proximo arquivo (ex: num de 000 para 001)
			ciclos++;
		}
	}

	/* Envia vetor com registros para serem ordenados na função de ordenação ordenaArquivo() */
	ordenaArquivo(vetor, fim);

	/* Envia vetor já ordenado para ser gravado em novo arquivo pela função criaArquivo() */
	zeraVetor(vetor, fim);

}

/* Função para ordenar vetor, com os registros lidos, com o Heapsort */
Candidato ordenaArquivo(Candidato *vetor, int fim)
{
	int k, l, ini, verif;
	Candidato sub[2000], aux;

	printf("Início de Heapsort.\n\n");
	//while(ini <= fim){ 	// Fica no loop enquanto todo o vetor não for 'varrido'
	for(ini = 1; ini <= fim; ini++){
		verif = 1;
		while(verif != 0){		// Permanece no loop enquanto ocorrer alguma troca na ordenação
			verif = 0;
			for(k = 0; 2*k+2 <= fim -ini; k++){		// Permanece no loop enquanto k diferir da última posição do vetor
				l = 2*k+1;
				if(strcmp(vetor[l].nome,vetor[l+1].nome) > 0)
					l++;
				if(strcmp(vetor[l].nome,vetor[k].nome) < 0){ 	// Compara 'Pai' com 'menor filho'
						aux = vetor[l];
						vetor[l] = vetor[k];
						vetor[k] = aux;
						verif = 1;		// Altera 'verif', forçando mais um Loop no final
				}
			}
		}
		sub[ini-1] = vetor[0];				// Próximo índice vazio recebe raíz de vetor[]
		vetor[0] = vetor[fim - ini];		// Raíz de vetor[] recebe último índice de vetor[]
	}
	criaArquivo(sub,fim);
	zeraVetor(sub, fim);
}

/* Função para criar arquivo com registros, dos últimos arquivos lidos, ordenados */
void criaArquivo(Candidato *vetor, int i)
{
	if(num >= qtdeArq){
		strcpy(arquivos,"candidatos.txt");
		final = 1;
	}else
		sprintf(arquivos,"%s%03d",cand,qtdeArq++);

	/* Escreve Vetor, já ordenado, no arquivo de saída */
	fp = fopen(arquivos,"wb");
	fwrite(vetor,sizeof(Candidato),i,fp);
	fclose(fp);
	/* Fim de leitura */
}

/* Função para zerar vetor() */
void zeraVetor(Candidato *vetor, int fim)
{
	int i;

	for(i = 0; i < fim; i++)
		vetor[i].periodo = 0;
}
/* Fim de função zeraVetor() */

