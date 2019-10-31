/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:31 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:01:50 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_exit(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

t_avl_str	*new_avl_str(char *key, t_content c)
{
	t_avl_str	*tmp;

	if (!(tmp = malloc(sizeof(t_avl_str))))
		ft_exit();
	tmp->key = key;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->c = c;
	return (tmp);
}

t_content	new_room(void)
{
	t_content	c;

	c.room.edges = NULL;
	c.room.froms = ctnr_new();
	c.room.out_exc = NULL;
	c.room.in_exc = NULL;
	c.room.divided = 0;
	c.room.shortest = 0;
	c.room.is_active = 1;
	return (c);
}

t_state		*new_state(void)
{
	t_state		*state;

	if (!(state = malloc(sizeof(t_state))))
		ft_exit();
	state->weight = 1;
	state->is_active = 1;
	state->cross = 0;
	return (state);
}

t_content	new_edge(t_avl_str *room, t_state *state, unsigned char n)
{
	t_content	c;

	c.edge.room = room;
	c.edge.state = state;
	c.edge.existance = 1;
	c.edge.n = n;
	return (c);
}
