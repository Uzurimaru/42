/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:26:13 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/15 15:10:42 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_node
{
	int				nb;
	int				index;

	int				ismax;
	int				ismin;

	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

void	ft_error(int err_id);

#endif