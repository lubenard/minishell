/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:52:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/03 11:47:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*external_autoco_command(char *command)
{
	int i;
	int e;

	i = ft_strlen(command);
	e = 0;
	while (!ft_isalpha(command[i]) && i >= 0)
		i--;
	while (ft_isalpha(command[i]) && i >= 0)
	{
		i--;
		e++;
	}
	return (ft_strsub(command, i + 1, e));
}

int		autocomp_builtins(char *command)
{
	int len;

	len = ft_strlen(command);
	if (ft_strncmp(command, "setenv", len) == 0)
	{
		ft_putstr("setenv\n");
		free(command);
		return (1);
	}
	else if (ft_strncmp(command, "unsetenv", len) == 0)
	{
		ft_putstr("unsetenv\n");
		free(command);
		return (1);
	}
	return (0);
}

void	autocomplete(char **path, char *command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*first_command;

	i = 0;
	if (path == NULL || command == NULL)
		return ;
	first_command = external_autoco_command(command);
	if (autocomp_builtins(first_command) == 1)
		return ;
	while (path[i + 1])
	{
		p_dir = opendir(path[i]);
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			if (ft_strncmp(p_dirent->d_name, first_command,
			ft_strlen(first_command)) == 0)
				ft_putendl(p_dirent->d_name);
		}
		closedir(p_dir);
		i++;
	}
	free(first_command);
}
