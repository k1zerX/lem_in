/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 06:17:25 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 06:22:10 by etuffleb         ###   ########.fr       */
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