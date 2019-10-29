/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_new_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:11:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 23:46:35 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_avl_tree	*avl_new_tree(int (*cmp)(t_avl_node *a, t_avl_node *b))
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
