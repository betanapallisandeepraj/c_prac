#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secretNumber, guess;
    srand(time(NULL));
    secretNumber = rand() % 100 + 1;

    printf("Welcome to the guessing game!\n");
    printf("I have chosen a number between 1 and 100.\n");
    printf("Can you guess what it is?\n");

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess == secretNumber) {
            printf("Congratulations! You guessed the secret number!\n");
            break;
        } else if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("Too high! Try again.\n");
        }
    }
    return 0;
}

