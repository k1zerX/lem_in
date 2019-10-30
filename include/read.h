/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:10:31 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/30 19:07:26 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct s_read			t_read;
typedef struct s_str_list		t_str_list;
typedef struct s_str_list_elem	t_str_list_elem;

struct					s_read
{
	t_avl_str			*root;
	t_avl_str			*start;
	t_avl_str			*end;
	int					ants;
	int					max_paths;
};

struct					s_str_list_elem
{
	char				*s;
	t_str_list_elem		*next;
};

struct					s_str_list
{
	t_str_list_elem		*start;
	t_str_list_elem		*end;
};

#endif
