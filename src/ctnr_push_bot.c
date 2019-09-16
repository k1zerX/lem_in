/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_push_bot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:33:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 23:52:55 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

void	ctnr_push_bot(t_ctnr *ctnr, t_elem *elem)
{
	if (ctnr->bot)
	{
		elem->prev = ctnr->bot;
		ctnr->bot->next = elem;
	}
	else
	{
		ctnr->bot = elem;
		ctnr->top = elem;
	}
}
