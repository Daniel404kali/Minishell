/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:29:19 by descamil          #+#    #+#             */
/*   Updated: 2024/03/03 16:21:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_single_quotes(t_data *data, int i, int q, int valid)
{
	if ((valid % 2) == 5 && data->str[i] == q && data->str[i + 1] == q)
		return (i + 2);
	else
	{
		i++;
		while (data->str[i++] != q)
			data->command_len++;
		return (i);
	}
	return (-1);
}

int	ft_valid_quotes(t_data *data, int i)
{
	int	valid;

	valid = 0;
	printf(PURPLE"LEN = 	%d\n"RESET, data->command_len);
	printf(PURPLE"Nº --> %d = %c\n"RESET, i, data->str[i]);
	if (data->str[i] == '\'')
	{
		valid += 1;
		printf(RED"V --> %d\n"RESET, valid);
		printf(RED"%c --> Nº = %d\n"RESET, data->str[i], i);
		i = ft_single_quotes(data, i, '\'', valid);
		printf(RED"%c --> Nº = %d\n"RESET, data->str[i], i);
		if (i == -1)
			return (-1);
	}
	else if (data->str[i] == '\"')
	{
		valid += 1;
		printf(GREEN"V --> %d\n"RESET, valid);
		printf(GREEN"%c --> Nº = %d\n"RESET, data->str[i], i);
		i = ft_double_quotes(data, i, '\"', valid);
		printf(GREEN"%c --> Nº = %d\n"RESET, data->str[i], i);
		if (i == -1)
			return (-1);
	}
	else if (data->str[i] == '$')
	{
		data->command_len = ft_translate(data, i);
		i += data->len_var - 1;
	}	
	else
	{
		data->command_len++;
		i++;
	}
	return (i);
}
