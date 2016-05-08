#include <string.h>
#include <sys/time.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdint.h>

#define ITERATIONS (100000) 

void output_hashes(char * filename, char * password);
void hash_letter(char letter, uint32_t salt, char * buffer);

int main (int argc, char *argv[]) {

	output_hashes("passfile.dat", "4534");

	return 0;
}

void hash_letter(char letter, uint32_t salt, char * buffer) {
	// Use lots of iterations to mitigate brute force attacks
	PKCS5_PBKDF2_HMAC(& letter, 1, (char *)(& salt), sizeof(uint32_t), ITERATIONS, EVP_sha512(), SHA_DIGEST_LENGTH, buffer);
}

void output_hashes(char * filename, char * password) {
	FILE * fh;
	int letter;
	size_t length;
	char hash[SHA_DIGEST_LENGTH];
	uint32_t salt = 23232u;
	
	fh = fopen(filename, "wb");
	if (fh != NULL) {
		length = strlen(password);
		for (letter = 0; letter < length; letter++) {
			hash_letter(password[letter], salt, hash);
			fwrite (& salt, sizeof(uint32_t), 1, fh);
			fwrite (hash, sizeof(char), SHA_DIGEST_LENGTH, fh);
			salt += 1;
		}
		fclose(fh);
	}
}
