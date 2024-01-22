#include "print.h"

typedef struct 
 { 
   char name[50];
   char surname[50];
   int IndexNr;
   float avg;

 } Student;

void PrintAll(int a, Student students[a]) // funkcja wyświetla całą listę, wszystkie dane
  {
    for(int i = 0; i < a; i++)
      {
        printf("%s, %s, %d, %f\n", 
          students[i].name, students[i].surname, 
          students[i].IndexNr, students[i].avg);
      }

    printf("\n");
  }

void PrintByName(int a, Student students[a]) // funkcja pobiera literę od użytkownika, a następnie wyświetla dane tylko tych osób, któych imię zaczyna się na podaną literę
  {
    char letter;
    printf("podaj literę(pamiętając o dużym znaku): ");
    scanf(" %c", &letter);

    for(int i = 0; i < a; i++)
      {
        if (students[i].name[0] == letter)
        {
          printf("%s, %s, %d, %f\n", 
          students[i].name, students[i].surname, 
          students[i].IndexNr, students[i].avg);
        }

      }
      printf("\n");


  }

void PrintBySurname(int a, Student students[a]) // analogicznie do funkcji PrintByName(), tylko po nazwisku 
  {
     char letter;
     printf("podaj literę (pamiętając o dużym znaku): ");
     scanf(" %c", &letter);

     for(int i = 0; i < a; i++)
       {
         if (students[i].surname[0] == letter)
         {
           printf("%s, %s, %d, %f\n", 
           students[i].name, students[i].surname, 
           students[i].IndexNr, students[i].avg);
         }

       }
       printf("\n");
   
  }

void PrintByIndexNr(int a, Student students[a]) // funkcja pobiera od użytkownika dwie liczby (jeśli poda ujemną - komunikat "błąd" - prośba o podanie kolejnej), następnie sprawdza, która liczba jest większa i ustala z tych liczb odpowiedni przedział domknięty, następnie wyświetla dane tylko tych osób, których nr indeksu należy do tego przedziału
  {
    float number1, number2;
    
    printf("podaj pierwszą liczbę: ");
    scanf("%f", &number1);
    
    while (number1 < 0 )
      {
      printf("błąd");
      printf("podaj jeszcze raz: ");
      scanf("%f", &number1);
      }

    printf("podaj drugą liczbę: ");
    scanf("%f", &number2);

    while (number2 < 0 )
      {
      printf("błąd");
      printf("podaj jeszcze raz: ");
      scanf("%f", &number2);
      }
    
    float max, min;
    
    if (number1 > number2)
      {
      max = number1;
      min = number2;
      }
    else 
      {
      max = number2;
      min = number1;
      }  

    for(int i = 0; i < a; i++)
    {
      if (students[i].IndexNr >= min && students[i].IndexNr <= max)
      {
        printf("%s, %s, %d, %f\n", 
        students[i].name, students[i].surname, 
        students[i].IndexNr, students[i].avg);
      }
      
    }
    printf("\n");
  
  }

void PrintByAvg(int a, Student students[a]) // analogicznie do funkcji PrintByIndexNr(), tylko po średniej ocen
  {
    float number1, number2;

    printf("podaj pierwszą liczbę: ");
    scanf("%f", &number1);

    while (number1 < 0 )
      {
      printf("błąd");
      printf("podaj jeszcze raz: ");
      scanf("%f", &number1);
      }

    printf("podaj drugą liczbę: ");
    scanf("%f", &number2);

    while (number2 < 0 )
      {
      printf("błąd");
      printf("podaj jeszcze raz: ");
      scanf("%f", &number2);
      }
    
    float max, min;

    if (number1 > number2)
      {
      max = number1;
      min = number2;
      }
    else 
      {
      max = number2;
      min = number1;
      }  

    for(int i = 0; i < a; i++)
    {
      if (students[i].avg >= min && students[i].avg <= max)
      {
        printf("%s, %s, %d, %f\n", 
        students[i].name, students[i].surname, 
        students[i].IndexNr, students[i].avg);
      }

    }
    printf("\n");

  }

