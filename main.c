#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[60];
    char surname[60];
    float avg;
    char avgOperator[2]; // Dodajemy pole do przechowywania operatora porównania
} StudentData;

FILE* openFile() {
    FILE *pliczusiunio = fopen("C:\\Users\\barto\\OneDrive\\Pulpit\\Project\\baza.csv", "r");
    if(pliczusiunio == NULL) {
        printf("(!) Nastapil blad w odczycie pliku. (!)\n\n");
        return NULL;
    } else {
        //printf("Pomyslnie odczytano plik\n\n");
        return pliczusiunio;
    }
}

StudentData getData() {
    StudentData data;
    int Gid;
    int resID;

    printf("(i) INSTRUKCJA (i)\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "Podaj kryteria, ktore maja zostac uwzglednione w wyszukiwaniu rekordow. \n"
           "Wpisz 0, w celu pominiecia wyszukiwania na podstawie kryterium.\n"
           "Podajac dwa i wiecej kryteriow, zwezasz zakres wynikow.\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    do {
        printf("1. ID/0:\n");
        resID = scanf("%d", &Gid);
        while(getchar() != '\n');
        if(resID != 1) {
            printf("(!) Niepoprawna wartosc. Podaj poprawne ID lub 0. (!)\n\n");
        }
    } while(resID != 1);

    int size = 100; // Zainicjowanie size na odpowiednią wartość
    char *GName = (char *)malloc(size * sizeof(char));
    char *GSurname = (char *)malloc(size * sizeof(char));

    do {
        printf("2. Name/0:\n");
        if(scanf("%s", GName) != 1) { // Usunięcie operatora &
            printf("(!) Niepoprawna wartosc. Podaj poprawne imie lub 0. (!)\n\n");
        } else {
            if(GName[0] == '0') {
                break;
            }
            int i = 0;
            bool isAllLetters = true;
            while(GName[i]) {
                if(!isalpha(GName[i])) {
                    isAllLetters = false;
                    break;
                }
                i++;
            }
            if(!isAllLetters) {
                printf("(!) Niepoprawna wartosc. Imie powinno zawierac tylko litery. (!)\n\n");
            } else {
                break;
            }
        }
        while(getchar() != '\n');
    } while(1);

    do {
        printf("3. Surname/0:\n");
        if(scanf("%s", GSurname) != 1) {
            printf("(!) Niepoprawna wartosc. Podaj poprawne nazwisko lub 0. (!)\n\n");
        } else {
            if(GSurname[0] == '0') {
                break;
            }
            int i = 0;
            bool isAllLetters = true;
            while(GSurname[i]) {
                if(!isalpha(GSurname[i])) {
                    isAllLetters = false;
                    break;
                }
                i++;
            }
            if(!isAllLetters) {
                printf("(!) Niepoprawna wartosc. Nazwisko powinno zawierac tylko litery.(!)\n\n");
            } else {
                break;
            }
        }
        while(getchar() != '\n');
    } while(1);

    float Gavg = 0;
    float resAvg;
    do {
        printf("4. Avg/0:\n");
        resAvg = scanf("%f", &Gavg);
        while(getchar() != '\n');
        if(resAvg != 1) {
            printf("(!) Niepoprawna wartosc. Podaj poprawna srednia lub 0. (!)\n\n");
        }
    } while(resAvg != 1);

    char GavgOperator[2];

    do {
        if(Gavg != 0) {
            printf("5. Operator porownawczy (>, <, =):\n");
            char input[10];
            fgets(input, sizeof(input), stdin);
            if(sscanf(input, "%s", GavgOperator) != 1 || (GavgOperator[0] != '>' && GavgOperator[0] != '<' && GavgOperator[0] != '=')) {
                printf("(!) Niepoprawna wartosc. Podaj poprawny operator porownania lub 0 (!)\n\n");
            } else {
                GavgOperator[1] = '\0'; // Usuwamy randomowe znaczki
                break;
            }
        } else {
            GavgOperator[0] = '0';
            GavgOperator[1] = '\0'; // Usuwamy randomowe znaczki
            break;
        }
    } while(1);

    // Przypisz wartości do pól struktury data
    data.id = Gid;
    strncpy(data.name, GName, sizeof(data.name) - 1);
    strncpy(data.surname, GSurname, sizeof(data.surname) - 1);
    data.avg = Gavg;
    strncpy(data.avgOperator, GavgOperator, sizeof(data.avgOperator) - 1); // Przypisz operator porównania do struktury data

    printf("Podane przez Ciebie dane to:\n%d | %s | %s | %.2f | %.1s\n\n", data.id, data.name, data.surname, data.avg, data.avgOperator);
    if(data.id == 0 && data.name[0] == '0' && data.surname[0] == '0' && data.avg == 0 && data.avgOperator[0] == '0') {
        printf("(!) Podane dane nie sa prawidlowe (Podano same pominiecia kryteriow) (!)\n\n");
        return getData();
    }
    return data;
}

