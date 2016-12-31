/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 03:54:29 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/31 00:23:32 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_needle(char **str)
{
    char    *needle;

    needle = "";
    while (*str)
    {
        if (*(*str) == '$' || *(*str) =='~')
        {
            needle = *str;
            break ;
        }
        str++;
    }
    return (needle);
}

void    ft_str_substitution(char **str, char **envp)
{
    t_search_hist   replace;
    char            *with;
    char            *result;
    char            *needle;
    char            **split;

    if (!ft_contains(*str, '$') && !ft_contains(*str, '~'))
        return ;
    split = ft_strsplit(*str, ' ');
    needle = get_needle(split);
    with = ft_get_env(needle, envp) ? ft_get_env(needle, envp) : "";
    if (*needle == '~')
    {
        needle = "~";
        with = ft_get_env("$HOME", envp);
    }
    replace.needle = needle;
    replace.with = with;
    replace.haystack = *str;
    result = ft_search_replace(replace, 0, 0, 0);
    ft_memset(*str, 0, BUFF_SIZE);
    ft_strcpy(*str, result);
    freecopy(split);
    free(result);
    if (ft_contains(*str, '$') || ft_contains(*str, '~'))
        ft_str_substitution(str, envp);
}