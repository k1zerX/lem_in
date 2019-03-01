/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/05 02:12:10 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_H
# define RBTREE_H

#include "libft.h"

# define BLACK 0
# define RED 1

typedef struct			s_rbnode
{
	void				*content;
	size_t				content_size;
	char				color;
	struct s_btree		*parent;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_rbnode;

typedef struct			s_rbtree
{
	struct s_btree		*root;
	size_t				height;
}						t_rbtree;

#endif
