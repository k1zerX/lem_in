/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_push_top.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:29:17 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 23:52:56 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"

void	ctnr_push_top(t_ctnr *ctnr, t_elem *elem)
{
	if (elem)
	{
		if (ctnr->top)
			elem->next = ctnr->top;
		else
			ctnr->bot = elem;
		ctnr->top = elem;
	}
}
