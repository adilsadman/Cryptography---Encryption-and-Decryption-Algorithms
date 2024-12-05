#include "cipher.h"

void ask_caesar() {
    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op, shift;
    scanf("%d", &op);
    if(op == 2) return;
    char cipherText[1000], decryptedText[1000];

    readFromFile("cipher_Caeser.txt", cipherText);
    printf("Cipher text read from file: %s\n", cipherText);

    printf("Enter shift value for Caesar Cipher used in encryption: ");
    scanf("%d", &shift);

    decryptCaesar(cipherText, shift, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return;
}

void encryptCaesar(char msg[], int shift, char cipher[]) {
    int i;
    for (i = 0; msg[i] != '\0'; i++) {
        if (msg[i] >= ASCII_START && msg[i] <= ASCII_END) {
            cipher[i] = ASCII_START + ((msg[i] - ASCII_START + shift) % ASCII_RANGE);
        } else {
            cipher[i] = msg[i];
        }
    }
    cipher[i] = '\0';
}

void decryptCaesar(char cipher[], int shift, char msg[]) {
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        if (cipher[i] >= ASCII_START && cipher[i] <= ASCII_END) {
            msg[i] = ASCII_START + ((cipher[i] - ASCII_START - shift + ASCII_RANGE) % ASCII_RANGE);
        } else {
            msg[i] = cipher[i];
        }
    }
    msg[i] = '\0';
}
