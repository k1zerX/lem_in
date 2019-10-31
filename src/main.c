/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:32:43 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "types.h"
#include "lem_in.h"
#include "read.h"

void		print_ants(t_path **sols, int min, int ind)
{
	int		i;
	int		j;
	t_ants	ingame;

	ft_printf("\n");
	ingame = (t_ants){NULL, NULL};
	i = 0;
	while (i < min)
	{
		j = 0;
		while (j < ind)
		{
			if ((*sols)[j].ants > 0)
			{
				add_ant(&ingame, (*sols)[j].path->top);
				--(*sols)[j].ants;
			}
			++j;
		}
		move_ants(&ingame);
		++i;
	}
}

void		count_ants2(t_path *paths, int n, int j)
{
	int		buf;
	int		div;
	int		mod;

	div = n / j;
	mod = n % j;
	--paths;
	--j;
	buf = 0;
	while (j >= mod)
	{
		paths->ants += buf;
		buf = paths->ants;
		paths->ants += div;
		--j;
		--paths;
	}
	while (j >= 0)
	{
		paths->ants += buf;
		buf = paths->ants;
		paths->ants += div + 1;
		--j;
		--paths;
	}
}

void		count_ants(t_path *paths, int n, int i)
{
	int		div;
	int		mod;
	int		j;

	paths[-1].ants = 0;
	j = 1;
	while (j < i)
	{
		paths[-1].ants = paths->len - paths[-1].len;
		n -= paths[-1].ants * j;
		div = n / j;
		mod = n % j;
		if (n <= 0 || div == 0 || (div == 1 && mod == 0))
		{
			n += paths[-1].ants * j;
			break ;
		}
		++paths;
		++j;
	}
	paths[-1].ants = 0;
	count_ants2(paths, n, j);
}

int			main_cycle(t_path **sols, t_min *min, t_read *terminates)
{
	int		i;

	i = 1;
	while (i <= terminates->max_paths)
	{
		ctnr_push_top(terminates->start->c.room.froms, new_elem(NULL));
		not_dijkstra(terminates->start);
		free(ctnr_pop_top(terminates->start->c.room.froms));
		if (terminates->end->c.room.froms->top == NULL)
			break ;
		path_invert(terminates->end);
		find_paths(terminates->start, terminates->end, sols, i);
		count_ants(*sols + 1, terminates->ants, i);
		if ((*sols)->ants + (*sols)->len - 1 < min->min || min->min == -1)
			*min = (t_min){(*sols)->ants + (*sols)->len - 1, i};
		reset(terminates->start);
		++sols;
		++i;
	}
	return (i);
}

int			main(int ac, char *av[])
{
	int			i;
	t_path		**sols;
	t_min		min;
	t_read		terminates;
	t_str_list	*str_list;

	terminates = (t_read){NULL, NULL, NULL, 0, 0};
	str_list = is_valid_map(&terminates);
	print_map(str_list->start);
	if (!(sols = ft_memalloc(terminates.max_paths * sizeof(t_path *))))
		ft_exit();
	min.min = -1;
	i = main_cycle(sols, &min, &terminates);
	if (min.min == -1)
		ft_exit();
	print_ants(sols + min.ind - 1, min.min, min.ind);
	free_str_list(str_list);
	smart_free(terminates.start);
	del_sols(sols, i);
	return (0);
}
