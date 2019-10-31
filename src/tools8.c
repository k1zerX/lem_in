/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:41:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:48:57 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	print_all_ants(t_avl_str *end, int n)
{
	int		i;

	i = 1;
	while (i < n)
	{
		ft_printf("L%d-%s ", i, end->key);
		++i;
	}
	ft_printf("L%d-%s\n", i, end->key);
}

void	find_in(t_avl_str *root, t_avl_str *room, int n)
{
	t_avl_str	*pot_room;
	t_avl_str	*edge_in;

	if (!root)
		return ;
	find_in(root->left, room, n);
	find_in(root->right, room, n);
	edge_in = root->c.edge.state->ends[root->c.edge.n];
	pot_room = edge_in->c.edge.room;
	if (pot_room == room)
	{
		print_all_ants(room, n);
		exit(0);
	}
}

void	start_to_end(t_read *terminates)
{
	find_in(terminates->start->c.room.edges, terminates->end, terminates->ants);
}
