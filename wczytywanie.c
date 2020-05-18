//Autor: Jakub Kokoszka

#include "projlib.h"

void wczytywanie(typ_element **rekord){
	FILE *fp;
	fp = fopen(plik, "r");
	char *linia = NULL;
	char *pole1;
	char *pole2;
	char *pole3;
	char *pole4;

	//Alokacja zmiennych
	pole1 = (char*)malloc(20*sizeof(char));
	pole2 = (char*)malloc(3*sizeof(char));
	pole3 = (char*)malloc(20*sizeof(char));
	pole4 = (char*)malloc(20*sizeof(char));
	size_t len = 0;
	unsigned long r;
	
	//Sprawdzenie czy plik poprawnie sie otwiera
	if (fp == NULL){
		fprintf(stderr, "Blad podczas wczytywania bazy danych.");
		exit(-1);
	}
	
	//Wlasciwe wczytywanie bazy z pliku
	while((r = getline(&linia, &len, fp)) != -1){
		printf("%s", linia);
		sscanf(linia, "%[^,],%[^,],%[^,],%s", pole1, pole2, pole3, pole4);
		//Dodanie elementu bazy danych do listy dwukierunkowej
		dodawanie_elementu(rekord, pole1, pole2, pole3, pole4);
	}
	
	//Zamkniecie pliku
	fclose(fp);
}