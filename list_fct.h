// Copyright 2022 Valentin Ionut Bobaru

#ifndef LIST_FCT_H_
#define LIST_FCT_H_

#define MAX_SYMBOL_LENGHT 24

typedef struct
{
	unsigned int nr;
	char sym[MAX_SYMBOL_LENGHT];
} card;

typedef struct node
{
	void* data;
	struct node *prev, *next;
} node;

typedef struct list
{
	node* head;
	unsigned int data_size;
	unsigned int size;
} list;

list* create_list(unsigned int);

node* get_nth_node(list*, unsigned int);

list *add_nth_node(list*, unsigned int n, const void*);

node* remove_nth_node(list*, unsigned int);

list *free_list(list*);

list *shuffle_a_list(list*);

list *reverse_a_list(list*);

list *split_a_list(list*, unsigned int, unsigned int);

list *merge_lists(list*, list*, unsigned int);

list *sort_a_list(list*, int (*compare)(void*, void *));

#endif  // LIST_FCT_H_
