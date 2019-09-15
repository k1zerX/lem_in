/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:44:34 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 23:41:00 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

t_elem	*elem_new(t_node *node)
{
	t_elem	*tmp;

	if ((tmp = malloc(sizeof(t_elem))))
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->weight = 1;
		tmp->node = node;
	}
	return (tmp);
}
