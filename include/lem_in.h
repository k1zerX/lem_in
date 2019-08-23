/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 00:21:10 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:33:40 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct		s_edge
{
	int				weight;
	struct s_node	*node;
}					t_edge

typedef struct		s_node
{
	t_edge			*edges;
	int				distance;
}					t_node;

#endif
