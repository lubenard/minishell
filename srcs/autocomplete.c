/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:52:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/02 17:27:36 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*external_autoco_command(char *command)
{
	int i;
	int e;

	i = ft_strlen(command);
	while (!ft_isalpha(command[i]))
		i--;
	e = i;
	while (ft_isalpha(command[i]) && i >= 0)
	{
		i--;
		e++;
	}
	//return (ft_strsub(command, i, e));
	return ("c");
}

void	autocomplete(char **path, char *command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*first_command;
	int				tmp;
	char			*tmp_command;
	int				e;

	i = 0;
	e = 300;
	if (path == NULL || command == NULL)
		return ;
	first_command = external_autoco_command(command);
	while (path[i + 1])
	{
		p_dir = opendir(path[i]);
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			tmp = ft_strcmp(p_dirent->d_name, first_command);
			if (tmp < e)
			{
				printf("e valait %d\n", e);
				e = tmp;
				printf("e vaut %d\n", e);
				tmp_command = p_dirent->d_name;
				printf("tmp_command vaut mtn %s\n", tmp_command);
			}
		}
		closedir(p_dir);
		i++;
	}
	ft_putstr_fd(tmp_command, 1);
	//free(first_command);
}
