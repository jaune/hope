#ifndef HOPE_CRYPTO_CRYPTO_H
#define HOPE_CRYPTO_CRYPTO_H

#include <stdint.h>

namespace hope {
namespace crypto {

	uint32_t crc32(unsigned char const *buffer, size_t length);

} /* namespace crypto */
} /* namespace hope */



#endif /* HOPE_CRYPTO_CRYPTO_H */