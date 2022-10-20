// Copyright 2022 Valentin Ionut Bobaru

#ifndef FUNCTIONS_H_

#define FUNCTIONS_H_

list *add_deck(list *);

list *add_cards(list *);

list *del_deck(list *);

list *del_card(list *);

list *free_resources(list *);

void print_deck(list *);

void print_all_decks(list *);

void show_deck_number(list *);

void show_deck_lenght(list *);

list *shuffle_deck(list *);

list *reverse_deck(list *);

list *split_deck(list *);

list *merge_decks(list *);

list *sort_deck(list *);

#endif  // FUNCTIONS_H_
