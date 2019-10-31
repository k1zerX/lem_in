/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:10:31 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 08:50:33 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "types.h"
# include "ctnr.h"
# include "avl.h"
# include "libft.h"

# include <stdlib.h>

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
