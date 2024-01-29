/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:33:34 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/29 16:35:33 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
		printf("sa\n");
}

void	sb(t_node **stack_b, int print)
{
	ft_swap(stack_b);
	if (print)
		printf("sb\n");
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	printf("ss\n");
}

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

void 	pa(t_node **stack_b, t_node **stack_a)
{
	ft_push(stack_b, stack_a);
	printf("pa\n");
}

void 	pb(t_node **stack_a, t_node **stack_b)
{
	ft_push(stack_a, stack_b);
	printf("pb\n");
}

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
		printf("ra\n");
}

void	rb(t_node **stack_b, int print)
{
	ft_rotate(stack_b);
	if (print)
		printf("rb\n");
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	printf("rr\n");
}

void	rra(t_node **stack_a, int print)
{
	ft_rev_rotate(stack_a);
	if (print)
		printf("rra\n");
}

void	rrb(t_node **stack_b, int print)
{
	ft_rev_rotate(stack_b);
	if (print)
		printf("rrb\n");
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	printf("rrr\n");
}
