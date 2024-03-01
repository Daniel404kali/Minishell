/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:32:55 by descamil          #+#    #+#             */
/*   Updated: 2024/03/01 17:28:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_count_quotes(t_data *data)
{
	int	size;
	int	i = 0;
	
	size = strlen(data->str);
	while (size-- > 0)
	{
		if (data->str[i] == 'd')
			data->d_quote++;
		else if (data->str[i] == 's')
			data->s_quote++;
		i++;
	}
	if (data->d_quote % 2 != 0 || data->s_quote % 2 != 0)
		return (0);
	return (1);
}

int	ft_single_quotes(t_data *data, int i)
{
	while (data->str[i] != 's')
		i++;
	if (data->str[i] == 's' && data->str[i + 1] == 's')
	{
		printf("Aqui hay ss\n");
		i += 2;
		data->s_quote -= 2;
		printf("%d\n", i);
		return (i);
	}
	else if (data->str[i] == 's' && data->str[i + 1] != 's' && data->str[i + 2] == 's')
	{
		if (data->str[i + 1] == 'd')
			return (-1);
		printf("Aqui hay sxs\n");
		i += 3;
		data->s_quote -= 2;
		printf("%d\n", i);
		return (i);
	}
	else if (data->d_quote == 0)
	{
		data->s_quote--;
		i++;
		printf("\nEmpieza Comm\n");
		printf("%d\n", i);
		while (data->str[i] != 's')
		{
			if (data->str[i] == 'd')
				return (-1);
			i++;
		}
		printf("%d\n", i);
		printf("Acaba Coom, o parte\n\n");
		data->s_quote--;
		return (i);
	}
	return (-1);
}

int	ft_take_valid_comm(t_data *data)
{
	int i = 0;
	
	if (ft_count_quotes(data) == 0)
		return (-1);
	printf("%d\n", data->s_quote);
	while (data->s_quote > 0)
	{
		i = ft_single_quotes(data, i);
		if (i == -1)
			return (-1);
	}
	// while (data->d_quote)
	return (0);
}

void	ft_values(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->d_quote = 0;
	data->s_quote = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		r;

	ft_values(&data);
	
	data.str = argv[1];
	r = ft_take_valid_comm(&data);
	printf(YELLOW"	[%s]\n"RESET, data.str);
	if (r == -1)
		printf(RED"	[ERROR]\n"RESET);
	else
		printf(GREEN"	[VALID]\n"RESET);

	return (0);
}