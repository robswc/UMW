#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// set default error message
char error_message[30] = "An error has occurred\n";

// create builtin functions
int cmd_cd(char **args);

int cmd_pwd();

int cmd_exit(char **args);

// use list of chars to define builtin functions
char *builtin_str[] = {
        "cd",
        "pwd",
        "exit"
};

// reference builtin functions
int (*builtin_func[])(char **) = {
        &cmd_cd,
        &cmd_pwd,
        &cmd_exit
};


// gets the total number of builtin functions
int get_builtin_num() {
    return sizeof(builtin_str) / sizeof(char *);
}

// builtin command, cd, changes the working directory
int cmd_cd(char **args) {
    // if no argument, take user to home directory, using HOME ENV.
    // else, use C builtin chdir to change the current directory.
    if (args[1] == NULL) {
        (chdir(getenv("HOME")));
    } else {
        if (chdir(args[1]) != 0) {
            // if there's an error, bypass and continue
            write(STDERR_FILENO, error_message, strlen(error_message));
            return 1;
        }
    }
    return 1;
}

// simple custom exit command, gracefully exits
int cmd_exit(char **args) {
    exit(0);
}

// builtin, prints working directory
int cmd_pwd() {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        write(STDERR_FILENO, error_message, strlen(error_message));
    else
        printf("Working Directory: %s\n", cwd);
    return 1;
}

// starts the process
int start(char **args) {
    pid_t pid, wpid;
    int status;

    // create a fork, set pid
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            // if there's an error, continue but print error
            write(STDERR_FILENO, error_message, strlen(error_message));
            return 0;
        }
    } else if (pid < 0) {
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 1;
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int execute(char **args) {
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    // search builtin list, to see if the command is a builtin command, if so override
    for (i = 0; i < get_builtin_num(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    // start process
    return start(args);
}

#define TOKEN_BUFFERSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

// splits the inputted string up, using delimiters
char **split_cmd(char *line) {
    int bufsize = TOKEN_BUFFERSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        write(STDERR_FILENO, error_message, strlen(error_message));
    }

    token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFFERSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

char *read_cmd(void) {

    char *line = NULL;
    ssize_t buffersize = 0;

    if (getline(&line, &buffersize, stdin) == -1) {
        if (feof(stdin)) {
            exit(0);
        } else {
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
    }

    return line;
}

void shell_loop(void) {
    // declare command and arguments
    char *cmd;
    char **args;
    int status;

    do {
        // prompt user, set cmd and args
        printf("mysh> ");
        cmd = read_cmd();
        args = split_cmd(cmd);
        status = execute(args);

        free(cmd);
        free(args);
    } while (status);
}

// special loop, for running batch files
void batch_loop(const char *file_name) {
    // declare command and arguments
    char *cmd;
    char **args;
    int status;


    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(1);

    do {
        char *line = NULL;
        ssize_t buffersize = 0;
        if (getline(&line, &buffersize, fp) == -1) {
            if (strcmp(line, "exit") == 0) {
                fclose(fp);
                exit(0);
            } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
                fclose(fp);
                exit(0);
            }
        }

        cmd = line;
        printf("\n%s\n", line);

        args = split_cmd(cmd);
        status = execute(args);
        free(cmd);
        free(args);
    } while (status);


    exit(0);
}


int main(int argc, char **argv) {

    // if there's an argument, run in batch mode, else run normally
    if (argc == 2) {
        printf("Running %s...\n", argv[1]);
        batch_loop(argv[1]);
    } else {
        if (argc > 2) {
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(0);
        }
    }

    // main shell loop
    shell_loop();
    return EXIT_SUCCESS;
}
