#include "monty.h"

/**
 * _strdup - Duplicates a string.
 * @str: String to duplicate.
 *
 * Return: Pointer to the duplicated string or NULL on failure.
 */
char *_strdup(const char *str)
{
	char *dup;
	size_t len, i;

	if (!str)
		return (NULL);

	len = 0;
	while (str[len])
		len++;

	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}

/**
 * tokenize_and_execute - Tokenizes a line
 * @line: Line containing the opcode and argument.
 * @stack: Pointer to the stack.
 * @opcodes: Array of opcodes with their corresponding functions.
 *
 * Return: 1 on success, 0 on failure.
 */
int tokenize_and_execute(char *line, stack_t **stack, instruction_t *opcodes)
{
	char *opcode = NULL;
	int ret;

	ret = sscanf(line, "%s", opcode);
	if (ret == EOF)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (0);
	}

	if (!opcode || opcode[0] == '#')
	{
		free(opcode);
		return (1);
	}

	if (!execute_opcode(stack, opcode, opcodes))
	{
		free(opcode);
		return (0);
	}

	free(opcode);
	return (1);
}

/**
 * execute_opcode - Executes the corresponding opcode.
 * @stack: Pointer to the stack.
 * @opcode: Opcode to execute.
 * @opcodes: Array of opcodes with their corresponding functions.
 *
 * Return: 1 on success, 0 on failure.
 */

int execute_opcode(stack_t **stack, char *opcode, instruction_t *opcodes)
{
	size_t i;

	for (i = 0; opcodes[i].opcode; i++)
	{
		if (strcmp(opcodes[i].opcode, opcode) == 0)
		{
			opcodes[i].f(stack);
			return (1);
		}
	}

	fprintf(stderr, "unknown instruction %s\n", opcode);
	return (0);
}

/**
 * free_resources - Frees resources allocated during Monty execution.
 * @stack: Pointer to the stack.
 * @line: Line read from the file.
 * @file: File pointer.
 */
void free_resources(stack_t **stack, char *line, FILE *file)
{
	if (stack)
		free_stack(*stack);
	if (line)
		free(line);
	if (file)
		fclose(file);
}

/**
 * main - Entry point for Monty interpreter.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	stack_t *stack = NULL;

	instruction_t opcodes[] = {
		{"push", op_push},
		{"pall", op_pall},
		{"pint", op_pint},
		{NULL, NULL}};

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		if (!tokenize_and_execute(line, &stack, opcodes))
		{
			fprintf(stderr, "Error: malloc failed\n");
			free_resources(&stack, line, file);
			exit(EXIT_FAILURE);
		}
	}

	free_resources(&stack, line, file);
	return (EXIT_SUCCESS);
}
