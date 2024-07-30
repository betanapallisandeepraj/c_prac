#include <stdio.h>
#include <string.h>

int main() {
    char inputString[] = "Hello, World!sdfkjdskfkjdskfksdfkkjsdfkj";  // Replace this string with your own
    char asciiString[500]; // To hold ASCII values and commas
    int asciiStringLength = 0;  // Length of the resulting ASCII string

    printf("Original String: %s\n", inputString);

    for (int i = 0; inputString[i] != '\0'; i++) {
        if (i > 0) {
            asciiString[asciiStringLength] = ',';
            asciiStringLength++;
        }

        asciiStringLength += sprintf(asciiString + asciiStringLength, "%d", (int)inputString[i]);
    }

    asciiString[asciiStringLength] = '\0'; // Null-terminate the resulting string

    printf("ASCII Integer String: %s\n", asciiString);

    return 0;
}

