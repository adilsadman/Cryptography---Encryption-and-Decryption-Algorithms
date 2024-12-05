#include "cipher.h"

void ask_affine() {
    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op;
    scanf("%d", &op);
    if(op == 2) return;
    char cipherText[1000], decryptedText[1000];
    readFromFile("cipher_Affine.txt", cipherText);
    printf("Cipher text read from file: %s\n", cipherText);

    printf("Enter values for 'a' and 'b' used in encryption: ");
    scanf("%d %d", &a, &b);
    if (modInverse(a, ASCII_RANGE) == -1) {
        printf("Invalid key 'a' - decryption not possible.\n");
    } else {
        decryptAffine(cipherText, decryptedText);
        printf("Decrypted Message: %s\n", decryptedText);
    }
    return;

}

void encryptAffine(char msg[], char cipher[]) {
    int i;
    int len = strlen(msg);

    for (i = 0; i < len; i++) {
        if (msg[i] >= ASCII_START && msg[i] <= ASCII_END) {
            cipher[i] = ASCII_START + ((a * (msg[i] - ASCII_START) + b) % ASCII_RANGE);
        } else {
            cipher[i] = msg[i];
        }
    }
    cipher[len] = '\0';
}

void decryptAffine(char cipher[], char msg[]) {
    int i;
    int len = strlen(cipher);
    int a_inv = modInverse(a, ASCII_RANGE);

    if (a_inv == -1) {
        printf("Modular inverse does not exist. Decryption is not possible.\n");
        return;
    }

    for (i = 0; i < len; i++) {
        if (cipher[i] >= ASCII_START && cipher[i] <= ASCII_END) {
            msg[i] = ASCII_START + ((a_inv * ((cipher[i] - ASCII_START) - b + ASCII_RANGE)) % ASCII_RANGE);
        } else {
            msg[i] = cipher[i];
        }
    }
    msg[len] = '\0';
}
