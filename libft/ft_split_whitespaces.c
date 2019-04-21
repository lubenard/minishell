/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:46:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/21 10:14:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

int		countwords(char *str, int i)
{
	int nbrmots;

	nbrmots = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 32 && str[i + 1] < 33)
			nbrmots++;
		i++;
	}
	return (nbrmots);
}

int		count_char(char *str, int i)
{
	int nbrchar;

	nbrchar = 0;
	while (str[i] != ' ')
	{
		nbrchar++;
		i++;
	}
	return (nbrchar);
}

char	**ft_split_whitespaces(char *str, int i)
{
	char	**tab;
	int		k;
	int		j;
	int		i2;

	i2 = i;
	j = 0;
	tab = (char **)malloc(sizeof(char) * (countwords(str, i) + 1));
	printf("There is %d elements\n", countwords(str, i));
	while (str[i] && j < countwords(str, i2))
	{
		k = 0;
		while (str[i] < 33)
		{
			printf("Je passe %c\n", str[i]);
			i++;
		}
		printf("Je malloc de %d chars\n", count_char(str, i));
		tab[j] = ft_strnew(count_char(str, i));
		while (str[i] > 32 && str[i])
		{
			printf("Je copie str[i] = %c\n", str[i]);
			tab[j][k++] = str[i++];
		}
	}
	tab[j] = 0;
	return (tab);
}
