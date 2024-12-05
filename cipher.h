#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_START 32
#define ASCII_END 126
#define ASCII_RANGE (ASCII_END - ASCII_START + 1)
#define SIZE 5

int a, b;

// Utility functions
int gcd(int a, int b);
int modInverse(int A, int M);
void displayMenu();

// Affine Cipher
void encryptAffine(char msg[], char cipher[]);
void decryptAffine(char cipher[], char msg[]);

// Caesar Cipher
void encryptCaesar(char msg[], int shift, char cipher[]);
void decryptCaesar(char cipher[], int shift, char msg[]);

// Vigenere Cipher
void encryptVigenere(char msg[], char key[], char cipher[]);
void decryptVigenere(char cipher[], char key[], char msg[]);

// XOR Cipher
void encryptXor(char cipher[], char key[], char msg[]);
void decryptXor(char cipher[], char key[], char msg[]);

// Playfair Cipher
void playfairEncrypt(char msg[], char key[], char cipher[]);
void playfairDecrypt(char cipher[], char key[], char msg[]);

//rsaCipher
void rsaKeyGeneration(int *e, int *d, int *n);
long long modPow(long long base, long long exp, long long mod);
long long encryptRSAChar(char message, int e, int n);
char decryptRSAChar(long long cipher, int d, int n);
void encryptRSAString(const char *message, long long *cipher, int e, int n);
void decryptRSAString(const long long *cipher, char *message, int length, int d, int n);


// File Handling
void readFromFile(char filename[], char content[]);
void writeToFile(char filename[], char content[]);

#endif
