/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:46:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/26 12:38:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_char(char *str, int i)
{
	int j;

	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (j);
		i++;
		j++;
	}
	return (j);
}

int		countwords(char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] != 0)
		k++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				i++;
			if (str[i] != 0)
				k++;
		}
		i++;
	}
	return (k);
}

char	**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	tab = (char **)malloc((countwords(str) + 1) * sizeof(char *));
	while (str[i] && j < countwords(str))
	{
		k = 0;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		tab[j] = (char *)malloc((count_char(str, i) + 1) * sizeof(char));
		while (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i])
			tab[j][k++] = str[i++];
		tab[j++][k] = 0;
	}
	tab[j] = 0;
	return (tab);
}
