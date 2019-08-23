/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 23:20:28 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:01:00 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "libft.h"

# define BUFF_SIZE 30

typedef struct		s_file
{
	char			*line;
	int				fd;
}					t_file;

int					gnl(const int fd, char **line, int buff_size);

#endif
