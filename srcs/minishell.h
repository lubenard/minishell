/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 21:21:04 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/15 16:58:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"

void	get_command(char *command, char **path, char **env);
char	**get_path(char *path_line);
char	*external_command(char **path, char *first_command);
int		execute_command(char *get_right_path, char *command);
/*
** Builtins
*/
int		echo(char *command);
void	print_env(char **env);

#endif
