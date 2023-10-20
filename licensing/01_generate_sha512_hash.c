#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main() {
    char license_data[] = "I am happy"; // Replace with your license data
    char calculated_hash[129];
    
    sha512_hash(license_data, calculated_hash);
    
    // Create and write the license file
    FILE *file = fopen("license.lic", "w");
    if (file == NULL) {
        perror("Error creating license file");
        return 1;
    }

    fprintf(file, "License Data: %s\n", license_data);
    fprintf(file, "SHA-512 Hash: %s\n", calculated_hash);

    fclose(file);

    printf("License file 'license.lic' has been generated.\n");

    return 0;
}

