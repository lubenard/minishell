/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/16 00:00:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*external_command(char **path, char *first_command)
{
	int				i;
	struct dirent	*pDirent;
	DIR				*pDir;

	i = 0;
	while (path[i+1])
	{
		pDir = opendir(path[i]);
		printf("J'explore %s\n", path[i]);
		while ((pDirent = readdir(pDir)) != NULL)
		{
			printf("Je regarde ce fichier: %s\n", pDirent->d_name);
			if (ft_strcmp(pDirent->d_name, first_command) == 0)
			{
				printf(">>>>>>>>>>>>>>>>>>>>>>>>>>Found it\n");
				return (path[i]);
			}
		}
		i++;
	}
	return (NULL);
}


void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, proc_signal_handler);
	}
}

int		execute_command(char *get_right_path, char *command,char **argv,char **env)
{
	pid_t	pid;

	(void)argv;
	char *argv2[1] = {"-lha"};
	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(ft_strjoin(get_right_path,command), argv2, env);
	else if (pid < 0)
	{
		ft_putendl("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	return (1);
}
