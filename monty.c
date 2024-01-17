#include "monty.h"

/**
 * main - Entry point for the Monty ByteCode interpreter
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Description: Reads and interprets Monty ByteCode instructions from a file.
 *              Executes the corresponding operations based on the opcodes.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	stack_t *stack = NULL;

	parse_and_execute(file, &stack, opcodes);

	fclose(file);
	free_stack(&stack);

	return (EXIT_SUCCESS);
}

/**
 * parse_and_execute - Parses and executes Monty ByteCode instructions
 * @file: Pointer to the Monty ByteCode file
 * @stack: Pointer to the stack
 * @opcodes: Opcode-function mappings
 */
void parse_and_execute(FILE *file, stack_t **stack, instruction_t *opcodes)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, file)) != -1)
	{
		tokenize_and_execute(line, stack, opcodes);
	}

	free(line);
}

/**
 * tokenize_and_execute - Tokenizes and executes Monty ByteCode instructions
 * @line: Monty ByteCode instruction line
 * @stack: Pointer to the stack
 * @opcodes: Opcode-function mappings
 */
void tokenize_and_execute(char *line, stack_t **stack, instruction_t *opcodes)
{
	char *opcode, *arg;
	int ret;

	ret = sscanf(line, "%ms %ms", &opcode, &arg);

	if (ret == 1)
	{
		tokenize_and_execute_helper(stack, opcode, NULL, opcodes);
	}
	else if (ret == 2)
	{
		tokenize_and_execute_helper(stack, opcode, arg, opcodes);
	}
	else
	{
		fprintf(stderr, "Error: Invalid input format\n");
		exit(EXIT_FAILURE);
	}

	free(opcode);
	if (arg)
		free(arg);
}

/**
 * tokenize_and_execute_helper - function for tokenizing Monty ByteCode
 * @stack: Pointer to the stack
 * @opcode: Monty ByteCode opcode
 * @arg: Argument for the Monty ByteCode operation
 * @opcodes: Opcode-function mappings
 */
void tokenize_and_execute_helper(stack_t **stack, char *opcode,
char *arg, instruction_t *opcodes)
{
	int found = 0;

	for (size_t i = 0; i < sizeof(opcodes) / sizeof(opcodes[0]); i++)
	{
		if (strcmp(opcode, opcodes[i].opcode) == 0)
		{
			opcodes[i].f(stack, 0, arg);
			found = 1;
			break;
		}
	}

	if (!found)
	{
		fprintf(stderr, "Error: Unknown opcode %s\n", opcode);
		exit(EXIT_FAILURE);
	}
}
