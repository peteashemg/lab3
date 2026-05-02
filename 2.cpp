#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdint>

using namespace std;

// умножение (a * b) % m
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t res = 0;
	a %= m;
	while (b > 0) {
		if (b % 2 == 1) res = (res + a) % m;
        	a = (a * 2) % m;
        	b /= 2;
    		}
    	return res;
}

// возведение в степень (a^b) % m
uint64_t power(uint64_t a, uint64_t b, uint64_t m) {
	uint64_t res = 1;
	a%= m;
	while (b > 0) {
		if (b % 2 == 1) res = mul_mod(res, a, m);
		a = mul_mod(a, a, m);
        	b /= 2;
   	}
	return res;
}

int main() {
    	srand(time(0));
    	
    	// шаг 1 ввод таблицы простых чисел
    	int64_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
	int primes_count = 95;

	int bits;
	cout << "введите разрядность: ";
	if (!(cin >> bits)) return 0;
	cout << "№\tчисло n\t\tрезультат\tотвергнутые" << endl;
	cout << "----------------------------------------------------" << endl;

	int total_rejected = 0;

	for (int i = 1; i <= 10; i++) {
        	uint64_t n;
        	vector<uint64_t> factors;
        	bool is_prime = false;
        	int current_rejected = 0;

        while (!is_prime) {
        	// шаг 2 формируем m
        	uint64_t m = 1;
        	factors.clear();
        	factors.push_back(2); // n-1 всегда делится на 2

        	// набираем множители, пока не достигнем нужной разрядности
            	while (m < (1ULL << (bits - 1))) {
                	uint64_t q = primes[rand() % primes_count];
                	if (m > 0xFFFFFFFFFFFFFFFFULL / q) break; 
                	m *= q;
                	factors.push_back(q);
		}

	// шаг 3 n = 2m + 1
        n = 2 * m + 1;
       	// шаг 4 выбираем случайное 'a' (1 < a < n)
	uint64_t a = 2 + (rand() % (n - 2));
	// шаг 5 проверка условий
        // a^(n-1) mod n == 1
        if (power(a, n - 1, n) == 1) {
        	bool cond2 = true;
            	// a^((n-1)/qi) mod n != 1
                for (uint64_t q : factors) {
                	if (power(a, (n - 1) / q, n) == 1) {
                        	cond2 = false;
                        	break;
                    	}
                }
                if (cond2) {
                    is_prime = true;
                }
        }

       	if (!is_prime) {
                current_rejected++;
                total_rejected++;
        	}
        }
        // шаг 6 вывод в таблицу
        cout << i << "\t" << n << "\ttrue\t\t" << current_rejected << endl;
	}

	return 0;
}

