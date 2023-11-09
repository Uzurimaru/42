/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:56:28 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/09 18:16:00 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_format(char c, va_list ap);
int	ft_printfchar(int c);
int	ft_printfpercent(int c);
int	ft_printfstr(char *str);
int	ft_printfnbr(int n, char *base);
int	ft_strlen(char *str);
int	ft_printfnbru(unsigned int n, char *base);
int	ft_printfnbrhex(unsigned int n, char *base);
int	ft_printfnbrptr(unsigned int n, char *base);

#endif
