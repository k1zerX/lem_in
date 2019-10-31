/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:20:37 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 08:57:22 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "lem_in.h"

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

void		free_str_list(t_str_list *term)
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

char		**rooms_split(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	if (!ft_strchr(str, '-'))
		ft_exit();
	arr = ft_strsplit(str, '-');
	return (arr);
}
