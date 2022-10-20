// Copyright 2022 Valentin Ionut Bobaru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_fct.h"
#include "utils.h"
#include "functions.h"

int main(void)
{
	list *deck_list = NULL;
	char command[MAX_STRING_SIZE]="", line[MAX_STRING_SIZE]="";
	do {
		scanf("%s", command);
		if (strcmp(command, "ADD_DECK") == 0) {
			deck_list = add_deck(deck_list);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			deck_list = add_cards(deck_list);
		} else if (strcmp(command, "DEL_DECK") == 0) {
			deck_list = del_deck(deck_list);
		} else if (strcmp(command, "DEL_CARD") == 0) {
		    deck_list = del_card(deck_list);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			show_deck_number(deck_list);
		} else if (strcmp(command, "DECK_LEN") == 0) {
		    show_deck_lenght(deck_list);
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
		    deck_list = reverse_deck(deck_list);
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
		    deck_list = merge_decks(deck_list);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0) {
		    deck_list = shuffle_deck(deck_list);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
		    deck_list = split_deck(deck_list);
		} else if (strcmp(command, "SORT_DECK") == 0) {
		    deck_list = sort_deck(deck_list);
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			print_deck(deck_list);
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			print_all_decks(deck_list);
		} else if (strcmp(command, "EXIT") == 0) {
		    deck_list = free_resources(deck_list);
		} else {
			fgets(line, MAX_STRING_SIZE, stdin);
			printf("Invalid command. Please try again.\n");
		}
	} while (strcmp(command, "EXIT"));

	return 0;
}
