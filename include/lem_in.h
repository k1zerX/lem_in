/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:59:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:00:14 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "types.h"

struct					s_path
{
	t_ctnr				*path;
	char				len;	// sdelat; int
	char				ants;	// sdelat' int
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

#endif
