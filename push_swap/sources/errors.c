/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:41:43 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/27 15:43:50 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_free_stack(t_node **stack)
{
	t_node	*curr;
	t_node	*tmp;

	curr = *stack;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*stack = NULL;
}

void	ft_err_free(int err_id, t_node **stack)
{
	if (err_id == 1)
		write(2, "Error: not enough arguments\n", 28);
	if (err_id == 2)
	{
		write(2, "Error: invalid syntax\n", 22);
		ft_free_stack(stack);
	}
	if (err_id == 3)
	{
		write(2, "Error: number too large\n", 24);
		ft_free_stack(stack);
	}
	if (err_id == 4)
	{
		write(2, "Error: duplicate number\n", 24);
		ft_free_stack(stack);
	}
	exit (err_id);
}

int	ft_err_dup(t_node *stack, int nb)
{
	while (stack)
	{
		if (stack->nb == nb)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int	ft_err_syntax(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] != '-' && nb[i] != '+' && !ft_isdigit(nb[i]))
		return (1);
	else if ((nb[i] == '-' || nb[i] == '+') && !ft_isdigit(nb[i + 1]))
		return (1);
	i++;
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
			return (1);
		i++;
	}
	return (0);
}
