/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_infix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:09 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:09:20 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

void	avl_str_infix(t_avl_str *root, void (*f)(t_avl_str *root))
{
	if (!root)
		return ;
	avl_str_infix(root->left, f);
	(*f)(root);
	avl_str_infix(root->right, f);
}
