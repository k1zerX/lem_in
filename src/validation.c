/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:05:59 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 06:24:49 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "lem_in.h"

void			free_str_list(t_str_list *term)
{
	t_str_list_elem		*tmp;
	t_str_list_elem		*next;

	tmp = term->start;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->s);
		free(tmp);
		tmp = next;
	}
}

void	print_test_avl(t_read *terminates)
{
	printf("root = %s\n", terminates->root->key);
	printf("start = %s\n", terminates->start->key);
	printf("end = %s\n", terminates->end->key);
	printf("max_path = %d\n", terminates->max_paths);
	printf("ants = %d\n", terminates->ants);
	avl_str_infix(terminates->root, &print_room);
}
