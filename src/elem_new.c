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
#include "stdlib.h"

t_elem	*elem_new(void)
{
	t_elem	*tmp;

	if ((tmp = malloc(sizeof(t_elem))))
	{
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return (tmp);
}
