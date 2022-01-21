// #include <string>
// #include <iostream>
// #include <iomanip>
// #include <vector>

// void CheckWidth(int *, int);
// template<typename T>
// void PrintBytes(T, int*, int);

// int main(void) {
// 	int a = 2;
// 	int b = 20;
// 	int c = 200;
// 	int d = a + b + c;

// 	std::string s = "Hello World!";

// 	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 	// Ask user for the width of the bytes on one line
// 	int width = 0;
// 	std::cout << "Enter the width of the bytes on one line: ";
// 	std::cin >> width;

// 	int bytes = 0;

// 	// Print the bytes
// 	for(long unsigned int i = 0; i < s.length(); i++) {
// 		std::cout << std::hex << s[i] << " ";
// 		CheckWidth(&bytes, width);
// 	}
// 	std::cout << std::hex << a << " ";
// 	CheckWidth(&bytes, width);
// 	std::cout << std::hex << b << " ";
// 	CheckWidth(&bytes, width);
// 	std::cout << std::hex << c << " ";
// 	CheckWidth(&bytes, width);
// 	std::cout << std::hex << d << " ";
// 	CheckWidth(&bytes, width);

// 	std::cout << std::endl;
// }

// void CheckWidth(int *bytes, int width) {
// 	(*bytes)++;
// 	if(*bytes == width) {
// 		std::cout << "\n";
// 		*bytes = 0;
// 	}
// }

// template<typename T>
// void PrintBytes(T t, int *bytes, int width) {
// 	std::cout << std::hex << t << " ";
// 	CheckWidth(bytes, width);
// }

// #include <AK/Array.h>
// #include <LibCore/ArgsParser.h>
// #include <LibCore/File.h>
// #include <LibMain/Main.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <sys/resource.h>
#include <array>
#include <span>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

void trace() {
	struct stackframe {
		struct stackframe* rbp;
		uint64_t rip;
	};
	struct stackframe *stk;
	asm ("movq %%rbp,%0" : "=r"(stk) ::);

	for(unsigned int frame = 0; stk && frame < 0xFF; ++frame)
	{
		std::cout << "trace " << frame << " dec " << std::hex << stk->rip << std::dec << std::endl;
		stk = stk->rbp;
	}
}

void urmom2() {
	trace();
}

void urmom1() {
	urmom2();
}

static size_t LINE_LENGTH_BYTES = 16;

