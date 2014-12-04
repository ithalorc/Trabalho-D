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

//char vetArquivos[] = {"candidatos.000","candidatos.001","candidatos.002","candidatos.003","candidatos.004","candidatos.005","candidatos.006","candidatos.007","candidatos.008","candidatos.009","candidatos.010","candidatos.011","candidatos.012","candidatos.013","candidatos.014","candidatos.015","candidatos.016","candidatos.017","candidatos.018","candidatos.019","candidatos.020","candidatos.021","candidatos.022","candidatos.023","candidatos.024","candidatos.025","candidatos.026","candidatos.027","candidatos.028","candidatos.029","candidatos.030","candidatos.031","candidatos.032","candidatos.033","candidatos.034","candidatos.035","candidatos.036","candidatos.037","candidatos.038","candidatos.039","candidatos.040","candidatos.041","candidatos.042","candidatos.043","candidatos.044","candidatos.045","candidatos.046","candidatos.047","candidatos.048","candidatos.049","candidatos.050","candidatos.051","candidatos.052","candidatos.053","candidatos.054","candidatos.055","candidatos.056","candidatos.057","candidatos.058","candidatos.059","candidatos.060","candidatos.061","candidatos.062","candidatos.063","candidatos.064","candidatos.065","candidatos.066","candidatos.067","candidatos.068};

FILE *fp;
int x = 0, cont = 0, i = 0, l, k, verif = 1;
char vetArquivos[2][15] = {"candidatos.000","candidatos.001"};

Candidato c[100], aux;

	/* Lendo 6 arquivos */
	while(verif != 0){
		fp = fopen(vetArquivos[x],"rb");
		if(fp == NULL){
			printf("Erro ao abrir arquivo.\n");
			verif = 0;
			break;
		}else{
		printf("Aberto arquivo %s\n\n",vetArquivos[x]);
		fread(&c[i],sizeof(Candidato),i+1,fp);

		while(c[i].periodo != 0){
			printf("i = %d, i+1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",i,i+1,
				c[i].inscr,c[i].nome,c[i].periodo,c[i].turno,c[i].posicao,c[i].curso);
			i++;
			fread(&c[i],sizeof(Candidato),SEEK_CUR,fp);
		}
		printf("Saiu do while\n\n");
		fclose(fp);
		x++;
		}
	}
	/* Fim de Leitura */

	/* escrevendo no arquivo de saída */
	fp = fopen("candidatos.txt","wb");
	
		// Heapsort
	printf("Inicio HeapSort\n\n");
	verif = 1;
	while(verif != 0){ 	// Se 'verif' retornar sem alterações, vetor já estará ordenado
		verif = 0;			// Zera o atributo a cada nova varredura
		for(k = 0; 2*k+2 <= i; k++){	
			l = 2*k+1;
			if(strcmp(c[l].nome,c[l+1].nome) > 0){
				l++;
			}
			if(strcmp(c[l].nome,c[k].nome) < 0){ 	// Compara 'Pai' com 'menor filho'
				aux = c[l];
				c[l] = c[k];
				c[k] = aux;
				verif = 1;		// Altera 'verif', forçando mais um Loop no final
				cont++;
			}
		}
	}

	printf("\ncont = %d\n",cont);

	for(k = 0; k < i; k++)
		fwrite(&c[k],sizeof(Candidato),k+1,fp);
	fclose(fp);
	/* fim da escrita */

	
	/* Lendo arquivo novo */
	fp = fopen("candidatos.txt","wb");
	
	if(fp == NULL)
		printf("Erro ao abrir arquivo.\n");
	else{
		for(k = 0; k < i ; k++){
			fread(&c[k],sizeof(Candidato),k+1,fp);
			printf("k = %d, k + 1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",k,k+1,
						c[k].inscr,c[k].nome,c[k].periodo,c[k].turno,c[k].posicao,c[k].curso);
		}
//		// Heapsort
//		while(verif != 0){ 	// Se 'verif' retornar sem alterações, vetor já estará ordenado
//			verif = 0;	// Zera o atributo a cada nova varredura
//			for(k = 0; k < i; k++){	
//				if(strcmp(c[2*k+1].nome,c[k].nome) < 0){ // Compara 'Pai' com 'filho da esquerda'
//					aux = c[2*k+1];
//					c[2*k+1] = c[k];
//					c[k] = aux;
//					verif = 1; 	// Altera 'verif', forçando mais um Loop no final
//				}
//				if(strcmp(c[2*k+2].nome,c[k].nome) < 0){ // Compara 'Pai' com 'filho da direita'
//						aux = c[2*k+2];
//						c[2*k+2] = c[k];
//						c[k] = aux;
//						verif = 1; // Altera 'verif', forçando mais um Loop no final
//				}
//			}
//		}
//
//	for(k = 0; k < i; k++)
//		fwrite(&c[k],sizeof(Candidato),k+1,fp);
//
//	fclose(fp);
//	}
	/* Fim de leitura */

	printf("Abrindo arquivo após Ordenação.\n\n");

	fp = fopen("candidatos.txt","rb");
	
	if(fp == NULL)
		printf("Erro ao abrir arquivo.\n");
	else{
		for(k = 0; k < i ; k++){
			fread(&c[k],sizeof(Candidato),k+1,fp);
			printf("k = %d, k + 1 = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",k,k+1,
						c[k].inscr,c[k].nome,c[k].periodo,c[k].turno,c[k].posicao,c[k].curso);
		}
	}
	fclose(fp);	
	// Heapsort
	/* Ordenando vetor com 6 arquivos em memória - Heapsort */
	
}

}
