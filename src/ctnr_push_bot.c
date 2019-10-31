/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_push_bot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:33:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:53:52 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

void	ctnr_push_bot(t_ctnr *ctnr, t_elem *elem)
{
	if (ctnr->bot)
	{
		elem->prev = ctnr->bot;
		ctnr->bot->next = elem;
		ctnr->bot = elem;
	}
	else
	{
		ctnr->bot = elem;
		ctnr->top = elem;
	}
}
