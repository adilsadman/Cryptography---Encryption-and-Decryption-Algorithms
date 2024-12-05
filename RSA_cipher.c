#include "cipher.h"

void rsaKeyGeneration(int *e, int *d, int *n) {
    int p = 61, q = 53;
    *n = p * q;
    int phi = (p - 1) * (q - 1);

    *e = 3;
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    *d = 1;
    while ((*d * *e) % phi != 1) {
        (*d)++;
    }
}

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long encryptRSAChar(char message, int e, int n) {
    return modPow(message, e, n);
}

char decryptRSAChar(long long cipher, int d, int n) {
    return (char)modPow(cipher, d, n);
}

void encryptRSAString(const char *message, long long *cipher, int e, int n) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        cipher[i] = encryptRSAChar(message[i], e, n);
    }
}

void decryptRSAString(const long long *cipher, char *message, int length, int d, int n) {
    for (int i = 0; i < length; i++) {
        message[i] = decryptRSAChar(cipher[i], d, n);
    }
    message[length] = '\0';
}
