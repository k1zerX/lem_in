/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:49:55 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:08:02 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_avl_str	*avl_str_find(t_avl_str *root, char *key, \
				int (*cmp)(char *a, char *b))
{
	int			buf;

	while (root)
		if ((buf = (*cmp)(key, root->key)) < 0)
			root = root->left;
		else if (buf > 0)
			root = root->right;
		else
			break ;
	return (root);
}
