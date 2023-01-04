#include <stdio.h>
#include <string.h>


// Funkcja, która odczytuje nazwę pliku z danymi do szyfrowania/odszyfrowania.

FILE* fileToRead(FILE *readFile, char *nameReadFile){
    printf("Write name/adres to file you want to READ from. Add the format '.txt':\n");
    scanf("%299s", nameReadFile);
    readFile = fopen(nameReadFile, "r");

    while (readFile == NULL) {
        printf("File is empty or doesn't exists. Change type or name of file:\n");
        scanf("%299s", nameReadFile);
        readFile = fopen(nameReadFile, "r");
    } //Sprawdzenie - czy plik istnieje.

    return readFile;
}


//Funkcja, która sprawdza, czy 2 podane przez uzytkownika pliki są różne.

int checkNames(char *fileName1, char *fileName2) {
    if(strlen(fileName1) == strlen(fileName2))
        for(int i = 0; i < strlen(fileName1); i++){
            if(fileName1[i] != fileName2[i]){
                return 0;
        }
            return 1;
    }
    return 0;
}


// Funkcja, która wczytuje plik do edycji i sprawdza czy on istnieje.

FILE * fileToEdit(FILE *writeFile, char *nameWriteFile, char *nameReadFile){
    printf("Write name/adres to file you want to EDIT. Add the format '.txt':\n");
    scanf("%299s", nameWriteFile);

    while (checkNames(nameWriteFile, nameReadFile) == 1){
        printf("File you want to edit has the same name as first you have mentioned. Write the new one name of the file to edit below:\n");
        scanf("%299s", nameWriteFile);
    }

    writeFile = fopen(nameWriteFile, "w");
    while (writeFile == NULL) {
        printf("File is empty or doesn't exists. Change type or name of file:\n");
        scanf("%299s", nameWriteFile);
        writeFile = fopen(nameWriteFile, "w");
    }
    return writeFile;
}


// Funkcja, która odpowiada za szyfrowanie tesktu z pliku readFile w plik editFile.

void szyfrowanie(FILE *readFile, FILE *editFile, char *key) {
    char sign;
    int indeks = 0;
    char signResult;
    while ((sign = getc(readFile)) != EOF) {

        if((sign >=65 )&&( sign <= 90)){
            signResult = (sign + key[indeks])%26 + 65;
            fputc(signResult, editFile);
            indeks++;

            if (indeks == strlen(key)){
                indeks = 0;
            }
        }
        else {
            fputc(sign, editFile);
        }
    }
    printf("Szyfrowanie is competed! Check the result in the file you have chosen.");
}


// Funkcja, która odpowiada za odszyfrowanie tesktu z pliku readFile w plik editFile.

void odszyfrowanie(FILE *readFile, FILE *editFile, char *key) {
    char sign;
    int indeks = 0;
    char signResult;

    while ((sign = getc(readFile)) != EOF) {
        if ((sign >= 65) && (sign <= 90)) {
            signResult = (sign - key[indeks] + 26)%26 + 'A';
            fputc(signResult, editFile);
            indeks++;
            if (indeks == strlen(key)) {
                indeks = 0;
            }
        } else {
            fputc(sign, editFile);
        }
    }

    printf("Odszyfrowanie is done :) Check the result in the edited file");
}


//Funkcja, która sprawdza rodzaj operacji i prawidłowość wpisanej liczby.

int operationType(int type){
    printf("What do you want to do now:\n szyfrowanie - 0 \n odszyfrowanie - 1\n");
    scanf("%d", &type);

    while (type != 0 && type != 1) {
        printf("Wrong operation type, please enter 0 or 1:\n szyfrowanie - 0 \n odszyfrowanie - 1\n");
        scanf("%d", &type);
    }

    return type;
}


//Funkcja, która sprawdza, czy klucz zawiera inne znaki oprócz dużych liter.

int checkKey(char *key){
    for(int i = 0; i < strlen(key); i++) {
        if ((key[i] < 65) || (key[i]) > 90) {
            printf("Wrong key. Please check if your key has not only caps letters\n");
            return 1;
        }
    }
    return 0;
}


//Funckcja, która zapisuje wprowadzony klucz.

int writeKey(char *key){
    printf("Write the key to szyfrowanie/odszyfrowanie:\n");
    scanf("%299s", key);

    while(checkKey(key) == 1){
        scanf("%299s", key);
    }
}

    int main() {
        FILE *fileOriginal;
        FILE *fileEdited;
        char nameOriginalFile [300];
        char nameEditedFile [300];
        char keyword [300];
        int operation;

        fileOriginal = fileToRead(fileOriginal, nameOriginalFile);
        fileEdited = fileToEdit(fileEdited, nameEditedFile, nameOriginalFile);
        writeKey(keyword);

        operation = operationType(operation);
        if (operation == 0) {
            szyfrowanie(fileOriginal, fileEdited, keyword);
        } else {
            odszyfrowanie(fileOriginal, fileEdited, keyword);
        }

        fclose(fileOriginal);
        fclose(fileOriginal);

        return 0;
    }