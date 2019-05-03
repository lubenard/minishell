/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:44:57 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/03 17:00:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_from_arg(char **argv, char *command)
{
	if (argv[1] == NULL)
		get_next_line(0, &command);
	else
	{
		command = ft_strdup(argv[1]);
		ft_putendl(argv[1]);
	}
	return (command);
}

int		get_multiple_command(char *command, char **path, t_env *lkd_env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(command, ';');
	while (tab[i])
	{
		get_command(tab[i], path, lkd_env);
		i++;
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	if (ft_strstr(command, "exit"))
		return (0);
	return (1);
}
