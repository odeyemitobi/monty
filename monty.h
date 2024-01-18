#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data structures */
/**
 * struct stack_s - Doubly linked list representation of a stack (or queue)
 * @n: Integer value of the node.
 * @prev: Pointer to the previous element of the stack (or queue).
 * @next: Pointer to the next element of the stack (or queue).
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - Struct for opcodes and their corresponding functions
 * @opcode: Opcode.
 * @f: Function to execute for the opcode.
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack);
} instruction_t;

/* Function prototypes */
char *_strdup(const char *str);
int tokenize_and_execute(char *line, stack_t **stack, instruction_t *opcodes);
int execute_opcode(stack_t **stack, char *opcode, instruction_t *opcodes);
void free_stack(stack_t *stack);
void op_push(stack_t **stack);
void op_pall(stack_t **stack);
stack_t *add_node(stack_t **stack, int n);

/* Additional definitions for compatibility */
typedef long ssize_t;
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif /* MONTY_H */
