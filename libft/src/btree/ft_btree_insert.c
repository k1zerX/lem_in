/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:38:13 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/05 02:18:40 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_btree_insert(t_btree **start, \
					void const *content, size_t content_size, \
					int (*cmp)(const void *, const void *, size_t))
{
	if (!start || !cmp)
		return ;
	if (!*start)
	{
		*start = ft_btree_new(content, content_size);
		return ;
	}
	if ((*cmp)(content, (*start)->content, \
				FT_MIN((*start)->content_size, \
				content_size)) < 0)
	{
		if ((*start)->left)
			ft_btree_insert(&(*start)->left, content, content_size, cmp);
		else
			(*start)->left = ft_btree_new(content, content_size);
	}
	else
	{
		if ((*start)->right)
			ft_btree_insert(&(*start)->right, content, content_size, cmp);
		else
			(*start)->right = ft_btree_new(content, content_size);
	}
}
