#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct stack_s - Doubly linked list representation of a stack (or queue)
 * @n: Integer value of the node
 * @prev: Points to the previous element of the stack (or queue)
 * @next: Points to the next element of the stack (or queue)
 *
 * Description: Doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - Opcode and its function
 * @opcode: The opcode
 * @f: Function to handle the opcode
 *
 * Description: Opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number, char *arg);
} instruction_t;

/* Function prototypes */
void parse_and_execute(FILE *file, stack_t **stack, instruction_t *opcodes);
void tokenize_and_execute(char *line, stack_t **stack, instruction_t *opcodes);
void tokenize_and_execute_helper(stack_t **stack, char *opcode,
char *arg, instruction_t *opcodes);

/* Opcode function prototypes */
void op_push(stack_t **stack, unsigned int line_number, char *arg);
void op_pall(stack_t **stack, unsigned int line_number);

/* Additional utility function prototypes */
void free_stack(stack_t **stack);

#endif /* MONTY_H */
