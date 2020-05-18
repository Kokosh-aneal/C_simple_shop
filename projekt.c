//W ramach projektu nalezy zaprojektowac prosta baze danych oparta na liscie dwukierunkowej. Aplikacja komunikuje sie z uzytkownikiem
//poprzez linie polecen. W kazdym z projektow musi byc zaimplementowana minimalna funkcjonalnosc:
//	>struktura danych reprezentujaca obiekt
//	>dodawanie obiektu na koniec listy
//	>Usuwanie obiektu (dowolnego)
//	>Wyszukiwanie obiektu po jednym z pol (wybrane przez programiste) i wypisanie wszystkich pol wyszukanego obiektu
//	>Wypisywanie na ekranie calej bazy danych
//	>Zapis bazy danych do pliku
//	>Wczytywanie bazy danych z pliku (czyli odtworzenie juz wprowadzonych danych z mozliwoscia dalszych modyfikacji bazy)
//
//Przykladowa aplikacja spelniajaca wymagania to: sklep, ksiegarnia, magazyn firmy kurierskiej itp
//
//Kazda osoba realizujaca projekt otrzymuje indywidualne rozszerzenie funkcjonalnosci, ktore musi byc zaimplementowane, aby projekt 
//mogl zostac ukonczony i zaliczony
//
//PROJEKT MUSI BYC PODZIELONY NA PLIKI (np. FUNKCJE REALIZUJACE WCZYTYWANIE I ZAPISYWANIE DANYCH SA IMPLEMENTOWANE W ODDZIELNYM PLIKU C)
//
//
//MODYFIKACJA:
//Wypisywanie statystyk elementow (np. srednia cena, dlugosc opisow, ilosc elementow)

//Autor: Jakub Kokoszka

#include "projlib.h"

//Funkcja dodajaca element do struktury
void dodawanie_elementu(typ_element **rekord, char *produkt, char *cena, char *opakowanie, char *marka){
	char *a;
	char *b;
	char *c;
	char *d;
	//Alokacja zmiennych oraz kopiowanie wartosci pol
	a = (char*)malloc(20*sizeof(char));
	b = (char*)malloc(20*sizeof(char));
	c = (char*)malloc(20*sizeof(char));
	d = (char*)malloc(20*sizeof(char));
	strncpy(a,produkt,20*sizeof(char));
	strncpy(b,cena,20*sizeof(char));
	strncpy(c,opakowanie,20*sizeof(char));
	strncpy(d,marka,20*sizeof(char));
	//Sprawdzenie czy istnieje pierwszy element listy
	if(*rekord==NULL){
		//Alokowanie miejsca dla pierwszego elementu listy
		*rekord = (typ_element *)malloc(sizeof(typ_element));
		(*rekord)->produkt = a;
		(*rekord)->cena = b;
		(*rekord)->opakowanie = c;
		(*rekord)->marka = d;
		(*rekord)->prev = NULL;
		(*rekord)->next = NULL;
	}
	else{
		//Tymczasowy element listy, potrzebny do kolejnych operacji
		typ_element *aktualny = *rekord;
		//Petla, ktora przenosi element aktualny na koniec listy
		while(aktualny->next != NULL){
			aktualny = aktualny->next;
		}
		//Alokacja pamieci dla kolejnego elementu listy
		aktualny->next = (typ_element *)malloc(sizeof(typ_element));
		aktualny->next->produkt = a;
		aktualny->next->cena = b;
		aktualny->next->opakowanie = c;
		aktualny->next->marka = d;
		aktualny->next->prev = aktualny;
		aktualny->next->next = NULL;
	}
}

//Funkcja usuwajaca pierwszy element listy
void usuwanie_pierwszego(typ_element **rekord){
	if(*rekord!=NULL){
		if((*rekord)->next==NULL){
			*rekord = NULL;
		}
		else{
			//Stworzenie tymczasowego elementu listy, ktory przybierze wartosc drugiego elementu listy
			typ_element *tmp;
			tmp=(*rekord)->next;
			//Zwolnienie pierwszego elementu
			free(*rekord);
			//Drugi element listy, staje sie pierwszym
			*rekord = tmp;
			(*rekord)->prev = NULL;
		}
	}
}

