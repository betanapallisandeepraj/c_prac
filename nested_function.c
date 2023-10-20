#include <stdio.h>

void outerFunction() {
    // Declaration of the nested function (local function)
    void nestedFunction() {
        printf("This is the nested function.\n");
    }

    printf("This is the outer function.\n");
    nestedFunction(); // Call the nested function
}

int main() {
    outerFunction();
    return 0;
}

