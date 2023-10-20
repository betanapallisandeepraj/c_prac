#!/bin/bash

# For RSA
# Encrypt a message using the recipient's public key
openssl rsautl -encrypt -pubin -inkey recipient_public.pem -in plaintext.txt -out encrypted.bin
# Decrypt the message using your private key
openssl rsautl -decrypt -inkey your_private.pem -in encrypted.bin -out decrypted.txt



# For AES
# Input data
plaintext="This is a secret message."
# Encryption
openssl enc -aes-256-cbc -salt -in <(echo -n $plaintext) -out encrypted.bin -pass pass:yourpassword
echo "Encryption complete."
# Decryption
decrypted=$(openssl enc -d -aes-256-cbc -in encrypted.bin -pass pass:yourpassword)
echo "Decrypted message: $decrypted"


# For SHA-512
# Specify the file for which you want to compute the SHA-512 hash
file="yourfile.txt"
# Calculate the SHA-512 hash
hash=$(sha512sum "$file" | awk '{print $1}')
# Print the SHA-512 hash
echo "SHA-512 Hash: $hash"
# Specify the input string
input="This is a test string."
# Calculate the SHA-512 hash of the input string
hash=$(echo -n "$input" | sha512sum | awk '{print $1}')
# Print the SHA-512 hash
echo "SHA-512 Hash: $hash"



