#ifndef CONTAINER_H
# define CONTAINER_H

typedef struct s_container	t_container;
typedef struct s_elem		t_elem;

#include "avl.h"

struct						s_container
{
	t_elem					*start;
	t_elem					*end;
//	size_t					length;
};

struct						s_elem
{
	char					weight;
	t_node					*node;

	t_elem					*next;
//	t_elem					*prev;
};

#endif
