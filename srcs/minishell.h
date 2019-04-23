/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 21:21:04 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/23 19:25:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <sys/wait.h>

#include <stdio.h>

typedef struct		s_env
{
	char			env_line[2056];
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

void				get_command(char *command, char **path, t_env *lkd_env);
char				**get_path(char *path_line);
char				*external_command(char **path, char *first_command);
int					execute_command(char *get_right_path, char *command, char **argv, char **env);
t_env				*get_env(char **env);
t_env				*new_maillon(void);
char				*extract_params(char *command);
char				*extract_command(char *command);
char				*find_path(char **env);
char				*find_name(char **env);
char				*find_cur_dir(t_env *lkd_env);
char				**compact_env(t_env *lkd_env);
char				*extract_first_env(char *command, int mode);
void				write_prompt(char *cur_name, char *cur_dir);
/*
** Builtins
*/
void				echo(char *command);
void				print_env(t_env *lkd_env);
void				set_env(t_env *lkd_env, char *command);
void				unset_env(t_env *lkd_env, char *command);
void				cd(t_env *lkd_env, char *command);

#endif
