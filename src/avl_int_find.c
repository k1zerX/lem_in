/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_int_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:49:55 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:26:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_avl_int	*avl_int_find(t_avl_int *root, int key, \
				int (*cmp)(int a, int b))
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
