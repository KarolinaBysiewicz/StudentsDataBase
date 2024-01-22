#include "add.h"

struct student {
    char name[50];
    char surname[50];
    int IndexNr;
    float avg;
};


struct DataBase {               //baza danych, w ktorej beda zapisywani wszyscy studenci
    struct student *AllStudents;
    int number_of_students;
};

void AddIndexNr(const struct DataBase * base, int IndexNr) {      //funkcja do wprowadzania numeru indeksu

    printf("Podaj numer indeksu studenta: \n");
    scanf("%d", &IndexNr);
    for(int i=0; i < base->number_of_students; i++) {
        if(base->AllStudents[i].IndexNr == IndexNr) {
            printf("Taki nr indeksu juz istnieje. Podaj inny nr: \n");
            AddIndexNr(base, IndexNr);
        }
        else {
            return;
        }
    }
}

void SaveData (struct DataBase *base, const char *name, const char *surname,int IndexNr, float avg) {

    base->AllStudents = realloc(base->AllStudents, (base->number_of_students + 1) * sizeof(struct student));

    strncpy(base->AllStudents[base->number_of_students].name, name, sizeof(base->AllStudents[base->number_of_students].name) - 1);             //-1 => zeby na końcu bylo NULL
    strncpy(base->AllStudents[base->number_of_students].surname, surname, sizeof(base->AllStudents[base->number_of_students].surname) - 1);
    base->AllStudents[base->number_of_students].IndexNr = IndexNr;
    base->AllStudents[base->number_of_students].avg = avg;

    base->number_of_students++;       //zwiekszenie numeru studenta o jeden

}

float AddAverage (char average[10]) {
    float avg;
    printf("Podaj srednia ocen studenta: \n");
    scanf("%s", average);
    if(sscanf(average, "%f", &avg) == 1) {
        return avg;
    }
    else {
        printf("Wprowadzono zle dane. Sprobuj jeszcze raz. \n");
        AddAverage(average);
    }
}

void AddStudent () {                   //funkcja do wybierania czy znamy wszystkie dane

    char answer[3];
    printf("Czy znasz wszystkie dane? (tak/nie) \n");

    scanf("%s", answer);
    if (strcmp(answer, "tak")==0) {
        NewStudent1();
    }
    else if (strcmp(answer, "nie")==0) {
        NewStudent2();
    }
    else {
        printf("Wprowadziles zla odpowiedz. Sprobuj jeszcze raz.\n");
        AddStudent();     //zapetlanie funkcji w przypadku blednej odpowiedzi;
    }

}

void ModifyDataReference(char answer[3]){       //funkcja do modyfikowania wprowadzonych danych/ dodawania nowych

    scanf("%s", answer);
    if (strcmp(answer, "tak")==0) {
        //ModifyData()        <-funkcja do modyfikowania Michala  .... musi być powrot do mojej funkcji pozniej
        printf("Czy chcesz dokonac wiecej modyfikacji? (tak/nie)\n");
        ModifyDataReference(answer);
    }
    else if (strcmp(answer, "nie")==0) {
        return;
    }
    else {
        printf("Wprowadziles zla odpowiedz. Sprobuj jeszcze raz.\n");
        ModifyDataReference(answer);
    }
}

void AnotherStudent(char answer[3]) {         //funkcja do dodawania kolejnego studenta
    struct student *NewStudent;
    struct DataBase *base;

    scanf("%s", answer);
    if (strcmp(answer, "tak")==0) {
        AddStudent(NewStudent);
    } else if (strcmp(answer, "nie")==0) {
        return;    //tutaj zrobic odniesienie do wyboru ogolnych funkcji- powrot do "centrum sterowania"
    } else {
        printf("Wprowadziles zla odpowiedz. Sprobuj jeszcze raz.\n");
        AnotherStudent(answer);      //zapetlanie w przypadku blednej odpowiedzi
    }
}

void MoreData (char answer[3]){     //funkcja: czy chcemy dodac wiecej danych
    scanf("%s", answer);
    if (strcmp(answer, "tak")==0) {
        AddMoreData(*answer);
    }
    else if (strcmp(answer, "nie")==0) {
        return;
    }
    else {
        printf("Wprowadziles zla odpowiedz. Sprobuj jeszcze raz.\n");
        MoreData(answer);
    }
}

void AddMoreData (int answer) {      //funkcja do dodawania wiecej danych

    char name[50], surname[50], average[10];
    float avg;
    int IndexNr;

    struct DataBase base;

    printf("Wybierz: \n 1-podaj nr indeksu\n 2-podaj srednia ocen\n ");
    scanf("%d", &answer);
    if (answer == 1) {
        AddIndexNr(&base, IndexNr);
    }
    else if (answer == 2) {
        AddAverage(average);
    }
    else {
        printf("Wprowadziles zla odpowiedz. Sprobuj jeszcze raz.\n");
        AddMoreData(answer);
    }
    printf("Czy chcesz dodac jeszcze jakies dane? (tak)/nie)\n ");
    MoreData(&answer);
}

void NewStudent1() {    //funkcja do dodawania studenta, gdy znamy wszystkie dane

    struct DataBase base = {NULL, 0};

    char name[50], surname[50], answer[3];
    float avg;
    char average[10];
    int IndexNr;

    printf("Podaj imie studenta: \n");
    scanf("%s", name);

    printf("Podaj nazwisko studenta: \n");
    scanf("%s", surname);

    AddIndexNr(&base, IndexNr);

    AddAverage(average);

    printf("Czy chcesz dodac jeszcze jakies dane? (tak)/nie)\n");
    ModifyDataReference(answer);

    SaveData(&base, name, surname, IndexNr, avg);

    printf("Czy chcesz zmodyfikowac wprowadzone dane? (tak/nie)\n");
    ModifyDataReference(answer);

    free(base.AllStudents);

    printf("Czy chcesz dodac kolejnego studenta? (tak)/(nie) \n");
    AnotherStudent(answer);
}

void NewStudent2 () {  //funkcja do dodawania studenta, gdy nie znamy wszystkich danych

    struct DataBase base = {NULL, 0};

    char name[50], surname[50], answer[3];
    float avg;
    int IndexNr;

    printf("Podaj imie studenta: \n");
    scanf("%s", name);

    printf("Podaj nazwisko studenta: \n");
    scanf("%s", surname);

    printf("Czy chcesz podac jeszcze jakies dane? (tak)/nie) \n");
    MoreData(answer);

    SaveData(&base, name, surname, IndexNr, avg);

    printf("Czy chcesz zmodyfikowac wprowadzone dane? (tak/nie)\n");
    ModifyDataReference(answer);

    free(base.AllStudents);

    printf("Czy chcesz dodac kolejnego studenta? (tak)/nie) \n");
    AnotherStudent(answer);
}

