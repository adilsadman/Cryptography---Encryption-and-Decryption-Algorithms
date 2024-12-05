#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

char password[] = "pass"; // password

int main()
{
    int keyMatrix[10][10], keySize;
    char msg[1000], cipherText[1000], decryptedText[1000], key[1000];
    int choice, shift, e, d, n;
    char inputPassword[50];

    printf("Enter the password to access the program: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, password) != 0) {
        printf("Incorrect password. Exiting...\n");
        exit(0);
    }

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                printf("Enter values for 'a' and 'b': ");
                scanf("%d %d", &a, &b);
                while (gcd(a, ASCII_RANGE) != 1) {
                    printf("'a' must be coprime with %d. Enter a new value for 'a': ", ASCII_RANGE);
                    scanf("%d", &a);
                }

                encryptAffine(msg, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_Affine.txt", cipherText);
                printf("\n");
                ask_affine();

                break;

            case 2:
                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                printf("Enter shift value for Caesar Cipher: ");
                scanf("%d", &shift);

                encryptCaesar(msg, shift, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_Caeser.txt", cipherText);
                printf("\n");
                ask_caesar();
                break;

            case 3:
                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                printf("Enter keyword for Vigenere Cipher: ");
                scanf("%s", key);

                encryptVigenere(msg, key, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_Vienere.txt", cipherText);

                printf("\n");
                ask_vigenere();
                break;

            case 4:
                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                printf("Enter keyword for XOR Cipher (one char): ");
                scanf("%s", key);

                encryptXor(msg, key, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_Xor.txt", cipherText);

                printf("\n");
                ask_xor();
                break;


            case 5:
                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                printf("Enter keyword for Playfair Cipher: ");
                scanf("%s", key);

                playfairEncrypt(msg, key, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_Playfair.txt", cipherText);

                printf("\n");
                ask_playpair();
                break;

            case 6: {
                printf("Enter the size of the key matrix (NxN): ");
                scanf("%d", &keySize);
                getchar();

                if (keySize > 10 || keySize <= 0) {
                    printf("Invalid key size! Must be between 1 and 10.\n");
                    break;
                }

                printf("Enter the key matrix (%dx%d):\n", keySize, keySize);
                getKeyMatrix(keySize, keyMatrix);

                int det = determinantModulo(keyMatrix, keySize, ASCII_RANGE);

                while (gcd(det, ASCII_RANGE) != 1) {
                    printf("Invalid key matrix (determinant not coprime with %d). Enter again:\n", ASCII_RANGE);
                    getKeyMatrix(keySize, keyMatrix);
                    det = determinantModulo(keyMatrix, keySize, ASCII_RANGE);
                }

                getchar();

                printf("Enter the message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0'; // Remove newline character

                encryptHill(msg, keyMatrix, keySize, cipherText);
                printf("Encrypted Message: %s\n", cipherText);
                writeToFile("cipher_hill.txt", cipherText);

                printf("\n");
                ask_hill();
                break;
            }

            case 7:
                rsaKeyGeneration(&e, &d, &n);

                printf("Enter a message to encrypt: ");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = '\0';

                int length = (int)strlen(msg);
                printf("%d \n", length);
                long long rsaCipher[100];
                encryptRSAString(msg, rsaCipher, e, n);

                printf("Encrypted Message: ");
                for (int i = 0; i < length; i++) {
                    printf("%lld ", rsaCipher[i]);
                }
                printf("\n");

                decryptRSAString(rsaCipher, decryptedText, length, d, n);
                printf("Decrypted Message: %s\n", decryptedText);

                break;

            case 8:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int A, int M) {
    int X;
    if (gcd(A, M) > 1) {
        return -1;
    }
    for (X = 1; X < M; X++) {
        if (((A % M) * (X % M)) % M == 1) {
            return X;
        }
    }
    return -1;
}


void displayMenu() {
    printf("\n\n");
    printf("\n==== Cipher Program Menu ====\n");
    printf("1. Affine Cipher Encryption\n");
    printf("2. Caesar Cipher Encryption\n");
    printf("3. Vigenere Cipher Encryption\n");
    printf("4. Xor Cipher Encryption\n");
    printf("5. Playfair Cipher Encryption\n");
    printf("6. Hill Cipher Encryption\n");
    printf("7. RSA eNcryption and Decryption\n");
    printf("8. Exit\n");
    printf("\n\n");
    getchar();
}

