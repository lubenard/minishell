/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:59:56 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/20 14:27:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		countwords(char const *s, char c)
{
	size_t	compteur;
	size_t	i;

	i = 0;
	compteur = 0;
	while (i < ft_strlen(s))
	{
		if (i == 0 && s[i] != c)
			compteur++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			compteur++;
		i++;
	}
	return (compteur);
}

static int		countchar(char const *str, int i, char c)
{
	int nbrchar;

	nbrchar = 0;
	while (str[i])
	{
		if (str[i] != c)
			nbrchar++;
		else
			return (nbrchar);
		i++;
	}
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		j;
	int		i;
	int		k;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	if (!(ret = (char **)malloc(sizeof(char *) * countwords(s, c) + 1)))
		return (0);
	while (j < countwords(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!(ret[j] = (char *)malloc(sizeof(char) * countchar(s, i, c) + 1)))
			return (0);
		while (s[i] != c && s[i])
			ret[j][k++] = s[i++];
		ret[j++][k] = '\0';
	}
	ret[j] = 0;
	return (ret);
}
