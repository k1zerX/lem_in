/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:40:40 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:06:02 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

# include "types.h"
# include "lem_in.h"
# include "ctnr.h"
# include <stdlib.h>

# define HEIGHT(x) ((x) ? (x->height) : (0))

struct						s_room
{
	t_avl_str				*edges;
	t_ctnr					*froms;
	int						distance;
	t_avl_str				*out_exc;
	t_avl_str				*in_exc;
	unsigned char			divided		: 1;
	unsigned char			shortest	: 1;
	unsigned char			is_active	: 1;
};

struct						s_edge
{
	t_avl_str				*room;
	t_state					*state;
	unsigned char			existance	: 1;
	unsigned char			n			: 1;
};

struct						s_state
{
	char					weight;
	unsigned char			is_active	: 1;
	unsigned char			cross		: 2;
	t_avl_str				*ends[2];
};

union						u_content
{
	t_edge					edge;
	t_room					room;
};

struct						s_avl_str
{
	char					*key;
	t_content				c;
	t_avl_str				*left;
	t_avl_str				*right;
	unsigned char			height;
};

struct						s_avl_int
{
	int						key;
	t_avl_int				*left;
	t_avl_int				*right;
	unsigned char			height;
};

t_avl_str					*avl_str_balance(t_avl_str *node);
t_avl_str					*avl_str_insert(t_avl_str *root, t_avl_str *node, \
									int (*cmp)(char *a, char *b));
t_avl_str					*avl_str_find(t_avl_str *root, char *key, \
									int (*cmp)(char *a, char *b));
void						avl_str_bfs(t_avl_str *root, \
									void (*f)(t_avl_str *node));
void						avl_str_infix(t_avl_str *root, \
									void (*f)(t_avl_str *node));
t_avl_str					*avl_str_remove(t_avl_str *root, char *key, \
									int (*cmp)(char *a, char *b));

t_avl_int					*avl_int_balance(t_avl_int *node);
t_avl_int					*avl_int_insert(t_avl_int *root, t_avl_int *node, \
									int (*cmp)(int a, int b));
t_avl_int					*avl_int_find(t_avl_int *root, int key, \
									int (*cmp)(int a, int b));
void						avl_int_bfs(t_avl_int *root, \
									void (*f)(t_avl_int *node));
void						avl_int_infix(t_avl_int *root, \
									void (*f)(t_avl_int *node));
t_avl_int					*avl_int_remove(t_avl_int *root, int key, \
									int (*cmp)(int a, int b));

#endif
