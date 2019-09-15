/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_pop_top.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:36:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 23:51:35 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

t_elem	*ctnr_pop_top(t_ctnr *ctnr)
{
	t_elem	*tmp;

	tmp = ctnr->top;
	if (tmp)
	{
		if (tmp->next)
		{
			ctnr->top = tmp->next;
			tmp->next = NULL;
		}
		else
		{
			ctnr->top = NULL;
			ctnr->bot = NULL;
		}
	}
	return (tmp);
}
