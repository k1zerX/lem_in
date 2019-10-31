/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:59:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 02:58:30 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "types.h"

struct						s_room
{
	t_avl_str				*edges;
	t_ctnr					*froms; // peredelat' na t_edge *, ibo huy ego znaet
	int						distance;
	t_avl_str				*out_exc;
	t_avl_str				*in_exc;
	unsigned char			divided		: 1;
	unsigned char			shortest	: 1;
	unsigned char			is_active	: 1;
};

struct						s_edge
{
	t_avl_str				*room;
	t_state					*state;
	unsigned char			existance	: 1;
	unsigned char			n			: 1;
};

struct						s_state
{
	char					weight;
	unsigned char			is_active	: 1;
	unsigned char			cross		: 2;
	t_avl_str				*ends[2];
};

struct					s_path
{
	t_ctnr				*path;
	int					len;
	int					ants;
};

struct					s_ants
{
	t_ant				*start;
	t_ant				*end;
};

struct					s_ant
{
	t_elem				*room;
	t_ant				*next;
	int					ind;
};

struct					s_my_queue
{
	t_qelem				*start;
	t_qelem				*end;
};

struct					s_qelem
{
	t_qelem				*next;
	t_avl_str			*room;
	t_avl_str			*edge_in;
};

#endif
