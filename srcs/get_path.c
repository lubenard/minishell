/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:01:21 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/15 15:20:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_len(char *path_line)
{
	int i;
	int j;

	i = 4;
	j = 0;
	while (path_line[i] != '\0')
	{
		if (path_line[i] == ':')
			++j;
		++i;
	}
	return (++j);
}

char	**get_path(char *path_line)
{
	int		i;
	int		j;
	char	**path;
	int		k;

	i = 0;
	j = 5;
	k = 0;
	if (!(path = (char **)malloc(sizeof(char *) * (ft_len(path_line)+ 1))))
		return (NULL);
	while (k < ft_len(path_line))
	{
		while (path_line[j + i] != ':')
			++i;
		path[k] = ft_strsub(path_line, j, i);
		j += i + 1;
		i = 0;
		++k;
	}
	path[k] = "\0";
	return (path);
}
