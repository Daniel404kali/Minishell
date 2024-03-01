/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:32:55 by descamil          #+#    #+#             */
/*   Updated: 2024/03/01 19:16:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	if (*s == (char)c)
		return (1);
	return (0);
}

int	ft_count_quotes(t_data *data)
{
	int	size;
	int	i = 0;
	
	size = ft_strlen(data->str);
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
	if ((data->s_quote + data->d_quote) == ft_strlen(data->str))
		return (0);
	if (data->d_quote == 0)
		data->d_quote = -1;
	if (data->s_quote == 0)
		data->s_quote = -1;
	return (1);
}

int	ft_single_quotes(t_data *data, int i, int q, int o)
{
	while (data->str[i] != q)
		i++;
	if (data->str[i] == q && data->str[i + 1] != q && data->str[i + 2] == q)
	{
		if (data->str[i + 1] == o)
			return (-1);
		i += 3;
		return (i);
	}
	else if (data->str[i] == q && data->str[i + 1] == q)
	{
		i += 2;
		return (i);
	}
	else 
	{
		i++;
		while (data->str[i] != q)
		{
			if (data->str[i++] == o)
				return (-1);
		}
		return (i);
	}
	return (0);
}

int	ft_double_quotes(t_data *data, int i, int q, int o)
{
	while (data->str[i] != q)
		i++;
	if (data->str[i] == q && data->str[i + 1] != q && data->str[i + 2] == q)
	{
		if (data->str[i + 1] == o)
			return (-1);
		i += 3;
		return (i);
	}
	else if (data->str[i] == q && data->str[i + 1] == q)
	{
		i += 2;
		return (i);
	}
	else if (data->s_quote == -1)
	{
		i++;
		while (data->str[i] != q)
		{
			if (data->str[i++] == o)
				return (-1);
		}
		return (i);
	}
	return (0);
}

// {
// 	printf("Aquí\n");
// 	return (-1);
// }

int	ft_take_valid_comm(t_data *data)
{
	int i;
	
	i = 0;
	if (ft_count_quotes(data) == 0)
		return (-1);
	if (ft_strchr(data->str, ' ') == 1)
		return (-1);
	while (data->s_quote > 0)
	{
		i = ft_single_quotes(data, i, 's', 'd');
		data->s_quote -= 2;
		if (i == -1)
			return (-1);
	}
	i = 0;
	while (data->d_quote > 0)
	{
		i = ft_double_quotes(data, i, 'd', 's');
		data->d_quote -= 2;
		if (i == -1)
			return (-1);
	}
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
		printf(RED"		[ERROR]\n"RESET);
	else
		printf(GREEN"		[VALID]\n"RESET);

	return (0);
}