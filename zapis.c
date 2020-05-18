//Autor: Jakub Kokoszka

#include "projlib.h"

void zapis(typ_element *rekord){
	FILE *fp = NULL;
	if(rekord==NULL){
		fprintf(stderr, "Lista jest pusta.");
	}
	else{
		fp = fopen(plik, "w");
		typ_element *aktualny = rekord;
		do{
			fprintf(fp, "%s,%s,%s,%s\n", aktualny->pole1, aktualny->pole2, aktualny->pole3, aktualny->pole4);
			aktualny = aktualny->next;
		}while (aktualny != NULL);
		printf("Baza danych zostala poprawnie zapisana.");
	}
	fclose(fp);
}
