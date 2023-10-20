#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    // Load the public key
    RSA *rsa = NULL;
    FILE *file = fopen("public.pem", "rb");
    rsa = PEM_read_RSA_PUBKEY(file, &rsa, NULL, NULL);
    fclose(file);

    if (rsa == NULL) {
        fprintf(stderr, "Error loading the public key.\n");
        return 1;
    }

    // Input data
    const char *data = "Hello, RSA!";
    unsigned char encrypted[2048]; // RSA has limitations on data size
    int encrypted_len = RSA_public_encrypt(strlen(data) + 1, (const unsigned char *)data, encrypted, rsa, RSA_PKCS1_PADDING);

    if (encrypted_len == -1) {
        fprintf(stderr, "RSA encryption failed.\n");
        return 1;
    }

    // Load the private key
    file = fopen("private.pem", "rb");
    rsa = PEM_read_RSAPrivateKey(file, &rsa, NULL, NULL);
    fclose(file);

    if (rsa == NULL) {
        fprintf(stderr, "Error loading the private key.\n");
        return 1;
    }
    // printf("%d,%ld\n",encrypted_len,strlen(encrypted));
    unsigned char decrypted[2048];
    int decrypted_len = RSA_private_decrypt(encrypted_len, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);

    if (decrypted_len == -1) {
        fprintf(stderr, "RSA decryption failed.\n");
        return 1;
    }

    printf("Original Data: %s\n", data);
    printf("Encrypted Data: %s\n", encrypted);
    printf("Decrypted Data: %s\n", decrypted);

    RSA_free(rsa);
    return 0;
}
