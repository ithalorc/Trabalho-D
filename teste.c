#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//char vetArquivos[] = {"candidatos.000","candidatos.001","candidatos.002","candidatos.003","candidatos.004","candidatos.005","candidatos.006","candidatos.007","candidatos.008","candidatos.009","candidatos.010","candidatos.011","candidatos.012","candidatos.013","candidatos.014","candidatos.015","candidatos.016","candidatos.017","candidatos.018","candidatos.019","candidatos.020","candidatos.021","candidatos.022","candidatos.023","candidatos.024","candidatos.025","candidatos.026","candidatos.027","candidatos.028","candidatos.029","candidatos.030","candidatos.031","candidatos.032","candidatos.033","candidatos.034","candidatos.035","candidatos.036","candidatos.037","candidatos.038","candidatos.039","candidatos.040","candidatos.041","candidatos.042","candidatos.043","candidatos.044","candidatos.045","candidatos.046","candidatos.047","candidatos.048","candidatos.049","candidatos.050","candidatos.051","candidatos.052","candidatos.053","candidatos.054","candidatos.055","candidatos.056","candidatos.057","candidatos.058","candidatos.059","candidatos.060","candidatos.061","candidatos.062","candidatos.063","candidatos.064","candidatos.065","candidatos.066","candidatos.067","candidatos.068};    // Vetor completo, será usado futuramente (teoricamente)

FILE *fp;
int x = 0, cont = 0, i = 0, m = 1, co = 0, l, k, verif = 1;		//Variáveis de auxílio, a maioria

// Vetor com o nome dos arquivos a serem lidos
char vetArquivos[6][15] = {"candidatos.000","candidatos.001","candidatos.002","candidatos.003","candidatos.004","candidatos.005"}; 

// Vetor c[] que irá receber os arquivos e v[] que receberá, de c[], os registros de c[0](raíz) até ficar completo(ordenado)
Candidato c[300], v[300], aux;

	/* Lendo registro dos 6 arquivos para o vetor */
	while(verif != 0){
		fp = fopen(vetArquivos[x],"rb");
		if(fp == NULL){
			printf("Erro ao abrir arquivo.\n");
			verif = 0;
			break;
		}else{
		printf("Aberto arquivo %s\n\n",vetArquivos[x]);

		fread(&c[i],sizeof(Candidato),i+1,fp);

		/* O loop abaixo descobre o tamanho de cada arquivo e armazena o próximo espaço livre para início do próximo arquivo */
		while(c[i].periodo != 0){
		printf("i = %d, i+1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",i,i+1,   // [Impressão]
				c[i].inscr,c[i].nome,c[i].periodo,c[i].turno,c[i].posicao,c[i].curso);											  // [Impressão]
			i++;
			fread(&c[i],sizeof(Candidato),SEEK_CUR,fp);
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
				if(strcmp(c[l].nome,c[l+1].nome) > 0)	// Verifica qual 'filho' é o menor
					l++;
				if(strcmp(c[l].nome,c[k].nome) < 0){ 	// Compara 'Pai' com 'menor filho'
					aux = c[l];
					c[l] = c[k];
					c[k] = aux;
					verif = 1;		// Altera 'verif', forçando mais um Loop no final
					cont++;
				}
			}
		}
		v[m-1] = c[0];			// Próximo índice vazio de v[] recebe raíz de c[]
		c[0] = c[i-m];			// Raíz de c[] recebe último índice do vetor
		m++;						// Incrementa m para atualizar próximo índice vazio de v[] (v[m-1]) e reduzir de i no loop (i-m+1)
	}	
	/* Fim de ordenação */	

	/* Escreve Vetor ordenado no arquivo de saída */
	fp = fopen("candidatos.txt","wb");
	fwrite(v,sizeof(Candidato),i,fp);
	fclose(fp);
	/* Fim de leitura */

	/* Leitura do novo arquivo, já ordenado - [Impressão] */
	printf("Abrindo arquivo após Ordenação.\n\n");

	fp = fopen("candidatos.txt","rb");
	
	if(fp == NULL)
		printf("Erro ao abrir arquivo.\n");
	else{
		fread(c,sizeof(Candidato),i,fp);
		for(k = 0; k < i ; k++){
			printf("k = %d, k + 1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",k,k+1,
						c[k].inscr,c[k].nome,c[k].periodo,c[k].turno,c[k].posicao,c[k].curso);
		}
	}
	fclose(fp);
	/* Fim de leitura */	
	
}

