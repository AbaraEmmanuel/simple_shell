#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>

void execmd(char **argv);
int execute_command(char **args);
extern char **environ;
size_t our_strlen(const char *str);
ssize_t our_getline(char **line, size_t *len, FILE *stream);
int our_strcmp(const char *string1, const char *string2);
char *our_strdup(const char *str);
char *our_strcpy(char *dest, char *src);
char *our_strcat(char *final_str, char *str_to);
void signal_handler(int signal);

/* global variables */
extern char **environ;
#endif
