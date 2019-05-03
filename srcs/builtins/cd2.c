/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:13:49 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/03 15:24:52 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_path(char *command)
{
	int i;
	int e;

	if (!ft_strcmp(command, ".."))
		return (ft_strdup(".."));
	i = 0;
	e = 0;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i] && command[i] != ' ')
		i++;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i + e])
		e++;
	return (ft_strsub(command, i, e));
}
