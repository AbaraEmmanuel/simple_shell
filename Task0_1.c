#include "main.h"

/**
 * main - Entry point for the simple shell program.
 * @ac: The number of arguments (unused).
 * @argv: An array of strings containing command-line arguments.
 * Return: Always returns 0.
 */
int main(int ac, char **argv) {
    char *prompt = "#cisfun$ ";
    char *line = NULL;
    char *ptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = "\n";
    int num_tokens = 0;
    char *tok;
    int b;

    /* Declare and suppress unused variable warnings */
    (void)ac;

    /* Create an infinite loop for the shell's prompt */
    while (1) {
        printf("%s", prompt);
        nchars_read = getline(&line, &n, stdin);
        /* Check if the getline function failed or reached EOF or if the user used CTRL + D */
        if (nchars_read == -1) {
            printf("\n");
            return (-1);
        }

        /* Allocate memory for a copy of the lineptr */
        ptr_copy = malloc(sizeof(char) * nchars_read);
        if (ptr_copy == NULL) {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* Copy lineptr to lineptr_copy */
        strcpy(ptr_copy, line);

        /********** Split the string (lineptr) into an array of words ********/
        /* Calculate the total number of tokens */
        tok = strtok(line, delim);

        while (tok != NULL) {
            num_tokens++;
            tok = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        tok = strtok(ptr_copy, delim);

        for (b = 0; tok != NULL; b++) {
            argv[b] = malloc(sizeof(char) * strlen(tok));
            strcpy(argv[b], tok);

            tok = strtok(NULL, delim);
        }
        argv[b] = NULL;

        /* Execute the command in a child process */
        int child_pid = fork();

        if (child_pid == 0) {
            // This is the child process
            execmd(argv);
        } else if (child_pid > 0) {
            // This is the parent process
            // Wait for the child to complete
            int status;
            waitpid(child_pid, &status, 0);
        } else {
            perror("Fork failed");
        }
    }

    /* Free up allocated memory */
    free(ptr_copy);
    free(line);

    return (0);
}

/**
 * execmd - Execute a command in a child process.
 * @argv: An array of strings containing the command and its arguments.
 */
void execmd(char **argv) {
    char *command = NULL;

    if (argv) {
        /* Get the command */
        command = argv[0];

        /* Execute the command with execve */
        if (execve(command, argv, NULL) == -1) {
            perror("Error");
        }
    }
}
