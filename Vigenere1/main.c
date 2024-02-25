#include<stdio.h>

#define OFFSET          32
#define ALPHABET_SIZE   91
#define KEY_SIZE        20
#define DEBUG           0


/**
 * @brief Encrypts a message with the Vigenère Cipher.
 * 
 * @param key The key for the Vigenère Cipher.
 * @param originalMessage String with the original message.
 * @param encryptedMessage String to put the encrypted message.
 * @param size The size of the message.
 */
void encrypt(char key[], char originalMessage[], char encryptedMessage[], int size){
    if (DEBUG) printf("Encrypted message (inside function): ");
    for (int i = 0; i < size; i++) {
        encryptedMessage[i] = ((((originalMessage[i] - OFFSET) + (key[i % KEY_SIZE]) - OFFSET)) % ALPHABET_SIZE) + OFFSET;
        if (DEBUG) printf("%c", encryptedMessage[i]);
    }
    if (DEBUG) printf("\n\n");
}


/**
 * @brief Decrypts a message encrypted with the Vigenère Cipher.
 * 
 * @param key Is the key for the Vigenère Cipher.
 * @param mEncrypted String with the encrypted message.
 * @param mDecrypted String to put the decrypted message. 
 * @param size The size of the message.
 */
void decrypt(char key[], char mEncrypted[], char mDecrypted[], int size){
    int i;
    if (DEBUG) printf("Decrypted message (inside function): ");
    for (i = 0; i < size; i++) {
        mDecrypted[i] = (((mEncrypted[i] - OFFSET) - (key[i % KEY_SIZE] - OFFSET) + ALPHABET_SIZE) % ALPHABET_SIZE) + OFFSET;
        if (DEBUG) printf("%c", mDecrypted[i]);
    }
    if (DEBUG) printf("\n\n");
}


/**
 * @brief Count the size of a vector.
 * 
 * @param message The vector to be measured.
 * @return int The size of a vector.
 */
int charCounter(char message[]) {
    int i = 0;

    while(message[i] != '\0') {
        i++;
    }
    return i;
}


int main(void) {
    char originalMessage[200] = "Nos so podemos ver um pouco do futuro, mas o suficiente para perceber que ha muito a fazer. [Alan Turing]";
    char messageEncrypted[200];
    char encryptKey[KEY_SIZE] = "abcdefghijklmnopqrts";
    char messageDecrypted[200];

    // View the original message:
    printf("Original message: %s", originalMessage);

    // Call the encrypt function:
    encrypt(encryptKey, originalMessage, messageEncrypted, charCounter(originalMessage));
    printf("\nEncrypted message: %s", messageEncrypted);

    // Call the decrypt function to get original message:
    decrypt(encryptKey, messageEncrypted, messageDecrypted, charCounter(originalMessage));
    printf("\nDecrypted message: %s", messageDecrypted);
       
    return 0;
}
