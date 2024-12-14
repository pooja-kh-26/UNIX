#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

void list_files (const char *path){
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    printf("Files in %s:\n", path);
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}

void file_details(const char *path) {
    struct stat file_stat;

    if (stat(path, &file_stat) < 0) {
        perror("stat");
        return;
    }

    printf("File: %s\n", path);
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("Permissions: %o\n", file_stat.st_mode & 0777);
    printf("Last modified: %s", ctime(&file_stat.st_mtime));
}

void create_file(const char *path) {
    int fd = creat(path, 0644);

    if (fd < 0) {
        perror("creat");
        return;
    }

    printf("File created: %s\n", path);
    close(fd);
}

void create_directory(const char *path) {
    if (mkdir(path, 0755) < 0) {
        perror("mkdir");
        return;
    }

    printf("Directory created: %s\n", path);
}

void delete_file(const char *path) {
    if (unlink(path) < 0) {
        perror("unlink");
        return;
    }

    printf("File deleted: %s\n", path);
}

void delete_directory(const char *path) {
    if (rmdir(path) < 0) {
        perror("rmdir");
        return;
    }

    printf("Directory deleted: %s\n", path);
}

int main() {
    int choice;
    char path[256];

    while (1) {
        printf("\n--- Simple File Explorer ---\n");
        printf("1. List files in a directory\n");
        printf("2. Show file details\n");
        printf("3. Create a file\n");
        printf("4. Create a directory\n");
        printf("5. Delete a file\n");
        printf("6. Delete a directory\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character

        switch (choice) {
            case 1:
                printf("Enter directory path: ");
                scanf("%s", path);
                list_files(path);
                break;
            case 2:
                printf("Enter file path: ");
                scanf("%s", path);
                file_details(path);
                break;
            case 3:
                printf("Enter file path: ");
                scanf("%s", path);
                create_file(path);
                break;
            case 4:
                printf("Enter directory path: ");
                scanf("%s", path);
                create_directory(path);
                break;
            case 5:
                printf("Enter file path: ");
                scanf("%s", path);
                delete_file(path);
                break;
            case 6:
                printf("Enter directory path: ");
                scanf("%s", path);
                delete_directory(path);
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

