/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctnr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 21:17:15 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/16 00:27:13 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTNR_H
# define CTNR_H

# include "avl.h"

typedef struct s_ctnr	t_ctnr;
typedef struct s_elem	t_elem;

struct					s_ctnr
{
	t_elem				*top;
	t_elem				*bot;
//	size_t				length;
};

struct					s_elem
{
	char				weight;
	t_node				*node;

	t_elem				*next;
	t_elem				*prev;
};

t_elem					*ctnr_pop_top(t_ctnr *ctnr);
t_elem					*ctnr_pop_bot(t_ctnr *ctnr);
void					ctnr_push_top(t_ctnr *ctnr, t_elem *elem);
void					ctnr_push_bot(t_ctnr *ctnr, t_elem *elem);
t_ctnr					*ctnr_new(void);
t_elem					*elem_new(t_node *node);

#endif
