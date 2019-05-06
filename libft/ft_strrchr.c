/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:41:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/06 16:21:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int start, int c)
{

	while (s[start])
	{
		if (s[start] == (char)c)
			return ((char *)&s[start]);
		start++;
	}
	return (0);
}
