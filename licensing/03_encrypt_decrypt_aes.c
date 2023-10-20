#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

// AES encryption function
int aes_encrypt(const char *plaintext, const char *key, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len, ciphertext_len;

    // Create and initialize the context
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return -1;
    }

    // Initialize the encryption operation
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    // Provide the plaintext to be encrypted
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, strlen(plaintext))) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len = len;

    // Finalize the encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

// AES decryption function
int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len, const char *key, char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len, plaintext_len;

    // Create and initialize the context
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return -1;
    }

    // Initialize the decryption operation
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    // Provide the ciphertext to be decrypted
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len = len;

    // Finalize the decryption
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main() {
    const char *key = "0123456789abcdefg"; // 128-bit key
    const char *plaintext = "Hello, AES!";
    unsigned char ciphertext[128];
    char decrypted_text[128];

    int ciphertext_len = aes_encrypt(plaintext, key, ciphertext);
    if (ciphertext_len < 0) {
        printf("Encryption failed.\n");
        return 1;
    }
    
    int decrypted_len = aes_decrypt(ciphertext, ciphertext_len, key, decrypted_text);
    if (decrypted_len < 0) {
        printf("Decryption failed.\n");
        return 1;
    }

    decrypted_text[decrypted_len] = '\0';
    
    printf("Original Text: %s\n", plaintext);
    printf("Encrypted Text: ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}
