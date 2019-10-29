/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:43:36 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"

#include <stdio.h>

void		ft_exit(char *str)
{
	ft_putendl(str);
	exit(1);
}

t_node		*new_node(T_AVL_KEY key, t_content c);
t_state		*new_state(void);
t_content	new_edge(t_node *room, t_state *state);
t_content	new_room(void);

typedef struct	s_terminates
{
	t_node		*root;
	t_node		*start;
	t_node		*end;
	int			max_paths;
	int			ants;
}				t_terminates;

char		*find_name(char *str)
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
		if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
			ft_exit("malloc");
		name = ft_strncpy(name, str, i);
		name[i] = '\0';
	}
	return (name);
}

void	print_nodes_test(t_terminates *term)
{
	printf("root: %s\n", term->root->name);
	printf("root left: %s\n", term->root->left->name);
	printf("root right: %s\n", term->root->right->name);
	printf("start: %s\n", term->start->name);
	printf("end: %s\n", term->end->name);
	printf("ants = %d, max paths = %d\n", term->ants, term->max_paths);
}

char		**rooms_split(char *str, char c, char *s_n, char *e_n)
{
	char	**arr;
	char	*new;
	int		i;

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

void		init_edges(t_terminates *term, char **arr)
{
	t_node	*tmp1;
	t_node	*tmp;
	t_node	*tmp2;
	t_state	*state;

	if (ft_strequ(arr[0], arr[1]))
		ft_exit("error same rooms");
	tmp1 = avl_find(term->root, arr[0], &ft_strcmp);
	tmp2 = avl_find(term->root, arr[1], &ft_strcmp);
	if (!tmp1 || !tmp2)
		ft_exit("Wrong room name!");
	free(arr);
	if (tmp1 == term->start || tmp2 == term->start)
		++(*(arr[2]));
	if (tmp1 == term->end || tmp2 == term->end)
		++(*(arr[3]));
	state = new_state();
	tmp = new_node(tmp1->name, new_edge(tmp1, state));
	tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
	tmp = new_node(tmp2->name, new_edge(tmp2, state));
	tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
}

int			push_edges(t_terminates *term, char *str, int i, char ***arr)
{
	char	s_n;
	char	e_n;

	s_n = 0;
	e_n = 0;
	init_edges(term, rooms_split(str, '-', &s_n, &e_n));
	free(str);

	while (gnl(0, &str) > 0)
	{
		if (!str || str[0] == '#')
			continue ;
		printf("str = %s\n", str);
		(*arr)[i] = ft_strdup(str);
		i++;
		free(str);
	}
	return ((s_n < e_n) ? (s_n) : (e_n));
}

t_node		*init_node(t_terminates *term, char *str, int *is_start)
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
	while (str[i + 1] != ' ')
		i++;
	if (*is_start == 1 || *is_start == -1)
	{
		term->start = (*is_start == 1) ? node : term->start;
		term->end = (*is_start == -1) ? node : term->end;
		*is_start = 0;
	}
	return (node);
}

t_node		*is_valid_map(t_terminates *term, char ***arr)
{
	char	*name;
	char	*str;
	t_node	*tmp;
	int		is_start;
	int		buf;
	int i = 1;

	is_start = 0;
	while ((buf = gnl(0, &str)) > 0)
	{
		if ((name = find_name(str)))
		{
			printf("str = %s\n", str);
			(*arr)[i] = ft_strdup(str);
			i++;
			if (!ft_strncmp(name, "##start", 7) || !ft_strncmp(name, "##end", 5))
			{
				is_start = (!ft_strncmp(name, "##start", 7)) ? 1 : is_start;
				is_start = (!ft_strncmp(name, "##end", 5)) ? -1 : is_start;
				continue ;
			}
			if (!(tmp = avl_find(term->root, name, &ft_strcmp)))
				term->root = avl_insert(term->root, init_node(term, str, &is_start), &ft_strcmp);
			else
			{
				term->max_paths = push_edges(term, str, i, arr);
			}
			free(str);
		}
	}
	if (buf == -1)
		ft_exit("buff == -1");
	return (term->root);
}

void	print_map(char **arr)
{
	while(arr)
	{
		printf("%s", *arr);
		arr++;
	}

}

t_node		*get_map(t_terminates *term)
{
	char	*str;
	char	**arr;

	term->max_paths = 0;
	term->ants = 0;
	if (gnl(0, &str) <= 0 || (term->ants = ft_atoi(str)) <= 0)
		ft_exit("Error, ants");
	arr = &str;
	term->start = NULL;
	term->end = NULL;
	
	term->root = is_valid_map(term, &arr);
	if (!term->max_paths)
		ft_exit("there is no edges");
	// print_map(arr);
	print_nodes_test(term);
//	free_arr(&arr[1]);
	return (term->root);
}

int			main()
{
	t_terminates	*term;

	if (!(term = (t_terminates *)malloc(sizeof(t_terminates))))
		ft_exit("Error");
	term->root = get_map(term);

	
}
