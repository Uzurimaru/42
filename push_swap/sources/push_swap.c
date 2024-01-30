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

// TODO modif libft makefile to add ft_fprintf
// TODO check why segfault when giving number > INT_MAX as argv

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
		// printf("sorting stacks...\n\n=============\n\n");
		if (ft_stack_len(stack_a) < 4)
			ft_easy_sort(&stack_a, ft_stack_len(stack_a));
		else
			ft_hard_sort(&stack_a, &stack_b);
	}
	// printf("\nfinal result:\n\n");
	// ft_print_stacks(stack_a, stack_b);
	// if (ft_stack_sorted(stack_a))
		// printf("stack is sorted.\n\n");
	// else
		// printf("stack could not be sorted. do better.\n\n");
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	return (0);
}
