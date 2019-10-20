/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/20 23:48:57 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "gnl.h"

#include <stdio.h>
/*
void		ft_exit(char *str)
{
	write(1, "\e[38;05;196m", 12);
	ft_putendl(str);
	exit(1);
}

t_node		*new_node(T_AVL_KEY key, t_content c);
t_state		*new_state(void);
t_content	new_edge(t_node *room, t_state *state);
t_content	new_room(void);

char *find_name(char *str)
{
	char *name;
		int i;

	if (*str == '#' && *(str + 1) != '#')//comment
	{
		return(NULL);
	}
	if (*str == '#')// st/end
	{
		return (str);
	}
	else
	{
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '-' && str[i] != '\n')
		{
			i++;
		}
		if (i == 0 || str[0] == 'L')
			ft_exit("error");
		name = malloc(sizeof(char) * (i + 1));
		name = ft_strncpy(name, str, i);
		name[i] = '\0';
	}
	return (name);
}


// int	is_valid_str(char **str)
// {
// 	int spaces;

// 	spaces = 0;
// 	if (ft_strequ(*str, "##start") || ft_strequ(*str, "##end"))
// 		return ;
// 	else if (**str == '#')
// 	{
// 		free(*str);
// 		gnl(0, &(*str), 6);
// 	}
// 	while(**str && **str != ' ')//name
// 		(*str)++;
// 	while (**str)//coords
// 	{
// 		if ((**str == '-' || **str == '+') && !ft_isdigit(*(*str + 1)))
// 			ft_exit("error, - or +");
// 		if (**str == ' ')
// 			spaces++;
// 		(*str)++;
// 	}
// 	if (spaces > 2)
// 		ft_error("spaces");
// }

void	print_nodes_test(t_node *root, t_node *start, t_node *end, int ants, int max_paths)
{
	printf("root: %s, %.1f, %.1f\n", root->name, root->x, root->y);
	printf("root left: %s, %.1f, %.1f\n", root->left->name, root->left->x, root->left->y);
	printf("root right: %s, %.1f, %.1f\n", root->right->name, root->right->x, root->right->y);
	printf("start: %s, %.1f, %.1f\n", start->name, start->x, start->y);
	printf("end: %s, %.1f, %.1f\n", end->name, end->x, end->y);
	printf("ants = %d, max paths = %d\n", ants, max_paths);

}

char **rooms_split(char *str, char c, char *s_n, char *e_n)
{
	char	**arr;
	char	*new;
	int i;

	i = 0;

	if (!ft_strchr(str, '-'))
		ft_exit("There's no edges in one of the rooms");
	arr = ft_strsplit(str, c);
	while (arr[1][i] != '\0')
		i++;
	if (arr[1][i - 1] == 13)
	{
		new = malloc(sizeof(char) * (i));
		new = ft_strncpy(new, arr[1], i);
		new[i - 1] = '\0';
		free(arr[1]);
		arr[1] = new;
	}
	arr[2] = s_n;
	arr[3] = e_n;
	return (arr);
}

void	init_edges(t_node *root, char **arr, t_node **start, t_node **end)
{
	t_node	*tmp1;
	t_node	*tmp;
	t_node	*tmp2;
	t_state	*state;

	if (ft_strequ(arr[0], arr[1]))
		ft_exit("error same rooms");
	tmp1 = avl_find(root, arr[0], &ft_strcmp);
	tmp2 = avl_find(root, arr[1], &ft_strcmp);
	if (!tmp1 || !tmp2)
		ft_exit("Wrong room name!");
	free(arr);
	if (tmp1 == *start || tmp2 == *start)
		++(*(arr[2]));
	if (tmp1 == *end || tmp2 == *end)
		++(*(arr[3]));
	state = new_state();
	tmp = new_node(tmp1->name, new_edge(tmp1, state));
	tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
	tmp = new_node(tmp2->name, new_edge(tmp2, state));
	tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
}

int		push_edges(t_node **start, t_node **end, t_node *root, char *str)
{
	char	s_n;
	char	e_n;

	s_n = 0;
	e_n = 0;
	init_edges(root, rooms_split(str, '-', &s_n, &e_n), start, end);
	free(str);
	while (gnl(0, &str) > 0)
	{
		if (!str || str[0] == '#')
			continue ;
		init_edges(root, rooms_split(str, '-', &s_n, &e_n), start, end);
		free(str);
	}
	return ((s_n < e_n) ? (s_n) : (e_n));
}
t_node		*init_node(t_node **start, t_node **end, char *str, int *is_start)
{
	int		i;
	t_node	*node;
	char	*name;

	i = 0;
	while (str[i] != ' ' && str[i] != '-')
		i++;
	if (str[i] == '-')
		ft_exit("Error, no such room");
	name = ft_memalloc(sizeof(char) * (i + 1));
	name = ft_strncpy(name, str, i);// i + 1???
	name[i] = '\0';
	node = new_node(name, new_room());
//	node->x = ft_atoi(str + i);
	while (str[i + 1] != ' ')
		i++;
//	node->y = ft_atoi(str + i + 1);
	if (*is_start == 1 || *is_start == -1)
	{
		*start = (*is_start == 1) ? node : *start;
		*end = (*is_start == -1) ? node : *end;
		*is_start = 0;
	}
	return (node);
}

t_node		*is_valid_map(t_node **start, t_node **end, int *ants, int *max_paths)
{
	char	*str;
	char	*name;
	t_node	*tmp;
	t_node	*root;
	int is_start = 0;

	root = NULL;
	if (gnl(0, &str) <= 0 || (*ants = ft_atoi(str)) <= 0)
		ft_exit("Error, ants");
	free(str);
	while (gnl(0, &str) > 0)
	{
		if ((name = find_name(str)))
		{
			if (!ft_strncmp(name, "##start", 7) || !ft_strncmp(name, "##end", 5))
			{
				is_start = (!ft_strncmp(name, "##start", 7)) ? 1 : is_start;
				is_start = (!ft_strncmp(name, "##end", 5)) ? -1 : is_start;
				free(str);
				continue ;
			}
			if (!(tmp = avl_find(root, name, &ft_strcmp)))
				root = avl_insert(root, init_node(start, end, str, &is_start), &ft_strcmp);
			else
				*max_paths = push_edges(start, end, root, str);
		}
		free(str);
	}
	if (!*max_paths)
		ft_exit("there is no edges");
	// print_nodes_and_edges(root, *start, *end, *ants, *max_paths);
	return (root);
}

int			main()
{
	t_node	*root;
	int		ants;
	int		max_paths;
	t_node	*start;
	t_node	*end;
	
	start = NULL;
	end = NULL;
	ants = 0;
	max_paths = 0;
	root = is_valid_map(&start, &end, &ants, &max_paths);
	
}*/
