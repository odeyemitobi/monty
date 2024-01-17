#include "monty.h"

/**
 * op_push - Opcode function to push an element onto the stack
 * @stack: Pointer to the stack
 * @line_number: Current line number in the Monty ByteCode file
 * @arg: Argument for the push operation
 *
 * Description: Pushes an element onto the stack.
 */
void op_push(stack_t **stack, unsigned int line_number, char *arg)
{
	instruction_t opcodes[] = {
		{"push", op_push},
		{"pall", op_pall},
		/* Add more opcodes as needed */
	};

	/* Implementing push operation */
	/* Example: push 10 */
	/* After execution, the stack should contain: 10 */

	/* Check if there is an argument */
	if (!stack || !line_number || !arg)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Use atoi to convert the argument to an integer */
	int value = atoi(arg);

	/* Create a new node */
	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize the new node */
	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	/* Update the previous node if the stack is not empty */
	if (*stack)
		(*stack)->prev = new_node;

	/* Update the stack to point to the new node */
	*stack = new_node;
}

/**
 * op_pall - Opcode function to print all values on the stack
 * @stack: Pointer to the stack
 * @line_number: Current line number in the Monty ByteCode file
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	/* Implementing pall operation */
	/* Example: pall */
	/* Output (if the stack contains values): 10 */

	(void)line_number; /* Unused parameter */

	if (!stack)
	{
		fprintf(stderr, "Error: op_pall - Stack is NULL\n");
		exit(EXIT_FAILURE);
	}

	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
