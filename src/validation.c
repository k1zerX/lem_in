/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:05:59 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 07:24:23 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "lem_in.h"

void		print_map(t_str_list_elem *start)
{
	while (start)
	{
		ft_printf("%s\n", start->s);
		start = start->next;
	}
}

void		add_to_list(t_str_list *list, char *s)
{
	t_str_list_elem *new;

	if (!(new = (t_str_list_elem *)malloc(sizeof(t_str_list_elem))))
		ft_exit();
	new->s = s;
	new->next = NULL;
	if (!list->start && !list->end)
		list->start = new;
	else if (!list->end)
	{
		list->end = new;
		list->start->next = list->end;
	}
	else
	{
		list->end->next = new;
		list->end = list->end->next;
	}
}
