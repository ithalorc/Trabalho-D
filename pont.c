#include <stdio.h>
#include <unistd.h>

main(){

char a[15], c[] = "2Lucas.001";
char arq[] = "candidatos.";

int i, cont = 0,j;

while (cont <= 68){
	sprintf(a,"%s%03d",arq,cont);
	cont++;
}

printf("%s\n",a);

if (access(a,F_OK) != -1){
	printf("OK");
}else{
	printf("NOTOK");
}

i = cont % 6;
j = cont / 6;

printf("\ni = %d j = %d cont = %d\t%d\n",i,j,cont,0%6);

}
