all:
	gcc 01_generate_sha512_hash.c -o 01_generate_sha512_hash -lssl -lcrypto
	gcc 02_verify_sha512_hash.c -o 02_verify_sha512_hash -lssl -lcrypto
	gcc 03_encrypt_decrypt_aes.c -o 03_encrypt_decrypt_aes -lcrypto
	gcc 04_encrypt_decrypt_rsa.c -o 04_encrypt_decrypt_rsa -lssl -lcrypto
	openssl genpkey -algorithm RSA -out private.pem
	openssl rsa -pubout -in private.pem -out public.pem

clean:
	rm 01_generate_sha512_hash 02_verify_sha512_hash 03_encrypt_decrypt_aes 04_encrypt_decrypt_rsa

distclean:
	rm 01_generate_sha512_hash 02_verify_sha512_hash 03_encrypt_decrypt_aes 04_encrypt_decrypt_rsa license.lic private.pem public.pem
