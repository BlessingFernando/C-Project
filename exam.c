// This program  performs security authorisation based authorisation on numeric codes
// The user will be required to enter four single digit integer numbers between 0-9 or random code, the program will then encrypt the code and compare it to a fixed authorsided access code.
// The user should be able to decrypt a code which has already been encrypted.
// Menu 1: The user gets to choose to enter four single digit integers or random code.
// Menu 2: The encryption will begin
// Menu 3: The encrypted code will be compared with the access code 4523, if both codes matches. A mesage will be shown stating " Correct code entered" otherwise if incorrect
// " Incorrect code entered" shall be displayed.
// Menu 4: The decryption of encrypted codes will be done.
// Menu 5: Display the number of times the encrypted code is entered
// Menu 6: Exit the program

// Author: Blessing Fernando
// OS: Windows 10
// Compiler: Borland
// Date: 13/05/2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct code_counter { // code_counter struct
    int correct_code;
    int wrong_code;
};

void menu();

int *enterCode();

int * setAccessCode();

void generateRandomCode(char *code);

void encryptTheCode(int *code);

int checkCodeMatches(const int *accessCode, int *code);

void decryptTheCode(int *code);

void displayTheTimes(struct code_counter* counter);

int validate(char *code);

void printCode(int *code);

int main() {
    const int *accessCode; // access code
    struct code_counter* counter = (struct code_counter*) malloc(sizeof(struct code_counter*)); // store the number of wrong_code and write_code
    counter->wrong_code =0; // set the initial wrong_code value to 0
    counter->correct_code=0; // set the initial correct_code value to 0
    int val = 0;
    int *code; // user entered or randomly generated code
    int codeEntered = 0;
    int encrypted = 0;
    srand(time(0)); // setting the seed
    accessCode = setAccessCode(); //  set the access code digits to the accessCode array
    while (1) { // loop until user press exit
        menu(); // display the menu to user
        printf("Enter a value :");
        scanf("%d", &val); // get user input value
        fflush(stdin);

        if (val == 1) { // if user entered value 1
            code = enterCode(); // get the code from user or randomly generate
            printf("%s", "The code is\n");
            printCode(code);
            codeEntered = 1; // set value to 1

        } else if (val == 2) { // if user entered value 2
            if (codeEntered == 1) { // if code is entered or randomly generated already
                encryptTheCode(code); // encrypt the code
                printf("%s", "Encrypted code is\n");
                printCode(code);
                encrypted = 1; // set value to 1

            } else { // if code is not entered or randomly generated already
                printf("%s", "Generate or enter a code first\n\n");
            }

        } else if (val == 3) { // if user entered value 3
            if(encrypted == 1){ // if code is encrypted already
                if(checkCodeMatches(accessCode, code) == 1){ // check weather access code and user entered code is matches
                    printf("%s", "Correct code entered\n\n");
                    counter->correct_code = counter->correct_code +1; // update the correct_code value
                } else { // check weather access code and user entered code is not matches
                    printf("%s", "Wrong code entered\n\n");
                    counter->wrong_code = counter->wrong_code +1; // update the wrong_code value
                }

            } else{ // if code is not encrypted already
                printf("%s", "You have to encrypt the code first\n\n");
            }

        } else if (val == 4) { // if user entered value 4
            if(encrypted == 1){  // if code is encrypted already
                decryptTheCode(code); // decrypt the code
                encrypted = 0; // se the value to 0
            } else { // if code is not encrypted already
                printf("%s", "You have to encrypt the code first\n\n");
            }
        } else if (val == 5) { // if user entered value 5
            displayTheTimes(counter); // display the correct_code and wrong_code values

        } else if (val == 6) { // if user entered value 6
            printf("%s", "Exiting......\n");
            return 0; // exit the program
        } else { // if user entered something else
            printf("%s", "Enter a valid input inside the range 1-6\n\n");
        }

    }
}

void menu() { // the menu that shown to the user

    printf("%s", "1. Enter a code or generate a random code\n");
    printf("%s", "2. Encrypt code\n");
    printf("%s", "3. Check if encrypted code matches the default authorized access code\n");
    printf("%s", "4. Decrypt the code\n");
    printf("%s", "5. Display the number of times the encrypted code is\n");
    printf("%s", "6. Exit program\n\n");

}

