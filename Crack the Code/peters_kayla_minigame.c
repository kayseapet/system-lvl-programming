/*
    Secrect Code Minigame
    Kayla Peters, July 25 2025
    - progam that generates a random number and asks the user to guess it
    - the user has fixed # of attempts to guess the number
    - the program provides feedback on the user's guess:
        - too high or too low
        - how many digits are correct & in the correct position
        - how many digits are correct but in the wrong position
    - the user wins if they guess the number within the allowed attempts
    - the user can quit the game at any time by entering 'q' or 'Q'
    - the difficulty level can be set to adjust the number of attempts and the length of the code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateSecretCode(char* code, int digits) 
{
    int i;
    for ( i = 0; i < digits; i++) 
    {
        int value;
        // to make sure there are no leading zeros in the first digit
        if (i == 0 && digits > 1) 
        {
            value = rand() % 9 + 1; // choose from numbers 1-9
        } 
        else 
        {
            value = rand() % 10; // choose from numbers 0-9
        }
        code[i] = '0' + value; // convert to character
    }
    code[digits] = '\0'; // null-terminate the string
}


void processTry(char *input,char *code, int digits, int* correct_right_digits, int* correct_wrong_digits)  //returns 0 if try was completely correct, and 1 if not
{
    *correct_right_digits = 0; //# of digits that are correct & in the right place
    *correct_wrong_digits = 0; //# of digits that are correct but in the wrong place

    // frequency arrays to count occurrences of each digit
    int freq_input[10] = {0};
    int freq_code[10] = {0};

    int i;
    // looking for digits that are correct and in the right place
    for (i = 0; i < digits; i++)
    {
        if (input[i] == code[i]) // if the digit is correct and in the right place
        {
            (*correct_right_digits)++;
        }
        else
        {
            // count occurrences of each digit in input and code
            freq_input[input[i] - '0']++;
            freq_code[code[i] - '0']++;
        }
    }
    // looking for digits that are correct but in the wrong place
    for (i = 0; i < digits; i++)
    {
        if(freq_code[i] > 0 && freq_input[i] > 0)
        {
            // the number of correct digits in the wrong place is the minimum of the two frequencies
            if (freq_code[i] < freq_input[i])
            {
                (*correct_wrong_digits) += freq_code[i];
            }
            else
            {
                (*correct_wrong_digits) += freq_input[i];
            }
        }
    }
}

int main()
{
    //1. Iniialize Difficulty Level
    int tries;
    int digits;
    printf("Select difficulty level (1-3):\n");
    printf("[1] Easy (3 digits, 8 tries)\n");
    printf("[2] Medium (4 digits, 6 tries)\n");
    printf("[3] Hard (7 digits, 5 tries)\n");
    printf(":> ");
    int level;
    scanf("%d", &level);
    switch (level) {
        case 1:
            digits = 3;
            tries = 8;
            break;
        case 2:
            digits = 4;
            tries = 6;
            break;
        case 3:
            digits = 7;
            tries = 5;
            break;
        default:
            printf("Invalid difficulty level. Exiting game.\n");
            return 1;
    }
    printf("You selected level %d: %d digits, %d tries.\n", level, digits, tries);
    
    //2. Generate Random Number
        printf("Generating a secret code up to %d digits...\n", digits);
        char secret_code[digits + 1];
        srand(time(NULL)); // Seed the random number generator
        
        generateSecretCode(secret_code, digits);
        printf("Secret code generated! You have %d tries to guess it.\n", tries);
        

    while(tries > 0) // Main game loop
    {
        //3. Get User Input
            char user_input[digits + 1];
            printf("What is the secret code? (%d digits, %d tries left)\n :>", digits, tries);
            scanf("%s", user_input);
            // Check if user wants to quit
                if (strcmp(user_input, "q") == 0 || strcmp(user_input, "Q") == 0) 
                {
                    printf("You chose to quit. The secret code was %s!\n", secret_code);
                    return 0;
                }
            // Check if input is valid (digits long and only contains numbers)
                if (strlen(user_input) != digits || strspn(user_input, "0123456789") != digits) 
                {
                    printf("Invalid input. Please enter a %d-digit number.\n", digits);
                    continue; // ask for input again
                }

        //4. Process User Input
            int correct_right_digits = 0;
            int correct_wrong_digits = 0;
            processTry(user_input, secret_code, digits, &correct_right_digits, &correct_wrong_digits);

        //5. write feeback output
            if (correct_right_digits == digits) 
            {
                printf("You guessed the secret code. You Win!\n");
                return 0; // user wins
            } 
            else 
            {
                // compare code and user input to see if try was too high or too low
                if (atoi(user_input) < atoi(secret_code))
                {
                    printf("Your guess is too low.\n");
                } 
                else 
                {
                    printf("Your guess is too high.\n");
                }
                // Display the number of correct digits
                printf("Correct digits in the right place: %d\n", correct_right_digits);
                printf("Correct digits in the wrong place: %d\n", correct_wrong_digits);
                tries--; // decrement tries
            }

        //6. if the user runs out of tries
            if (tries == 0) 
            {
                printf("You ran out of tries. The secret code was: %s\n You Lost :(", secret_code);
                return 0; // user loses
            }
    }
}