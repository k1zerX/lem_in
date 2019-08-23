/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:53:03 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:01:44 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"

typedef struct			s_queue
{
	t_elem				*start;
	t_elem				*end;
	size_t				len;
}						t_queue;

t_elem					*ft_queue_pop(t_queue *queue);
void					ft_queue_push(t_queue *queue, t_elem *tmp);
t_queue					*ft_queue_new(void);

#endif