//Funkcja usuwajaca wybrany element z listy
void usuwanie(typ_element **rekord, int pozycja){
	if(pozycja>rozmiar(rekord)){
		fprintf(stderr, "Podany indeks jest zbyt duzy.");
		exit(-1);
	}
	else{
		//Usuniecie pierwszego elementu z listy
		if(pozycja==0){
			usuwanie_pierwszego(rekord);
		}
		else{
			//Usuwanie ostatniego elementu listy
			if(pozycja==(rozmiar(rekord)-1)){
				if((*rekord)->next == NULL){
					*rekord = NULL;
				}
				else{
					//Stworzenie tymczasowego elementu do operacji usuwania
					typ_element *aktualny = *rekord;
					//Przechodzenie na koniec listy
					while(aktualny->next->next!=NULL){
						aktualny = aktualny->next;
					}
					//Zwolnienie elementu nastepnego po ostatnim
					free(aktualny->next);
					//Wyzerowanie nastepnego po ostatnim
					aktualny->next = NULL;
				}
			}
			//Pozostale elementy
			else{
				//Stworzenie tymczasowego elementu do poruszania sie po liscie
				typ_element *aktualny = *rekord;
				//Stworzenie tymczasowego elementu do przechowywania wartosci nastepnego elementu
				typ_element *tmp;
				int i=0;
				//Przechodzenie do nastepnego elementu
				while(aktualny->next != NULL && i<pozycja-1){
					aktualny = aktualny->next;
					i++;
				}
				//Zapamietanie wartosci kolejnego elementu
				tmp= aktualny->next;
				//Przypisanie wskaznika z pominieciem elementu tmp
				aktualny->next = tmp->next;
				aktualny->next->prev = aktualny;
				free(tmp);
			}
		}
	}
}

//Funkcja wyswietlajaca baze danych na ekranie
void wyswietlanie(typ_element **rekord){
	printf("\n");
	int n=1;
	if(*rekord==NULL){
		fprintf(stderr, "Lista jest pusta.");
		exit(-1);
	}
	else{
		typ_element *aktualny = *rekord;
		printf("Nr. | Produkt | Cena | Opakowanie | Marka\n");
		do{
			printf("%d. | %s | %s | %s | %s |\n", n++, aktualny->produkt, aktualny->cena, aktualny->opakowanie, aktualny->marka);
			aktualny = aktualny->next;
		}while (aktualny != NULL);
	}
}

//Funkcja szukajaca wybranego przez uzytkownika elementu po polu nazwie marki produktu
void szukanie(typ_element *rekord, char *nazwa){
	//Zmienna potrzebna do porownywania kolejnych elementow z listy
	char *porownanie;
	porownanie = (char *)malloc(20*sizeof(char));
	if(rekord == NULL){
		fprintf(stderr,"Lista jest pusta.");
		exit(-1);
	}
	else{
		typ_element *aktualny = rekord;
		do{
			//Wyciagniecie wartosci pola danego elementu, ktorego szukamy
			porownanie = aktualny->seek;
			//Porownanie konkretnych elementow
			if(strcmp(nazwa, porownanie)==0){
				printf("Znaleziono: ");
				//Wypisanie zawartosci znalezionego elementu
				printf("%s %s %s %s\n", aktualny->produkt, aktualny->cena, aktualny->opakowanie, aktualny->marka);
			}
			//Przejscie do kolejnego elementu listy
			aktualny = aktualny->next;
		}while(aktualny != NULL);
	}
}

//Funkcja sprawdzajaca ilosc elementow listy
int rozmiar(typ_element **rekord){
	int licznik=0;
	if(*rekord==NULL){
		return licznik;
	}
	else{
		typ_element *aktualny = *rekord;
		do{
			licznik++;
			aktualny = aktualny->next;
		}while(aktualny != NULL);
	}
	return licznik;
}

//Funkcja liczaca srednia dlugosc nazw marek
double srednia(typ_element **rekord){
	double srednia;
	double ilosc=rozmiar(rekord);
	typ_element *aktualny = *rekord;
	if(rekord!=NULL){
		while(aktualny != NULL){
			//printf("Dlugosc %s to: %d: \n", aktualny->marka, strlen(aktualny->marka));
			srednia+=strlen(aktualny->marka);
			//printf("suma: \n");
			aktualny = aktualny->next;
		}
		srednia=srednia/ilosc;
	}
	else{
		fprintf(stderr, "Baza danych jest pusta, musisz cos zaladowac.");
		exit(-1);
	}
	return srednia;
}

