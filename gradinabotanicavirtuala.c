#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structura care stocheaza info despre o planta
typedef struct planta {
	char nume[50];
	char specie[50];
	char origine[50];
	int inaltime;
	int perioada_inflorire;
	char descriere[200];
} Planta;


//Prototipuri functii
void afisare_meniu();
void adaugare_planta(Planta *plante, int *n);
void afisare_plante(Planta *plante, int n);
void cautare_planta(Planta* plante, int n);
void actualizare_planta(Planta* plante, int n);
void stergere_planta(Planta* plante, int n);
void creare_fisier_binar(Planta* plante, int n);
void citire_fisier_binar(Planta* plante, int* n);


void afisare_meniu() {
	printf("--------------------\n");
	printf("Gradina Botanica Virtuala\n");
	printf("--------------------\n");
	printf("Meniu principal\n");
	printf("1. Creare fisier binar\n");
	printf("2. Adaugare articol\n");
	printf("3. Afisare plante\n");
	printf("4. Cautare planta\n");
	printf("5. Actualizare planta\n");
	printf("6. Stergere planta\n");
	printf("0. Iesire\n");
}

void adaugare_planta(Planta* plante, int* n) {
	printf("Nume planta: ");
	scanf("%s", plante[*n].nume);
	printf("Specie planta: ");
	scanf("%s", plante[*n].specie);
	printf("Origine planta: ");
	scanf("%s", plante[*n].origine);
	printf("Inaltime planta (cm): ");
	scanf("%d", &plante[*n].inaltime);
	printf("Perioada inflorire (luni): ");
	scanf("%d", &plante[*n].perioada_inflorire);
	printf("Descriere planta: ");
	scanf(" %[^\n]%*c", plante[*n].descriere);
	(*n)++;
}

void afisare_plante(Planta* plante, int n) {
	for (int i = 0; i < n; i++) {
		printf("--------------------");
		printf("Nume: % s\n", plante[i].nume);
			printf("Specie: %s\n", plante[i].specie);
		printf("Origine: %s\n", plante[i].origine);
		printf("Inaltime: %d cm\n", plante[i].inaltime);
		printf("Perioada de inflorire: %d luni\n", plante[i].perioada_inflorire);
		printf("Descriere:%s\n ", plante[i].descriere);
	}
}

//Functie cautare planta dupa nume
void cautare_planta(Planta *plante, int n)
{
	char nume_cautat[50];
	printf("Introduceti numele plantei cautate: ");
	scanf("%s", nume_cautat);

	int gasita = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(plante[i].nume, nume_cautat) == 0) {
			printf("--------------------\n");
			printf("Nume: %s\n", plante[i].nume);
			printf("Specie: %s\n", plante[i].specie);
			printf("Origine: %s\n", plante[i].origine);
			printf("Inaltime: %d cm\n", plante[i].inaltime);
			printf("Perioada inflorire: %d luni\n", plante[i].perioada_inflorire);
			printf("Descriere: %s\n", plante[i].descriere);
			gasita = 1;
			break;
		}
	}

	if (!gasita) {
		printf ("Planta nu a fost gasita.\n");

	}
}

//Functie pentru actualizare plante
void actualizare_planta(Planta* plante, int n)
{
	char nume_cautat[50];
	printf("Introduceti numele plantei de actualizat: ");
	scanf("%s", nume_cautat);


	int gasita = 0;
	int index = -1;
	for (int i = 0; i < n; i++) {
		if (strcmp(plante[i].nume, nume_cautat) == 0)
		{
			gasita = 1;
			index = i;
			break;
		}
	}
	if (!gasita) {
		printf("Planta nu a fost gasita.\n");
		return;
	}

	int optiune_actualizare;
	printf("Alegeti informatia de actualizat: \n");
	printf("1. Specie\n");
	printf("2. Origine\n");
	printf("3. Inaltime\n");
	printf("4. Perioada inflorire\n");
	printf("5. Descriere:\n");
	scanf("%d", &optiune_actualizare);

	switch (optiune_actualizare) {
	case 1:
		printf("Introduceti noua specie: ");
		scanf("%s", plante[index].specie);
		break;
	case 2:
		printf("Introduceti noua origine: ");
		scanf("%s", plante[index].origine);
		break;
	case 3:
		printf("Introduceti noua inaltime (cm): ");
		scanf("%d", &plante[index].inaltime);
		break;
	case 4:
		printf("Introduceti noua perioada de inflorire (luni): ");
		scanf("%d", &plante[index].perioada_inflorire);
		break;
	case 5:
		printf("Introduceti noua descriere: ");
		scanf(" %[^\n]%*c", plante[index].descriere);
		break;
	default:
		printf("aoaptiune invalida.\n");


	}

	//Salvarea actualizarii in fisier
	creare_fisier_binar(plante, n);
}

