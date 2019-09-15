/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/16 00:27:16 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"
#include "container.h"

int		cmp(t_node *a, t_node *b)
{
	return (ft_strcmp(((t_node *)a->content)->name, \
			((t_node *)b->content)->name));
}

t_node	*new_node(T_AVL_KEY key)
{
	t_node	*tmp;

	if (!(tmp = malloc(sizeof(t_node))))
		ft_exit();
	tmp->name = key;
	tmp->left = NULL;
	tmp->right = NULL;
	if (tmp->edges = ctnr_new())
		ft_exit();
	return (tmp);
}

int		main(void)
{
	t_node	*root;
	int		i;
	char	**arr;
	t_node	*tmp;

	i = 1;
	while (i < ac && *av[i] != ';')
	{
		root = avl_insert(root, new_node(av[i]));
		++i;
	}
	++i;
	while (i < ac)
	{
		arr = ft_strsplit(av[i], '-');
		tmp1 = avl_find(root, arr[0], &cmp);
		tmp2 = avl_find(root, arr[1], &cmp);
		ctnr_push_bot(tmp1->edges, elem_new(tmp2));
		ctnr_push_bot(tmp2->edges, elem_new(tmp1));
	}
	return (0);
}
/*
void	ft_add_node(t_node *nodes, int *len, char *str)
{
	int		name_len;

	nodes = ft_realloc(nodes, *len * sizeof(t_node), sizeof(t_node));
	nodes[len] = ft_memalloc(sizeof(t_node));
	name_len = str - ft_strchr(str, ' ');
	nodes[len].name = malloc((name_len + 1) * sizeof(char));
	nodes[len].name[name_len] = 0;
	ft_memcpy(&nodes[len].name, str, name_len);
	++len;
}

int		main(int ac, char **av)
{
	int		start;
	int		end;
	t_node	*nodes;
	int		len;
	int		ants;
	char	*str;

	nodes = NULL;
	len = 0;
	gnl(0, &str, GNL_BUFF);
	ants = ft_atoi(str);
	free(str);
	while (gnl(0, &str, GNL_BUFF) > 0)
	{
		if (ft_strequ(str, "##start"))
		{
			free(str);
			gnl(0, &str, GNL_BUFF);
			start = len;
			ft_add_node(nodes, &len, str);
		}
		if (ft_strequ(str, "##end"))
		{
			free(str);
			gnl(0, &str, GNL_BUFF);
			start = end;
			ft_add_node(nodes, &len, str);
		}
		ft_add_node(nodes, &len, str);
		free(str);
	}
	return (0);
}
