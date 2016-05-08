#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>

#define ITERATIONS (100000) 

void hash_letter(char letter, uint32_t salt, char * buffer);
bool check_password(char * filename, char * password);

int main (int argc, char *argv[]) {
	if ((argc != 2) || ((argc == 2) && strlen(argv[1]) > 4)) {
		printf ("Syntax:\ttimeside <pin>\n");
		printf ("\tWhere <pin> is a number up to 4 digits.\n");
		printf ("\tReturns 1 if the pin is correct, 0 o/w.\n");
	}
	else {
		if (check_password("passfile.dat", argv[1]) == true) {
			printf ("1\n");
		}
		else {
			printf ("0\n");
		}
	}

	return 0;
}

bool check_password(char * filename, char * password) {
	FILE * fh;
	int letter;
	char hash[SHA_DIGEST_LENGTH];
	char check[SHA_DIGEST_LENGTH];
	uint32_t salt;
	bool same;
	int pos;
	
	// Load the password file
	same = false;
	fh = fopen(filename, "rb");
	if (fh != NULL) {
		same = true;
		letter = 0;
		while (same && !feof(fh) && letter < strlen(password)) {
			// Read salted hash from file
			fread(& salt, sizeof(uint32_t), 1, fh);
			fread(hash, sizeof(char), SHA_DIGEST_LENGTH, fh);

			// Generate the hashed digit
			hash_letter(password[letter], salt, check);

			// Are they the same??
			for (pos = 0; (pos < SHA_DIGEST_LENGTH) && (hash[pos] == check[pos]); pos++);
			same = (pos == SHA_DIGEST_LENGTH);
			letter++;
		}
		fclose(fh);
	}
	
	return same;
}

void hash_letter(char letter, uint32_t salt, char * buffer) {
	// Use lots of iterations to mitigate brute force attacks
	PKCS5_PBKDF2_HMAC(& letter, 1, (char *)(& salt), sizeof(uint32_t), ITERATIONS, EVP_sha512(), SHA_DIGEST_LENGTH, buffer);
}
