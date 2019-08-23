/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:53:09 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:11:29 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*get_lst(t_list **all_data, int fd, int bsize)
{
	t_file	struc;
	t_list	*tmp;
	t_list	*prev;

	struc.line = ft_memalloc(bsize + 1);
	struc.fd = fd;
	if (!*all_data)
	{
		*all_data = ft_lstnew(&struc, sizeof(struc));
		return (*all_data);
	}
	tmp = *all_data;
	while (tmp && ((t_file *)tmp->content)->fd != fd && (prev = tmp))
		tmp = tmp->next;
	if (!tmp)
	{
		prev->next = ft_lstnew(&struc, sizeof(struc));
		return (prev->next);
	}
	free(struc.line);
	return (tmp);
}

size_t	str_rec(char *str, char **line, size_t len, long n)
{
	long	i;
	char	*tmp;

	tmp = ft_strchr(str, '\n');
	if (tmp)
		i = tmp - str;
	else
		i = n;
	*line = ft_realloc(*line, len, i);
	ft_strncpy(*line + len - 1, str, i);
	ft_memmove(str, str + i + 1, n - i + 1);
	if (i < n)
		return (0);
	return (len + i);
}

void	ft_free(t_list **tmp)
{
	if ((*tmp)->content)
	{
		if (((t_file *)(*tmp)->content)->line)
			free(((t_file *)(*tmp)->content)->line);
		free((*tmp)->content);
	}
	ft_memdel((void **)tmp);
}

void	ft_lst_free(t_list **all_data, int fd)
{
	t_list	*tmp;
	t_list	*buf;

	tmp = *all_data;
	if (!tmp)
		return ;
	if (tmp->next)
	{
		while (((t_file *)(tmp->next)->content)->fd != fd)
			tmp = tmp->next;
		buf = tmp->next;
		tmp->next = buf->next;
		ft_free(&buf);
		return ;
	}
	ft_free(all_data);
}

int		gnl(const int fd, char **line, int buff_size)
{
	static t_list	*all_data;
	static int		bsize = buff_size;
	ssize_t			n;
	size_t			len;
	char			*str;

	if (bsize <= 0)
		bsize = BUFF_SIZE;
	if (!line || read(fd, *line, 0) == -1)
		return (-1);
	*line = NULL;
	str = ((t_file *)get_lst(&all_data, fd, bsize)->content)->line;
	if (!(len = str_rec(str, line, 1, ft_strlen(str))))
		return (1);
	while ((n = read(fd, str, bsize)) > 0)
	{
		str[n] = 0;
		if (!(len = str_rec(str, line, len, n)))
			return (1);
	}
	ft_lst_free(&all_data, fd);
	if (n == 0 && **line)
		return (1);
	ft_memdel((void **)line);
	return (n);
}
