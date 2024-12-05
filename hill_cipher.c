#include "cipher.h"

void ask_hill() {

    printf("Do you want to decrypt this (Yes == 1 and No == 2) : ");
    int op, shift;
    scanf("%d", &op);
    if(op == 2) return;
    int keyMatrix[10][10], keySize;
    char cipherText[1000], decryptedText[1000], key[100];

    printf("Enter the size of the key matrix (NxN): ");
    scanf("%d", &keySize);
    getchar(); // Consume newline

    if (keySize > 10 || keySize <= 0) {
        printf("Invalid key size! Must be between 1 and 10.\n");
        return;
    }

    printf("Enter the key matrix (%dx%d):\n", keySize, keySize);
    getKeyMatrix(keySize, keyMatrix);

    int det = determinantModulo(keyMatrix, keySize, ASCII_RANGE);

    if (gcd(det, ASCII_RANGE) != 1) {
        printf("Invalid key matrix (determinant not coprime with %d). Cannot decrypt.\n", ASCII_RANGE);
        return;
    }

    readFromFile("cipher_hill.txt", cipherText);
    cipherText[strcspn(cipherText, "\n")] = '\0'; // Remove newline character

    decryptHill(cipherText, keyMatrix, keySize, decryptedText);
    printf("Decrypted Message: %s\n", decryptedText);
    return;
}

void getKeyMatrix(int keySize, int keyMatrix[10][10]) {
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }
}

void encryptHill(char msg[], int keyMatrix[10][10], int keySize, char cipherText[]) {
    int i, j, k;
    int msgLen = strlen(msg);
    int paddedLen = ((msgLen + keySize - 1) / keySize) * keySize;
    char *paddedMsg = (char *)malloc(paddedLen + 1); // Dynamic allocation for padded message

    strcpy(paddedMsg, msg);
    for (i = msgLen; i < paddedLen; i++) {
        paddedMsg[i] = ' ';
    }
    paddedMsg[paddedLen] = '\0';

    for (i = 0; i < paddedLen; i += keySize) {
        for (j = 0; j < keySize; j++) {
            int sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += keyMatrix[j][k] * (paddedMsg[i + k] - ASCII_START);
            }
            cipherText[i + j] = (sum % ASCII_RANGE + ASCII_RANGE) % ASCII_RANGE + ASCII_START;
        }
    }
    cipherText[paddedLen] = '\0';
    free(paddedMsg); // Free allocated memory
}

void decryptHill(char cipherText[], int keyMatrix[10][10], int keySize, char decryptedText[]) {
    int invMatrix[10][10];
    int i, j, k;
    int msgLen = strlen(cipherText);

    inverseMatrix(keyMatrix, invMatrix, keySize, ASCII_RANGE);

    for (i = 0; i < msgLen; i += keySize) {
        for (j = 0; j < keySize; j++) {
            int sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += invMatrix[j][k] * (cipherText[i + k] - ASCII_START);
            }
            decryptedText[i + j] = (sum % ASCII_RANGE + ASCII_RANGE) % ASCII_RANGE + ASCII_START;
        }
    }
    decryptedText[msgLen] = '\0';
}


int determinantModulo(int matrix[10][10], int size, int mod) {
    if (size == 1) return matrix[0][0] % mod;

    int det = 0;
    int subMatrix[10][10];

    for (int x = 0; x < size; x++) {
        int subi = 0;
        for (int i = 1; i < size; i++) {
            int subj = 0;
            for (int j = 0; j < size; j++) {
                if (j == x) continue;
                subMatrix[subi][subj++] = matrix[i][j];
            }
            subi++;
        }
        det = (det + (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinantModulo(subMatrix, size - 1, mod)) % mod;
    }
    return (det + mod) % mod;
}

void adjointMatrix(int matrix[10][10], int adj[10][10], int size) {
    if (size == 1) {
        adj[0][0] = 1;
        return;
    }

    int subMatrix[10][10];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int subi = 0;
            for (int x = 0; x < size; x++) {
                if (x == i) continue;
                int subj = 0;
                for (int y = 0; y < size; y++) {
                    if (y == j) continue;
                    subMatrix[subi][subj++] = matrix[x][y];
                }
                subi++;
            }
            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinantModulo(subMatrix, size - 1, ASCII_RANGE);
            adj[j][i] = (adj[j][i] + ASCII_RANGE) % ASCII_RANGE;
        }
    }
}

void inverseMatrix(int matrix[10][10], int inv[10][10], int size, int mod) {
    int adj[10][10];
    int det = determinantModulo(matrix, size, mod);
    int detInv = modInverse(det, mod);

    adjointMatrix(matrix, adj, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inv[i][j] = (adj[i][j] * detInv) % mod;
            if (inv[i][j] < 0) inv[i][j] += mod;
        }
    }
}

