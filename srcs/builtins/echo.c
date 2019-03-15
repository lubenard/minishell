/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/15 17:05:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_usage(void)
{
	ft_putstr("Please learn how to use echo\n");
}

int		echo(char *command)
{
	int i;

	i = 5;
	while (command[i])
		ft_putchar(command[i++]);
	ft_putchar('\n');
	return (0);
}
