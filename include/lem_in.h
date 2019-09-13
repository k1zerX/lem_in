/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 00:21:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 22:23:34 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define GNL_BUFF 6

typedef struct		s_edge
{
	char			weight;
	struct s_node	*node;
}					t_edge

typedef struct		s_node
{
	char			*name;
	t_edge			*edges;
	int				distance;
}					t_node;

typedef struct			s_avl_node
{
	void				*content;
	size_t				content_size;
	struct s_avl_node	*left;
	struct s_avl_node	*right;
//	struct s_avl_node	*parent; // ubrat' po vozmozhnosti
	char				balance;
	unsigned char		level;
}						t_avl_node;

typedef struct			s_avl_tree
{
	size_t				n;
	unsigned char		height;
	struct s_avl_node	*root;
	int					(*cmp)(t_avl_node *a, t_avl_node *b);
}						t_avl_tree;

#endif
