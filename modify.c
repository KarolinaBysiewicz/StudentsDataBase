#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struktura reprezentująca studenta
struct Student
{
    char name[50];
    char surname[50];
    int IndexNr;
    float avg;
};

// Prototypy funkcji
int CompareStrings(char str1[], char str2[]);
void NoCommas(char string[]);
void LoadDatabase(const char* file_name, struct Student** database, int* databaseSize);
int SearchByIndex(struct Student* database, int databaseSize);
int SearchBySurname(struct Student* database, int databaseSize);
void ModifyData(struct Student* database, int index);
void ModifyName(struct Student* database, int index);
void ModifySurname(struct Student* database, int index);
void ModifyIndex(struct Student* database, int index);
void ModifyAvg(struct Student* database, int index);
void SaveToFile(const char* file_name, struct Student* database, int databaseSize);

int main()
{
    struct Student* database = NULL;
    int databaseSize = 0;
    int choice, index, end;

    LoadDatabase("student_database.csv", &database, &databaseSize);

    do
    {
        printf("\nWpisz:\n1 - jesli chcesz wyszukac po nr. indeksu\n2 - jesli po nazwisku\n");
        scanf("%d", &choice);
        
        if (choice == 1)
        {
            index = SearchByIndex(database, databaseSize);
        }
        else if (choice == 2)
        {
            index = SearchBySurname(database, databaseSize);
        }

        if (index != -1)
        {
            ModifyData(database, index);
        }

        printf("\nJesli chcesz wyszukac kolejnego studenta, wpisz 1: ");
        scanf("%d", &end);
        choice = 0;

    } while (end == 1);

    SaveToFile("student_database.csv", database, databaseSize);

    free(database);

    printf("\nZycze milego dnia ;)\n");
    return 0;
}

void LoadDatabase(const char* file_name, struct Student** database, int* databaseSize)
{
    FILE* plik = fopen(file_name, "r");
    if (plik == NULL)
    {
        printf("Nie udalo sie otworzyc pliku.\n");
        return;
    }

    *databaseSize = 50;
    *database = malloc(*databaseSize * sizeof(struct Student));
    int studentNr = 0;


    // Pominięcie pierwszej linii pliku csv
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), plik) == NULL)
    {
        printf("\nBład podczas czytania pierwszej linii :(\n");
        fclose(plik);
        return;
    }

    do
    {
        if (studentNr == *databaseSize)
        {
            (*databaseSize)++;
            *database = realloc(*database, *databaseSize * sizeof(struct Student));
        }

        if (fscanf(plik, "%49[^,],%49[^,],%d,%f\n", (*database)[studentNr].name,
                   (*database)[studentNr].surname, &(*database)[studentNr].IndexNr, &(*database)[studentNr].avg) == 4)
        {
            studentNr++;
        }
        else
        {
            printf("Bład formatowania pliku :( \n");
            break;
        }
    } while (!feof(plik));

    fclose(plik);
}

int SearchByIndex(struct Student* database, int databaseSize)
{
    int answer, end;
    do
    {
        printf("\nWpisz numer wyszukiwanego indeksu: ");
        scanf("%d", &answer);
        for (int i = 0; i < databaseSize; i++)
        {
            if (database[i].IndexNr == answer)
            {
                printf("%s %s, numer:%d, srednia:%f",database[i].name, database[i].surname, database[i].IndexNr, database[i].avg);
                return i;
            }
        }
        printf("\nNie ma takiego indeksu.\nWpisz 1 jesli chcesz ponowic probe: ");
        scanf("%d", &end);
    } while (end == 1);
    return -1;
}

int SearchBySurname(struct Student* database, int databaseSize)
{
    char answer[50];
    int end, count = 0;
    int tab[10];
    do
    {
        printf("\nWpisz nazwisko studenta ktorego szukasz: ");
        scanf("%s", answer);

        for (int i = 0; i < databaseSize; i++)
        {
            if (CompareStrings(database[i].surname, answer))
            {
                tab[count] = i;
                count++;
            }
        }
        if (count == 1)
        {
            printf("\n%s %s, numer:%d, srednia:%f",database[tab[0]].name, database[tab[0]].surname, database[tab[0]].IndexNr, database[tab[0]].avg);
            return tab[0];
        }
        else if (count != 0)
        {
            int j = 1, c;
            for (j; j < count + 1; j++)
            {
                printf("\n%d) %s %s, numer:%d, srednia:%f", j, database[tab[j - 1]].name, database[tab[j - 1]].surname, database[tab[j - 1]].IndexNr, database[tab[j - 1]].avg);
            }
            printf("\nWypisz numer przy studencie o którego ci chodzi,a jesli go nie ma wpisz dowolna inna liczbe: ");
            scanf("%d", &c);
            if (c > 0 && c < j + 1)
            {
                return tab[c - 1];
            }
            else
            {
                printf("\nNie wybrales żadnego studenta. Jesli chcesz wyszukac ponownie, wpisz 1: ");
            }
        }
        else
        {
            printf("\nNie ma studenta o takim nazwisku.\nWpisz 1 jeśli chcesz ponowic próbę: ");
        }
        scanf("%d", &end);
    } while (end == 1);
    return -1;
}

