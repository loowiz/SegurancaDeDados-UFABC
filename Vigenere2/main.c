#include<stdio.h>

#define OFFSET          32
#define ALPHABET_SIZE   91
#define FILENAME        "../texto_cripto_chave20.txt"
#define KEY_SIZE        20

char charTable[ALPHABET_SIZE];


void encrypt(char key[], char mToEncrypt[], char originalMessage[], int size){
    for (int i = 0; i < size; i++) {
        mToEncrypt[i] = (originalMessage[i] + key[i % KEY_SIZE]) % ALPHABET_SIZE;
    }
}


void decrypt(char key[], char mEncrypted[], char mDecrypted[], int size){
    for (int i = 0; i < size; i++) {
        mDecrypted[i] = (mEncrypted[i] - key[i % KEY_SIZE] + ALPHABET_SIZE) % ALPHABET_SIZE;
        printf("%c", mDecrypted[i]);
    }
}


int main(void) {
    char ch;
    char messageEncrypted[10000];
    char encryptKey[KEY_SIZE] = "o\\X`WC]b**5a[UTh\\r]";
    char messageDecrypted[10000];
    int messageSize = 0;

    // Open the encrypted file data:
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot find %s", FILENAME);
        return 1;
    }

    // Calculate the size of the message:
    while ((ch = fgetc(fp)) != EOF) {
        messageEncrypted[messageSize] = ch;
        //printf("%c", ch);
        messageSize++;
    }
    printf("Message size: %d\n\n", messageSize);

    // Call the decrypt function to get original message:
    decrypt(encryptKey, messageEncrypted, messageDecrypted, messageSize);
    printf("\n\n\n%s", messageDecrypted);

    //printf("%s", messageEncrypted);
    
    // cifragem básica:
    //messageEncrypted[i] = (messageDecrypted[i] + encryptKey[i % KEY_SIZE]) % ALPHABET_SIZE;

    // Decifragem básica:
    //messageDecrypted[i] = (messageEncrypted[i] - encryptKey[i % KEY_SIZE] + ALPHABET_SIZE) % ALPHABET_SIZE;
    

    fclose(fp);
    return 0;
}
