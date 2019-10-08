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

#include <stdio.h>
void	gg_print_ctnr(t_ctnr *ctnr)
{
	t_elem	*tmp;

	tmp = ctnr->top;
	if (tmp)
		while (tmp->next)
		{
			printf("%p -> ", tmp);
			tmp = tmp->next;
		}
	printf("%p\n", tmp);
}

void	ctnr_push_bot(t_ctnr *ctnr, t_elem *elem)
{
/*	printf("before: ");
	gg_print_ctnr(ctnr);
	printf("before\n");
	if (ctnr->top)
		printf("\ttop:%p -> %p ->%p\n", ctnr->top->prev, ctnr->top, ctnr->top->next);
	if (ctnr->bot)
		printf("\tbot:%p -> %p ->%p\n", ctnr->bot->prev, ctnr->bot, ctnr->bot->next);*/
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
/*	printf("after:\n");
	if (ctnr->top)
		printf("\ttop:\n\t%p -> %p ->%p\n", ctnr->top->prev, ctnr->top, ctnr->top->next);
	if (ctnr->bot)
		printf("\tbot:\n\t%p -> %p ->%p\n", ctnr->bot->prev, ctnr->bot, ctnr->bot->next);
	printf("after: ");
	gg_print_ctnr(ctnr);*/
}
