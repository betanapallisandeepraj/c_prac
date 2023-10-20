#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

void sha512_hash(const char *input, char *output) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, input, strlen(input));
    SHA512_Final(hash, &sha512);
    
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", hash[i]);
    }
    output[128] = '\0';
}

int verify_license_file(const char *filename) {
    char stored_hash[129];
    char calculated_hash[129];
    char license_data[256];
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening license file");
        return -1; // Error opening file
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int line_count = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        line_count++;
        if (line_count == 1) {
            sscanf(line, "License Data: %[^\n]", license_data);
        } else if (line_count == 2) {
            sscanf(line, "SHA-512 Hash: %[^\n]", stored_hash);
        }
    }

    if (line) {
        free(line);
    }

    fclose(file);

    sha512_hash(license_data, calculated_hash);

    // Compare the stored hash with the calculated hash
    if (strcmp(stored_hash, calculated_hash) == 0) {
        return 0; // License is valid
    } else {
        return 1; // License is invalid
    }
}

int main() {
    int result = verify_license_file("license.lic");
    
    if (result == 0) {
        printf("License is valid.\n");
    } else {
        printf("License is invalid.\n");
    }

    return 0;
}

