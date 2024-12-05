#include "cipher.h"

void ask_xor() {
    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op;
    scanf("%d", &op);
    if(op == 2) return;
    char cipherText[1000], decryptedText[1000], key[1000];

    readFromFile("cipher_Xor.txt", cipherText);
    printf("Cipher text read from file: %s\n", cipherText);

    printf("Enter keyword for Vigenere Cipher used in encryption: ");
    scanf("%s", key);

    decryptXor(cipherText, key, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return;
}

void encryptXor(char cipher[], char key[], char msg[]) {
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        msg[i] = cipher[i] ^ key[0];
        if (msg[i] == '\n') msg[i] = cipher[i];
    }
    msg[i] = '\0';
}

void decryptXor(char cipher[], char key[], char msg[]) {
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        msg[i] = cipher[i] ^ key[0];
        if (msg[i] == '\n') msg[i] = cipher[i];
    }
    msg[i] = '\0';
}
