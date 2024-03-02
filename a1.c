#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 4096
#define BUFFER 4096

void simple_listing(char *dir_path)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    while ((dirEntry = readdir(dir)) != 0)
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
            printf("%s\n", path);
        }
    }
    closedir(dir);
}
void recursive_listing(char *dir_path)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        return;
    }

    while ((dirEntry = readdir(dir)) != 0)
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
            printf("%s\n", path);
            struct stat file_info;
            if (stat(path, &file_info) == 0)
            {
                if (S_ISDIR(file_info.st_mode))
                {
                    recursive_listing(path);
                }
            }
        }
    }

    closedir(dir);
}
void simple_name_ends_with(char *dir_path, char *name_end)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        printf("ERROR\ninvalid path");
        return;
    }
    printf("SUCCESS\n");
    while ((dirEntry = readdir(dir)) != 0)
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            if (strcmp(dirEntry->d_name + (strlen(dirEntry->d_name) - strlen(name_end)), name_end) == 0)
            {
                snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
                printf("%s\n", path);
            }
        }
    }

    closedir(dir);
}
void recursive_name_ends_with(char *dir_path, char *name_end)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        return;
    }

    while ((dirEntry = readdir(dir)) != 0)
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            if (strcmp(dirEntry->d_name + (strlen(dirEntry->d_name) - strlen(name_end)), name_end) == 0)
            {
                snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
                printf("%s\n", path);
            }
            struct stat file_info;
            if (stat(path, &file_info) == 0)
            {
                if (S_ISDIR(file_info.st_mode))
                {
                    recursive_name_ends_with(path, name_end);
                }
            }
        }
    }

    closedir(dir);
}
void simple_permissions(char *dir_path, char *permissions)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        printf("ERROR\ninvalid path");
        return;
    }
    printf("SUCCESS\n");
    while ((dirEntry = readdir(dir)) != 0)
    {
        char permissions_aux[20] = "";
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
            struct stat file_info;
            if (stat(path, &file_info) == 0)
            {
                if (file_info.st_mode & S_IRUSR)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWUSR)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXUSR)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IRGRP)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWGRP)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXGRP)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IROTH)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWOTH)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXOTH)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (strcmp(permissions, permissions_aux) == 0)
                {
                    printf("%s\n", path);
                    // printf("Permissions: %o\n", file_info.st_mode & 0777);
                }
            }
        }
    }

    closedir(dir);
}
void recursive_permissions(char *dir_path, char *permissions)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];

    dir = opendir(dir_path);
    if (dir == NULL)
    {
        return;
    }

    while ((dirEntry = readdir(dir)) != 0)
    {
        char permissions_aux[20] = "";
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
            struct stat file_info;
            if (stat(path, &file_info) == 0)
            {
                if (file_info.st_mode & S_IRUSR)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWUSR)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXUSR)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IRGRP)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWGRP)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXGRP)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IROTH)

                    strcat(permissions_aux, "r");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IWOTH)

                    strcat(permissions_aux, "w");
                else
                    strcat(permissions_aux, "-");

                if (file_info.st_mode & S_IXOTH)

                    strcat(permissions_aux, "x");
                else
                    strcat(permissions_aux, "-");

                if (strcmp(permissions, permissions_aux) == 0)
                {
                    printf("%s\n", path);
                    // printf("Permissions: %o\n", file_info.st_mode & 0777);
                }
                if (S_ISDIR(file_info.st_mode))
                {
                    recursive_permissions(path, permissions);
                }
            }
        }
    }

    closedir(dir);
}
void parse(char *path)
{

    // int file = open(path, O_RDONLY);
    struct stat file_info;
    if (stat(path, &file_info) == 0)
    {
        if (S_ISREG(file_info.st_mode))
        {
        }
        else
        {
            printf("ERROR\nnot a file\n");
            return;
        }
    }
    int file = open(path, O_RDONLY);
    lseek(file, -6, SEEK_END); // move to the last 6 bytes
    char magic[5] = {0};
    int header_size = 0;
    read(file, &header_size, 2); // read header_size
    read(file, magic, 4);        // read magic

    if (strcmp(magic, "0Tr3") != 0)
    {
        printf("ERROR\nwrong magic\n");
        return;
    }
    lseek(file, -header_size, SEEK_END);
    int version = 0;
    read(file, &version, 4);
    if (version < 39 || version > 75)
    {
        printf("ERROR\nwrong version\n");
        return;
    }
    int no_of_sections = 0;

    read(file, &no_of_sections, 1);

    if (no_of_sections < 3 || no_of_sections > 15)
    {
        printf("ERROR\nwrong sect_nr\n");
        return;
    }
    char name[17][15] = {{0}};
    int type[17] = {0}, offset[17] = {0}, size[17] = {0};
    for (int i = 1; i <= no_of_sections; i++)
    {
        read(file, name[i], 14);
        read(file, &type[i], 2);
        int ok = 0;
        if (type[i] == 21 || type[i] == 47 || type[i] == 59 || type[i] == 15 || type[i] == 26 || type[i] == 46)
        {
            ok = 1;
        }
        if (ok == 0)
        {
            printf("ERROR\nwrong sect_types\n");
            return;
        }
        read(file, &offset[i], 4);
        read(file, &size[i], 4);
    }
    printf("SUCCESS\n");
    printf("version=%d\n", version);
    printf("nr_sections=%d\n", no_of_sections);
    for (int i = 1; i <= no_of_sections; i++)
    {
        printf("section%d: ", i);
        printf("%s ", name[i]);
        printf("%d ", type[i]);
        printf("%d\n", size[i]);
    }
}
void extract(char *path, int section_no, int line_no)
{

    struct stat file_info;
    if (stat(path, &file_info) == 0)
    {
        if (S_ISREG(file_info.st_mode))
        {
        }
        else
        {
            printf("ERROR\ninvalid file\n");
            return;
        }
    }
    int file = open(path, O_RDONLY);
    lseek(file, -6, SEEK_END);
    char magic[5] = {0};
    int header_size = 0;
    read(file, &header_size, 2);
    read(file, magic, 4);
    if (strcmp(magic, "0Tr3") != 0)
    {
        printf("ERROR\ninvalid file\n");
        return;
    }
    lseek(file, -header_size, SEEK_END);
    int version = 0;
    read(file, &version, 4);
    if (version < 39 || version > 75)
    {
        printf("ERROR\ninvalid file\n");
        return;
    }
    int no_of_sections = 0;

    read(file, &no_of_sections, 1);

    if (no_of_sections < 3 || no_of_sections > 15)
    {
        printf("ERROR\ninvalid file\n");
        return;
    }
    char name[17][15] = {{0}};
    int type[17] = {0}, offset[17] = {0}, size[17] = {0};
    for (int i = 1; i <= no_of_sections; i++)
    {
        read(file, name[i], 14);
        read(file, &type[i], 2);
        int ok = 0;
        if (type[i] == 21 || type[i] == 47 || type[i] == 59 || type[i] == 15 || type[i] == 26 || type[i] == 46)
        {
            ok = 1;
        }
        if (ok == 0)
        {
            printf("ERROR\ninvalid file\n");
            return;
        }
        read(file, &offset[i], 4);
        read(file, &size[i], 4);
    }

    if (section_no > no_of_sections)
    {
        printf("ERROR\ninvalid section\n");
        return;
    }
    lseek(file, offset[section_no], SEEK_SET);
    char *section_content = (char *)malloc(size[section_no]);

    read(file, section_content, size[section_no]);
    int count_lines = 0;
    char *ptr = section_content;
    while ((ptr = strstr(ptr, "\r\n")) != NULL)
    {
        count_lines++;
        ptr += strlen("\r\n"); // move to the next line
    }
    count_lines++;
    if (line_no > count_lines)
    {
        printf("ERROR\ninvalid line\n");
        return;
    }
    char *p;
    p = strtok(section_content, "\r\n");
    int i = 1;
    while (p != NULL)
    {
        if (i == count_lines - line_no + 1)
        {
            break;
        }
        i++;
        p = strtok(NULL, "\r\n");
    }

    char aux;
    int length = strlen(p);
    for (int i = 0; i < length / 2; i++)
    {
        aux = p[i];
        p[i] = p[length - i - 1];
        p[length - i - 1] = aux;
    }
    printf("SUCCESS\n%s\n", p);
    free(section_content);
}
void findall(char *dir_path)
{
    DIR *dir;
    struct dirent *dirEntry;
    char path[MAX_PATH_LEN];
    dir = opendir(dir_path);
    if (dir == NULL)
    {
        return;
    }

    while ((dirEntry = readdir(dir)) != 0)
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
        {
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir_path, dirEntry->d_name);
            struct stat file_info;
            if (lstat(path, &file_info) == 0 && S_ISLNK(file_info.st_mode))
            {
                continue;
            }
            if (stat(path, &file_info) == 0)
            {
                if (S_ISREG(file_info.st_mode))
                {
                    int max_lines = 0;
                    int file = open(path, O_RDONLY);
                    lseek(file, -6, SEEK_END);
                    char magic[5] = {0};
                    int header_size = 0;
                    read(file, &header_size, 2);
                    read(file, magic, 4);
                    if (strcmp(magic, "0Tr3") != 0)
                    {
                        // printf("%s\n", path);
                        // printf("ERROR\ninvalid file1\n");
                        break;
                    }
                    lseek(file, -header_size, SEEK_END);
                    int version = 0;
                    read(file, &version, 4);
                    if (version < 39 || version > 75)
                    {
                        // printf("ERROR\ninvalid file2\n");
                        break;
                    }
                    int no_of_sections = 0;

                    read(file, &no_of_sections, 1);

                    if (no_of_sections < 3 || no_of_sections > 15)
                    {
                        // printf("ERROR\ninvalid file3\n");
                        break;
                    }
                    char name[17][15] = {{0}};
                    int type[17] = {0}, offset[17] = {0}, size[17] = {0};
                    for (int i = 1; i <= no_of_sections; i++)
                    {
                        read(file, name[i], 14);
                        read(file, &type[i], 2);
                        int ok = 0;
                        if (type[i] == 21 || type[i] == 47 || type[i] == 59 || type[i] == 15 || type[i] == 26 || type[i] == 46)
                        {
                            ok = 1;
                        }
                        if (ok == 0)
                        {
                            // printf("ERROR\ninvalid file4\n");
                            break;
                        }
                        read(file, &offset[i], 4);
                        read(file, &size[i], 4);
                    }
                    for (int i = 1; i <= no_of_sections; i++)
                    {
                        lseek(file, offset[i], SEEK_SET);
                        char *section_content = (char *)malloc(size[i]);

                        read(file, section_content, size[i]);

                        int count_lines = 0;
                        char *ptr = section_content;
                        while ((ptr = strstr(ptr, "\r\n")) != NULL)
                        {
                            count_lines++;
                            ptr += strlen("\r\n");
                        }
                        count_lines++;
                        if (count_lines > max_lines)
                            max_lines = count_lines;
                        free(section_content);
                    }
                    if (max_lines > 16)
                    {
                        printf("%s\n", path);
                    }
                }
                else if (S_ISDIR(file_info.st_mode))
                {
                    findall(path);
                }
            }
        }
    }

    closedir(dir);
}

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        if (strcmp(argv[1], "variant") == 0) // variant
        {
            printf("33534\n");
        }
        if (strcmp(argv[1], "list") == 0) // list
        {
            if (argc == 3)
            {
                if (strncmp(argv[2], "path=", 5) == 0)
                {
                    char dir_path_aux[MAX_PATH_LEN];
                    char dir_path[MAX_PATH_LEN];
                    strcpy(dir_path_aux, argv[2]);
                    strcpy(dir_path, dir_path_aux + 5);
                    DIR *dir;
                    dir = opendir(dir_path);
                    if (dir == NULL)
                    {
                        printf("ERROR\ninvalid path");
                    }
                    else
                    {
                        printf("SUCCESS\n");
                        simple_listing(dir_path);
                    }
                    closedir(dir);
                }
                else
                {
                    printf("ERROR\ninvalid path");
                }
            }
            if (argc == 4)
            {
                if (strncmp(argv[2], "path=", 5) == 0)
                {
                    char dir_path_aux[MAX_PATH_LEN];
                    char dir_path[MAX_PATH_LEN];
                    strcpy(dir_path_aux, argv[2]);
                    strcpy(dir_path, dir_path_aux + 5);
                    if (strcmp(argv[3], "recursive") == 0)
                    {
                        DIR *dir;
                        dir = opendir(dir_path);
                        if (dir == NULL)
                        {
                            printf("ERROR\ninvalid path");
                        }
                        else
                        {
                            printf("SUCCESS\n");
                            recursive_listing(dir_path);
                        }
                        closedir(dir);
                    }
                    else if (strncmp(argv[3], "name_ends_with=", 15) == 0)
                    {
                        char name_end[100];
                        char name_end_aux[100];
                        strcpy(name_end_aux, argv[3]);
                        strcpy(name_end, name_end_aux + 15);
                        simple_name_ends_with(dir_path, name_end);
                    }
                    else if (strncmp(argv[3], "permissions=", 12) == 0)
                    {
                        char permissions[100];
                        char permissions_aux[100];
                        strcpy(permissions_aux, argv[3]);
                        strcpy(permissions, permissions_aux + 12);
                        simple_permissions(dir_path, permissions);
                    }
                }
                else if (strncmp(argv[3], "path=", 5) == 0)
                {
                    char dir_path_aux[MAX_PATH_LEN];
                    char dir_path[MAX_PATH_LEN];
                    strcpy(dir_path_aux, argv[3]);
                    strcpy(dir_path, dir_path_aux + 5);
                    if (strcmp(argv[2], "recursive") == 0)
                    {
                        DIR *dir;
                        dir = opendir(dir_path);
                        if (dir == NULL)
                        {
                            printf("ERROR\ninvalid path");
                        }
                        else
                        {
                            printf("SUCCESS\n");
                            recursive_listing(dir_path);
                        }
                        closedir(dir);
                    }
                    else if (strncmp(argv[2], "name_ends_with=", 15) == 0)
                    {
                        char name_end[100];
                        char name_end_aux[100];
                        strcpy(name_end_aux, argv[2]);
                        strcpy(name_end, name_end_aux + 15);
                        simple_name_ends_with(dir_path, name_end);
                    }
                    else if (strncmp(argv[2], "permissions=", 12) == 0)
                    {
                        char permissions[100];
                        char permissions_aux[100];
                        strcpy(permissions_aux, argv[2]);
                        strcpy(permissions, permissions_aux + 12);
                        simple_permissions(dir_path, permissions);
                    }
                }
                else
                {
                    printf("ERROR\n");
                    printf("path must be provided\n");
                }
            }
            if (argc == 5)
            {
                char dir_path[MAX_PATH_LEN];
                char name_end[100];
                char permissions[100];
                int aux_name = 0, aux_perm = 0, aux_rec = 0, aux_path = 0;
                for (int i = 2; i < argc; i++)
                {

                    if (strncmp(argv[i], "path=", 5) == 0)
                    {
                        char dir_path_aux[MAX_PATH_LEN];
                        strcpy(dir_path_aux, argv[i]);
                        strcpy(dir_path, dir_path_aux + 5);
                        aux_path = 1;
                    }
                    if (strncmp(argv[i], "permissions=", 12) == 0)
                    {
                        strcpy(permissions, argv[i]);
                        strcpy(permissions, permissions + 12);
                        aux_perm = 1;
                    }
                    if (strncmp(argv[i], "name_ends_with=", 15) == 0)
                    {
                        char name_end_aux[100];
                        strcpy(name_end_aux, argv[i]);
                        strcpy(name_end, name_end_aux + 15);
                        aux_name = 1;
                    }
                    if (strcmp(argv[i], "recursive") == 0)
                    {
                        aux_rec = 1;
                    }
                }
                if (aux_path == 1 && aux_rec == 1 && aux_name == 1)
                {
                    DIR *dir;
                    dir = opendir(dir_path);
                    if (dir == NULL)
                    {
                        printf("ERROR\ninvalid path");
                    }
                    else
                    {
                        printf("SUCCESS\n");
                        recursive_name_ends_with(dir_path, name_end);
                    }
                    closedir(dir);
                }
                else if (aux_path == 1 && aux_rec == 1 && aux_perm == 1)
                {
                    DIR *dir;
                    dir = opendir(dir_path);
                    if (dir == NULL)
                    {
                        printf("ERROR\ninvalid path");
                    }
                    else
                    {
                        printf("SUCCESS\n");
                        recursive_permissions(dir_path, permissions);
                    }
                    closedir(dir);
                }
                if (aux_path == 0)
                {
                    printf("ERROR\n");
                    printf("path must be provided\n");
                }
            }
        }
        if (strcmp(argv[1], "parse") == 0) // parse
        {
            if (strncmp(argv[2], "path=", 5) == 0)
            {
                char path_aux[MAX_PATH_LEN];
                char path[MAX_PATH_LEN];
                strcpy(path_aux, argv[2]);
                strcpy(path, path_aux + 5);
                parse(path);
            }
        }
        if (strcmp(argv[1], "extract") == 0) // extract
        {
            char path[MAX_PATH_LEN] = "";
            int section = -1;
            int line = -1;
            if (strncmp(argv[2], "path=", 5) == 0)
            {
                char path_aux[MAX_PATH_LEN];
                strcpy(path_aux, argv[2]);
                strcpy(path, path_aux + 5);
            }
            if (strncmp(argv[3], "section=", 8) == 0)
            {
                char section1[MAX_PATH_LEN];
                char section_aux[MAX_PATH_LEN];
                strcpy(section_aux, argv[3]);
                strcpy(section1, section_aux + 8);
                section = atoi(section1);
            }
            if (strncmp(argv[4], "line=", 5) == 0)
            {
                char line1[MAX_PATH_LEN];
                char line_aux[MAX_PATH_LEN];
                strcpy(line_aux, argv[4]);
                strcpy(line1, line_aux + 5);
                line = atoi(line1);
            }
            if (strcmp(path, "") != 0 && section != -1 && line != -1)
            {
                extract(path, section, line);
            }
            else
            {
                printf("ERROR\ninvalid file|section|line\n");
            }
        }
        if (strcmp(argv[1], "findall") == 0) // findall
        {
            if (strncmp(argv[2], "path=", 5) == 0)
            {
                char dir_path_aux[MAX_PATH_LEN];
                char dir_path[MAX_PATH_LEN];
                strcpy(dir_path_aux, argv[2]);
                strcpy(dir_path, dir_path_aux + 5);
                DIR *dir;
                dir = opendir(dir_path);
                if (dir == NULL)
                {
                    printf("ERROR\ninvalid path");
                }
                else
                {
                    printf("SUCCESS\n");
                    findall(dir_path);
                }
                closedir(dir);
            }
        }
    }

    return 0;
}
