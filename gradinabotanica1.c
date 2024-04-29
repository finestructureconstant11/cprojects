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
		struct planta* urmator; //Pointer la urmatoarea planta in lista inlantuita
	} Planta;


	//Prototipuri functii
	void afisare_meniu();
	void adaugare_planta_la_sfarsit(Planta** head);
	void afisare_plante(Planta* head);
	void cautare_planta_dupa_nume(Planta* head, char* nume_cautat);
	void actualizare_planta(Planta* head);
	void stergere_planta_dupa_nume(Planta** head, char* nume_cautat);
	void creare_fisier_binar(Planta* head);
	void citire_fisier_binar(Planta** head);
	void generare_raport_total(Planta* head);
	void generare_raport_partial(Planta* head, char* criteriu1, char* criteriu2);
	void afisare_articol_conditie(Planta* head, char* criteriu);

	int main() {
		Planta* plante = NULL;
		citire_fisier_binar(&plante);

		while (1) {
			afisare_meniu();
			int optiune;
			printf("Alegeti optiunea: ");
			scanf("%d", &optiune);


			switch (optiune) {
			case 1:
				creare_fisier_binar(plante);
				break;
			case 2:
				adaugare_planta_la_sfarsit(&plante);
				break;
			case 3:
				afisare_plante(plante);
				break;
			case 4:
			{
				char nume_cautat[50];
				printf("Introduceti numele plantei de cautat: ");
				scanf("%s", nume_cautat);
				cautare_planta_dupa_nume(plante, nume_cautat);
				break;

			}
			case 5:
				actualizare_planta(plante);
				break;
			case 6:
			{
				char nume_de_sters[50];
				printf("Introduceti numele plantei de sters: ");
				scanf("%s", nume_de_sters);
				stergere_planta_dupa_nume(&plante, nume_de_sters);
				break;
			}
			case 7:
				generare_raport_total(plante);
				break;
			case 8:
			{
				char criteriu1[50], criteriu2[50];
				printf("introduceti primul criteriu pentru raport: ");
				scanf("%s", criteriu1);
				printf("Introduceti al doilea criteriu: ");
				scanf("%s", criteriu2);
				generare_raport_partial(plante, criteriu1, criteriu2);
				break;
			}
			case 9: {
				char criteriu[50];
				printf("Introduceti criteriul pentru afisarea articolului: ");
				scanf("%s", criteriu);
				afisare_articol_conditie(plante, criteriu);
				break;
			}
			case 0: printf("Iesire\n");
				while (plante != NULL) {
					Planta* temp = plante;
					plante = plante->urmator;
					free(temp);
				}
				return 0;
			default:
				printf("Optiune invalida. Alegeti o optiune valida.\n");
			}
		}
		return 0;
	}
			

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
	printf("7.Generare raport total.\n");
	printf("8.Generare raport partial.\n");
	printf("9.Afisare articol cu conditie.\n");
	printf("0. Iesire\n");
		}

	void generare_raport_total(Planta* head) {
		FILE* raport_total = fopen("raport_total.txt", "w");
		if (raport_total == NULL) {
			printf("Eroare la crearea raportului total.\n");
			return;
		}

		fprintf(raport_total, "Raport total al plantelor:\n\n");
		for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
			fprintf(raport_total, "Nume: %s\n", planta->nume);
			fprintf(raport_total, "Specie: %s\n", planta->specie);
			fprintf(raport_total, "Origine: %s\n", planta->origine);
			fprintf(raport_total, "Inaltime: %d cm\n", planta->inaltime);
			fprintf(raport_total, "Perioada inflorire: %d luni\n", planta->perioada_inflorire);
			fprintf(raport_total, "Descriere: %s\n", planta->descriere);
			fprintf(raport_total, "\n");
		}
		fclose(raport_total);
		printf("Raportul total a fost generat cu succes!\n");
	}

	void generare_raport_partial(Planta* head, char* criteriu1, char* criteriu2) {
		FILE* raport_partial = fopen("raport_partial.txt", "w");
		if (raport_partial == NULL) {
			printf("Eroare la crearea raportului partial.\n");
			return;
		}
		fprintf(raport_partial, "Rport partial al plantelor cu criteriile: %s si %s\n\n", criteriu1, criteriu2);
		for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
			fprintf(raport_partial, "Nume: %s\n", planta->nume);
			fprintf(raport_partial, "Criteriu 1 (%s): %s\n", criteriu1, (strcmp(criteriu1, "specie") == 0) ? planta->specie : planta->origine);
			fprintf(raport_partial, "Criteriu 2 (%s): %s\n", criteriu2, (strcmp(criteriu2, "specie") == 0) ? planta->specie : planta->origine);
			fprintf(raport_partial, "\n");
		}
		fclose(raport_partial);
		printf("Raportul partial a fost generat cu succes!\n");
	}

	void afisare_articol_conditie(Planta* head, char* criteriu) {
		printf("Articolul care indeplineste conditia: %s: \n", criteriu);
		int gasit = 0;
		for (Planta* planta = head; planta != NULL; planta = planta ->urmator) {
			if (strcmp(criteriu, "specie") == 0 && strcmp(planta->specie, criteriu) == 0) {
				printf("Nume: %s\n", planta->nume);
				printf("Specie: %s\n", planta->specie);
				printf("Origine: %s\n", planta->origine);
				printf("Inaltime: %d cm\n", planta->inaltime);
				printf("Perioada inflorire: %d luni\n", planta->perioada_inflorire);
				printf("Descriere: %s\n", planta->descriere);
				gasit = 1;
				break;
			}
			else if (strcmp(criteriu, "origine") == 0 && strcmp(planta->origine, criteriu) == 0) {
				printf("Nume: %s\n", planta->nume);
				printf("Specie: %s\n", planta->specie);
				printf("Origine: %s\n", planta->origine);
				printf("Inaltime: %d cm\n", planta->inaltime);
				printf("Perioada inflorire: %d luni\n", planta->perioada_inflorire);
				printf("Descriere: %s\n", planta->descriere);
				gasit = 1;
				break;
			}
		}
		if (!gasit) {
			printf("Nu s-a gasit nicio planta care sa indeplineasca conditia %s\n", criteriu);
		}
	}

	void adaugare_planta_la_sfarsit(Planta** head) {
	Planta* noua_planta = (Planta*)malloc(sizeof(Planta));
	if (noua_planta == NULL) {
	printf ("Eroare la alocarea memoriei pentru planta!\n");
	return;
	}

	printf("Nume planta: ");
	scanf("%s", noua_planta->nume);
	printf("Specie planta: ");
	scanf("%s", noua_planta->specie);
	printf("Origine planta: ");
	scanf("%s", noua_planta->origine);
	printf("Inaltime planta (cm): ");
	scanf("%d", &noua_planta->inaltime);
	printf("Perioada inflorire (luni): ");
	scanf("%d", &noua_planta->perioada_inflorire);
	printf("Descriere planta: ");
	scanf(" %[^\n]%*c", noua_planta->descriere);
	noua_planta->urmator = NULL;

		if (*head == NULL) {
		*head = noua_planta;
		}
		else {
		Planta* ultima_planta = *head;
		while (ultima_planta->urmator != NULL) {
		ultima_planta = ultima_planta->urmator;

		}
		ultima_planta->urmator = noua_planta;
		}
}



	void afisare_plante(Planta *head) {
	if (head == NULL) {
	printf("Nu exista plante in lista.\n");
	return;
	}

	for (Planta* planta = head; planta != NULL; planta=planta->urmator) {
		printf("--------------------");
		printf("Nume: %s\n", planta->nume);
		printf("Specie: %s\n", planta->specie);
		printf("Origine: %s\n", planta->origine);
		printf("Inaltime: %d cm\n", planta->inaltime);
		printf("Perioada de inflorire: %d luni\n", planta->perioada_inflorire);
		printf("Descriere:%s\n ", planta->descriere);
		printf("\n");
	}
}


