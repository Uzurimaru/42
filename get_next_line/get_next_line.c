/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:29:44 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/15 17:54:40 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_buftostr(char *buf, char *str, int fd)
{
	int	chrd;

	chrd = 1;
	while (chrd != 0 && !ft_findnewline(buf))
	{
		chrd = read(fd, buf, BUFFER_SIZE);
		if (chrd == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[chrd] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);

	str = ft_buftostr(buf, str, fd);
	if (!str)
		return (NULL);

	line = ft_getline(str);
	
	str = ft_clear(str);
	
	return (line);
}

//	Methode GNL
//
//	Transferer le contenu du buffer "buf" dans une autre string "str" statique (!!!) pour qu'il ne soit pas ecrase
//
//	Checker si on a un \n dans notre str ou EOF
//
//		Si non :
//			On recommence
//
//		Si oui : 
//			Extraire le contenu de str jusqu'au \n inclus
//			Le mettre dans une string "line"
//			Clear le contenu de str jusqu'au \n inclus
//			Return line


