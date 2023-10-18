#include "main.h"

void exec_cmd(char **argv) {
    if (argv) {
        char *command = argv[0];

        // Execute the command with execvp, which searches for the command in the PATH
        if (execvp(command, argv) == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    char *prompt = "emmanuel@DESKTOP-24P3IC9:~$ ";
    char *line = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";  // Tokenize by space and newline
    char **argv;
    int b;

    while (1) {
        printf("%s", prompt);
        nchars_read = getline(&line, &n, stdin);

        if (nchars_read == -1) {
            printf(" \n");
            break;  // Exit the shell on EOF (Ctrl+D)
        }

        // Tokenize the input into command and arguments
        char *tok = strtok(line, delim);
        int num_tokens = 0;

        while (tok != NULL) {
            num_tokens++;
            tok = strtok(NULL, delim);
        }

        if (num_tokens == 0) {
            continue;  // Empty line, continue without forking
        }

        // Allocate space for the argv array
        argv = (char **)malloc((num_tokens + 1) * sizeof(char *));
        if (argv == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Copy tokens to the argv array
        tok = strtok(line, delim);
        b = 0;

        while (tok != NULL) {
            argv[b] = strdup(tok);
            tok = strtok(NULL, delim);
            b++;
        }
        argv[b] = NULL;  // Null-terminate the argv array

        // Fork a child process to execute the command
        pid_t child_pid = fork();

        if (child_pid == 0) {
            // This is the child process
            exec_cmd(argv);
        } else if (child_pid > 0) {
            // This is the parent process
            int status;
            waitpid(child_pid, &status, 0);

            // Free memory allocated for argv
            for (int i = 0; i < num_tokens; i++) {
                free(argv[i]);
            }
            free(argv);
        } else {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Free memory for the line
    free(line);

    return 0;
}

