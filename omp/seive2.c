#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void SieveOfEratosthenes(int n)
{
	bool prime[n + 1];
	memset(prime, true, sizeof(prime));
	int prime_count = 0;

	for (int p = 2; p * p <= n; p++) {

		if (prime[p] == true) {
			for (int i = p*p; i <= n; i += p)
				prime[i] = false;
		}
	}

	// Print all prime numbers
	for (int p = 2; p <= n; p++)
		if (prime[p])
		{
			prime_count++;
		}
	printf("prime numbers: %d ",prime_count);
}

// Driver Code
int main()
{
	int n = 500000000;
	printf("Following are the prime numbers smaller than or equal to %d \n", n);
	SieveOfEratosthenes(n);
	return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)
