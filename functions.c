// Copyright 2022 Valentin Ionut Bobaru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_fct.h"
#include "utils.h"

list *add_deck(list *deck_list)
{
	if(!deck_list)
		deck_list = create_list(sizeof(list));

	list *card_list = NULL;
	unsigned int nr_cards;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1) || atoi(line) <= 0) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	nr_cards = atoi(line);
	card_list = read_card_list(card_list, nr_cards);
	deck_list = add_nth_node(deck_list, deck_list->size, card_list);
	free(card_list);
	printf("The deck was successfully created with %d cards.\n", nr_cards);
	return deck_list;
}

list *add_cards(list *deck_list)
{
	unsigned int index, nr_cards;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 2)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	char *param = strtok(line, " ");
	if(atoi(param) < 0 || atoi(param) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index = atoi(param);
	param = strtok(NULL, " ");
	if(atoi(param) > 0) {
		nr_cards = atoi(param);
		node *deck = get_nth_node(deck_list, index);
		list *card_list = (list *)(deck->data);
		card_list = read_card_list(card_list, nr_cards);
	}
	printf("The cards were successfully added to deck %u.\n", index);
	return deck_list;
}

list *del_deck(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index = atoi(line);
	node *deck = remove_nth_node(deck_list, index);

	deck->data = free_list((list *)(deck->data));
	free(deck->data);
	free(deck);
	printf("The deck %u was successfully deleted.\n", index);
	return deck_list;
}

list *del_card(list *deck_list)
{
	unsigned int index_deck, index_card;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 2)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	char *param = strtok(line, " ");
	if(atoi(param) < 0 || atoi(param) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index_deck = atoi(param);
	node *deck = get_nth_node(deck_list, index_deck);
	param = strtok(NULL, " ");
	if(atoi(param) < 0 || atoi(param) >= ((list *)(deck->data))->size) {
		printf("The provided index is out of bounds for deck %u.\n", index_deck);
		return deck_list;
	}

	index_card = atoi(param);
	node *card = remove_nth_node(((list *)(deck->data)), index_card);
	free(card->data);
	free(card);

	// Daca pachetul ramane gol, il eliminam
	if(!((list *)(deck->data))->size)
	{
		node *rm_deck = remove_nth_node(deck_list, index_deck);
		free(rm_deck->data);
		free(rm_deck);
	}
	printf("The card was successfully deleted from deck %u.\n", index_deck);
	return deck_list;
}

list *free_resources(list *deck_list)
{
	if(!deck_list)
		return NULL;

	node *deck = deck_list->head;
	int i = 0;
	while(i < deck_list->size)
	{
		node *aux = deck->next;
		deck->data = free_list((list *)(deck->data));
		deck = deck->next;
		i++;
	}

	deck_list = free_list(deck_list);
	free(deck_list);
	return deck_list;
}

void print_deck(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	index = atoi(line);
	node *ptr = get_nth_node(deck_list, index);
	printf("Deck %u:\n", index);
	print_card_list((list *)(ptr->data));
}

void print_all_decks(list *deck_list)
{
	node *deck = deck_list->head;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 0)) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	int index = 0;
	while(deck) {
		printf("Deck %u:\n", index);
		print_card_list((list *)(deck->data));
		deck = deck->next;
		index++;
	}
}

void show_deck_number(list *deck_list)
{
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 0)) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	printf("The number of decks is %u.\n", deck_list->size);
}

void show_deck_lenght(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	index = atoi(line);
	node *deck = get_nth_node(deck_list, index);
	printf("The length of deck %u is %u.\n", index, ((list *)(deck->data))->size);
}

list *shuffle_deck(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index = atoi(line);
	node *deck = get_nth_node(deck_list, index);
	deck->data = shuffle_a_list((list *)(deck->data));
	printf("The deck %u was successfully shuffled.\n", index);
	return deck_list;
}

list *reverse_deck(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index = atoi(line);
	node *deck = get_nth_node(deck_list, index);
	deck->data = reverse_a_list((list *)(deck->data));
	printf("The deck %u was successfully reversed.\n", index);
	return deck_list;
}

list *split_deck(list *deck_list)
{
	unsigned int index_deck, index_split;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 2)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	char *param = strtok(line, " ");
	if(atoi(param) < 0 || atoi(param) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index_deck = atoi(param);
	node *deck = get_nth_node(deck_list, index_deck);
	param = strtok(NULL, " ");
	if(atoi(param) < 0 || atoi(param) >= ((list *)(deck->data))->size) {
		printf("The provided index is out of bounds for deck %u.\n", index_deck);
		return deck_list;
	}
	index_split = atoi(param);
	list *new_card_list =
		split_a_list((list *)(deck->data), sizeof(list), index_split);
	if(new_card_list->size) {
		deck_list = add_nth_node(deck_list, index_deck + 1, new_card_list);
		free(new_card_list);
	}
	if(!((list *)(deck->data))->size) {
		deck = remove_nth_node(deck_list, index_deck);
		free(deck->data);
		free(deck);
	}
	printf("The deck %u was successfully split by index %u.\n",
		index_deck, index_split);
	return deck_list;
}

list *merge_decks(list *deck_list)
{
	unsigned int index_deck1, index_deck2;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 2)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	char *param = strtok(line, " ");
	if(atoi(param) < 0 || atoi(param) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index_deck1 = atoi(param);
	param = strtok(NULL, " ");
	if(atoi(param) < 0 || atoi(param) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index_deck2 = atoi(param);
	node *deck1 = get_nth_node(deck_list, index_deck1);
	node *deck2 = get_nth_node(deck_list, index_deck2);

	// creearea noului deck si adaugarea acestuia la final
	list *new_card_list =
	merge_lists((list *)(deck1->data), (list *)(deck2->data), sizeof(list));

	deck_list = add_nth_node(deck_list, deck_list->size, new_card_list);

	free(new_card_list);

	// eliminarea primelor doua deckuri, dupa caz
	if(index_deck1 == index_deck2) {
		node *rm_node = remove_nth_node(deck_list, index_deck1);
		rm_node->data = free_list((list *)(rm_node->data));
		free(rm_node->data);
		free(rm_node);
	} else if (index_deck1 > index_deck2) {
		deck1 = remove_nth_node(deck_list, index_deck1);
		deck1->data = free_list((list *)(deck1->data));
		free(deck1->data);
		free(deck1);
		deck2 = remove_nth_node(deck_list, index_deck2);
		deck2->data = free_list((list *)(deck2->data));
		free(deck2->data);
		free(deck2);
	} else {
		deck2 = remove_nth_node(deck_list, index_deck2);
		deck2->data = free_list((list *)(deck2->data));
		free(deck2->data);
		free(deck2);
		deck1 = remove_nth_node(deck_list, index_deck1);
		deck1->data = free_list((list *)(deck1->data));
		free(deck1->data);
		free(deck1);
	}
	printf("The deck %u and the deck %u were successfully merged.\n",
		index_deck1, index_deck2);
	return deck_list;
}

list *sort_deck(list *deck_list)
{
	unsigned int index;
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if(check_nr_param(line, 1)) {
		printf("Invalid command. Please try again.\n");
		return deck_list;
	}
	if(atoi(line) < 0 || atoi(line) >= deck_list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return deck_list;
	}
	index = atoi(line);
	node *deck = get_nth_node(deck_list, index);
	int (*cmp_fct)(void *, void *) = &compare_card;
	deck->data = sort_a_list((list *)(deck->data), cmp_fct);
	printf("The deck %u was successfully sorted.\n", index);

	return deck_list;
}
