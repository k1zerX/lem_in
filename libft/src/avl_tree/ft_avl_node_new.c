/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avl_node_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:15:11 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 23:11:49 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_avl_node	*ft_avl_node_new(void *content, size_t content_size, char copy)
{
	t_avl_node	*tmp;

	if (!(tmp = ft_memalloc(sizeof(*tmp))))
		return (NULL);
	if (content)
	{
		tmp->content_size = content_size;
		if (copy)
		{
			if (!(tmp->content = malloc(content_size)))
			{
				free(tmp);
				return (NULL);
			}
			ft_memcpy(tmp->content, content, content_size);
		}
		else
			tmp->content = content;
	}
	tmp->height = 1;
	return (tmp);
}
