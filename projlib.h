//Autor: Jakub Kokoszka
#ifndef projlib_h
#define projlib_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Zdefiniowanie makr sluzacych do konfiguracji kodu
#define plik "baza_danych.txt"
#define pole1 produkt
#define pole2 cena
#define pole3 opakowanie
#define pole4 marka
#define seek pole4

//Stworzenie struktury elementu listy dwukierunkowej w bazie danych
typedef struct element{
	struct element *next;	//wskaznik na nastepny element
	struct element *prev;	//wskaznik na poprzedni element
	char *pole1;		//pola opisujace kazdy rekord w bazie
	char *pole2;
	char *pole3;
	char *pole4;
}typ_element;

//Zdefiniowanie funkcji
void dodawanie_elementu(typ_element **rekord, char *pole1, char *pole2, char *pole3, char *pole4);
void wyswietlanie(typ_element **rekord);
int rozmiar(typ_element **rekord);
void usuwanie_pierwszego(typ_element **rekord);
void usuwanie(typ_element **rekord, int pozycja);
int menu(typ_element **rekord);
void wczytywanie(typ_element **rekord);
void szukanie(typ_element *, char *);
void zapis(typ_element *);

#endif