void cautare_planta_dupa_nume(Planta* head, char* nume_cautat)
{
	if (head == NULL) {
		printf("Nu exista plante in lista. \n");
		return;
	}

	int gasita = 0;
	for (Planta* planta = head; planta != NULL; planta = planta->urmator) {

		if (strcmp(planta->nume, nume_cautat) == 0)
			{
				printf("--------------------\n");
				printf("Nume: %s\n", planta->nume);
				printf("Specie: %s\n", planta->specie);
				printf("Origine: %s\n", planta->origine);
				printf("Inaltime: %d cm\n", planta->inaltime);
				printf("Perioada inflorire: %d luni\n", planta->perioada_inflorire);
				printf("Descriere: %s\n", planta->descriere);
				gasita = 1;
				break;
			}
		}

		if (!gasita) {
		printf("Planta nu a fost gasita.\n");
	}
		}
void actualizare_planta(Planta* head) {
	if (head == NULL) {
		printf("Nu exista plante in lista.\n");
		return;
	}
	char nume_cautat[50];
	printf("Introduceti numele plantei de actualizat: ");
	scanf("%s", nume_cautat);

	int gasita = 0;
	for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
		if (strcmp(planta->nume, nume_cautat) == 0) {
			gasita = 1;
			printf("Alegeti informatia de actualizat: \n");
			printf("1.Specie\n");
			printf("2.Origine\n");
			printf("3.Inaltime\n");
			printf("4.Perioada inflorire\n");
			printf("5.Descriere");

			int optiune_actualizare;
			scanf("%d", &optiune_actualizare);
			switch (optiune_actualizare) {
			case 1:
				printf("Introduceti noua specie:");
				scanf("%s", planta->specie);
				break;
			case 2:
				printf("Introduceti noua origine:");
				scanf("%s", planta->origine);
				break;
			case 3:
				printf("Introduceti noua inaltime(cm):");
				scanf("%d", &planta->inaltime);
				break;
			case 4:
				printf("Introduceti noua perioada de inflorire(luni):");
				scanf("%d", &planta->perioada_inflorire);
				break;
			case 5:
				printf("Introduceti noua descriere: ");
				scanf("%[^\n]%*c", planta->descriere);
				break;
			default:
				printf("Optiune invalida.\n");
			}
			break;
		}
	}
	if (!gasita) {
		printf("Planta nu a fost gasita.\n");
	}
}

	void stergere_planta_dupa_nume(Planta** head, char* nume_cautat) {
		if (*head == NULL) {
			printf("Nu exista plante in lista.\n");
			return;
		}
		Planta* planta_curenta = *head;
		Planta* planta_anterioara = NULL;
		while (planta_curenta != NULL) {
			if (strcmp(planta_curenta->nume, nume_cautat) == 0) {
				if (planta_anterioara == NULL) {
					*head = planta_curenta->urmator;
				}
				else {
					planta_anterioara->urmator = planta_curenta->urmator;
				}
				free(planta_curenta);
				printf("Planta a fost stearsa.\n");
				return;
			}
			planta_anterioara = planta_curenta;
			planta_curenta = planta_curenta->urmator;
		}
		printf("Planta nu a fost gasita.\n");
	}

		void creare_fisier_binar(Planta* head) {
		FILE* fp = fopen("gradina_botanica.bin", "wb");
		if (fp == NULL) {
		printf("Eroare la deschiderea fisierului binar!\n");
		return;
		}
		int numar_plante = 0;
		for (Planta* planta = head; planta != NULL;
			planta = planta->urmator) {
			numar_plante++;
		}
		fwrite(&numar_plante, sizeof(int), 1, fp);
		rewind(fp); 
		for (Planta* planta = head; planta != NULL; 
			planta = planta->urmator) {
			fwrite(planta, sizeof(Planta), 1, fp);
		}
	
	fclose(fp);
	printf ("Fisierul binar a fost creat cu succes!\n");
}

		void citire_fisier_binar(Planta** head) {
			FILE* fp = fopen("gradina_botanica.bin", "rb");
			if (fp == NULL) {
				printf("Fisierul binar nu exista sau nu poate fi deschis!\n");
				*head = NULL;
				return;
			}
			int numar_plante;
			fread(&numar_plante, sizeof(int), 1, fp);

			*head = NULL;
			for (int i = 0; i < numar_plante; i++) {
				Planta* noua_planta = (Planta*)malloc(sizeof(Planta));
				if (noua_planta == NULL) {
					printf("Eroare la alocarea memoriei pentru plante din fisier!\n");
					fclose(fp);
					return;
				}

				fread(noua_planta, sizeof(Planta), 1, fp);
				//Setarea urmatorului nod al plantei curente la NULL initial 
				noua_planta->urmator = NULL;

				if (*head == NULL) {
					*head = noua_planta;
				}
				else {
					Planta* ultima_planta = *head; 
						while (ultima_planta->urmator !=NULL) {
							ultima_planta = ultima_planta->urmator;
 }
						ultima_planta->urmator = noua_planta;
					}
			}
			fclose(fp);

		}
	




