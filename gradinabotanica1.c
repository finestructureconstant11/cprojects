#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


	//Structura care stocheaza info despre o planta
	typedef struct planta {
		int id; 
		char nume[50];
		char specie[50];
		char origine[50];
		int inaltime;
		int perioada_inflorire;
		char *descriere;
		struct planta* urmator; //Pointer la urmatoarea planta in lista inlantuita
	} Planta;


	//Prototipuri functii
	void afisare_meniu();
	void adaugare_planta_la_sfarsit(Planta** head);
	void inserare_planta_la_inceput(Planta** head);
	void afisare_plante(Planta* head);
	void cautare_planta_dupa_nume(Planta* head, char* nume_cautat);
	void cautare_planta_dupa_id(Planta* head, int id_cautat);
	void actualizare_planta(Planta* head);
	void stergere_planta_dupa_nume(Planta** head, char* nume_cautat);
	void stergere_prima_planta(Planta** head);
	void creare_fisier_binar(Planta* head);
	void citire_fisier_binar(Planta** head);
	void generare_raport_total(Planta* head);
	void generare_raport_partial(Planta* head, char* criteriu1, char* criteriu2);
	void afisare_articol_conditie(Planta* head, char* criteriu);

	//Functie principala
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
				stergere_prima_planta(&plante);
				break;
			case 8:
			{
				int id_cautat;;
				printf("introduceti ID-ul plantei de cautat: ");
				scanf("%d", &id_cautat);
				cautare_planta_dupa_id(plante, id_cautat);
				break;
			}
			case 9: {
				inserare_planta_la_inceput(&plante);
				break;

			case 10: 
				generare_raport_total(plante);
				break;

			case 11: {
				char criteriu1[50], criteriu2[50];
				printf("Introduceti primul criteriu pentru raport: ");
				scanf("%s", criteriu1);
				printf("Introduceti al doilea criteriu: ");
				scanf("%s", criteriu2);
				generare_raport_partial(plante, criteriu1, criteriu2);
				break;
			}
			case 12:
			{
				char criteriu[50];
				printf("Introduceti criteriul pentru afisarea articolului: ");
				scanf("%s", criteriu);
				afisare_articol_conditie(plante, criteriu);
				break;
			}
			case 0:
				printf("Iesire\n");
				while (plante != NULL) {
					Planta* temp = plante;
					plante = plante->urmator;
					free(temp->descriere); // Elibereaza memoria pentru descriere
					free(temp);
				}
				return 0;
			default:
				printf("Optiune invalida. Alegeti o optiune valida.\n");
			}
		}
		return 0;
	}
			
		//Functie pentru afisare meniu 
		void afisare_meniu(); {
			printf("--------------------\n");
			printf("Gradina Botanica Virtuala\n");
			printf("--------------------\n");
			printf("Meniu principal\n");
			printf("1. Creare fisier binar\n");
			printf("2. Adaugare articol(final)\n");
			printf("3. Afisare plante\n");
			printf("4. Cautare planta dupa nume\n");
			printf("5. Actualizare planta\n");
			printf("6. Stergere planta dupa nume\n");
			printf("7. Stergere prima planta\n");
			printf("8. Cautare planta dupa ID\n");
			printf("9. Inserare articol (inceput)\n");
			printf("10.Generare raport total\n");
			printf("11.Generare raport partial.\n");
			printf("12.Afisare articol cu conditie.\n");
			printf("0. Iesire\n");
		}


	//Functii pentru gestionarea listelor de plante
	void adaugare_planta_la_sfarsit(Planta** head) {
		// Allocate memory for the new plant structure
		Planta* noua_planta = (Planta*)malloc(sizeof(Planta));
		if (noua_planta == NULL) {
			printf("Eroare la alocarea memoriei!\n");
			return;
		}

		// Get plant information (ID, name, species, origin, height, flowering period, description)
		printf("Introduceti ID-ul plantei: ");
		scanf("%d", &noua_planta->id);
		printf("Introduceti numele plantei: ");
		scanf("%s", noua_planta->nume);
		printf("Introduceti specia plantei: ");
		scanf("%s", noua_planta->specie);
		printf("Introduceti originea plantei: ");
		scanf("%s", noua_planta->origine);
		printf("Introduceti inaltimea plantei (cm): ");
		scanf("%d", &noua_planta->inaltime);
		printf("Introduceti perioada de inflorire (luni): ");
		scanf("%d", &noua_planta->perioada_inflorire);

		// Allocate memory for description
		noua_planta->descriere = (char*)malloc(255 * sizeof(char));
		if (noua_planta->descriere == NULL) {
			printf("Eroare la alocarea memoriei pentru descriere!\n");
			free(noua_planta);
			return;
		}

		printf("Introduceti descrierea plantei: ");
		fgets(noua_planta->descriere, 256, stdin); // Use fgets to read description with spaces
		noua_planta->descriere[strcspn(noua_planta->descriere, "\n")] = '\0'; // Remove newline from description

		// Add plant to the end of the list
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

		printf("Planta adaugata cu succes la sfarsit.\n");
	}


	
		void inserare_planta_la_inceput(Planta** head) {
			Planta* noua_planta = (Planta*)malloc(sizeof(Planta));
			if (noua_planta == NULL) {
				printf("Eroare la alocarea memoriei.\n");
				return;
			}

			printf("Introduceti ID-ul plantei: ");
			scanf("%d", &noua_planta->id);
			printf("Introduceti numele plantei: ");
			scanf("%s", noua_planta->nume);
			printf("Introduceti specia plantei: ");
			scanf("%s", noua_planta->specie);
			printf("Introduceti originea plantei: ");
			scanf("%s", noua_planta->origine);
			printf("Introduceti inaltimea plantei (cm): ");
			scanf("%d", &noua_planta->inaltime);
			printf("Introduceti perioada de inflorire (luni): ");
			scanf("%d", &noua_planta->perioada_inflorire);

			//Alocare memorie pentru descriere
			noua_planta->descriere = (char*)malloc(255 * sizeof(char)); 
			if (noua_planta->descriere=NULL) {
				printf("Eroare la alocarea memoriei pentru descriere.\n");
				free(noua_planta);
				return;
			}
			printf("Introduceti descrierea plantei: ");
			fgets(noua_planta->descriere, 255, stdin); // Citeste descrierea cu fgets pentru a evita overflow

			noua_planta->urmator = *head;
			*head = noua_planta;

			printf("Planta inserata cu succes la inceput.\n");
		}

		void cautare_planta_dupa_id(Planta* head, int id_cautat) {
			if (head == NULL) {
				printf("Nu exista plante in lista.\n");
				return;
			}

			int gasita = 0;
			for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
				if (planta->id == id_cautat) {
					printf("Planta cu ID-ul %d:\n", id_cautat);
					printf("Nume: %s\n", planta->nume);
					printf("Specie: %s\n", planta->specie);
					printf("Origine: %s\n", planta->origine);
					printf("Inaltime: %dcm\n", planta->inaltime);
					printf("Perioada inflorire: %dluni\n", planta->perioada_inflorire);
					printf("Descriere: %s\n\n", planta->descriere);
					gasita = 1;
					break;
				}
			}

			if (gasita == 0) {
				printf("Planta cu ID-ul %d nu a fost gasita.\n", id_cautat);
			}
		}

		void actualizare_planta(Planta* head) {
			if (head == NULL) {
				printf("Nu exista plante in lista.\n");
				return;
			}
			int id_actualizat;
			printf("Introduceti ID-ul plantei de actualizat: ");
			scanf("d", &id_actualizat);

			Planta* planta_gasita = NULL;
			for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
				if (planta->id == id_actualizat) {
					planta_gasita = planta;
					break;
				}
			}
			if (planta_gasita == NULL) {
				printf("Planta cu ID-ul %d nu a fost gasita.\n", id_actualizat);
				return;
			}
			printf("Introduceti noul nume (sau apasati Enter pentru a pastra actualul): ");
			char nume_nou[50];
			fgets(nume_nou, 50, stdin); //Citeste cu fgets pentru a evita overflow
			if (strlen(nume_nou) > 0) {
				strcpy(planta_gasita->nume, nume_nou);
			}
			printf("Introduceti noua specie (sau apasati Enter pentru a pastra actuala): ");
			char specie_noua[50];
			fgets(specie_noua, 50, stdin); // Citeste cu fgets pentru a evita overflow
			if (strlen(specie_noua) > 0) {
				strcpy(planta_gasita->specie, specie_noua);
			}

			printf("Introduceti noua origine (sau apasati Enter pentru a pastra actuala): ");
			char origine_noua[50];
			fgets(origine_noua, 50, stdin); // Citeste cu fgets pentru a evita overflow
			if (strlen(origine_noua) > 0) {
				strcpy(planta_gasita->origine, origine_noua);
			}

			printf("Introduceti noua inaltime (sau apasati Enter pentru a pastra actuala): ");
			int inaltime_noua;
			scanf("%d", &inaltime_noua);
			if (inaltime_noua != 0) { // Verifica daca s-a introdus o valoare
				planta_gasita->inaltime = inaltime_noua;
			}

			printf("Introduceti noua perioada de inflorire (sau apasati Enter pentru a pastra actuala): ");
			int perioada_noua;
			scanf("%d", &perioada_noua);
			if (perioada_noua != 0) { // Verifica daca s-a introdus o valoare
				planta_gasita->perioada_inflorire = perioada_noua;
			}

			printf("Introduceti noua descriere (sau apasati Enter pentru a pastra actuala): ");
			char descriere_noua[255];
			fgets(descriere_noua, 255, stdin); // Citeste cu fgets pentru a evita overflow
			if (strlen(descriere_noua) > 0) { // Verifica daca s-a introdus o valoare
				// Aloca memorie noua pentru descriere
				free(planta_gasita->descriere); // Elibereaza memoria veche
				planta_gasita->descriere = (char*)malloc(255 * sizeof(char));
				if (planta_gasita->descriere == NULL) {
					printf("Eroare la alocarea memoriei pentru descriere.\n");
					return;
				}
				strcpy(planta_gasita->descriere, descriere_noua);
			}

			printf("Planta actualizata cu succes.\n");
		}


			void creare_fisier_binar(Planta * head) {
				if (head == NULL) {
					printf("Nu exista plante de salvat.\n");
					return;
				}

				char nume_fisier[50];
				printf("Introduceti numele fisierului binar: ");
				scanf("%s", nume_fisier);

				FILE* fisier = fopen(nume_fisier, "wb");
				if (fisier == NULL) {
					printf("Eroare la deschiderea fisierului %s.\n", nume_fisier);
					return;
				}

				// Bucla pentru a scrie fiecare planta in fisier
				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					if (fwrite(planta, sizeof(Planta), 1, fisier) != 1) {
						printf("Eroare la scrierea in fisier.\n");
						fclose(fisier);
						return;
					}
				}

				fclose(fisier);
				printf("Fisierul binar %s a fost creat cu succes.\n", nume_fisier);
			}
	
		
			void citire_fisier_binar(Planta** head) {
				char nume_fisier[50];
				printf("Introduceti numele fisierului binar: ");
				scanf("%s", nume_fisier);

				FILE* fisier = fopen(nume_fisier, "rb");
				if (fisier == NULL) {
					printf("Eroare la deschiderea fisierului %s.\n", nume_fisier);
					return;
				}

				// Elibereaza memoria pentru lista existenta (daca e cazul)
				while (*head != NULL) {
					Planta* temp = *head;
					*head = (*head)->urmator;
					free(temp->descriere);
					free(temp);
				}

				Planta planta_noua;
				while (fread(&planta_noua, sizeof(Planta), 1, fisier) == 1) {
					// Aloca memorie pentru descrierea plantei citite
					planta_noua.descriere = (char*)malloc(255 * sizeof(char));
					if (planta_noua.descriere == NULL) {
						printf("Eroare la alocarea memoriei pentru descriere.\n");
						fclose(fisier);
						return;
					}
					strcpy(planta_noua.descriere, planta_noua.descriere); // Copiaz? descrierea citit?

					// Insereaz? planta noua la finalul listei
					Planta* nou = (Planta*)malloc(sizeof(Planta));
					memcpy(nou, &planta_noua, sizeof(Planta)); // Copiaz? datele plantei
					nou->urmator = NULL;

					if (*head == NULL) {
						*head = nou;
					}
					else {
						Planta* temp = *head;
						while (temp->urmator != NULL) {
							temp = temp->urmator;
						}
						temp->urmator = nou;
					}
				}

				fclose(fisier);
				printf("Plantele din fisierul binar au fost citite cu succes.\n");
			}

	


			void generare_raport_total(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				printf("---------- Raport Total ----------\n");
				printf("ID\tNume\tSpecie\tOrigine\tInaltime\tPerioada Inflorire\n");

			 for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					printf("%d\t%s\t%s\t%s\t%dcm\t%dluni\n", planta->id, planta->nume, planta->specie, planta->origine, planta->inaltime, planta->perioada_inflorire);
				}

				printf("---------------------------------\n");
			}


			void generare_raport_partial(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				int inaltime_minima, inaltime_maxima;
				printf("Introduceti inaltimea minima: ");
				scanf("%d", &inaltime_minima);
				printf("Introduceti inaltimea maxima: ");
				scanf("%d", &inaltime_maxima);

				printf("---------- Raport Partial ----------\n");
				printf("ID\tNume\tSpecie\tOrigine\tInaltime\tPerioada Inflorire\n");

				int plante_gasite = 0;
				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					if (planta->inaltime >= inaltime_minima && planta->inaltime <= inaltime_maxima) {
						plante_gasite = 1;
						printf("%d\t%s\t%s\t%s\t%dcm\t%dluni\n", planta->id, planta->nume, planta->specie, planta->origine, planta->inaltime, planta->perioada_inflorire);
					}
				}

				if (plante_gasite == 0) {
					printf("Nu s-au gasit plante in intervalul specificat.\n");
				}

				printf("---------------------------------\n");
			}


			void afisare_articol_conditie(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				char specie_cautata[50];
				printf("Introduceti specia cautata: ");
				scanf("%s", specie_cautata);

				int plante_gasite = 0;
				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					if (strcmp(planta->specie, specie_cautata) == 0) {
						plante_gasite = 1;
						printf("---------- Articol ------------\n");
						printf("Nume: %s\n", planta->nume);
						printf("Specie: %s\n", planta->specie);
						printf("Origine: %s\n", planta->origine);
						printf("Inaltime: %dcm\n", planta->inaltime);
						printf("Perioada inflorire: %dluni\n", planta->perioada_inflorire);
						printf("Descriere: %s\n", planta->descriere);
						printf("------------------------------\n");
						break; // Oprire dupa prima planta gasita (daca e cazul)
					}
				}

				if (plante_gasite == 0) {
					printf("Nu s-a gasit nicio planta cu specia %s.\n", specie_cautata);
				}
			}



			void afisare_plante(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				printf("---------- Lista Plante ----------\n");

				int i = 1; // Contor pentru numarul de plante
				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					printf("%d. %s (%s)\n", i++, planta->nume, planta->specie);
					i++; // Incrementeaza contorul dupa afisarea numelui si speciei
				}

				printf("------------------------------\n");
			}


			void cautare_planta_dupa_nume(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				char nume_cautat[50];
				printf("Introduceti numele plantei cautate: ");
				scanf("%s", nume_cautat);

				int plante_gasite = 0;
				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					if (strcasecmp(planta->nume, nume_cautat) == 0) { // Comparare fara sensibilitate la litere
						plante_gasite = 1;
						printf("---------- Articol ------------\n");
						printf("ID: %d\n", planta->id);
						printf("Nume: %s\n", planta->nume);
						printf("Specie: %s\n", planta->specie);
						printf("Origine: %s\n", planta->origine);
						printf("Inaltime: %dcm\n", planta->inaltime);
						printf("Perioada inflorire: %dluni\n", planta->perioada_inflorire);
						printf("Descriere: %s\n", planta->descriere);
						printf("------------------------------\n");
						break; // Oprire dupa prima planta gasita (daca e cazul)
					}
				}

				if (plante_gasite == 0) {
					printf("Nu s-a gasit nicio planta cu numele %s.\n", nume_cautat);
				}
			}




			void stergere_planta_dupa_nume(Planta* head) {
				if (head == NULL) {
					printf("Nu exista plante in lista.\n");
					return;
				}

				char nume_sterge[50];
				printf("Introduceti numele plantei de sters: ");
				scanf("%s", nume_sterge);

				Planta* planta_anterioara = NULL; // Pointer catre planta anterioara
				Planta* planta_sterge = NULL; // Pointer catre planta de sters

				for (Planta* planta = head; planta != NULL; planta = planta->urmator) {
					if (strcmp(planta->nume, nume_sterge) == 0) {
						planta_sterge = planta;
						break;
					}

					planta_anterioara = planta; // Actualizeaza pointerul catre planta anterioara
				}

				if (planta_sterge == NULL) {
					printf("Planta cu numele %s nu a fost gasita.\n", nume_sterge);
					return;
				}

				// Cazul special: planta de sters este prima din lista
				if (planta_sterge == head) {
					head = head->urmator;
				}
				else {
					planta_anterioara->urmator = planta_sterge->urmator;
				}

				// Elibereaza memoria alocata pentru descrierea plantei
				free(planta_sterge->descriere);
				free(planta_sterge);

				printf("Planta cu numele %s a fost stearsa cu succes.\n", nume_sterge);
			}



			

			// Elibereaza memoria alocata dinamic in lista
			while (plante != NULL) {
				Planta* temp = plante;
				plante = plante->urmator;
				free(temp->descriere);
				free(temp); // Elibereaz? memoria pentru structura Planta (dac? a fost alocat? dinamic)
			}




		

		

		





