#include "cipher.h"

void ask_vigenere() {
    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op;
    scanf("%d", &op);
    if(op == 2) return;
    char cipherText[1000], decryptedText[1000], key[1000];
    readFromFile("cipher_Vienere.txt", cipherText);
    printf("Cipher text read from file: %s\n", cipherText);

    printf("Enter keyword for Vigenere Cipher used in encryption: ");
    scanf("%s", key);

    decryptVigenere(cipherText, key, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return;
}

void encryptVigenere(char msg[], char key[], char cipher[]) {
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; msg[i] != '\0'; i++) {
        if (msg[i] >= ASCII_START && msg[i] <= ASCII_END) {
            cipher[i] = ASCII_START + ((msg[i] - ASCII_START + (key[j % keyLen] - ASCII_START)) % ASCII_RANGE);
            j++;
        } else {
            cipher[i] = msg[i];
        }
    }
    cipher[i] = '\0';
}

void decryptVigenere(char cipher[], char key[], char msg[]) {
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; cipher[i] != '\0'; i++) {
        if (cipher[i] >= ASCII_START && cipher[i] <= ASCII_END) {
            msg[i] = ASCII_START + ((cipher[i] - ASCII_START - (key[j % keyLen] - ASCII_START) + ASCII_RANGE) % ASCII_RANGE);
            j++;
        } else {
            msg[i] = cipher[i];
        }
    }
    msg[i] = '\0';
}
