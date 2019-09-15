/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_pop_bot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:42:33 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 23:50:52 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

t_elem	*ctnr_pop_bot(t_ctnr *ctnr)
{
	t_elem	*tmp;

	tmp = ctnr->bot;
	if (tmp)
	{
		if (tmp->prev)
		{
			ctnr->bot = tmp->prev;
			tmp->prev = NULL;
		}
		else
		{
			ctnr->bot = NULL;
			ctnr->top = NULL;
		}
	}
	return (tmp);
}
