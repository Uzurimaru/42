/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:30:07 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/15 17:48:14 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		combsize;
	char	*combstr;

	if (!s1)
		return (NULL);
	combsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	combstr = malloc(sizeof(char) * combsize);
	if (!combstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		combstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		combstr[i + j] = s2[j];
		j++;
	}
	combstr[i + j] = '\0';
	return (combstr);
}

int	ft_findnewline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		line[i] = str[i++];
	if (str[i] == '\n')
		line[i] = str[i++];
	line[i] = '\0';
	return (line);
}

char	*ft_clear(char *str)
{

}
