#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    int lower = 1, upper = 100;

    // Seed the random number generator
    srand(time(0));
    number = (rand() % (upper - lower + 1)) + lower; // Random number between 1 and 100

    printf("Welcome to the Guessing Game!\n");
    printf("I have chosen a number between %d and %d.\n", lower, upper);
    printf("Can you guess the number?\n");

    // Infinite loop to keep the game running until the correct guess
    while (1) {
        attempts++;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Check if the guess is correct, too high, or too low
        if (guess == number) {
            printf("Congratulations! You guessed the number %d in %d attempts.\n", number, attempts);
            break;
        } else if (guess > number) {
            printf("Too high! Try again.\n");
        } else {
            printf("Too low! Try again.\n");
        }
    }

    return 0;
}
