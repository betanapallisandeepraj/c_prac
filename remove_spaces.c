#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeSpaces(char *input) {
    int i, j = 0;
    
    for (i = 0; input[i] != '\0'; i++) {
        if (!isspace((unsigned char)input[i])) {
            input[j] = input[i];
            j++;
        }
    }
    
    input[j] = '\0'; // Null-terminate the modified string
}

int main() {
    char buffer[100] = "This is a sample string with spaces.";
    
    printf("Original: %s\n", buffer);
    removeSpaces(buffer);
    printf("Modified: %s\n", buffer);
    
    return 0;
}

