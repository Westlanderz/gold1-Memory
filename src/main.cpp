#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <array>
#include <string>
#include <vector>
#include <iostream>

static size_t LINE_LENGTH_BYTES = 16;

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	// DATA
	int a = 2;
	int b = 20;
	int c = 200;
	int d = a + b + c;
	(void)d;

	std::string s = "Hello World!";

	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	// END DATA

	uint32_t amountOfBytes = 0;

	// Ask user for the width of the bytes on one line
	std::cout << "Enter the width of the bytes on one line (recommended 16): ";
	std::cin >> LINE_LENGTH_BYTES;
	
	// Ask user for the amount of bytes to print
	std::cout << "Enter the amount of bytes you want to display (0 for all): ";
	std::cin >> amountOfBytes;

	auto print_line = [](void* buf, size_t size) {
		int count = 1;
		// Show address in fornt of line
		std::cout << std::hex << (void*)buf << std::dec << " :   ";
		for(size_t i = 0; i < LINE_LENGTH_BYTES; i++) {
			if(i < size) {
				printf("%02X ", ((uint8_t *)buf)[i]);
			} else {
				printf("   ");
			}

			if(count == 8) {
				printf("  ");
				count = 0;
			}
			count++;
		}

		printf("  |");

		for(size_t i = 0; i < size; i++) {
			if(isprint(((uint8_t *)buf)[i])) {
				putchar(((uint8_t *)buf)[i]);
			} else {
				putchar('.');
			}
		}

		putchar('|');
		putchar('\n');
	};

	std::array<void *, 0xFFFF> contents;
	if(amountOfBytes == 0) {
		amountOfBytes = 0xFFFF;
	}
	size_t contents_size = amountOfBytes;

	contents[0] = (void*)&main;
	print_line(contents[0], LINE_LENGTH_BYTES);

	for(unsigned long int i = 1; i < contents_size / LINE_LENGTH_BYTES; i++) {
		contents[i] = contents[i - 1] + LINE_LENGTH_BYTES;
		print_line(contents[i], LINE_LENGTH_BYTES);
	}

	return 0;
}

