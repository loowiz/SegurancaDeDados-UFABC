#include<stdio.h>

#define OFFSET          32
#define ALPHABET_SIZE   91
#define FILENAME        "../texto_cripto_chave20.txt"
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
    char messageEncrypted[10000];
    char messageDecrypted[10000];
    char encryptKey[KEY_SIZE] = "";
    char ch;

    // Open the encrypted file data:
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot find %s", FILENAME);
        return 1;
    }

    // Copy the data from the file to an array:
    for (int i = 0; (ch = fgetc(fp)) != EOF; i++) {
        messageEncrypted[i] = ch;
    }

    printf("Message encrypted: %s\n\n", messageEncrypted);

    // -----------
    // FIRST TRY:
    // -----------
    // Trying to get the key inside the encrypted message (brute force):
    for (int keyOffSet = 0; keyOffSet < charCounter(messageEncrypted) - 20; keyOffSet++) {
        for (int i = 0 + keyOffSet; i < 20 + keyOffSet; i++) {
            encryptKey[i - keyOffSet] = messageEncrypted[i];
        }

        // Call the decrypt function to get original message:
        decrypt(encryptKey, messageEncrypted, messageDecrypted, charCounter(messageEncrypted));

        // Print only the first 10 chars. If it has some portuguese words, I found the key!
        //printf("POSITION: %d\t", keyOffSet);
        //printf("Message decrypted (10 chars): ");
        //for (int i = 0; i < 10; i++) {
        //    printf("%c", messageDecrypted[i]);
        //}
        //printf("\n");

        // I know that the first word is "F", so...
        if (messageDecrypted[0] == 'F') {
            printf("POSITION: %d\t", keyOffSet);
            printf("Message decrypted (10 chars starting with \"F\"): ");
            for (int i = 0; i < 10; i++) {
                printf("%c", messageDecrypted[i]);
            }
            printf("\n");
        }
    }

    // Call the decrypt function to get original message:
    //decrypt(encryptKey, messageEncrypted, messageDecrypted, charCounter(messageEncrypted));
    //printf("Message decrypted: %s\n\n", messageDecrypted);

    fclose(fp);
    return 0;
}
