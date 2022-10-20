// Copyright 2022 Valentin Ionut Bobaru

#ifndef UTILS_H_

#define UTILS_H_

#define MAX_STRING_SIZE 64

int compare_card(void *, void *);

int check_nr_param(char *, int);

int get_card(char *, card *);

list *read_card_list(list *, unsigned int);

void print_card_list(list *);

#endif  // UTILS_H_
