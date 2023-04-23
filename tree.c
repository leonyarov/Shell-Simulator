//Leon Yarovinski 206817181
//Daniel Grounin 319191680

#define _GNU_SOURCE // C will not recognize "DT_DIR" whithout this definition.
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void print_tree(char *path, int level) {
    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "Error: Failed to open directory %s\n", path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            // Skip the "." and ".." directories
            continue;
        }

        for (int i = 0; i < level; i++) {
            printf("  ");  // Indent based on level
        }

        printf("%s", entry->d_name);
        if (entry->d_type == DT_DIR) {
            printf("/\n");
            // Recursively call print_tree on the subdirectory
            char subpath[1024];
            snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
            print_tree(subpath, level + 1);
        } else {
            printf("\n");
        }
    }

    closedir(dir);
}
