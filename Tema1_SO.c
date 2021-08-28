#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

/*void listRec(const char *path, int size, char *name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    int sizePath=0;
    //printf("%s",path);

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("ERROR");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        //printf("%s\n",entry->d_name);
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {   
                
                sizePath = statbuf.st_size;
                if(sizePath < size && (strncmp(entry->d_name, name, strlen(name))==0)){
                printf("%s\n", fullPath);
                }
                else{
                    printf("SUCCESS\n");
                }
                if (S_ISDIR(statbuf.st_mode))
                {
                    listRec(fullPath,size, name);
                }
            }
        }
    }
    closedir(dir);
}*/
void listRec1(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    // int succes = 0;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {
                printf("%s\n", fullPath);
                if (S_ISDIR(statbuf.st_mode))
                {
                    listRec1(fullPath);
                }
            }
        }
        //else
        //{
        //    succes = 1;
        //}
    }
    /* if ((entry = readdir(dir)) == NULL)
    {
        if (succes == 1)
        {
            printf("SUCCESS\n");
        }
    }*/
    closedir(dir);
}
void listRec2(const char *path, int size, char *successOut)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int succes = 0;
    char fullPath[512];
    struct stat statbuf;
    int sizePath = 0;
    //printf("%s",path);

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        //printf("%s\n",entry->d_name);
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {

                sizePath = statbuf.st_size;
                if (S_ISDIR(statbuf.st_mode) == 0)
                {
                    if (sizePath < size)
                    {
                        printf("%s\n", fullPath);
                    }
                    else
                    {
                        succes = 1;
                    }
                }
                if (S_ISDIR(statbuf.st_mode))
                {
                    listRec2(fullPath, size, successOut);
                }
            }
        }
    }
    if (succes == 1)
    {
        //printf("SUCCESS\n");
        *successOut = 1;
    }
    closedir(dir);
}

void listRec3(const char *path, char *name, char *successOut)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int succes = 0;
    char fullPath[512];
    struct stat statbuf;
    //printf("%s",path);

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR");
        printf("invalid directory path");
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        //printf("%s\n",entry->d_name);
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {
                //if (S_ISDIR(statbuf.st_mode) == 0)
                // {

                if (strncmp(entry->d_name, name, strlen(name)) == 0)
                {
                    printf("%s\n", fullPath);
                }
                else
                {
                    succes = 1;
                }
                //}
                if (S_ISDIR(statbuf.st_mode))
                {
                    listRec3(fullPath, name, successOut);
                }
            }
        }
    }
    if (succes == 1)
    {
        // printf("SUCCESS\n");
        *successOut = 1;
    }
    closedir(dir);
}

