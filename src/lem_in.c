/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/15 18:05:17 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "lem_in.h"

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

void	read_map(int *ants)
{
	char	*str;
	char	*start;
	char	*end;
	char	rooms;

	gnl(0, &str, 6);//6
	if ((ants = ft_atoi(str)) < 0)// if 0??
		ft_error("Error\n");
	free(str);
	rooms = 1;
	ft_avl_tree_new(int (*ft_cmp)(t_avl_node *a, t_avl_node *b));
	while (gnl(0, &str, 6) != -1)
	{
		if (!str)
			ft_error("Error\n");
		is_start_or_end(str, rooms, start, end);
		is_valid_str(str, rooms);
		free(str);
	}
}


int		main(int ac, char **av)
{
	int		ants;


	read_map(&ants, );

	//algorithm();
	//put_solution();
	return (0);
}*/
