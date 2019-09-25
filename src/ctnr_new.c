/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:19:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/25 20:51:34 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "stdlib.h"

t_ctnr	*ctnr_new(void)
{
	t_ctnr	*tmp;

	if ((tmp = malloc(sizeof(t_ctnr))))
	{
		tmp->top = NULL;
		tmp->bot = NULL;
	}
	return (tmp);
}
