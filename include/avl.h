/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:40:40 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/16 00:27:12 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

typedef struct	s_node		t_node;
typedef struct	s_edge		t_edge;
typedef struct	s_room		t_room;
typedef union	u_content	t_content;
typedef enum	e_type		t_type;

# define T_AVL_KEY char *

# define AVL_KEY name

# define HEIGHT(x) ((x) ? (x->height) : (0))
/*
enum						e_type
{
	ROOM,
	EDGE
};
*/
struct						s_edge
{
	t_node					*room;
	char					weight;
};

struct						s_room
{
	t_node					*edges;
	int						distance;
	char					visited;
};

union						u_content
{
	t_edge					edge;
	t_room					room;
};

struct						s_node
{
	T_AVL_KEY				AVL_KEY;
	t_content				c;
	t_node					*left;
	t_node					*right;
	unsigned char			height;
};

t_node						*avl_balance(t_node *node);
t_node						*avl_insert(t_node *root, t_node *node, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
t_node						*avl_find(t_node *root, T_AVL_KEY key, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
void						avl_bfs(t_node *root, void (*f)(t_node *node));
void						avl_infix(t_node *root, void (*f)(t_node *node));

#endif
