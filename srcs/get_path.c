/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:01:21 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/06 13:51:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

char	*find_cur_dir(t_env *lkd_env)
{
	if (ft_strcmp(lkd_env->env_line, "") == 0)
		return (ft_strdup("~#"));
	while (lkd_env)
	{
		if (ft_strncmp("PWD", lkd_env->env_line, 2) == 0)
			return (ft_strsub(lkd_env->env_line, 4, 400));
		lkd_env = lkd_env->next;
	}
	return (ft_strdup("~#"));
}

char	*find_name(char **env)
{
	int i;

	i = 0;
	if (env[0] == NULL)
		return (ft_strdup("John Doe"));
	while (ft_strncmp("USER", env[i], 3) != 0)
		++i;
	return (ft_strsub(env[i], 5, 50));
}

char	*find_path(t_env *lkd_env)
{
	while (lkd_env)
	{
		if (ft_strncmp("PATH", lkd_env->env_line, 3) == 0)
			return (lkd_env->env_line);
		lkd_env = lkd_env->next;
	}
	return (NULL);
}

char	**get_path(char *path_line)
{
	int		i;
	int		j;
	char	**path;
	int		k;
	char	*tmp;

	i = 0;
	j = 5;
	k = 0;
	if (!path_line
	|| !(path = (char **)malloc(sizeof(char *) * (ft_len(path_line) + 1))))
		return (NULL);
	while (k < ft_len(path_line))
	{
		while (path_line[i + j] && path_line[j + i] != ':')
			++i;
		tmp = ft_strsub(path_line, j, i);
		path[k] = ft_strjoin(tmp, "/");
		free(tmp);
		j += i + 1;
		i = 0;
		++k;
	}
	path[k] = NULL;
	return (path);
}
