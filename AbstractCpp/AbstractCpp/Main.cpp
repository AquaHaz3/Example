
#include <vector>
#include <iostream>
#include "binary/BasicCrypto.h"
#include "binary/CryptoLevel1.h"

//int main()
//{
//	for (int i = 0; i < 256; i++) {
//		uint8_t hash = simple8(i);
//		uint8_t collision = find_collision_8(get_lazy8(hash));
//		uint8_t rehash = simple8(collision);
//		std::cout << crypto::bin8(i) << " -> "
//			<< crypto::bin8(hash)
//			<< " ? " << crypto::bin8(rehash)
//			<< " {" << crypto::bin8(collision) << "}";
//		if (hash != rehash) std::cout << " X";
//		std::cout << '\n';
//	}
//}

uint8_t buf[8] = { 0 };
uint16_t temp[8] = { 0 };

int main() {

	const char* str = "123456789";
	int len = 9;
	int base = 10;

	int j = 0;
	uint32_t t = 0;
	for (int i = 0; i < len; i++) {
		temp[j] += (str[i] - '0');
		t = temp[j] * 10;
		temp[j + 1] += t >> 8;
		for (int k = j + 1; k < 8; k++) {
			if (temp[k] > 255) {
				temp[k + 1] += temp[k] >> 8;
				temp[k] = temp[k] & 0xff;
			}
			if (i < len - k - 1) temp[k] *= 10;
		}
		if (i == len - 1) break;
		temp[j] = t & 0xff;
	}

	printf("%x\n", t);

	for (int i = 0; i < 8; i++) {
		printf("%x ", temp[i]);
	}

}