/*int listDir(const char *path, int size, const char *name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    struct stat st;
    char filePath[512];
    int sizePath;

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("ERROR");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(filePath, 512, "%s/%s", path, entry->d_name);
        if(stat(filePath, &st)==0)
                sizePath = st.st_size;
            else
                return -1;

        printf("%s",entry->d_name);
        printf("%d ",sizePath);
        
        if (sizePath < size && (strncmp(entry->d_name, name, strlen(name)) == 0))
        {
            printf("%s\n", filePath);
        }
        else
        {
            printf("SUCCESS\n");
        }
    }
    closedir(dir);
    return 0;
}*/
int listDir1(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char filePath[512];

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(filePath, 512, "%s/%s", path, entry->d_name);
            printf("%s\n", filePath);
        }
        else if (strcmp(entry->d_name, "..") == 0)
        {
            printf("SUCCESS\n");
        }
    }
    closedir(dir);
    return 0;
}
int listDir2(const char *path, int size)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    struct stat st;
    int succes = 0;
    char filePath[512];
    int sizePath = 0;

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(filePath, 512, "%s/%s", path, entry->d_name);
            if (stat(filePath, &st) == 0)
                sizePath = st.st_size;
            else
                return -1;

            if (S_ISDIR(st.st_mode) == 0)
            {
                if (sizePath < size)
                {
                    printf("%s\n", filePath);
                }
                else
                {
                    succes = 1;
                }
            }
        }
    }
    if (succes == 1)
    {
        printf("SUCCESS\n");
    }
    closedir(dir);
    return 0;
}
int listDir3(const char *path, const char *name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    struct stat st;
    int succes = 0;
    char filePath[512];

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(filePath, 512, "%s/%s", path, entry->d_name);

            if (lstat(filePath, &st) == 0)
            {
                if (S_ISDIR(st.st_mode) == 0)
                {
                    if (strncmp(entry->d_name, name, strlen(name)) == 0)
                    {
                        printf("%s\n", filePath);
                    }
                    else
                    {
                        succes = 1;
                    }
                }
                else
                {
                    if (strncmp(entry->d_name, name, strlen(name)) == 0)
                    {
                        printf("%s\n", filePath);
                    }
                }
            }
        }
    }
    if (succes == 1)
    {
        printf("SUCCESS\n");
    }
    closedir(dir);
    return 0;
}
int sizeDir(const char *path)
{
    int fd;
    off_t size;
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("Could not open input file");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    return (int)size;
    close(fd);
}
int parseFile(char *path)
{
    int fd = -1;
    int vers = 0, nrSect = 0, sectType = 0, sectOffset = 0, sectSize = 0, headerSize = 0;
    int magic = 0;
    char sectName[13] = {0};
    fd = open(path, O_RDONLY);
    //int ok=1;
    if (fd == -1)
    {
        printf("ERROR\n");
        printf("invalid input directory");
        return -5;
    }

    lseek(fd, -3, SEEK_END);
    read(fd, &headerSize, 2);
    //printf("%d\n",headerSize);
    read(fd, &magic, 1);
    //printf("%d", magic);
    if (magic != 'x')
    { //magic!='x'
        //ok=0;
        printf("ERROR\n");
        printf("wrong magic");
        exit(-5);
    }

    lseek(fd, -headerSize, SEEK_CUR);
    read(fd, &vers, 4);
    if (vers < 92 || vers > 156)
    {
        //ok=0;
        printf("ERROR\n");
        printf("wrong version");
        exit(-5);
    }
    read(fd, &nrSect, 1);
    if (nrSect < 7 || nrSect > 15)
    {
        //ok=0;
        printf("ERROR\n");
        printf("wrong sect_nr");
        exit(-5);
    }

    int t = 0;
    while (t < nrSect)
    {
        //printf("%d\n",t);
        read(fd, sectName, 12);
        //printf("%s\n",sectName);
        read(fd, &sectType, 4);
        //printf("%d\n",sectType);
        read(fd, &sectOffset, 4);
        //printf("%d\n",sectOffset);
        read(fd, &sectSize, 4);
        //printf("%d\n",sectSize);
        //printf("%d\n",sectType);

        if (sectType != 47 && sectType != 74 && sectType != 39 && sectType != 72)
        {
            //ok=0;
            printf("ERROR\n");
            printf("wrong sect_types");
            exit(-5);
        }

        t++;
    }
    //printf("aaaa");
    lseek(fd, -24 * nrSect, SEEK_CUR);
    printf("SUCCESS\n");
    printf("version=%d\n", vers);
    printf("nr_sections=%d\n", nrSect);

    int k = 0;
    while (k < nrSect)
    {
        //printf("%d\n",t);
        read(fd, sectName, 12);
        //printf("%s\n",sectName);
        read(fd, &sectType, 4);
        //printf("%d\n",sectType);
        read(fd, &sectOffset, 4);
        //printf("%d\n",sectOffset);
        read(fd, &sectSize, 4);
        //printf("%d\n",sectSize);

        printf("section%d: %s %d %d\n", k + 1, sectName, sectType, sectSize);
        k++;
    }
    close(fd);
    return 0;
}
char *strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}
int extractFile(char *path, int nrSect1, int line)
{
    int fd = -1;
    int vers = 0, nrSect = 0, sectType = 0, sectOffset = 0, sectSize = 0, headerSize = 0;
    int magic = 0;
    char sectName[13] = {0};
    char linie[100] = {0};
    fd = open(path, O_RDONLY);
    //int ok=1;
    if (fd == -1)
    {
        printf("ERROR\n");
        printf("invalid file");
        return -5;
    }
    if (nrSect < 0)
    {
        printf("EROPR\n");
        printf("invalid section");
        return -5;
    }
    if (line < 1)
    {
        printf("ERROR\n");
        printf("invalid line");
        return -5;
    }

    lseek(fd, -3, SEEK_END);
    read(fd, &headerSize, 2);
    //printf("%d\n",headerSize);
    read(fd, &magic, 1);
    //printf("%d", magic);
    if (magic != 'x')
    { //magic!='x'
        //ok=0;
        printf("ERROR\n");
        printf("invalid file");
        exit(-5);
    }

    lseek(fd, -headerSize, SEEK_CUR);
    read(fd, &vers, 4);
    if (vers < 92 || vers > 156)
    {
        //ok=0;
        printf("ERROR\n");
        printf("invalid file");
        exit(-5);
    }
    read(fd, &nrSect, 1);
    if (nrSect < 7 || nrSect > 15)
    {
        //ok=0;
        printf("ERROR\n");
        printf("invalid file");
        exit(-5);
    }

    int t = 1;
    int marime = 0;
    while (t <= nrSect1)
    {
        //printf("%d\n",t);
        read(fd, sectName, 12);
        //printf("%s\n",sectName);
        read(fd, &sectType, 4);
        //printf("%d\n",sectType);
        read(fd, &sectOffset, 4);
        //printf("%d\n",sectOffset);
        read(fd, &sectSize, 4);
        marime += sectSize;
        //printf("%d\n",sectSize);
        //printf("%d\n",sectType);

        if (sectType != 47 && sectType != 74 && sectType != 39 && sectType != 72)
        {
            //ok=0;
            printf("ERROR\n");
            printf("invalid file");
            exit(-5);
        }

        t++;
    }
    char c;
    printf("%s\n", sectName);
    printf("size:%d\n", sectSize);
    printf("%d\n", marime);
    lseek(fd, marime - sectSize, SEEK_SET);
    //read(fd, &c, 1);
    //strncat(linie,&c,1);
        while (c != '\n')
        {
            read(fd, &c, 1);
            strncat(linie, &c, 1);
        }


            printf("Linie:%s", linie);
        
    close(fd);
    return 0;
}
int findAll(const char *path, char *successOut)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    //printf("%s",path);

    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ERROR\n");
        printf("invalid directory path");
        return -5;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        //printf("%s\n",entry->d_name);
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if (lstat(fullPath, &statbuf) == 0)
            {

                if (S_ISDIR(statbuf.st_mode) == 0)
                {

                    int fd = -1;
                    int vers = 0, nrSect = 0, sectType = 0, sectOffset = 0, sectSize = 0, headerSize = 0;
                    int succes = 0;
                    int magic = 0;
                    char sectName[13] = {0};
                    fd = open(fullPath, O_RDONLY);
                    if (fd == -1)
                    {
                        printf("ERROR\n");
                        printf("invalid input directory");
                        //return -5;
                    }

                    lseek(fd, -3, SEEK_END);
                    read(fd, &headerSize, 2);
                    //printf("%d\n",headerSize);
                    read(fd, &magic, 1);
                    //printf("%d", magic);
                    if (magic != 'x')
                    { //magic!='x'
                        //ok=0;
                        printf("ERROR\n");
                        printf("wrong magic");
                        //exit(-5);
                    }

                    lseek(fd, -headerSize, SEEK_CUR);
                    read(fd, &vers, 4);
                    if (vers < 92 || vers > 156)
                    {
                        //ok=0;
                        printf("ERROR\n");
                        printf("wrong version");
                        //exit(-5);
                    }
                    read(fd, &nrSect, 1);
                    if (nrSect < 7 || nrSect > 15)
                    {
                        //ok=0;
                        printf("ERROR\n");
                        printf("wrong sect_nr");
                        //exit(-5);
                    }

                    int t = 0;
                    while (t < nrSect)
                    {
                        //printf("%d\n",t);
                        read(fd, sectName, 12);
                        //printf("%s\n",sectName);
                        read(fd, &sectType, 4);
                        //printf("%d\n",sectType);
                        read(fd, &sectOffset, 4);
                        //printf("%d\n",sectOffset);
                        read(fd, &sectSize, 4);
                        // if (sectSize > 940)
                        // {
                        //     succes = 1;
                        //     return -5;
                        // }
                        //printf("%d\n",sectSize);
                        //printf("%d\n",sectType);

                        if (sectType != 47 && sectType != 74 && sectType != 39 && sectType != 72)
                        {
                            printf("ERROR\n");
                            printf("wrong sect_types");
                            //exit(-5);
                        }

                        t++;
                    }
                //     //printf("%s\n", fullPath);

                //     close(fd);

                    if (succes == 0)
                    {
                        
                        *successOut = 0;
                    }
                }
                if (S_ISDIR(statbuf.st_mode))
                {
                    findAll(fullPath, successOut);
                }
            }
        }
    }
    closedir(dir);

    return 0;
}

