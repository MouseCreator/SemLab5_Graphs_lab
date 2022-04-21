#include "Header.h"

struct BitVector {
	unsigned bits;
	BitVector() { bits = 0; }

	bool get(std::size_t index) {
		return (bits >> index) & 1;
	}
	
	void set(std::size_t index, bool value) {
		if (value == true) {
			bits |= (1 << index);
		}
		else {
			bits &= ~(1 << index);
		}
	}
	void print() {
		std::string str;
		unsigned current = bits;
		for (std::size_t i = 0; i < 32; i++) {
			std::cout << (current & 1) << " ";
			current >>= 1;
		}
	}
};