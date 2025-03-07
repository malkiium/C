#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#endif

#define MAX_ENTRY_LENGTH 1000
#define MAX_FILENAME_LENGTH 100
#define JOURNAL_DIR "journal_entries"

void create_directory_if_not_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        #ifdef _WIN32
            _mkdir(dir);
        #else
            mkdir(dir, 0700);
        #endif
    }
}

void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date_str, 11, "%Y-%m-%d", tm);
}

void save_entry(const char *entry) {
    char filename[MAX_FILENAME_LENGTH];
    char date_str[11];

    get_current_date(date_str);  // No more implicit declaration warning

    int ret = snprintf(filename, sizeof(filename), "%s/journal_%s.txt", JOURNAL_DIR, date_str);
    if (ret < 0 || (size_t)ret >= sizeof(filename)) {
        printf("Error: Filename too long!\n");
        return;
    }


    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char timestamp[9];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", tm);

    fprintf(file, "----- Entry at %s -----\n", timestamp);
    fprintf(file, "%s\n\n", entry);

    fclose(file);
    printf("Entry saved successfully.\n");
}



void view_entries() {
    char command[MAX_FILENAME_LENGTH + 10];
    #ifdef _WIN32
        snprintf(command, sizeof(command), "dir /B %s\\*.txt", JOURNAL_DIR);
    #else
        snprintf(command, sizeof(command), "ls %s/*.txt", JOURNAL_DIR);
    #endif
    
    char date_str[11];
    get_current_date(date_str);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }
    
    char filename[MAX_FILENAME_LENGTH];
    while (fgets(filename, sizeof(filename), fp) != NULL) {
        filename[strcspn(filename, "\n")] = 0; // Remove newline
        
        char full_path[MAX_FILENAME_LENGTH + 10];
        int ret = snprintf(filename, sizeof(filename), "%s/journal_%s.txt", JOURNAL_DIR, date_str);
        if (ret < 0 || ret >= (int)sizeof(filename)) {
            printf("Error: Filename too long!\n");
            return;
        }     
        full_path[sizeof(full_path) - 1] = '\0';  // Ensure null termination

        
        FILE *entry_file = fopen(full_path, "r");
        if (entry_file == NULL) {
            printf("Error opening file: %s\n", full_path);
            continue;
        }
        
        printf("Date: %s\n", filename + 8); // Skip "journal_" prefix
        char line[MAX_ENTRY_LENGTH];
        while (fgets(line, sizeof(line), entry_file) != NULL) {
            printf("%s", line);
        }
        printf("----------------------------------------\n");
        
        fclose(entry_file);
    }
    
    pclose(fp);
}

int main() {
    create_directory_if_not_exists(JOURNAL_DIR);
    
    char choice;
    char entry[MAX_ENTRY_LENGTH];
    
    while (1) {
        printf("\nDaily Journal App\n");
        printf("1. Write a new entry\n");
        printf("2. View all entries\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case '1':
                printf("Enter your journal entry (max %d characters):\n", MAX_ENTRY_LENGTH);
                fgets(entry, sizeof(entry), stdin);
                entry[strcspn(entry, "\n")] = 0; // Remove trailing newline
                save_entry(entry);
                break;
            case '2':
                view_entries();
                break;
            case '3':
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}