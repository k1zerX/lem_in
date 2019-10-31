/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:05:59 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 06:34:43 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "lem_in.h"

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

char		*ft_str_dupl(int size, char *str)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * (size + 1))))
		ft_exit();
	res = ft_strncpy(res, str, size);
	res[size] = '\0';
	return (res);
}

char		*find_name(char *str)
{
	char	*name;
	int		i;

	if (*str == '#' && *(str + 1) == '#')
		return (str);
	if (*str == '#')
		return (NULL);
	else
	{
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '-' && str[i] != '\n')
			i++;
		if (i == 0 || str[0] == 'L')
			ft_exit();
		name = ft_str_dupl(i, str);
	}
	return (name);
}

char		**rooms_split(char *str)
{
	char	**arr;
	char	*new;
	int		i;

	i = 0;
	if (!ft_strchr(str, '-'))
		ft_exit();
	arr = ft_strsplit(str, '-');
	return (arr);
}

void		init_edges(t_read *term, char **arr, char *s_n, char *e_n)
{
	t_avl_str	*tmp;
	t_avl_str	*tmp1;
	t_avl_str	*tmp2;
	t_state		*state;

	if (ft_strequ(arr[0], arr[1]))
		ft_exit();
	tmp1 = avl_str_find(term->root, arr[0], &ft_strcmp);
	tmp2 = avl_str_find(term->root, arr[1], &ft_strcmp);
	if (!tmp1 || !tmp2)
		ft_exit();
	if (tmp1 == term->start || tmp2 == term->start)
		++(*s_n);
	if (tmp1 == term->end || tmp2 == term->end)
		++(*e_n);
	state = new_state();
	tmp = new_avl_str(tmp1->key, new_edge(tmp2, state, 1));
	state->ends[0] = tmp;
	tmp2->c.room.edges = avl_str_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
	tmp = new_avl_str(tmp2->key, new_edge(tmp1, state, 0));
	state->ends[1] = tmp;
	tmp1->c.room.edges = avl_str_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
	free(arr[0]);
	free(arr[1]);
	free(arr);
}

int			push_edges(t_read *term, char *str, t_str_list *str_list)
{
	char	s_n;
	char	e_n;

	s_n = 0;
	e_n = 0;
	init_edges(term, rooms_split(str), &s_n, &e_n);
	while (gnl(0, &str) > 0)
	{
		add_to_list(str_list, str);
		if (str[ft_strlen(str) - 1] == 13)
			str[ft_strlen(str) - 1] = '\0';
		if (!str || str[0] == '#')
			continue ;
		init_edges(term, rooms_split(str), &s_n, &e_n);
	}
	return ((s_n < e_n) ? (s_n) : (e_n));
}

t_avl_str		*init_node(t_read *term, char *str, int *is_start)
{
	int			i;
	t_avl_str	*node;
	char		*name;

	i = 0;
	while (str[i] != ' ' && str[i] != '-' && str[i] && str[i] != '\n')
		i++;
	if (str[i] == '-')
		ft_exit();
	name = ft_str_dupl(i, str);
	node = new_avl_str(name, new_room());
	while (str[i] && str[i + 1] != ' ')
		i++;
	if (*is_start == 1 || *is_start == -1)
	{
		term->start = (*is_start == 1) ? node : term->start;
		term->end = (*is_start == -1) ? node : term->end;
		*is_start = 0;
	}
	return (node);
}

void			is_valid(t_read *term, t_str_list *str_list)
{
	char		*str;
	char		*name;
	t_avl_str	*tmp;
	int			is_start;

	is_start = 0;
	while (gnl(0, &str) > 0)
	{
		add_to_list(str_list, str);
		if (str[ft_strlen(str) - 1] == 13)
			str[ft_strlen(str) - 1] = '\0';
		if ((name = find_name(str)))
		{
			if (ft_strequ(name, "##start") || ft_strequ(name, "##end"))
			{
				is_start = (ft_strequ(name, "##start")) ? 1 : is_start;
				is_start = (ft_strequ(name, "##end")) ? -1 : is_start;
				continue ;
			}
			if (!(tmp = avl_str_find(term->root, name, &ft_strcmp)))
				term->root = avl_str_insert(term->root, init_node(term, str, &is_start), &ft_strcmp);
			else
				term->max_paths = push_edges(term, str, str_list);
		}
		free(name);
	}
}

t_str_list		*is_valid_map(t_read *term)
{
	char			*str;
	t_str_list		*str_list;

	if (!(str_list = (t_str_list *)malloc(sizeof(t_str_list))))
		ft_exit();
	term->root = NULL;
	term->ants = 0;
	str_list->start = NULL;
	str_list->end = NULL;
	if (gnl(0, &str) <= 0 || (term->ants = ft_atoi(str)) <= 0)
		ft_exit();
	add_to_list(str_list, str);
	is_valid(term, str_list);
	if (!term->max_paths)
		ft_exit();
	return (str_list);
}

void			print_map(t_str_list_elem *start)
{
	while (start)
	{
		printf("%s\n", start->s);
		start = start->next;
	}
}

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
	exit(0);
}