void stergere_planta(Planta * plante, int n) 
{
	char nume_cautat[50];
	printf("Introduceti numele plantei de sters: ");
	scanf("%s", nume_cautat);
	int gasita = 0;
	int index = -1;
	for (int i = 0; i < n; i++) {
		if (strcmp(plante[i].nume, nume_cautat) == 0) {
			gasita = 1;
			index = i;
			break;
		}
	}
	if (!gasita) {
		printf("Planta nu a fost gasita.\n");
		return;

	}

	for (int i = index; i < n - 1; i++) {
		plante[i] = plante[i + 1];
	}

	(n)--;

	creare_fisier_binar(plante, n);
}

//Functie pt crearea fisierului binar
void creare_fisier_binar(Planta* plante, int n) 
{
	FILE* fp = fopen("gradina_botanica.bin", "wb");
	if (fp == NULL) {
		printf("Eroare la deschiderea fisierului binar!\n");
		return;
	}

	//Scrie numarul de plante in fisier
	fwrite(&n, sizeof(int), 1, fp);

	//Scrie fiecare planta in fisier
	for (int i = 0; i < n; i++) {
		fwrite(&plante[i], sizeof(Planta), 1, fp);
	}

	//Inchide fisierul binar
	fclose(fp);
	printf("Fisierul binar a fost creat cu succes!\n");
}

//Functie pt citirea datelor din fisier binar
void citire_fisier_binar(Planta* plante, int* n) 
{
	FILE* fp = fopen("gradina_botanica.bin", "rb");
	if (fp == NULL) {
		printf("Fisierul binar nu exista sau nu poate fi deschis!\n");
		*n = 0;
		return;
	}

	//Citirea nr de plante din fisier
	fread(n, sizeof(int), 1, fp);

	//Alocare de memorie pentru vectorul de plante dinamic
	plante = (Planta*)malloc(*n * sizeof(Planta));
	if (plante == NULL) {
		printf("Eroare la alocarea memoriei pentru plante!\n");
		fclose(fp);
		*n = 0;
		return;
	}

	//Citire fiecare planta din fisier
	for (int i = 0; i < *n; i++) {
		fread(&plante[i], sizeof(Planta), 1, fp);
	}

	//Inchiderea fisierului binar
	fclose(fp);
	printf("Datele au fost citite cu succes din fisierul binar!\n");
}

int main() 
{
	Planta* plante = NULL;
	int n = 0;

	citire_fisier_binar(plante, &n);

	while (1) {
		afisare_meniu();

		int optiune;
	
		printf("Alegeti optiunea: ");
		int ret = scanf("%d", &optiune);

		switch (optiune) {
		case 1:
			creare_fisier_binar(plante, n);
			break;
		case 2:
			adaugare_planta(plante, &n);
			break;
		case 3:
			afisare_plante(plante, n);
			break;
		case 4:
			cautare_planta(plante, n);
			break;
		case 5:
			actualizare_planta(plante, n);
			break;
		case 6:
			stergere_planta(plante, &n);
			break;

		case 0:
			printf("Exit\n");
			free(plante);
			return 0;
		default:
			printf("Optiune invalida. Alegeti o optiune valida\n");
		}
	}
	return 0;
}		

