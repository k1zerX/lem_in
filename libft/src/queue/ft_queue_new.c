/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:47:37 by kbatz             #+#    #+#             */
/*   Updated: 2019/03/04 15:42:53 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue		*ft_queue_new(void)
{
	t_queue		*queue;

	if (!(queue = ft_memalloc(sizeof(*queue))))
		return (NULL);
	return (queue);
}
