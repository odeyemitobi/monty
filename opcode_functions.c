#include "monty.h"

/**
 * op_push - Pushes an element to the stack
 * @stack: Pointer to the stack
 */
void op_push(stack_t **stack)
{
	int value;

	if (!stack)
	{
		fprintf(stderr, "Error: Stack not found\n");
		exit(EXIT_FAILURE);
	}

	value = 10;

	if (add_node(stack, value) == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * op_pall - Prints all elements in the stack
 * @stack: Pointer to the stack
 */
void op_pall(stack_t **stack)
{
	stack_t *current = *stack;

	if (!stack)
	{
		fprintf(stderr, "Error: Stack not found\n");
		exit(EXIT_FAILURE);
	}

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
