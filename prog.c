#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

main(){

FILE *fp;
int num = 0, x = 0, cont = 0, i = 0, m = 1, co = 0, l, k, verif = 1, qtdeArq = 0, sum = 0;		//Variáveis de auxílio, a maioria
char arquivos[15], cand[] = "candidatos.";

// Vetor vetor[] que irá receber os arquivos e vetorAux[] que receberá, de vetor[], os registros de vetor[0](raíz) até ficar completo(ordenado)
//Candidato vetor[300], vetorAux[300], aux;

do{	// Verifica quantos arquivos existem no diretório
	sprintf(arquivos,"%s%03d",cand,num);
	num++;
	qtdeArq++;
while(access(arquivos,F_OK) != -1)	

while((qtdeArq % 6) != 0){		// Calcula a quantidade de arquivos que serão criados na Implementação
	sum+= qtdeArq;
	qtdeArq = (qtdeArq % 6) + (qtdeArq / 6);
}

Candidato vetor[] = (char*)malloc(sum*sizeof(Candidato));
Candidato vetorAux[] = (char*)malloc(sum*sizeof(Candidato));

cand = 0;

	/* Lendo registro dos 6 arquivos para o vetor */
	while(verif != 0){
		sprintf(arquivos,"%s%03d",cand,num);
		cand++;
		fp = fopen(arquivos,"rb");
		if(fp == NULL){
			printf("Erro ao abrir arquivo.\n");
			verif = 0;
			break;
		}else{
		printf("Aberto arquivo %s\n\n",arquivos);

		fread(&vetor[i],sizeof(Candidato),i+1,fp);

		/* O loop abaixo descobre o tamanho de cada arquivo e armazena o próximo espaço livre para início do próximo arquivo */
		while(vetor[i].periodo != 0){
		printf("i = %d, i+1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",i,i+1,   // [Impressão]
				vetor[i].inscr,vetor[i].nome,vetor[i].periodo,vetor[i].turno,vetor[i].posicao,vetor[i].curso);											  // [Impressão]
			i++;
			fread(&vetor[i],sizeof(Candidato),SEEK_CUR,fp);
		}
		fclose(fp);
		x++;
		}
	}
	/* Fim de Leitura */

	/* Ordenando vetor com registros dos 6 arquivos abertos */
	printf("Inicio Heapsort\n\n");
	verif = 1;
	while(m <= i){
		verif = 1;
		while(verif != 0){ 	// Se 'verif' retornar sem alterações, vetor já estará ordenado
			verif = 0;			// Zera o atributo a cada nova varredura
			for(k = 0; 2*k+2 <= i-m; k++){	
				l = 2*k+1;
				if(strcmp(vetor[l].nome,vetor[l+1].nome) > 0)	// Verifica qual 'filho' é o menor
					l++;
				if(strcmp(vetor[l].nome,vetor[k].nome) < 0){ 	// Compara 'Pai' com 'menor filho'
					aux = vetor[l];
					vetor[l] = vetor[k];
					vetor[k] = aux;
					verif = 1;		// Altera 'verif', forçando mais um Loop no final
					cont++;
				}
			}
		}
		vetorAux[m-1] = vetor[0];			// Próximo índice vazio de vetorAux[] recebe raíz de vetor[]
		vetor[0] = vetor[i-m];			// Raíz de vetor[] recebe último índice do vetor
		m++;						// Incrementa m para atualizar próximo índice vazio de vetorAux[] (vetorAux[m-1]) e reduzir de i no loop (i-m+1)
	}	
	/* Fim de ordenação */	

	/* Escreve Vetor ordenado no arquivo de saída */
	fp = fopen("candidatos.txt","wb");
	fwrite(vetorAux,sizeof(Candidato),i,fp);
	fclose(fp);
	/* Fim de leitura */

	/* Leitura do novo arquivo, já ordenado - [Impressão] */
	printf("Abrindo arquivo após Ordenação.\n\n");

	fp = fopen("candidatos.txt","rb");
	
	if(fp == NULL)
		printf("Erro ao abrir arquivo.\n");
	else{
		fread(vetor,sizeof(Candidato),i,fp);
		for(k = 0; k < i ; k++){
			printf("k = %d, k + 1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",k,k+1,
						vetor[k].inscr,vetor[k].nome,vetor[k].periodo,vetor[k].turno,vetor[k].posicao,vetor[k].curso);
		}
	}
	fclose(fp);
	/* Fim de leitura */	

	dispose(vetor);
	dispose(vetorAux);
	
}

