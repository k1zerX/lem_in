# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rename.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 13:46:55 by kbatz             #+#    #+#              #
#    Updated: 2018/12/03 14:07:46 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

head -n 3 $1 > f_test
cat $1 | head -n 4 | tail -n 1 | sed "s/   /   ft_/" | sed "s/.c   /.c/" >> f_test
cat $1 | head -n 11 | tail -n 7 >> f_test
cat $1 | grep -v "/\*" >> f_test
