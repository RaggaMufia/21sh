/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:09:22 by julekgwa          #+#    #+#             */
/*   Updated: 2017/01/02 14:22:34 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_uneven(char *str)
{
	int	countsingle;
	int	countdouble;

	countsingle = 0;
	countdouble = 0;
	while (*str)
	{
		if (*str == '\"')
			countdouble++;
		if (*str == '\'')
			countsingle++;
		str++;
	}
	if ((countdouble % 2 == 0) && (countsingle % 2 == 0))
		return (0);
	else
		return (1);
}

int		ft_is_slash_inhibitor(char *str)
{
	char	**split;

	split = SPLIT(str, ' ');
	if (ft_array_len(split) <= 1)
		return (0);
	if (EQUAL(split[1], "\\"))
		return (1);
	else
		return (0);
}

void	ft_rm_newline(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\n')
			j++;
		cmd[i] = cmd[j];
		i++;
		j++;
	}
	cmd[j] = 0;
}
