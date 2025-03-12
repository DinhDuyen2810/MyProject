//#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>  

void append(char **source, const char *add) {
    int srclen = ((*source == NULL) ? 0 : strlen(*source));
    int len = srclen + strlen(add) + 1;
    *source = (char *)realloc(*source, len);
    if (srclen == 0) {
        strcpy(*source, add);
    } else {
        strcat(*source, add);
    }
    memset(*source + len - 1, 0, 1);
}


int compare(const struct dirent **a, const struct dirent **b) {
    return strcmp((*a)->d_name, (*b)->d_name);
}

int main() {
    struct dirent **nameList;
    int n = scandir(".", &nameList, NULL, compare);
    
    if (n < 0) {
        perror("scandir");
        return 1;
    }
    char *path = nullptr;
    append(&path, "<html>\n<body>\n");
    for (int i = 0; i < n; i++) {
        if(nameList[i]->d_type == DT_REG){
            append(&path, "<i>");
            append(&path, nameList[i]->d_name);
            append(&path, "</i>\n");
        } else if(nameList[i]->d_type == DT_DIR){
            append(&path, "<b>");
            append(&path, nameList[i]->d_name);
            append(&path, "</b>\n");
        }
        free(nameList[i]);
    }
    append(&path, "</body>\n</html>\n");
    free(nameList);  // Giải phóng bộ nhớ cấp phát động
    printf("%s", path);
    return 0;
}
