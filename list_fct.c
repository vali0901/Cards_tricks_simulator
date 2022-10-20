// Copyright 2022 Valentin Ionut Bobaru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_fct.h"
#include "utils.h"

list* create_list(unsigned int data_size)
{
	list *tmp = malloc(sizeof(list));
	tmp->data_size = data_size;
	tmp->head = NULL;
	tmp->size = 0;
	return tmp;
}

node* get_nth_node(list* list, unsigned int n)
{
	node *ptr = list->head;
	int i = 0;
	while(i < n)
	{
		ptr = ptr->next;
		i++;
	}
	return ptr;
}

list *add_nth_node(list* list, unsigned int n, const void* data)
{
	node *new_nod = malloc(sizeof(node));
	new_nod->data = malloc(list->data_size);
	memcpy(new_nod->data, data, list->data_size);

	if(n == 0) {
		list->head = new_nod;
		new_nod->next = NULL;
		new_nod->prev = NULL;
		list->size += 1;
		return list;
	}
	node *ptr = get_nth_node(list, n - 1);

	new_nod->next = ptr->next;
	if(ptr->next)
		ptr->next->prev = new_nod;
	new_nod->prev = ptr;
	ptr->next = new_nod;
	list->size += 1;

	return list;
}

node* remove_nth_node(list* list, unsigned int n)
{
	if(n == 0)
	{
		node *ptr = list->head;
		if(ptr->next)
			ptr->next->prev = NULL;

		list->head = ptr->next;

		ptr->next = NULL;
		ptr->prev = NULL;

		list->size -= 1;
		return ptr;
	}
	node *ptr = get_nth_node(list, n);

	ptr->prev->next = ptr->next;

	if(ptr->next)
		ptr->next->prev = ptr->prev;

	ptr->prev = ptr->next = NULL;

	list->size -= 1;
	return ptr;
}

list *free_list(list* pp_list)
{
	node *ptr = pp_list->head;
	int i = 0;
	while(i < pp_list->size) {
		node *q = ptr->next;
		free(ptr->data);
		free(ptr);
		ptr = q;
		i++;
	}

	return pp_list;
}

// In cazul in care lista are un numar impar de elemente, ultimul element este
// adus in mijlocul listei, apoi se va face interschimbarea valorilor nodurilor
// aflate la aceeasi distanta fata de centrul listei
list *shuffle_a_list(list *list)
{
	unsigned int n;
	if(list->size == 1)
		return list;
	if(list->size % 2 != 0)
	{
		node *tmp_node = get_nth_node(list, list->size - 1);

		list = add_nth_node(list, list->size / 2, tmp_node->data);

		node *rm_node = remove_nth_node(list, list->size - 1);
		free(rm_node->data);
		free(rm_node);
		n = list->size / 2 + 1;
	}
	else
		n = list->size / 2;

	node *node1 = list->head;
	node *node2 = get_nth_node(list, n);
	while(node2)
	{
		void *aux = node1->data;
		node1->data = node2->data;
		node2->data = aux;
		node1 = node1->next;
		node2 = node2->next;
	}
	return list;
}

// Functia face interschimbarea valorilor nodurilor aflate la aceeasi distanta
// de mijlocul listei
list *reverse_a_list(list *list)
{
	node *first_node = list->head;
	node *last_node = get_nth_node(list, list->size - 1);
	unsigned int i = 0, j = list->size - 1;
	while(i < j)
	{
		void *aux = first_node->data;
		first_node->data = last_node->data;
		last_node->data = aux;

		first_node = first_node->next;
		last_node = last_node->prev;
		i++;
		j--;
	}
	return list;
}

// Functia returneaza noua lista ce contine toate nodurile incepand cu indexul
// index, acestea fiind sterse din lista initiala
list *split_a_list
(list *curr_list, unsigned int new_list_data_size, unsigned int index)
{
	list *new_list = create_list(new_list_data_size);
	node *curr_node = get_nth_node(curr_list, index);
	unsigned int i = index;
	unsigned int n = curr_list->size;
	while(i < n) {
		new_list = add_nth_node(new_list, new_list->size, curr_node->data);
		curr_node = curr_node->next;
		node *rm_node = remove_nth_node(curr_list, index);
		free(rm_node->data);
		free(rm_node);
		i++;
	}
	return new_list;
}

// Functia creeaza o noua lista punand, succesiv, cate un nod din fiecare lista
// pana una din ele se goleste, apoi pune nodurile ramase in cealalta lista
// nevida
list *merge_lists(list *list1, list *list2, unsigned int new_list_data_size)
{
	list *new_list = create_list(new_list_data_size);
	node *node1 = list1->head;
	node *node2 = list2->head;
	unsigned int i = 0, j = 0;
	while(node1 && node2)
	{
		if(i == j) {
			new_list = add_nth_node(new_list, new_list->size, node1->data);
			i++;
			node1 = node1->next;
		} else {
			new_list = add_nth_node(new_list, new_list->size, node2->data);
			j++;
			node2 = node2->next;
		}
	}
	while(node1) {
		new_list = add_nth_node(new_list, new_list->size, node1->data);
		node1 = node1->next;
	}
	while(node2) {
		new_list = add_nth_node(new_list, new_list->size, node2->data);
		node2 = node2->next;
	}
	return new_list;
}

// Functia face interschimbarea valorilor nodurilor doar atunci cand functia
// de comparare data ca parametru returneaza o valoare pozitiva
list *sort_a_list(list *curr_list, int (*compare)(void*, void *))
{
	node *curr_node = curr_list->head;
	node *next_node = curr_node->next;
	while(curr_node->next)
	{
		while(next_node)
		{
			if(compare(curr_node->data, next_node->data) > 0) {
				void *aux = curr_node->data;
				curr_node->data = next_node->data;
				next_node->data = aux;
			}
			next_node = next_node->next;
		}
		curr_node = curr_node->next;
		next_node = curr_node->next;
	}
	return curr_list;
}
