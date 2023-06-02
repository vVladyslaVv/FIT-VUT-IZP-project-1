#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_CONTACTS 42

typedef struct
{
    char phoneNumber[MAX_LINE_LENGTH];
    char fullName[MAX_LINE_LENGTH];
} Contact;

bool getContacts(Contact* contacts, size_t* size);

void getSingleContact(Contact* contact);

void printContact(const Contact* contact);

void printAllContacts(const Contact* contact, size_t size);

void searchContacts(const Contact* contacts, size_t size, const char* searchString);

bool isContactMatch(const Contact* contact, const char* searchString);

bool isMatchPhone(const char* contactPhone, const char* searchString);

bool isMatchName(const char* contactName, const char* searchString);

bool isValidContact(const Contact* contact);

bool isValidPhone(const char* contactPhone);

bool isValidName(const char* contactName);

bool isValidInput(const char* input);

char getNumberFromChar(char symbol);

int main(int argc, char* argv[])
{

    Contact contacts[MAX_CONTACTS];
    size_t size;

    const char* tmp = "Petr Dvorak\n603123456\nJana Novotna\n77987654\nBedrich Smetana ml.\n541141120";
    const char* tmp2 = "686";

    if (!getContacts(contacts, &size))
    {
        fprintf(stdout, "Not valid input!\n");
    }

    if (argc == 1)
    {
        printAllContacts(contacts, size);
        return 0;
    }

    if (!isValidInput(argv[1]))
    {
        fprintf(stdout, "Not valid input!\n");
        return 0;
    }

    searchContacts(contacts, size, argv[1]);
    return 0;
}

bool getContacts(Contact* contacts, size_t* size)
{
    int chr;
    *size = 0;
    while ((chr = getchar()) != -1)
    {
        ungetc(chr, stdin);
        Contact contactNew;
        getSingleContact(&contactNew);

        if (!isValidName(contactNew.fullName))
        {
            return 0;
        }

        if (!isValidPhone(contactNew.phoneNumber))
        {
            return 0;
        }

        contacts[*size] = contactNew;
        (*size)++;
    }

    return 1;
}

void getSingleContact(Contact* contact)
{
    char data[MAX_LINE_LENGTH];

    fgets(data, MAX_LINE_LENGTH, stdin);
    if (data[strlen(data) - 1] == '\n')
    {
        data[strlen(data) - 1] = '\0';
    }
    strcpy(contact->fullName, data);

    memset(data, sizeof(data), 0);
    fgets(data, MAX_LINE_LENGTH, stdin);
    if (data[strlen(data) - 1] == '\n')
    {
        data[strlen(data) - 1] = '\0';
    }
    strcpy(contact->phoneNumber, data);
}

void printContact(const Contact* contact)
{
    fputs(contact->fullName, stdout);
    fputs(", ", stdout);
    fputs(contact->phoneNumber, stdout);
}

void printAllContacts(const Contact* contact, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printContact(&contact[i]);
        fputs("\n", stdout);
    }
}

void searchContacts(const Contact* contacts, size_t size, const char* searchString)
{
    bool found = 0;
    for (int i = 0; i < size; i++)
    {
        if (isContactMatch(&contacts[i], searchString))
        {
            printContact(&contacts[i]);
            fprintf(stdout, "\n");
            found = 1;
        }
    }
    if (!found)
    {
        fprintf(stdout, "Not Found!\n");
    }
}

bool isContactMatch(const Contact* contact, const char* searchString)
{
    return isMatchPhone(contact->phoneNumber, searchString) || isMatchName(contact->fullName, searchString);
}

bool isMatchPhone(const char* contactPhone, const char* searchString)
{
    if (searchString == NULL)
    {
        return true;
    }

    char* match = strstr(contactPhone, searchString);
    if (match != NULL)
    {
        return true;
    }

    return false;
}

bool isMatchName(const char* contactName, const char* searchString)
{
    size_t nameLength = strlen(contactName);
    size_t searchLength = strlen(searchString);

    for (int nameIter = 0; nameIter < nameLength - searchLength; nameIter++)
    {
        bool match = 1;
        for (size_t searchIter = 0; searchIter < searchLength; searchIter++)
        {
            if (getNumberFromChar(contactName[nameIter + searchIter]) != searchString[searchIter])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            return 1;
        }
    }
    return 0;
}

bool isValidContact(const Contact* contact)
{
    return isValidPhone(contact->phoneNumber) && isValidName(contact->fullName);
}

bool isValidPhone(const char* contactPhone)
{
    int i = 0;
    while (contactPhone[i] != '\0')
    {
        if ((contactPhone[i] < '0' || contactPhone[i] > '9') && !((i == 0 && contactPhone[i] == '+') || contactPhone[i] == ' '))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

bool isValidName(const char* contactName)
{
    int i = 0;
    while (contactName[i] != '\0')
    {
        if ((contactName[i] < 'A' || contactName[i] > 'Z') && (contactName[i] < 'a' || contactName[i] > 'z'))
        {
            if (!(contactName[i] == ' ' || contactName[i] == '.' || contactName[i] == ','))
            {
                return 0;
            }
        }
        i++;
    }

    return 1;
}

bool isValidInput(const char* input)
{
    size_t inputLength = strlen(input);
    for (size_t i = 0; i < inputLength; i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

char getNumberFromChar(char symbol)
{
    if (symbol == ' ' || symbol == '.' || symbol == ',')
        return symbol;
    else if (symbol == '+')
        return '0';
    else if (strchr("AaBbCc", symbol))
        return '2';
    else if (strchr("DdEeFf", symbol))
        return '3';
    else if (strchr("GgHhIi", symbol))
        return '4';
    else if (strchr("JjKkLl", symbol))
        return '5';
    else if (strchr("MmNnOo", symbol))
        return '6';
    else if (strchr("PpQqRrSs", symbol))
        return '7';
    else if (strchr("TtUuVv", symbol))
        return '8';
    else if (strchr("WwXxYyZz", symbol))
        return '9';

    return '\0';
}
