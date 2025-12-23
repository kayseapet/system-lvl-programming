/*
    Command Launcher Program
    Kayla Peters, July 24 2025
    -simulates a very basic command shell
        - always displays a command prompt when not in use (using a loop)
        - reads a line of input from user that represents a valid shell command (ex: ls, cal, & date):
            To process command inputs:
            1. take the first word of input as a command, and concat that command to the path where the UNIX shell executables are stored /bin/.
            2. Use fork() to create a child process:
                -in child process: use execl() to execute the command. if it fails, child should print and error msg and exit.
                - in parent process: use wait() to wait for child process to complete. after child termincates, parent should loop back to starting command prompt, & wait for the next command given.

        - when user types 'exit', the prorgram terminates
        - any basic error handling for fork() execl() & wait() prints an error.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // This header provides fork()
#include <string.h>
#include <sys/wait.h> // For wait()

//Function to parse user input into arguments
void parse_input(char *input, char **args)
{
    int i = 0; // Index for storing tokens in args array

    // Get the first token
    args[i] = strtok(input, "\t\n"); //split by whitespace and newline characters
    if (args[i] == NULL) // If no command is entered
    {
        return; // Return without doing anything
    }

    // Walk through other tokens
    while (args[i] != NULL && i < 255) // Ensure we don't exceed the array size
    {
        i++; // Move to the next index
        args[i] = strtok(NULL, "\t\n"); // Get the next token
    }
    args[i] = NULL; // Null-terminate the array of arguments
}

int main()
{
    char command[256];
    char *args[256]; // Array to hold command and arguments
    pid_t pid;

    //loop looking for new commands
    while (1)
    { 
        // Display command prompt
        printf("myshell :> ");
        fflush(stdout); // Ensure prompt is displayed immediately

        // Read command from user
        if(fgets(command, sizeof(command), stdin) == NULL)
        {
            break;  // end of input
        }
    
        // we need to remove newline character at the end of given input
        command[strcspn(command, "\n")] = '\0';

        // Parse the input into command and arguments
        parse_input(command, args);

        // Process input given
        //look for exit command
        if (strcmp(command, "exit") == 0)
        {
           break; //end loop
        }

        //fork another process
        pid = fork();

        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)  
        {
            // Child Process
            char path[256];
            snprintf(path, sizeof(path), "/bin/%s", command); // Concat /bin with command        
            execvp(args[0], args); // Execute the command with arguments

            perror("execl failed"); //only if theres an error
            exit(EXIT_FAILURE);
        }
        else    // Parent Process
        {
            wait(NULL); // wait for child process to complete
        }
    }
    return 0;
}