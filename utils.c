// Copyright 2022 Valentin Ionut Bobaru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_fct.h"
#define MAX_STRING_SIZE 64


// Functie folosita pentru sortarea cartilor, returneaza o valoare pozitiva
// daca trebuie facuta interschimbarea
int compare_card(void *card1, void *card2)
{
	if(((card *)card1)->nr != ((card *)card2)->nr)
		return ((card *)card1)->nr - ((card *)card2)->nr;
	int index1_sym = 0, index2_sym = 0;
	if (!strcmp(((card *)card1)->sym, "CLUB"))
		index1_sym = 4;
	else if (!strcmp(((card *)card1)->sym, "DIAMOND"))
		index1_sym = 3;
	else if (!strcmp(((card *)card1)->sym, "SPADE"))
		index1_sym = 2;
	else if (!strcmp(((card *)card1)->sym, "HEART"))
		index1_sym = 1;
	if (!strcmp(((card *)card2)->sym, "CLUB"))
		index2_sym = 4;
	else if (!strcmp(((card *)card2)->sym, "DIAMOND"))
		index2_sym = 3;
	else if (!strcmp(((card *)card2)->sym, "SPADE"))
		index2_sym = 2;
	else if (!strcmp(((card *)card2)->sym, "HEART"))
		index2_sym = 1;
	return index1_sym - index2_sym;
}

// Functie care verifica numarul de parametrii ai unei comenzi,
// ea returneaza 0 daca avem numarul corect de parametrii indicat prin nr
int check_nr_param(char *line, int nr)
{
	if (!strcmp(line, "\n"))
		return nr;
	char aux[MAX_STRING_SIZE];
	strcpy(aux, line);
	char *p = strtok(aux, " ");
	while (p)
	{
		nr--;
		p = strtok(NULL, " ");
	}
	return nr;
}

// Functie ce verifica corectitudinea inputului pentru carte pe care o va stoca
// in variabila c si care returneaza 0 daca inputul este corect
int get_card(char *line, card *c)
{
	char *param;
	param = strtok(line, " ");
	if(atoi(param) < 1 || atoi(param) > 14)
		return 1;

	c->nr = atoi(param);
	param = strtok(NULL, " ");
	param[strlen(param) - 1] = '\0';
	if(strcmp(param, "HEART") && strcmp(param, "CLUB")
	&& strcmp(param, "DIAMOND") && strcmp(param, "SPADE"))
		return 1;
	else
		strcpy(c->sym, param);

	return 0;
}

// Functia adauga o lista de carti la finalul unei liste de carti ce va fi
// ulterior adaugata/va fi actualizata intr-un deck
list *read_card_list(list *card_list, unsigned int nr_cards)
{
	int i = 0;
	while(i < nr_cards) {
		card tmp;
		char line[MAX_STRING_SIZE];
		fgets(line, MAX_STRING_SIZE, stdin);
		if(check_nr_param(line, 2) || get_card(line, &tmp)) {
			printf("The provided card is not a valid one.\n");
		} else {
			if(!card_list)
				card_list = create_list(sizeof(card));
			card_list = add_nth_node(card_list, card_list->size, &tmp);
			i++;
		}
	}
	return card_list;
}

// Functie ce printeaza cartile unui pachet
void print_card_list(list *card_list)
{
	node *c = card_list->head;
	while(c) {
		printf("\t%u %s\n", (*(card *)(c->data)).nr, (*(card *)(c->data)).sym);
		c = c->next;
	}
}
