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

	FILE *fp;
	Candidato c[5000], x[1];
	int k = 0,a;

	/* Leitura do novo arquivo, já ordenado - [Impressão] */
	printf("Abrindo arquivo após Ordenação.\n\n");
	
	fp = fopen("candidatos.txt","rb");
	
	//fread(&x[0],sizeof(Candidato),SEEK_END,fp);
	
	if(fp == NULL)
		printf("Erro ao abrir arquivo.\n");
	else{
		a = fread(c,sizeof(Candidato),20000,fp);
		while(c[k].periodo != 0){
			printf("a=%d,k = %d, Inscrição: %s, Nome: %s, Período: %d, Turno: %s, Posição: %d, Curso: %s\n",a,k,
						c[k].inscr,c[k].nome,c[k].periodo,c[k].turno,c[k].posicao,c[k].curso);
			k++;
		}
	}

	//printf("\n\nx[end].nome = %s\n",x[0].nome);
	
	fclose(fp);
	/* Fim de leitura */	

}
