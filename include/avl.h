/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:40:40 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:07:02 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

# include "ctnr.h"
# include "types.h"
# include <stdlib.h>

# define HEIGHT(x) ((x) ? (x->height) : (0))

struct						s_edge
{
	t_avl_str				*room;
	t_state					*state;
	unsigned char			existance	: 1;
	unsigned char			n			: 1;
};

struct						s_room
{
	t_avl_str				*edges;
	t_ctnr					*froms;
	int						distance;
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

struct						s_state
{
	char					weight;
	unsigned char			is_active	: 1;
	unsigned char			cross		: 2;
	t_edge					*ends[2];
};

t_avl_str					*avl_str_balance(t_avl_str *node);
t_avl_str					*avl_str_insert(t_avl_str *root, t_avl_str *node, \
									int (*cmp)(char *a, char *b));
t_avl_str					*avl_str_find(t_avl_str *root, char *key, \
									int (*cmp)(char *a, char *b));
void						avl_str_bfs(t_avl_str *root, void (*f)(t_avl_str *node));
void						avl_str_infix(t_avl_str *root, void (*f)(t_avl_str *node));
t_avl_str					*avl_str_remove(t_avl_str *root, char *key, \
									int (*cmp)(char *a, char *b));

t_avl_str					*avl_int_balance(t_avl_str *node);
t_avl_str					*avl_int_insert(t_avl_str *root, t_avl_str *node, \
									int (*cmp)(int a, int b));
t_avl_str					*avl_int_find(t_avl_str *root, int key, \
									int (*cmp)(int a, int b));
void						avl_int_bfs(t_avl_str *root, void (*f)(t_avl_str *node));
void						avl_int_infix(t_avl_str *root, void (*f)(t_avl_str *node));
t_avl_str					*avl_int_remove(t_avl_str *root, int key, \
									int (*cmp)(int a, int b));

#endif
