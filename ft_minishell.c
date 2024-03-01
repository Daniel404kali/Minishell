/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:22:49 by descamil          #+#    #+#             */
/*   Updated: 2024/03/01 15:33:17 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_mini(void)
{
	write (1, "\t                                                      \n", 57);
	write (1, "\t _  _   __   __ _   __   ____  _  _  ____  __    __   \n", 57);
	write (1, "\t( \\/ ) (  ) (  ( \\ (  ) / ___)/ )( \\(  __)(  )  (  )  \n", 57);
	write (1, "\t/ \\/ \\  )(  /    /  )(  \\___ \\) __ ( ) _) / (_/\\/ (_/\\\n", 57);
	write (1, "\t\\_)(_/ (__) \\_)__) (__) (____/\\_)(_/(____)\\____/\\____/\n", 57);
	write (1, "\t                                                      \n", 57);
	write (1, "\t                                                      \n", 57);
}

char	*ft_validate_comm_term(t_mini *mini, int i)
{
	if (access(*mini->split_line, X_OK) == 0
		&& ft_strrchr_bonus(*mini->split_line, '/'))
		return (*mini->split_line);
	if (access(*mini->split_line, X_OK) != 0
		&& ft_strrchr_bonus(*mini->split_line, '/'))
		write(1, "Command not found\n", 19);
	mini->names->command = ft_strjoin_bonus("/", mini->split_line[0]);
	while (mini->names->path[i] != NULL)
	{
		printf("COMMAND--> %s", mini->names->command);
		mini->names->path_comm = ft_strjoin_bonus(mini->names->path[i++], mini->names->command);
		printf("PATH = %s", mini->names->path_comm);
		if (access(mini->names->path_comm, X_OK) == 0)
			return (mini->names->path_comm);
	}
	write(1, "Command not found\n", 19);
	return (NULL);
}

char	*ft_pick_str(t_mini *mini)
{
	char	*tmp;
	int		size;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	size = ft_strlen(mini->split_line[0]);
	while (size-- > 0)
	{
		if (mini->split_line[0][i] != '\'' && mini->split_line[0][i] != '\"')
			j++;
		i++;
	}
	size = ft_strlen(mini->split_line[0]);
	tmp = malloc(j + 1);
	i = 0;
	j = 0;
	while (size-- > 0)
	{
		if (mini->split_line[0][i] != '\'' && mini->split_line[0][i] != '\"')
			tmp[j++] = mini->split_line[0][i];
		i++;
	}
	tmp[j + 1] = '\0';
	return (tmp);
}

void	ft_count_quote(t_mini *mini)
{
	int	size;
	int	i;

	i = 0;
	mini->quote->d_quote = 0;
	mini->quote->s_quote = 0;
	size = ft_strlen(mini->split_line[0]);
	while (size > 0)
	{
		if (mini->split_line[0][i] == '\"')
			mini->quote->d_quote++;
		else if (mini->split_line[0][i] == '\'')
			mini->quote->s_quote++;
		i++;
		size--;
	}
}

void	ft_execute_term(t_mini *mini, char *argv)
{
	int	fork_id;

	fork_id = fork();
	if (fork_id == -1)
		ft_error_bonus("Error fork()", 1);
	mini->split_line = ft_split_bonus(argv, ' ');
	if (mini->split_line == NULL)
		ft_error_bonus("Bad split", 1);
	ft_count_quote(mini);
	printf("SPLIT = %s\n", mini->split_line[0]);
	printf("D = %d\n", mini->quote->d_quote);
	printf("S = %d\n", mini->quote->s_quote);
	if ((mini->quote->d_quote % 2) == 1)
		write(1, "Repeat command with even \"\"\n", 33);
	else if ((mini->quote->s_quote % 2) == 1)
		write(1, "Repeat command with even \'\'\n", 33);
	else
	{	
		write(1, "COMMAND VALID\n", 15);
		mini->split_line[0] = ft_pick_str(mini);
		printf("Without \"\" --> %s\n", mini->split_line[0]);
	}
	mini->route = ft_validate_comm_term(mini, 1);
	execve(mini->route, mini->split_line, mini->names->envp);
}

// void	ft_only_one_comm(t_mini *mini)
// {
// 	if (pipe(mini->names->fd_pipe) == -1)
// 		ft_error_bonus("Pipe error", 1);
// 	mini->names->proc[mini->names->index] = fork();
// 	if (mini->names->proc[mini->names->index] == -1)
// 		ft_error_bonus("Filed in fork()", 1);
// 	if (mini->names->proc[mini->names->index] == 0)
// 	{
// 		close(mini->names->fd_pipe[0]);
// 		mini->names->fd_infile = open(mini->names->input, O_RDONLY);
// 		dup2(mini->names->fd_infile, STDIN_FILENO);
// 		dup2(mini->names->fd_pipe[1], STDOUT_FILENO);
// 		close(mini->names->fd_infile);
// 		close(mini->names->fd_pipe[1]);
// 		ft_execute_bonus(mini, mini->names->argv[2]);
// 	}
// 	mini->names->fd_tmp = mini->names->fd_pipe[0];
// 	mini->names->index++;
// 	close(mini->names->fd_pipe[1]);
// }

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*line;
	int		start;

	start = 1;
	ft_set_values(&mini, argv, envp, argc);
	while (1)
	{
		if (start == 1)
		{
			ft_print_mini();
			start = 0;
		}
		ft_find_pwd(&mini);
		if (mini.pwd == NULL)
			ft_error_bonus("Can't find pwd", 1);
		write(1, mini.pwd, ft_strlen(mini.pwd));
		line = get_next_line(0);
		if (line == NULL)
			break;
		line[ft_strlen(line) - 1 ] = '\0';
		mini.split_line = ft_split_bonus(line, ' ');
		// int i = 0;
		// while (mini.split_line[i])
		// 	printf("%s\n", mini.split_line[i++]);
		ft_execute_term(&mini, line);
		// if (ft_funcions(&mini) == 0)
		// 	write(1, "Command not found", 18);
	}
}