int main(int argc, char *argv[]) {
	std::cout << (void*)&main << '\n';
	// return 0;
	// void *sucky = malloc(0x100000);
	// std::cout << std::hex << sucky << std::dec << std::endl;
	// memset(sucky, 0xFF, 0x100000);

	// return 0;
	// DATA
	int a = 2;
	int b = 20;
	int c = 200;
	int d = a + b + c;

	std::string s = "Hello World!";

	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	std::string path;
	uint32_t amountOfBytes = 0;

	// urmom1();
	// return 0;


	// Ask user for the width of the bytes on one line
	std::cout << "Enter the width of the bytes on one line: (default 16) ";
	std::cin >> LINE_LENGTH_BYTES;
	
	// Ask user for the amount of bytes to print
	std::cout << "Enter the amount of bytes you want to display: (0 for all)";
	std::cin >> amountOfBytes;

	std::streampos size;
  	uint8_t *memblock;

	// Read in file
	// FILE *file;
	std::ifstream file;

	// if(path.empty()) {
	// 	file = stdin;
	// } else {
	// 	file = fopen(path.c_str(), "r");
	// }

	// 0x32423dd
	// for() {
	// 
	//}


	// file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

	// if (file.is_open()) {
	// 	size = file.tellg();
	// 	memblock = new uint8_t[size];
	// 	file.seekg(0, std::ios::beg);
	// 	file.read((char *)memblock, size);
	// 	file.close();

	// 	// std::cout << "the entire file content is in memory";

	// 	// delete[] memblock;
	// } else if(!file) {
	// 	std::cout << "Could not open file" << std::endl;
	// 	return 1;
	// }

	auto print_line = [](void* buf, size_t size_) {
		assert(size_ <= LINE_LENGTH_BYTES);
		int count = 1;
		// Show address in fornt of line
		std::cout << std::hex << (void*)buf << std::dec << " :   ";
		for(size_t i = 0; i < LINE_LENGTH_BYTES; ++i) {
			if (i < size_)
				printf("%02X ", ((uint8_t *)buf)[i]);
			else
				printf("   ");

			if (count == 8) {
				printf("  ");
				count = 0;
			}
			count++;
		}

		printf("  |");

		for (size_t i = 0; i < size_; ++i) {
			if (isprint(((uint8_t *)buf)[i]))
				putchar(((uint8_t *)buf)[i]);
			else
				putchar('.');
		}

		putchar('|');
		putchar('\n');
	};
	if(amountOfBytes == 0) {
		// Set amount of bytes to the size of the stack
		struct rlimit rlim = {0};
		int err = getrlimit(RLIMIT_DATA, &rlim);
		if(err) {
			std::cout << "Could not get rlimit, reason: " << strerror(errno) << std::endl;
			return 1;
		}
		amountOfBytes = rlim.rlim_cur;
	}
	std::array<void*, 0xFFFF> contents;
	void *previous_line;
	amountOfBytes = 0xFFFF;
	size_t contents_size = amountOfBytes;
	// static_assert(LINE_LENGTH_BYTES * 2 <= contents.size(), "Buffer is too small?!");
	// int nread;

	// while (true) {
		// std::cout << "1" << std::endl;
		// nread = fread(&contents[contents_size], 999999 - contents_size, sizeof(contents), file);
        // if (nread <= 0) {
		// 	printf("FUCKY WUCKY, errno: %d, str: %s\n", errno, strerror(errno));
		// 	break;
		// }
        // contents_size = amountOfBytes;
		std::cout << "size of contents: " << contents_size << std::endl;
		// return 0;
		// std::cout << "2" << std::endl;

		contents[0] = (void*)&main;
		// return 0;

		for(long unsigned int i = 1; i < contents.size(); i++) {
			contents[i] = contents[i - 1] + LINE_LENGTH_BYTES;
			print_line(contents[i], LINE_LENGTH_BYTES);
		}
		// size_t offset;
		// for (offset = 0; offset < contents.size(); offset++) {
		// 	// if (verbose) {
		// 		print_line(contents[offset], LINE_LENGTH_BYTES);
		// 		// std::cout << "3" << std::endl;
		// 		// continue;
		// 	// }

		// 	// auto current_line = contents.span().slice(offset, LINE_LENGTH_BYTES);
		// 	auto current_line = contents[offset];
		// 	// bool is_same_contents = (current_line == previous_line);

		// 	// Coalesce repeating lines
		// 	// switch (state) {
		// 	// case State::Print:
		// 	//     print_line(&contents[offset], LINE_LENGTH_BYTES);
		// 	//     break;
		// 	// case State::PrintFiller:
		// 	//     outln("*");
		// 	//     state = State::SkipPrint;
		// 	//     break;
		// 	// case State::SkipPrint:
		// 	//     break;
		// 	// }
		// 	previous_line = current_line;
		// 	// std::cout << "4" << std::endl;
		// }

		// contents_size -= offset;
		assert(contents_size < LINE_LENGTH_BYTES);
		// std::cout << "5" << std::endl;
		// If we managed to make the buffer exactly full, &contents[BUFSIZ] would blow up.
		// if (contents_size > 0) {
		// 	// std::cout << "6" << std::endl;
		// 	// Regions cannot overlap due to above static_assert.
		// 	memcpy(contents[0], contents[offset], contents_size);
		// }
		// std::cout << "7" << std::endl;
	// }
	// std::cout << "8" << std::endl;
	assert(contents_size <= LINE_LENGTH_BYTES - 1);
	if (contents_size > 0) {
		// std::cout << "9" << std::endl;
		print_line(contents[0], contents_size);
	}
	// std::cout << "exit" << std::endl;

	return 0;
}

