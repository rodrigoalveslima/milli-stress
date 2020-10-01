/*
 * Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
 * Systems
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Define a boolean type. */
typedef enum {
  false = 0,
  true = 1
} bool;

/* Compute the Sieve of Eratosthenes up to n and return true if n is prime. */
bool is_prime(int n) {
  /* Initialize the sieve. */
  bool *sieve = (bool *) malloc((int) sizeof(bool) * (n + 1));
  sieve[0] = sieve[1] = false;
  for (int i = 2; i <= n; i++)
    sieve[i] = true;

  /*
   * Invariant:
   *  - p is the smallest prime < n that has not been processed, or
   *  - p is >= n (end).
   */
  int p = 2;
  while (p < n) {
    /* Eliminate the multiples of p up to n. */
    for (int i = p * 2; i <= n; i += p)
      sieve[i] = false;
    /* Find the next prime < n. */
    for (p = p + 1; p < n && !sieve[p]; p++);
  }

  bool ret = sieve[n];
  free(sieve);
  return ret;
}

int main(int argc, char *argv[]) {
  time_t epoch, start_epoch;
  int n = atoi(argv[1]);
  int duration = atoi(argv[2]);
  int interval = atoi(argv[3]);
  int count = atoi(argv[4]);
  int indefinitely = (count == 0 && duration == 0) ? 1 : 0;

  start_epoch = time(NULL);
  while ((epoch = time(NULL)) - start_epoch <= duration || count-- > 0 ||
      indefinitely == 1) {
    printf("[%ld] %d %s\n", epoch, n,
        is_prime(n) ? "is prime" : "is not prime");
    sleep(interval);
  }

  return 0;
}
