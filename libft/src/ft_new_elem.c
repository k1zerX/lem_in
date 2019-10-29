/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 16:56:53 by kbatz             #+#    #+#             */
/*   Updated: 2019/03/04 15:47:15 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem		*ft_new_elem(void *content, size_t content_size, char copy)
{
	t_elem		*tmp;

	if (!(tmp = ft_memalloc(sizeof(*tmp))))
		return (NULL);
	if (content)
	{
		tmp->content_size = content_size;
		if (!copy)
			tmp->content = content;
		else
		{
			if (!(tmp->content = malloc(content_size)))
			{
				free(tmp);
				return (NULL);
			}
			ft_memcpy(tmp->content, content, content_size);
		}
	}
	return (tmp);
}
