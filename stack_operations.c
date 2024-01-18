#include "monty.h"

/**
 * add_node - Adds a new node at the beginning of a stack_t list
 * @stack: Pointer to the head of the stack_t list
 * @n: Value to be added to the new node
 *
 * Return: Address of the new element, or NULL if it failed
 */
stack_t *add_node(stack_t **stack, int n)
{
	stack_t *new_node;

	if (!stack)
		return (NULL);

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
		return (NULL);

	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
	return (new_node);
}
