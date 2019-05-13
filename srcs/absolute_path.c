/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:23:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/13 18:31:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_absolute_path2(char *command, char *str, char *str2)
{
	int length;

	length = ft_strlen(command);
	while (command[length] != '/')
		length--;
	free(str);
	free(str2);
	return (ft_strndup(command, length + 1));
}

char	*search_absolute_path(char *command)
{
	char	*str;
	char	*str2;
	char	buff[6000];

	str2 = ft_strjoin(getcwd(buff, 6000), "/");
	str = ft_strjoin(str2, command);
	if (command[0] != '/' && ft_strncmp(command, "..", 2)
	&& command[0] && !access(str, F_OK))
	{
		free(str);
		if (ft_strchr(command, '/'))
			return (str2);
		free(str2);
		return (NULL);
	}
	else if (access(command, F_OK) != -1)
		return (search_absolute_path2(command, str, str2));
	free(str);
	free(str2);
	return (NULL);
}

void	free_prompt(char *username, char *curr_dir, char **path)
{
	int		i;

	i = 0;
	free(username);
	free(curr_dir);
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}
