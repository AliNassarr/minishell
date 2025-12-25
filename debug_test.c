#include <stdio.h>

int main() {
    char str[] = "echo \x01a\x02";
    int i = 0;
    
    printf("String contents:\n");
    while (str[i]) {
        if (str[i] == 1)
            printf("[\\x01]");
        else if (str[i] == 2)
            printf("[\\x02]");
        else
            printf("%c", str[i]);
        i++;
    }
    printf("\n");
    
    // Simulate wordsize
    i = 0;
    if (str[i] == '(') {
        printf("Starts with ( - extracting quoted content\n");
        i++;
        int size = 0;
        while (str[i] && str[i] != ')')
        {
            size++;
            i++;
        }
        printf("Size: %d\n", size);
    }
    
    return 0;
}
