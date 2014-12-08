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

void leArquivo();
int verifTamanho(int i, Candidato *vetor);
Candidato ordenaArquivo(Candidato *vetor, int fim);
void criaArquivo(Candidato *vetor, int i);


FILE *fp;
int num = 0, qtdeArq = -1, final = 0;
char vetArquivos[15], arquivos[15], cand[15] = "candidatos.";
void leArqOrdenado();

main(){

	/* Verifica quantidade de arquivos */
	do{
		sprintf(arquivos,"%s%03d",cand,num);
		num++;
		qtdeArq++;
	}while(access(arquivos,F_OK) != -1);

	num = 0;		// Para reler os arquivos a partir de "candidatos.000", onde 000 = n

	/* Fim de verificação - Resultado em qtdeArq */

	while(final != 1)
		leArquivo();	// Função para ler 6 arquivos
}

void leArquivo(){

	int i = 0, ciclos = 0, verif = 1;
	Candidato vetor[1000];
	
	while(verif != 0 && ciclos < 6){
		sprintf(vetArquivos,"%s%03d",cand,num);	
		fp = fopen(vetArquivos,"rb");
		if(fp == NULL){
			printf("Erro ao abrir arquivo.\n");
			verif = 0;
			break;
		}else{
			printf("Aberto arquivo %s\n\n",vetArquivos);
			fread(&vetor[i],sizeof(Candidato),i+1,fp);
			i = verifTamanho(i, vetor);	// i recebe tamanho calculado na função verifTamanho()
			fclose(fp);
			num++;	// num incrementado para leitura de proximo arquivo (ex: num de 000 para 001)
			ciclos++;
		}
	}

	/* Envia vetor com registros para serem ordenados na função de ordenação ordenaArquivo() */
	//*vetor = ordenaArquivo(vetor,i);
	ordenaArquivo(vetor, i);
	/* Envia vetor já ordenado para ser gravado em novo arquivo pela função criaArquivo() */
	//criaArquivo(ordenaArquivo(vetor, i),i);

}

/* Função para descobrir tamanho de cada arquivo para que o próximo seja armazenado no indice seguinte do vetor */
int verifTamanho(int i, Candidato *vetor){
		
	while(vetor[i].periodo != 0){
		printf("i = %d Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",i, 
					vetor[i].inscr,vetor[i].nome,vetor[i].periodo,vetor[i].turno,vetor[i].posicao,vetor[i].curso);
		i++;
		fread(&vetor[i],sizeof(Candidato),SEEK_CUR,fp);
		
	}

	return i;

}

/* Função para ordenar vetor, com os registros lidos, com o Heapsort */
Candidato ordenaArquivo(Candidato *vetor, int fim){
	int k, l, ini, verif;
	Candidato sub[1000], aux;

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
	//	ini++;									// Incrementa ini para atualizar próximo índice vazio de sub[]
	//	printf("sub[ini-1] = %s e vetor[] = %s\n",sub[ini-1].nome,vetor[0].nome);
	}

	criaArquivo(sub,fim);
	
//	return *sub;

}

/* Função para criar arquivo com registros, dos últimos arquivos lidos, ordenados */
void criaArquivo(Candidato *vetor, int i){

	if(num >= qtdeArq){
		strcpy(arquivos,"candidatos.txt");
		final = 1;
	}else
		sprintf(arquivos,"%s%03d",cand,qtdeArq++);
		
	printf("\nDepois do if|else - arquivos = %s\n\n",arquivos);

	/* Escreve Vetor, já ordenado, no arquivo de saída */ 
	fp = fopen(arquivos,"wb");
	fwrite(vetor,sizeof(Candidato),i,fp);
	fclose(fp);
	/* Fim de leitura */
	
}

/* Função (bônus) para ler arquivo já ordenado */
void leArqOrdenado(int i){
	int k;
	Candidato vet[1000];
	printf("Abrindo arquivo após Ordenação.\n\n");

   fp = fopen("candidatos.txt","rb");

   if(fp == NULL)
      printf("Erro ao abrir arquivo.\n");
   else{
      fread(vet,sizeof(Candidato),i,fp);
      for(k = 0; k < i ; k++){
         printf("k = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",k,
                  vet[k].inscr,vet[k].nome,vet[k].periodo,vet[k].turno,vet[k].posicao,vet[k].curso);
      }
   }
   fclose(fp);
   /* Fim de leitura */	


}
