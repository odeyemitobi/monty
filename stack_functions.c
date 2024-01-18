#include "monty.h"

/**
 * free_stack - Frees all nodes in the stack.
 * @stack: Pointer to the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *current, *next;

	current = stack;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
