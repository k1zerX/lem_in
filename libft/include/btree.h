/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:43:23 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:00:40 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "libft.h"

typedef struct			s_btree
{
	void				*content;
	size_t				content_size;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

void					ft_btree_infix(t_btree *start, \
							void (*f)(t_btree *));
void					ft_btree_prefix(t_btree *start, \
							void (*f)(t_btree *));
void					ft_btree_suffix(t_btree *start, \
							void (*f)(t_btree *));
t_btree					*ft_btree_new(void const *content, \
							size_t content_size);
void					ft_btree_insert(t_btree **start, \
							void const *content, size_t content_size, \
							int (*cmp)(const void *, const void *, size_t));
void					ft_btree_bfs(t_btree *start, \
							void (*f)(t_btree *));
t_btree					ft_btree_search(t_btree *start, void *content, \
							size_t content_size);

#endif
