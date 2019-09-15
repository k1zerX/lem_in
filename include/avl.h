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

# include "container.h"

typedef struct s_avl_node	t_avl_node;

# define T_AVL_KEY char *

# define AVL_KEY name

# define HEIGHT(x) ((x) ? (x->height) : (0))

struct						s_avl_node
{
	T_AVL_KEY				AVL_KEY;

	t_ctnr					edges;
	int						distance;

	t_avl_node				*left;
	t_avl_node				*right;
	unsigned char			height;
};

t_avl_node					*avl_balance(t_avl_node *node);
t_avl_node					*avl_insert(t_avl_node *root, t_avl_node *node, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
t_avl_node					*avl_find(t_avl_node *root, T_AVL_KEY key, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
void						avl_bfs(t_avl_node *root, void (*f)(t_avl_node *node));
void						avl_infix(t_avl_node *root, void (*f)(t_avl_node *node));

#endif
