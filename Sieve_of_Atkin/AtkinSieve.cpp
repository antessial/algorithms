#include <iostream>
#include <boost/dynamic_bitset.hpp>

// Actually, you may replace dynamic bitset with anything else
// like std::bitset or std::vector, I made my choice because of
// this totally reliable (random link from google) research:
// https://www.researchgate.net/publication/220803585_Performance_of_C_bit-vector_implementations

static bool buildAtkinSieve(boost::dynamic_bitset<>& sieve) {
	if (&sieve == nullptr || sieve.size() < 2)
		return false;
	int size = sieve.size() - 1;
	sieve[2] = true;
	sieve[3] = true;
	int n, x = 0, y;
	int sizeSqrt = sqrt(size);
	for (int i = 1; i <= sizeSqrt; ++i) {
		x += (i << 1) - 1;
		y = 0;
		for (int j = 1; j <= sizeSqrt; ++j) {
			y += (j << 1) - 1;
			n = (x << 2) + y;
			if ((n <= size) && (n % 12 == 1 || n % 12 == 5))
				sieve[n].flip();
			n -= x;
			if ((n <= size) && (n % 12 == 7))
				sieve[n].flip();
			n -= (y << 1);
			if ((i > j) && (n <= size) && (n % 12 == 11))
				sieve[n].flip();
		}
	}
	for (int i = 5; i <= sizeSqrt; ++i) {
		if (sieve[i]) {
			n = i * i;
			for (int j = n; j <= size; j += n)
				sieve[j] = false;
		}
	}
	return true;
}

int main() {
	std::cout << "Enter the initial capacity of the sieve: ";
	int size;
	std::cin >> size;
	boost::dynamic_bitset<> sieve(size + 1);
	if (!buildAtkinSieve(sieve)) {
		std::cout << "It's too small for me to work with, so I'm done";
		return 1;
	}
	int answer;
	while (true) {	// feel free to Alt + F4
		std::cout << "\nEnter the number to check if it's prime: ";
		std::cin >> answer;
		if (answer >= sieve.size() || answer < 1) {
			std::cout << "Wrong input\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');		// ignores current input just in case
		}
		else
			std::cout << (sieve[answer] ? "It's prime.\n" : "It's not prime.\n");
	}
	return 0;
}