int CompareStrings(char str1[], char str2[])
{
    if (strlen(str1) == strlen(str2))
    {
        for (int i = 0; i < strlen(str1); i++)
        {
            if (tolower(str1[i]) != tolower(str2[i]))
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void ModifyData(struct Student* database, int index)
{
    int end = 0,choice;
    do
    {
        
        printf("\nNapisz:\n1 - jesli chcesz edytowac imie\n2 - nazwisko\n3 - numer indeksu\n4 - srednia\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            ModifyName(database, index);
        }
        else if (choice == 2)
        {
            ModifySurname(database, index);
        }
        else if (choice == 3)
        {
            ModifyIndex(database, index);
        }
        else if (choice == 4)
        {
            ModifyAvg(database, index);
        }

        printf("\nWpisz 1, jesli chcesz edytowac kolejne dane tego studenta: ");
        scanf("%d", &end);

    } while (end == 1);

    return;
}

void NoCommas(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == ',')
        {
            for (int j = i; j < strlen(string); j++)
            {
                string[j] = string[j + 1];
            }
        }
    }
}

void ModifyName(struct Student* database, int index)
{
    char string[50];
    int confirm;

    printf("\nWpisz nowe imie studenta: ");
    scanf("%s", string);
    NoCommas(string);

    printf("\nNowe imie: %s\nWpisz 1, by potwierdzic: ", string);
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(database[index].name, string);
    }
    else
    {
        printf("\nOk, nie to nie :/");
    }

    return;
}

void ModifySurname(struct Student* database, int index)
{
    char string[50];
    int confirm;

    printf("\nWpisz nowe nazwisko studenta: ");
    scanf("%s", string);
    NoCommas(string);

    printf("\nNowe nazwisko: %s\nWpisz 1, by potwierdzic: ", string);
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(database[index].surname, string);
    }
    else
    {
        printf("\nOk, nie to nie :/");
    }

    return;
}

void ModifyIndex(struct Student* database, int index)
{
    int num, confirm;

    printf("\nWpisz nowy indeks studenta (5 cyfr max): ");
    scanf("%d", &num);

    if (num > 99999 || num < 0)
    {
        printf("\nBłąd. Zła liczba >:( ");
        return;
    }

    printf("\nNowy indeks: %d\nWpisz 1, by potwierdzic: ", num);
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        database[index].IndexNr = num;
    }
    else
    {
        printf("\nOk, nie to nie :/");
    }

    return;
}

void ModifyAvg(struct Student* database, int index)
{
    float num;
    int confirm;

    printf("\nWpisz nową srednia studenta: ");
    scanf("%f", &num);

    if (num >= 5 || num <= 2)
    {
        printf("\nBlad. Zla liczba >:( ");
        return;
    }

    printf("\nNowa srednia: %f\nWpisz 1, by potwierdzic: ", num);
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        database[index].avg = num;
    }
    else
    {
        printf("\nOk, nie to nie :/");
    }

    return;
}

void SaveToFile(const char* file_name, struct Student* database, int databaseSize)
{
    FILE *plik = fopen(file_name, "w");

    if (plik == NULL)
    {
        printf("\nBlad przy otwieraniu pliku :(\n");
        return;
    }

    fprintf(plik, "Imię,Nazwisko,Numer Indeksu,Średnia\n");

    for (int i = 0; i < databaseSize; i++)
    {
        fprintf(plik, "%s,%s,%d,%.2f\n", database[i].name, database[i].surname, database[i].IndexNr, database[i].avg);

        if (ferror(plik))
        {
            printf("\nBlad przy zapisywaniu pliku :C\n");
        }
    }

    fclose(plik);
}