void findStudent(StudentData data, FILE *pliczusiunio) {
    if(pliczusiunio == NULL) {
        printf("(!) Nastapil blad w odczycie pliku (!)");
        return;
    }
    char line[100];
    fgets(line, sizeof(line), pliczusiunio); // Pomiń pierwszy wiersz (nagłówek)
    fseek(pliczusiunio, strlen(line), SEEK_SET); // Przesuń wskaźnik pliku na początek drugiej linii
    int matchCount = 0; // Dodajemy zmienną matchCount
    printf("----------------------------------------------\n");
    while(fgets(line, sizeof(line), pliczusiunio)) { //Funkcja fgets() jest używana do odczytywania linii tekstu z pliku.
        char *endptr;
        char *token = strtok(line, ",");
        long id = strtol(token, &endptr, 10);
        if (endptr == token) {
            // handle the error, the conversion failed because no number was found
            continue;
        }
        token = strtok(NULL, ",");
        char *name = token;
        token = strtok(NULL, ",");
        char *surname = token;
        token = strtok(NULL, ",");
        float avg = atof(token);

        bool idMatches = (data.id == 0 || data.id == id);
        bool nameMatches = (data.name[0] == '0' || strcmp(data.name, name) == 0);
        bool surnameMatches = (data.surname[0] == '0' || strcmp(data.surname, surname) == 0);
        bool avgMatches = (data.avgOperator[0] == '0' || (data.avgOperator[0] == '>' && avg > data.avg) || (data.avgOperator[0] == '<' && avg < data.avg) || (data.avgOperator[0] == '=' && avg == data.avg));

        if(idMatches && nameMatches && surnameMatches && avgMatches && id != 0) {
            matchCount++;
            printf("%d | %s | %s | %.2f\n", id, name, surname, avg);
        }
    }
    printf("----------------------------------------------\n");
    if(matchCount == 0) {
        printf("(!) W pliku nie znajduja sie dane pasujace do podanych kryteriow (!)\n\n");
        fclose(pliczusiunio);
        pliczusiunio = openFile();
        printf("\n");
        data = getData();
        findStudent(data, pliczusiunio);
    } else {
        printf("Pomyslnie odczytano z pliku: %d rekordow.\n", matchCount); // Wydrukuj ilość rekordów spełniających kryteria
    }
    fclose(pliczusiunio);

}

void delStudent() {
    FILE *file = openFile();
    if(file == NULL) {
        printf("(!) Nastapil blad w odczycie pliku (!)");
        return;
    }

    // Wczytaj dane do listy
    StudentData students[1000]; // Zakładamy, że mamy maksymalnie 1000 studentów
    int studentCount = 0;
    char line[1000];
    fgets(line, sizeof(line), file); // Pomiń pierwszy wiersz (nagłówek)
    fseek(file, strlen(line), SEEK_SET); // Przesuń wskaźnik pliku na początek drugiej linii
    while(fgets(line, sizeof(line), file)) {
        char *endptr;
        char *token = strtok(line, ",");
        long id = strtol(token, &endptr, 10);
        if (endptr == token) {
            continue;
        }
        students[studentCount].id = id;
        token = strtok(NULL, ",");
        strncpy(students[studentCount].name, token, sizeof(students[studentCount].name) - 1);
        token = strtok(NULL, ",");
        strncpy(students[studentCount].surname, token, sizeof(students[studentCount].surname) - 1);
        token = strtok(NULL, ",");
        students[studentCount].avg = atof(token);
        studentCount++;
    }
    fclose(file);

    // Zapytaj o ID studenta do usunięcia
    int idToDelete;
    printf("Podaj ID studenta do usuniecia:\n");
    scanf("%d", &idToDelete);

    // Usuń studenta o podanym ID
    int i;
    bool studentExists = false;
    for(i = 0; i < studentCount; i++) {
        if(students[i].id == idToDelete) {
            // Przechowaj imię i nazwisko studenta do usunięcia
            char nameToDelete[60];
            char surnameToDelete[60];
            strncpy(nameToDelete, students[i].name, sizeof(nameToDelete) - 1);
            strncpy(surnameToDelete, students[i].surname, sizeof(surnameToDelete) - 1);

            // Przesuń wszystkich studentów za tym studentem o jedno miejsce do przodu
            memmove(&students[i], &students[i + 1], (studentCount - i - 1) * sizeof(StudentData));
            studentCount--;
            studentExists = true;
            printf("(i) Student o ID %d (%s %s) zostal poprawnie usuniety. (i)\n", idToDelete, nameToDelete, surnameToDelete); // Dodajemy komunikat o poprawnym usunięciu
            break;
        }
    }

    if (!studentExists) {
        printf("(!) Nie istnieje student o podanym ID (!)\n");
        return;
    }

    // Zapisz dane z powrotem do pliku
    file = fopen("C:\\Users\\barto\\OneDrive\\Pulpit\\Project\\baza.csv", "w");
    if(file == NULL) {
        printf("(!) Nastapil blad w zapisie do pliku (!)");
        return;
    }
    fprintf(file, "id,name,surname,avg\n"); // Nagłówek
    for(i = 0; i < studentCount; i++) {
        fprintf(file, "%d,%s,%s,%.2f\n", students[i].id, students[i].name, students[i].surname, students[i].avg);
    }
    fclose(file);
}

int main() {
    while (1) {
        printf("Wybierz opcje:\n");
        printf("1. Wyszukaj studenta\n");
        printf("2. Usun studenta\n");
        printf("3. Wyjscie\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE *file = openFile();
                if (file != NULL) {
                    printf("\n");
                    StudentData data = getData();
                    findStudent(data, file);
                    fclose(file);
                }
                break;
            }
            case 2: {
                delStudent();
                break;
            }
            case 3:
                return 0;
            default:
                printf("Nieznana opcja, sprobuj ponownie.\n");
        }
    }
}