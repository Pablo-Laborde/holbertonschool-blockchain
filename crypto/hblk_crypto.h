#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H


#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/obj_mac.h> /* Here is where NID_secp256k1 is defined */
#include <openssl/sha.h>


#include <errno.h>
#include <stdint.h>
#include <string.h>


# define EC_CURVE   NID_secp256k1

/* EC_KEY public key octet string length (using 256-bit curve) */
# define EC_PUB_LEN 65
/* Maximum signature octet string length (using 256-bit curve) */
# define SIG_MAX_LEN    72

# define PRI_FILENAME   "key.pem"
# define PUB_FILENAME   "key_pub.pem"

/**
 * struct sig_s - EC Signature structure
 *
 * @sig: Signature buffer. The whole space may not be used
 * @len: Actual signature size. Can't exceed SIG_MAX_LEN,
 * therefore stored on a byte
 */
typedef struct sig_s
{
	/*
	 * @sig must stay first, so we can directly use the structure as
	 * an array of char
	 */
	uint8_t     sig[SIG_MAX_LEN];
	uint8_t     len;
} sig_t;

/* Functions */

	/* sha256.c */
		uint8_t *sha256(int8_t const *s, size_t len,
						uint8_t digest[SHA256_DIGEST_LENGTH]);
		void *sha256_errors(int error);

	/* ec_create.c */
		EC_KEY *ec_create(void);
		void *ec_create_errors(int error);

	/* ec_to_pub.c */
		uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
		void *ec_to_pub_errors(int error);

	/* ec_from_pub.c */
		EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);
		void *ec_from_pub_errors(int error);


#endif
