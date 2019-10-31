/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:46 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 07:35:29 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

# include "avl.h"

typedef struct s_elem		t_elem;

struct						s_container
{
	t_elem					*start;
	t_elem					*end;
};

struct						s_elem
{
	char					weight;
	t_node					*node;
	t_elem					*next;
};

#endif
