/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:17:15 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 07:41:59 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTNR_H
# define CTNR_H

# include "avl.h"
# include "types.h"
# include <stdlib.h>

# ifndef NULL
#  define NULL (void *)0
# endif

struct					s_ctnr
{
	t_elem				*top;
	t_elem				*bot;
};

struct					s_elem
{
	t_avl_str			*edge;
	t_elem				*next;
	t_elem				*prev;
};

t_elem					*ctnr_pop_top(t_ctnr *ctnr);
t_elem					*ctnr_pop_bot(t_ctnr *ctnr);
void					ctnr_push_top(t_ctnr *ctnr, t_elem *elem);
void					ctnr_push_bot(t_ctnr *ctnr, t_elem *elem);
t_ctnr					*ctnr_new(void);
void					ctnr_clear(t_ctnr *ctnr, void (*del)(t_elem *elem));

#endif
