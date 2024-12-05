#include "cipher.h"

void ask_playpair() {
    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op, shift;
    scanf("%d", &op);
    if(op == 2) return;
    char cipherText[1000], decryptedText[1000], key[100];

    readFromFile("cipher_Playfair.txt", cipherText);
    printf("Cipher text read from file: %s\n", cipherText);

    printf("Enter keyword for Playfair Cipher used in encryption: ");
    scanf("%s", key);

    playfairDecrypt(cipherText, key, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return;
}

void generateKeyMatrix(char key[], char matrix[SIZE][SIZE]) {
    int alphabet[26] = {0};
    int i, j, k = 0;
    char ch;

    for (i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I';
        if (key[i] >= 'A' && key[i] <= 'Z' && !alphabet[key[i] - 'A']) {
            alphabet[key[i] - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = key[i];
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!alphabet[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }

}

void preprocessPlayfairText(char text[], char processed[]) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) { // uppercase and j to i
        if (isalpha(text[i])) {
            processed[j++] = toupper(text[i] == 'J' ? 'I' : text[i]);
        }
    }
    processed[j] = '\0';

    char finalText[1000];
    j = 0;
    for (i = 0; processed[i] != '\0'; i++) {
        finalText[j++] = processed[i];
        if (processed[i] == processed[i + 1]) {
            finalText[j++] = 'X'; // AA to AX A
        }
    }
    finalText[j] = '\0';

    if (j % 2 != 0) {
        finalText[j++] = 'X'; // AX A to AX AX
    }
    finalText[j] = '\0';

    strcpy(processed, finalText);
}

void playfairEncrypt(char msg[], char key[], char cipher[]) {
    char matrix[SIZE][SIZE];
    generateKeyMatrix(key, matrix);

    char processedMsg[1000];
    preprocessPlayfairText(msg, processedMsg);

    int i, row1, col1, row2, col2;
    for (i = 0; processedMsg[i] != '\0'; i += 2) {
        char first = processedMsg[i];
        char second = processedMsg[i + 1];

        // find possition
        for (row1 = 0; row1 < SIZE; row1++) {
            for (col1 = 0; col1 < SIZE; col1++) {
                if (matrix[row1][col1] == first) break;
            }
            if (col1 < SIZE) break;
        }
        for (row2 = 0; row2 < SIZE; row2++) {
            for (col2 = 0; col2 < SIZE; col2++) {
                if (matrix[row2][col2] == second) break;
            }
            if (col2 < SIZE) break;
        }

        if (row1 == row2) { // same row
            cipher[i] = matrix[row1][(col1 + 1) % SIZE];
            cipher[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) { // same column
            cipher[i] = matrix[(row1 + 1) % SIZE][col1];
            cipher[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else { // rectangle
            cipher[i] = matrix[row1][col2];
            cipher[i + 1] = matrix[row2][col1];
        }
    }
    cipher[i] = '\0';

    printf("\n Generated Matrix : \n"); // matrix print

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void playfairDecrypt(char cipher[], char key[], char msg[]) {
    char matrix[SIZE][SIZE];
    generateKeyMatrix(key, matrix);

    int i, row1, col1, row2, col2;
    for (i = 0; cipher[i] != '\0'; i += 2) {
        char first = cipher[i];
        char second = cipher[i + 1];

        for (row1 = 0; row1 < SIZE; row1++) {
            for (col1 = 0; col1 < SIZE; col1++) {
                if (matrix[row1][col1] == first) break;
            }
            if (col1 < SIZE) break;
        }
        for (row2 = 0; row2 < SIZE; row2++) {
            for (col2 = 0; col2 < SIZE; col2++) {
                if (matrix[row2][col2] == second) break;
            }
            if (col2 < SIZE) break;
        }

        if (row1 == row2) {
            msg[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            msg[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            msg[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            msg[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else { //
            msg[i] = matrix[row1][col2];
            msg[i + 1] = matrix[row2][col1];
        }
    }
    msg[i] = '\0';
}
