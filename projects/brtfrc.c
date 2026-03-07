#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>  // Include OpenMP for multithreading

#define CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=,./<>?;:'\"[]{}`~|\\"
#define CHARSET_LEN (sizeof(CHARSET) - 1)  // Adjust length to exclude null terminator

// Function to generate a random password of a given length
void generate_random_password(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = CHARSET[rand() % CHARSET_LEN];
    }
    password[length] = '\0';  // Null-terminate the string
}

// Struct to store brute-force context
typedef struct {
    char *target;
    long attempts;
    int found;
} BruteForceContext;

// Multithreaded brute-force function
void brute_force_parallel(char *target_password) {
    int max_length = strlen(target_password);
    char guess[max_length + 1];  // Buffer for generated password
    BruteForceContext context = {target_password, 0, 0};

    printf("🔎 Brute-force attack started on a %d-character password with multithreading...\n", max_length);
    
    #pragma omp parallel for shared(context) private(guess) schedule(dynamic)
    for (size_t i = 0; i < CHARSET_LEN && !context.found; i++) {
        for (size_t j = 0; j < CHARSET_LEN && !context.found; j++) {
            for (size_t k = 0; k < CHARSET_LEN && !context.found; k++) {
                for (size_t l = 0; l < CHARSET_LEN && !context.found; l++) {
                    for (size_t m = 0; m < CHARSET_LEN && !context.found; m++) {
                        snprintf(guess, max_length + 1, "%c%c%c%c%c", CHARSET[i], CHARSET[j], CHARSET[k], CHARSET[l], CHARSET[m]);
                        
                        #pragma omp atomic
                        context.attempts++;

                        if (strcmp(guess, context.target) == 0) {
                            context.found = 1;
                            printf("✅ Password found after %ld attempts: %s\n", context.attempts, guess);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    int password_length = 5;  // Change this for longer passwords
    char target_password[password_length + 1];
    generate_random_password(target_password, password_length);

    printf("🎯 Generated password: %s\n", target_password);

    // Run the brute-force attack with multithreading
    brute_force_parallel(target_password);

    return 0;
}