int main(int argc, char **argv)
{
    char *token = NULL;
    char *path = NULL;
    char *name = NULL;
    int recurs = 0;
    int size = 0;
    int flagSize = 0;
    int flagNume = 0;
    if (argc >= 2)
    {
        if (strcmp(argv[1], "variant") == 0)
        {
            printf("75219\n");
        }
        else if (strcmp(argv[1], "list") == 0)
        {
            int j = 2;

            while (j < argc)
            {
                if (strchr(argv[j], '=') != NULL)
                {
                    token = strtok(argv[j], "=");
                    if (strcmp(token, "path") == 0)
                    {
                        path = strtok(NULL, "=");
                        //printf("Calea este %s", path);
                    }
                    else if (strcmp(token, "size_smaller") == 0)
                    {
                        size = atoi(strtok(NULL, "="));
                        flagSize = 1;
                        //printf("Dimensiunea este %d", size);
                    }
                    else if (strcmp(token, "name_starts_with") == 0)
                    {
                        name = strtok(NULL, "=");
                        flagNume = 1;
                        //printf("Numele este %s ",name);
                    }
                }
                if (strcmp(argv[j], "recursive") == 0)
                {
                    recurs = 1;
                }
                j++;
            }
            if (recurs == 1)
            {
                if (flagSize == 0 && flagNume == 0)
                {
                    printf("SUCCESS\n");
                    listRec1(path);
                }
                else if (flagSize == 1 && flagNume == 0)
                {
                    char success = 0;
                    listRec2(path, size, &success);
                    if (success == 1)
                    {
                        printf("SUCCESS\n");
                    }
                }
                else if (flagSize == 0 && flagNume == 1)
                {
                    char successOut = 0;
                    listRec3(path, name, &successOut);
                    if (successOut == 1)
                    {
                        printf("SUCCESS\n");
                    }
                }
            }
            else
            {
                if (flagSize == 0 && flagNume == 0)
                    listDir1(path);
                else if (flagSize == 1 && flagNume == 0)
                    listDir2(path, size);
                else if (flagSize == 0 && flagNume == 1)
                    listDir3(path, name);
            }
        }
        else if (strcmp(argv[1], "parse") == 0)
        {
            int j = 1;
            while (j < argc)
            {
                if (strchr(argv[j], '=') != NULL)
                {
                    token = strtok(argv[j], "=");
                    //printf("Calea este %s", token);
                    if (strcmp(token, "path") == 0)
                    {
                        path = strtok(NULL, "=");
                        //printf("Calea este %s", path);
                        parseFile(path);
                    }
                }
                j++;
            }
        }
        else if (strcmp(argv[1], "extract") == 0)
        {
            int j = 1;
            int sectNr = 0;
            int line = 0;
            while (j < argc)
            {
                if (strchr(argv[j], '=') != NULL)
                {
                    token = strtok(argv[j], "=");
                    //printf("Calea este %s", token);
                    if (strcmp(token, "path") == 0)
                    {
                        path = strtok(NULL, "=");
                        //printf("Calea este %s", path);
                    }
                    else if (strcmp(token, "section") == 0)
                    {
                        sectNr = atoi(strtok(NULL, "="));
                    }
                    else if (strcmp(token, "line") == 0)
                    {
                        line = atoi(strtok(NULL, "="));
                    }
                }
                j++;
            }
            extractFile(path, sectNr, line);
        }
        else if (strcmp(argv[1], "findall") == 0)
        {
            int j = 1;
            while (j < argc)
            {
                if (strchr(argv[j], '=') != NULL)
                {
                    token = strtok(argv[j], "=");
                    //printf("Calea este %s", token);
                    if (strcmp(token, "path") == 0)
                    {
                        char successOut = 0;
                        path = strtok(NULL, "=");
                        //printf("Calea este %s", path);
                        findAll(path, &successOut);
                        if (successOut == 0)
                        {
                            printf("SUCCESS\n");
                        }
                    }
                }
                j++;
            }
        }
    }
    return 0;
}