/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/06 22:12:11 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "lem-in.h"

void	ft_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

int		ft_cmp(t_avl_node *a, t_avl_node *b)
{
	return (ft_strcmp(a->content->name, b->content->name));
}

int		is_valid_str(char *str)
{
	t_avl_node	*new;

	if (str[0] == '#')
	{
		if (str[1] == '#')
		{
			if (!ft_strcmp(str, "##start"))
			{
				free(str);
				gnl(0, &str, 6);
				new = ft_avl_node_new;
				return (1);
			}
			else if (!ft_strcmp(str, "##end"))
			{
				free(str);
				gnl(0, &str, 6);
				new = ft_avl_node_new;
				return (2);
			else
				return (0);
		}
		else //comment
			return (0);
	}
	else if (*str != 'L')
	{
		while(*str && *str != ' ' && *str != '-')
			str++;
		if (*str == ' ')
			return (3);
		else if (*str == '-')
			return (4);
		else
			return (-1);
	}
	else
		return (-1);
}

int		is_start_or_end(char *str, int rooms, t_container *cont, int visual)
{

}


void	read_map(t_node *root, int *ants, int visual)
{
	char		*str;
	t_container	*cont;
	int			*rooms;

	if (gnl(0, &str, 6) <= 0 || (ants = ft_atoi(str)) <= 0)
		ft_error("Error\n");
	free(str);

	cont = NULL;
	*rooms = 1;

	while (gnl(0, &str, 6) > 0)
	{
		if (!str)
			ft_error("Error\n");
		is_valid_str(str, rooms, cont);
		if (visual)
			create_coords();
		free(str);
	}
}

int		main(int ac, char **av)
{
	int		ants;
	t_node	*root;

	root = NULL;
	read_map(root, &ants, ft_strequ(av[1], "-v"));//is need to visualise
	while ()
	//algorithm();
	//put_solution();
	return (0);
}*/
