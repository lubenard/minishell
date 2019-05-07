/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/07 14:48:36 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *command)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(" : command not found ¯\\_(ツ)_/¯\n", 2);
}

void	get_error_exec(char path[6000])
{
	struct stat filestat;

	if (stat(path, &filestat) < 0)
		return ;
	if (!(filestat.st_mode & S_IXUSR))
		ft_putstr_fd("You do not have execution rights (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
	else if (!S_ISDIR(filestat.st_mode))
		ft_putstr_fd("Hum, apparently it's a folder (●__●)\n", 2);
}

int		free_after_exec(char **argv, char *get_right_path,
	char *command, char **env)
{
	int i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(get_right_path);
	free(argv);
	free(env);
	free(command);
	return (0);
}

char	*extract_command(char *command)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (command[e] == ' ' || command[e] == '\t')
		e++;
	while (command[e + i] != ' ' && command[e + i])
		++i;
	return (ft_strlower(ft_strsub(command, e, i)));
}
