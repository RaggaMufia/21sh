/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:07:17 by julekgwa          #+#    #+#             */
/*   Updated: 2016/12/15 14:12:44 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_line(int fd, char *s)
{
	char	line[SIZE];
	char	*list[SIZE];
	int		i;
	ssize_t	retval;

	ft_memset(line, 0, SIZE);
	ft_memset(list, 0, SIZE * sizeof(*list));
	i = 0;
	ft_putstr("> ");
	while ((retval = read(1, line, SIZE)) > 0)
	{
		ft_putstr("> ");
		if (!strncmp(line, s, strlen(line) - 1))
			break ;
		else
			list[i++] = strdup(line);
		ft_memset(line, 0, SIZE);
	}
	if (retval == 0)
		ft_putendl("21sh: warning: here-document delimited by end-of-file");
	i = -1;
	while (list[++i])
		write(fd, list[i], strlen(list[i]));
}

int		ft_get_here_doc_pos(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strequ(cmd[i], "<<"))
			return (i);
		i++;
	}
	return (0);
}

void	ft_open_file_fd(int pos, char **cmd)
{
	char	*file_name;
	int		fd;

	if (ft_strequ(cmd[pos + 2], ">"))
	{
		if (cmd[pos + 3] != NULL)
		{
			file_name = cmd[pos + 3];
			fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			dup2(fd, 1);
		}
	}
	else if (ft_strequ(cmd[pos + 2], ">>"))
	{
		if (cmd[pos + 3] != NULL)
		{
			file_name = cmd[pos + 3];
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			dup2(fd, 1);
		}
	}
}

int     ft_process_here_doc(char **cmd)
{
    char    *delimiter;
    int     heredoc_pos;
    int     fd[2];
    pid_t   pid;
    int     status;

    heredoc_pos = ft_get_here_doc_pos(cmd);
    delimiter = cmd[heredoc_pos + 1];
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDIN_FILENO);
        ft_read_line(fd[1], delimiter);
        exit(0);
    }
    else
    {
        close(fd[1]);
        wait(&status);
    }
    if (cmd[heredoc_pos + 2] != NULL && cmd[heredoc_pos + 3] != NULL)
        ft_open_file_fd(heredoc_pos, cmd);
    return (heredoc_pos);
}