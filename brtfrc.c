#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the character set: letters, digits, punctuation, and some extended symbols.
#define CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=,./<>?;:'\"[]{}`~|\\¡¿€£¥©®±×÷"
#define CHARSET_LEN 94  // The length of the CHARSET array

// Function to generate a random string of a given length from the CHARSET
void generate_random_password(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = CHARSET[rand() % CHARSET_LEN];
    }
    password[length] = '\0';  // Null-terminate the string
}

// Function to perform the brute-force attack
int brute_force(char *target_password) {
    int length = 1;
    char guess[256];  // Buffer to store current guess
    long attempts = 0;

    while (1) {
        // Try all combinations of the current length
        printf("🔎 Trying length %d...\n", length);

        // Generate all possible combinations for the current length
        int found = 0;
        for (int i = 0; i < CHARSET_LEN; i++) {
            for (int j = 0; j < CHARSET_LEN; j++) {
                for (int k = 0; k < CHARSET_LEN; k++) {
                    // Generate guess string
                    guess[0] = CHARSET[i];
                    guess[1] = CHARSET[j];
                    guess[2] = CHARSET[k];
                    guess[3] = '\0';

                    attempts++;

                    // Reduce print frequency for performance
                    if (attempts % 100000000 == 0) {
                        printf("Attempt %ld: %s\n", attempts, guess);
                    }

                    // Check if the guess matches the target password
                    if (strcmp(guess, target_password) == 0) {
                        printf("✅ Password found after %ld attempts: %s\n", attempts, guess);
                        found = 1;
                        break;
                    }
                }
            }
        }

        if (found) {
            break;  // Password found, exit loop
        }

        length++;  // Increase length and try again
    }

    return 0;
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    // Generate a random password
    int password_length = 5;  // Start with a password of length 3
    char target_password[256];
    generate_random_password(target_password, password_length);

    printf("🎯 Generated password: %s\n", target_password);

    // Run the brute-force attack
    brute_force(target_password);

    return 0;
}
