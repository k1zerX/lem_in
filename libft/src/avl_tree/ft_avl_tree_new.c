/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avl_tree_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:11:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 23:46:35 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_avl_tree	*ft_avl_tree_new(int (*cmp)(t_avl_node *a, t_avl_node *b))
{
	t_avl_tree	*tmp;

	if ((tmp = malloc(sizeof(*tmp))))
	{
		tmp->n = 0;
		tmp->root = NULL;
		tmp->cmp = cmp;
	}
	return (tmp);
}
