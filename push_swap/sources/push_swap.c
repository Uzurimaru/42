/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:20 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/11 22:18:00 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

#include <stdio.h>

// TODO modif libft makefile to add ft_printf

////////// CMDS //////////

////////// SWAP

void	ft_swap(t_node **top)
{
	t_node	*sec;
	t_node	*thr;

	if (!(*top) || !((*top)->next))
		return ;
	(*top)->prev = sec;
	(*top)->next = thr;
	sec->prev = NULL;
	sec->next = *top;
	if (thr)
		thr->prev = *top;
	*top = sec;
}

void	sa(t_node **stack_a)
{
	ft_swap(stack_a);
}

void	sb(t_node **stack_b)
{
	ft_swap(stack_b);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	ft_swap(stack_a);
	ft_swap(stack_b);
}

////////// PUSH

void	ft_push(t_node **src, t_node **dst)
{
	t_node	*src_sec;

	if (!(*src))
		return ;
	src_sec = (*src)->next;
	if (src_sec)
		src_sec->prev = NULL;
	(*src)->next = *dst;
	(*dst)->prev = *src;
	*dst = *src;
	*src = src_sec;
}

////////// UTIL //////////

t_node	*ft_get_max(t_node *stack)
{
	int		max;
	t_node	*max_node;

	max = INT_MIN;
	max_node = NULL;
	while (stack)
	{
		if (stack->nb > max)
		{
			max = stack->nb;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

t_node	*ft_get_min(t_node *stack)
{
	int 	min;
	t_node	*min_node;

	min = INT_MAX;
	min_node = NULL;
	while (stack)
	{
		if (stack->nb > min)
		{
			min = stack->nb;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

int	ft_stack_len(t_node *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

t_node	*ft_get_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

int	ft_is_stack_sorted(t_node *stack)
{
	while (stack->next)
	{
		if (stack->nb >= stack->next->nb)
			return (1);
		stack = stack->next;
	}
	return (0);
}

////////// ERRS //////////

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

////////// INIT //////////

void	ft_lst_append(t_node **stack, int nb)
{
	t_node	*last_node;
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->nb = nb;
	if (!(*stack))
	{
		new_node->prev = NULL;
		*stack = new_node;
	}
	else
	{
		last_node = ft_get_last_node(*stack);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	printf("%d\n", new_node->nb);
}

void	ft_init_stack_a(t_node **stack_a, char **argv)
{
	long	nb;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_err_syntax(argv[i]))
			ft_err_free(2, stack_a);
		nb = ft_atol(argv[i]);
		if (nb < INT_MIN || nb > INT_MAX)
			ft_err_free(3, stack_a);
		if (ft_err_dup(*stack_a, nb))
			ft_err_free(4, stack_a);
		ft_lst_append(stack_a, nb);
		i++;
	}
}

////////// ALGO //////////

void	ft_easy_sort(t_node **stack_a, int stack_len)
{
	t_node	*big;

	big = NULL;
	if (stack_len == 2)
		sa(stack_a);
	else
	{
		big = ft_get_max(*stack_a);
		if (big == *(stack_a))
			ra(stack_a);
		else if (big == *(stack_a)->next)
			rra(stack_a);
		if (*(stack_a)->nb > *(stack_a)->next->nb)
			sa(stack_a);
	}
}

////////// MAIN //////////

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	// t_node	*stack_b;

	stack_a = NULL;
	// stack_b = NULL;

	if (argc == 1 || (argc == 2 && !argv[1][0]))
		ft_err_free(1, &stack_a);
	else if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		ft_init_stack_a(&stack_a, argv);
	}
	else
		ft_init_stack_a(&stack_a, argv + 1);

	if (!ft_stack_sorted(a))
	{
		if (ft_stack_len(stack_a) < 4)
			ft_easy_sort(stack_a, ft_stack_len(stack_a));
		else
			ft_hard_sort(stack_a, stack_b);
	}
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	return (0);
}