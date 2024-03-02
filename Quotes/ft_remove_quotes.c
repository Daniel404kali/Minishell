/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:47:41 by descamil          #+#    #+#             */
/*   Updated: 2024/03/02 11:03:08 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_count_letters(t_data *data)
{
	int 	letters;
	int		i;
	
	i = 0;
	letters = 0;
	while (data->str[i++] != '\0')
	{
		if (data->str[i] != 'd' || data->str[i] != 's')
			letters++;
	}
	return (letters);
}

int	ft_remove_quotes(t_data *data)
{
	char	*rm_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rm_str = malloc(ft_count_letters(data) + 1);
	if (rm_str == NULL)
		return (0);
	i = 0;
	while (data->str[i] != '\0')
	{
		if (data->str[i] != 'd' && data->str[i] != 's')
			rm_str[j++] = data->str[i];
		i++;
	}
	rm_str[j] = '\0';
	printf("rm_str =	%p\n", rm_str);
	data->rm_str = rm_str;
	free(rm_str);
	rm_str = NULL;
	printf("data->rm_str =	%p\n", data->rm_str);
	return (1);
}
