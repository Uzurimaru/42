/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:20 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/25 13:54:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

#include <stdio.h>

// TODO modif libft makefile to add ft_fprintf
// TODO check why segfault when giving number > INT_MAX as argv

////////// UTIL //////////

t_node	*ft_get_max_node(t_node *stack)
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

t_node	*ft_get_min_node(t_node *stack)
{
	int		min;
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

int	ft_stack_sorted(t_node *stack)
{
	while (stack->next)
	{
		if (stack->nb >= stack->next->nb)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	ft_tokenize(t_node *stack)
{
	int	index;
	int	median;

	if (!stack)
		return ;
	index = 0;
	median = ft_stack_len(stack) / 2;
	while (stack)
	{
		stack->pos = index;
		if (index < median)
			stack->top_half = 1;
		else
			stack->top_half = 0;
		index++;
		stack = stack->next;
	}
}

void	ft_targetize(t_node *stack_a, t_node *stack_b)
{
	t_node	*cursor_b;
	t_node	*target_node;
	long	closest_sm;

	cursor_b = NULL;
	target_node = NULL;
	closest_sm = LONG_MIN;
	while (stack_a)
	{
		cursor_b = stack_b;
		while (cursor_b)
		{
			if (cursor_b->nb < stack_a->nb && cursor_b->nb > closest_sm)
			{
				target_node = cursor_b;
				closest_sm = cursor_b->nb;
			}
			cursor_b = cursor_b->next;
		}
		if (closest_sm == LONG_MIN)
			target_node = ft_get_max_node(stack_b);
		stack_a->target = target_node;
		stack_a = stack_a->next;
	}
}

void	ft_cost_analyze(t_node *stack_a, t_node *stack_b)
{
	while (stack_a)
	{
		if (stack_a->top_half)
			stack_a->cost = stack_a->pos;
		else
			stack_a->cost = ft_stack_len(stack_a) - stack_a->pos;
		if (stack_a->target->top_half)
			stack_a->cost += stack_a->target->pos;
		else
			stack_a->cost += ft_stack_len(stack_b) - stack_a->target->pos;
		stack_a = stack_a->next;
	}
}

void	ft_find_cheapest(t_node *stack)
{
	long	cheapest_v;
	t_node	*cheapest_n;

	cheapest_n = NULL;
	cheapest_v = LONG_MAX;
	if (!stack)
		return ;
	while (stack)
	{
		if (stack->cost < cheapest_v)
		{
			cheapest_v = stack->cost;
			cheapest_n = stack;
		}
		stack->cheapest = 0;
		stack = stack->next;
	}
	cheapest_n->cheapest = 1;
}

t_node	*ft_get_cheapest(t_node *stack)
{
	while (stack && !(stack->cheapest))
		stack = stack->next;
	return (stack);
}

void	ft_print_stacks(t_node *stack_a, t_node *stack_b)
{
	int	index;
	int	max;
	int	len_a;
	int	len_b;

	len_a = ft_stack_len(stack_a);
	len_b = ft_stack_len(stack_b);
	max = len_a;
	if (len_a < len_b)
		max = len_b;
	index = 0;
	while (index < max)
	{
		if (stack_a)
		{
			printf("%d", stack_a->nb);
			stack_a = stack_a->next;
		}
		else
			printf("_");
		printf("\t");
		if (stack_b)
		{
			printf("%d", stack_b->nb);
			stack_b = stack_b->next;
		}
		else
			printf("_");
		printf("\n");
		index++;
	}
	printf("_\t_\na\tb\n\n");
}

////////// CMDS //////////

////////// SWAP

void	ft_swap(t_node **top)
{
	t_node	*sec;
	t_node	*thr;

	if (!(*top) || !((*top)->next))
		return ;
	sec = (*top)->next;
	thr = sec->next;
	(*top)->prev = sec;
	(*top)->next = thr;
	sec->prev = NULL;
	sec->next = *top;
	if (thr)
		thr->prev = *top;
	*top = sec;
}

void	sa(t_node **stack_a, int print)
{
	ft_swap(stack_a);
	if (print)
		printf("\tsa\n");
}

void	sb(t_node **stack_b, int print)
{
	ft_swap(stack_b);
	if (print)
		printf("\tsb\n");
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	printf("\tss\n");
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
	if (*dst)
		(*dst)->prev = *src;
	*dst = *src;
	*src = src_sec;
}

void 	pa(t_node **stack_a, t_node **stack_b)
{
	ft_push(stack_a, stack_b);
	printf("\tpa\n");
}

void 	pb(t_node **stack_b, t_node **stack_a)
{
	ft_push(stack_b, stack_a);
	printf("\tpb\n");
}

////////// ROTATE

void	ft_rotate(t_node **top)
{
	t_node	*sec;
	t_node	*last;

	if (!(*top) || !(*top)->next)
		return ;
	sec = (*top)->next;
	last = ft_get_last_node(*top);
	(*top)->next = NULL;
	(*top)->prev = last;
	last->next = *top;
	sec->prev = NULL;
	*top = sec;
}

void	ft_rev_rotate(t_node **top)
{
	t_node	*last;
	t_node	*b_last;

	if (!(*top) || !(*top)->next)
		return ;
	last = ft_get_last_node(*top);
	b_last = last->prev;
	(*top)->prev = last;
	last->prev = NULL;
	last->next = *top;
	b_last->next = NULL;
	*top = last;
}

void	ra(t_node **stack_a, int print)
{
	ft_rotate(stack_a);
	if (print)
		printf("\tra\n");
}

void	rb(t_node **stack_b, int print)
{
	ft_rotate(stack_b);
	if (print)
		printf("\trb\n");
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	printf("\trr\n");
}

void	rra(t_node **stack_a, int print)
{
	ft_rev_rotate(stack_a);
	if (print)
		printf("\trra\n");
}

void	rrb(t_node **stack_b, int print)
{
	ft_rev_rotate(stack_b);
	if (print)
		printf("\trrb\n");
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	printf("\trrr\n");
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
	printf("\n===============\n\nstack init:\n\n");
	ft_print_stacks(*stack_a, NULL);
}

////////// ALGO //////////

void	ft_easy_sort(t_node **stack_a, int stack_len)
{
	t_node	*big;

	big = NULL;
	if (stack_len == 2)
		sa(stack_a, 1);
	else
	{
		big = ft_get_max_node(*stack_a);
		if (big == *(stack_a))
			ra(stack_a, 1);
		else if (big == (*stack_a)->next)
			rra(stack_a, 1);
		if ((*stack_a)->nb > (*stack_a)->next->nb)
			sa(stack_a, 1);
	}
}

void	ft_init_data(t_node *stack_a, t_node *stack_b)
{
	ft_tokenize(stack_a);
	ft_tokenize(stack_b);
	ft_targetize(stack_a, stack_b);
	ft_cost_analyze(stack_a, stack_b);
	ft_find_cheapest(stack_a);
}
void	ft_bring_to_top(t_node **a, t_node **b, t_node *top_a, t_node *top_b)
{
	while (*a != top_a)
	{
		if (top_a->top_half)
			ra(a, 1);
		else
			rra(a, 1);
	}
	while (*b != top_b)
	{
		if (top_b->top_half)
			rb(b, 1);
		else
			rrb(b, 1);
	}
}

void	ft_transfer_to_b(t_node **stack_a, t_node **stack_b)
{
	t_node	*cheapest;

	cheapest = ft_get_cheapest(*stack_a);
	if (cheapest->top_half && cheapest->target->top_half)
	{
		while (*stack_a != cheapest && *stack_b != cheapest->target) 
			rr(stack_a, stack_b);
		ft_tokenize(*stack_a);
		ft_tokenize(*stack_b);
	}
	else if (!(cheapest->top_half) && !(cheapest->target->top_half))
	{
		while (*stack_a != cheapest && *stack_b != cheapest->target) 
			rrr(stack_a, stack_b);
		ft_tokenize(*stack_a);
		ft_tokenize(*stack_b);
	}
	ft_bring_to_top(stack_a, stack_b, cheapest, cheapest->target);
	pb(stack_a, stack_b);
}

void	ft_hard_sort(t_node **stack_a, t_node **stack_b)
{
	unsigned int	len_a;
	unsigned int	len_b;

	len_a = ft_stack_len(*stack_a);
	len_b = ft_stack_len(*stack_b);
	while (len_a > 3 && len_b < 2 && !ft_stack_sorted(*stack_a)) // push to b untill 3 items remaining in a or 2 items in b
	{
		pb(stack_a, stack_b);
		len_a--;
		len_b++;
	}
	while (len_a > 3 && !ft_stack_sorted(*stack_a))
	{
		ft_init_data(*stack_a, *stack_b);
		// if ((*stack_a)->cheapest)
		// 	printf("chibre");
		ft_transfer_to_b(stack_a, stack_b);
		len_a--;
	}
	ft_easy_sort(stack_a, ft_stack_len(*stack_a));
	//TODO init nodes from b stack and move them back to a. 42:37
}

////////// MAIN //////////

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;

	if (argc == 1 || (argc == 2 && !argv[1][0]))
		ft_err_free(1, &stack_a);
	else if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		ft_init_stack_a(&stack_a, argv);
	}
	else
		ft_init_stack_a(&stack_a, argv + 1);

	if (!ft_stack_sorted(stack_a))
	{
		printf("sorting stacks...\n\n");
		if (ft_stack_len(stack_a) < 4)
			ft_easy_sort(&stack_a, ft_stack_len(stack_a));
		else
			ft_hard_sort(&stack_a, &stack_b);
	}
	printf("\nfinal result:\n\n");
	ft_print_stacks(stack_a, stack_b);
	if (ft_stack_sorted(stack_a))
		printf("stack is sorted.\n\n");
	else
		printf("stack could not be sorted. do better.\n\n");
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	return (0);
}