int * setAccessCode() { //  set the access code digits to the accessCode array
    int *accessCode = (int *) malloc(4 * sizeof(int *)); // initialization
    //put each digit value
    *(accessCode + 0) = 4;
    *(accessCode + 1) = 5;
    *(accessCode + 2) = 2;
    *(accessCode + 3) = 3;
    return accessCode; // return that
}

int *enterCode() { // get the code from user or randomly generate
    int val;
    int *code = (int *) malloc(4 * sizeof(int *)); // initialization
    char *userInput = (char *) malloc(4 * sizeof(char *)); // to get users input
    userInput[0] = '\0';
    while (!validate(userInput)) { // loop through user enter a valid input
        printf("%s", "Enter a code or press enter to generate a random code:");
        val = scanf("%99[^\n]", userInput); // get user input
        fflush(stdin);
        if (val != 1) { // if user press enter without entering a value
            generateRandomCode(userInput); // get a randomly generate value for the code
            break;
        }
    }
    for (int i = 0; i < 4; i++) { // convert user input char values to integers
        *(code + i) = userInput[i] - 48; // store that to code array
    }
    return code; // return the code
    //printCode(code);

}

void generateRandomCode(char *code) { // random code generation
    int i;
    int upper = 57; // upper limit as ascii value of 9
    int lower = 48; // lower limit as ascii value of 0
    for (i = 0; i < 4; i++) { // loop through for 4 digits
        char j = (char) ((rand() % (upper - lower + 1)) + lower); // get random value and convert it to char
        *(code + i) = j; // put that char value to code array
    }
}

void encryptTheCode(int *code) { // encryption of user entered code

    int firstElement = *code; // swap the first digit with 3rd digit
    *code = *(code + 2);
    *(code + 2) = firstElement;

    int secondElement = *(code + 1); // swap the 2nd digit with 4th digit
    *(code + 1) = *(code + 3);
    *(code + 3) = secondElement;

    for (int i = 0; i < 4; i++) { // add 1 to all the digits
        *(code + i) = *(code + i) + 1;
    }

    for (int i = 0; i < 4; i++) { // if any digit is equal to 10 change it to 0
        if (*(code + i) == 10) {
            *(code + i) = 0;
        }
    }

}

int checkCodeMatches(const int *accessCode, int *code) {// check weather access code and user encrypted code is matching
    for (int i = 0; i < 4; i++) {  // loop through each digit and check each digit is equal
        if(*(code + i) != *(accessCode + i)){ // if at least one digit is not equal
            return 0; // return 0 as not equal
        }
    }
    return 1; // return 1 as equal
}

void decryptTheCode(int *code) { // decryption of the encrypted code

    for (int i = 0; i < 4; i++) { // remove 1 from each digit
        *(code + i) = *(code + i) - 1;
    }

    for (int i = 0; i < 4; i++) { // if any digit is -1 change it to 9
        if (*(code + i) == -1) {
            *(code + i) = 9;
        }
    }

    int firstElement = *code; // swap the first digit with 3rd digit
    *code = *(code + 2);
    *(code + 2) = firstElement;

    int secondElement = *(code + 1); // swap the second digit with 4th digit
    *(code + 1) = *(code + 3);
    *(code + 3) = secondElement;
}

void displayTheTimes(struct code_counter* counter) { // display the correct_code and wrong_code values
    printf("Number of times encrypted code is correct: %d\n", counter->correct_code);
    printf("Number of times encrypted code is wrong: %d\n\n", counter->wrong_code);
}

int validate(char *code) { // validation of user input code
    int i = 0;
    if (code[i] == '\0') { // if code array is empty return not valid
        return 0;
    }
    while (code[i] != '\0') { // if code array is not empty
        if ((int) code[i] < 48 || (int) code[i] > 57) { // if user entered digits are not in 0 to 9 return not valid
            printf("%s", "Please enter a 4 digit number\n\n");
            return 0;
        }
        i++;
    }

    if (i > 4) { // if user entered a value larger than 4 digits return invalid
        printf("%s", "Please enter a 4 digit number\n\n");
        return 0;
    }

    return 1; // return valid
}

void printCode(int *code) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", *(code + i));
    }

    printf("\n\n");
}