//Funkcja obslugujaca menu programu
int menu(typ_element **rekord){
	//Zmienna obslugujaca petle menu
	int opcja = -1;
	//Wartosci zmiennych, ktore bedzie wprowadzal uzytkownik
	char *produkt;
	char *cena;
	char *opakowanie;
	char *marka;
	//Zmienna obslugujaca menu
	//int key=0;
	//Zmienna zawierajaca indeks elementu, ktory uzytkownik chce usunac
	int pozycja=0;
	//Zmienna, ktora przechowuje nazwe szukanego pola (elementu)
	char *nazwa;
	//Alokacja pamieci dla zmiennych
	produkt=(char*)malloc(20*sizeof(char));
	cena=(char*)malloc(20*sizeof(char));
	opakowanie=(char*)malloc(20*sizeof(char));
	marka=(char*)malloc(20*sizeof(char));
	nazwa=(char*)malloc(20*sizeof(char));
	while(opcja!=0){
		//Wyswietlenie prostego menu
		printf("\n\n=====================================================\n");
		printf("Witaj w Zadaniu programistycznym nr 2! Program umozliwia wykonywanie prostych operacji na bazach danych.\n");
		printf("=====================================================\n");
		printf("1. Wczytac baze danych z pliku\n");
		printf("2. Zapisac baze danych do pliku\n");
		printf("3. Dodac element do bazy danych (na koniec listy)\n");
		printf("4. Usunac element o wybranym indeksie\n");
		printf("5. Wyszukac element po nazwie marki\n");
		printf("6. Wyswietlic baze danych\n");
		printf("*7. [MODYFIKACJA] Wypisac srednia dlugosc nazw marek\n");
		printf("0. Zakonczyc program\n");
		printf("=====================================================\n");
		printf("Wybierz opcje: ");
		//Wybieranie opcji przez uzytkownika
		scanf("%i", &opcja);
		printf("=====================================================\n");
		switch(opcja){
			//Wyjscie z programu
			case 0:
				return 0;
				break;
			//Wczytanie bazy danych z pliku
			case 1:
				system("clear");
				if(rekord!=NULL){
					//Przygotowanie listy pod wczytanie bazy z pliku
					while(rozmiar(rekord)!=0){
						usuwanie_pierwszego(rekord);
					}
					//Wczytanie bazy z pliku
					wczytywanie(rekord);
				}
				break;
			//Zapisanie bazy danych do pliku
			case 2:
				system("clear");
				zapis(*rekord);
				break;
			//Dodanie elementu do bazy danych (na koniec listy)
			case 3:
				system("clear");
				//Pobranie od uzytkownika wartosci pol
				printf("Produkt: ");
				scanf("%s", produkt);
				printf("Cena [jezeli grosze to w formie z kropka np. 0.45]: ");
				scanf("%s", cena);
				printf("Opakawanie: ");
				scanf("%s", opakowanie);
				printf("Marka: ");
				scanf("%s", marka);
				dodawanie_elementu(rekord, produkt, cena, opakowanie, marka);
				break;
			//Usuniecie elementu o wybranym indeksie
			case 4: 
				system("clear");
				if(rozmiar(rekord)==0){
					fprintf(stderr, "Lista jest pusta.");
					exit(-1);
				}
				else{
					printf("Podaj numer indeksu elementu, ktory chcesz usunac: ");
					scanf("%d", &pozycja);
					usuwanie(rekord, pozycja-1);
				}
				break;
			//Wyszukanie elementu po nazwie marki
			case 5: 
				system("clear");
				printf("Podaj nazwe marki, ktorej produkty chcesz wyszukac: ");
				scanf("%s", nazwa);
				szukanie(*rekord, nazwa);
				break;
			//Wyswietlenie bazy danych
			case 6: 
				system("clear");
				wyswietlanie(rekord);
				break;
			//Wypisanie sredniej dlugosci nazw marek
			case 7:
				
				printf("Srednia dlugosc nazw marek: %.0f\n", srednia(rekord));
				break;
		}
	}
}

//Glowne cialo funkcji
int main(){
	//Stworzenie pierwszego elementu listy oraz alokacja pamieci
	typ_element *rekord;
	rekord = (typ_element*)malloc(sizeof(typ_element));
	rekord = NULL;
	menu(&rekord);
	printf("Konczenie pracy programu... \n\n");
	return 0;
}
