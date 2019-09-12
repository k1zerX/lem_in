/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:53:41 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/05 02:13:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

typedef struct			s_elem
{
	void				*content;
	size_t				content_size;
	struct s_elem		*next;
}						t_elem;

t_elem					*ft_new_elem(void *content, \
							size_t content_size, char copy);

#endif
