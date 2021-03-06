/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:06:30 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 11:55:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_command_from_arg(char **argv, char **command)
{
	if (argv[1] == NULL)
		get_next_line(0, command);
	else
	{
		*command = ft_strdup(argv[1]);
		ft_putendl(argv[1]);
		return (1);
	}
	return (0);
}

void	free_multiple_command(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int		get_multiple_command(char *command, char **path, t_env *lkd_env)
{
	char	**tab;
	int		i;
	int		e;
	char	*str;

	i = 0;
	e = 0;
	tab = ft_strsplit(command, ';');
	while (tab[i])
	{
		str = ft_strtrim(tab[i]);
		get_command(str, path, lkd_env);
		if (find_exit(tab[i]))
		{
			e = 1;
			free(str);
			break ;
		}
		i++;
		free(str);
	}
	free_multiple_command(tab);
	if (e == 1)
		return (0);
	return (1);
}
