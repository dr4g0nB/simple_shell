#include "header.h"
#include <unistd.h>

/**
 * read_line - Reads a line.
 * Return: line.
 */

char *read_line()
{
	size_t sizeline;
	char *line = NULL;

	/** If ctrl + D  is pressed then exit the shell*/
	if (getline(&line, &sizeline, stdin) == EOF)
	{
		exit(0);
	}

	/**Checks the new line*/
	if (line[0] == '\n' && _strlen(line) == 1)
	{
		return (NULL);
	}

	/**Sends line to token*/
	if (line[strlen(line) - 1] == '\n')
	{
		line[strlen(line) - 1] = '\0';
	}
	return (line);
}

/**
 * string_split - Separates the lines in tokens.
 * @line: Line that is received.
 * @delim: Delimeter that separates the tokens.
 * Return: Token.
 */

char **string_split(char *line, char *delim)
{
	int len = 0;
	char **token;

	token = malloc(sizeof(char *) * 1024);
	/** Checks if malloc did alloc */
	if (token == NULL)
	{
		return (NULL);
	}

	/** First token in 0 position is gonna receive line and delim  */
	token[0] = strtok(line, delim);

	/** If its different than NULL then tokenaze every argument knowing delim*/
	while (token[len] != NULL)
	{
		len++;
		token[len] = strtok(NULL, delim);
	}
	token[len] = NULL;

	return (token);
}

/**
 * get_exec_path - returns the absolte path to execute a given
 * command taking $PATH into consideration
 * @command: an executable
 * @paths: an array of paths where to check for an executable
 * Return: absolute path to execute a given command
 */

char *get_exec_path(char *command, char **paths)
{
	int i;
	char *result;
	char *tmp;

	/** If no command is passed */
	if (command == NULL)
	{
		return (NULL);
	}

	/** Instead of command a slash is passed */
	if (command[0] == '/')
	{
		if (access(command, X_OK) == -1)
		{
			return (NULL);
		}
		return (command);
	}

	/** Gonna traverse path from i position while beening different than NULL */
	for (i = 0; paths[i] != NULL; i++)
	{
		/** Concatenates the path and the slash and gonna be stored at tmp */
		tmp = _concat(paths[i], "/");

		/** result is gonna have the concatenation of command and tmp*/
		result = _concat(tmp, command);
		free(tmp);

		if (access(result, X_OK) == -1)
		{
			free(result);
			continue;
		}
		return (result);
	}

	return (NULL);
}

/**
 * execute - Executes.
 * @token: All arguments.
 * @paths: All the paths from $PATH environment variable
 * @env: Environment variable.
 * Return: 1
 */

int execute(char *token[], char **paths, char *env[])
{
	pid_t parent_id;
	pid_t child_status;
	char *exec_path;

	/** Env builtin */
	if (_strcmp(token[0], "env") == 0)
	{
		env_builtin(env);
		return (1);
	}

	/** Exit builtin */
	if (_strcmp(token[0], "exit") == 0)
		exit(0);

	/** Creates a child */
	parent_id = fork();

	/** If its on the child */
	if (parent_id == 0)
	{
		exec_path = get_exec_path(token[0], paths);
		if (exec_path == NULL)
		{
			perror("DOES NOT EXIST");
			exit(0);
		}
		token[0] = exec_path;
		if (execv(exec_path, token) == -1)
		{
			perror("DOES NOT EXIST");
			exit(0);
		}
	}
	else
	{
		/** If its not on the child then wait for it */
		wait(&child_status);
	}
	return (1);
}
