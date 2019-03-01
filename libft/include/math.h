/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:14:48 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/17 03:06:10 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

#include "libft.h"

# define LOG_PR 0.000001
# define LOG_ADD_PR 1000000

# define FT_ABS(x) (x < 0 ? -(x) : x)
# define FT_SIGN(x) (x < 0 ? -1 : 1)
# define FT_MIN(a,b) (a < b ? a : b)
# define FT_MAX(a,b) (a > b ? a : b)

double					ft_log(double n);

#endif
