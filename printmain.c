#include <stdio.h>
#include <stdlib.h>
#include "print.h"

int main() 
{
  FILE *tabela;
  tabela = fopen("dane.csv", "r");

  if (tabela == NULL)
  { 
  /* moduł dodawania nowych osob do pliku */
  }  

  Student *students = NULL; // inicjalizacja tablicy struktur
  int capacity = 10;

  students = (Student *)malloc(capacity * sizeof(Student));

  int read = 0;
  int records = 0;

  do 
    {
       read = fscanf(tabela, "%49[^,],%49[^,],%d,%f\n",
         &students[records].name, &students[records].surname,
         &students[records].IndexNr, &students[records].avg);

      if (read == 4) 
        records++;

      if (records >= capacity) 
      {
      capacity *= 2;  // Podwajamy pojemność
      students = (Student *)realloc(students, capacity * sizeof(Student));
      }

      if ((read != 4) && !feof(tabela))
      {
        printf("błąd w pliku\n");
        return 1;
      }
      
      if (ferror(tabela))
      {
        printf("błąd\n");
        return 1;
      }  
    }  
    while (!feof(tabela));

  fclose(tabela);

  char answer;

  do
    {
      
      printf("czy chcesz coś wyświetlić? wpisz t/n :");
      scanf(" %c", &answer);
 
      if (answer == 't')
      {

        char choice;
        printf("\nwybierz opcję(wpisz jedną cyfrę z podanych):\n 1(wszystkie dane)\n 2(dane po imieniu)\n 3(dane po nazwisku)\n 4(dane po nr indeksu)\n 5(dane po średniej)\n");
        
        scanf(" %c", &choice);

        switch(choice)
          {
            case '1':
               PrintAll(records, students);
               break;
            case '2':
               PrintByName(records, students);
               break;
            case '3':
               PrintBySurname(records, students);
               break;
            case '4':
               PrintByIndexNr(records, students);
               break;
            case '5':
               PrintByAvg(records, students);
               break;
            default:
               printf("źle podana odpowiedź\n");
               break;

          }
      }
      

      else if (answer == 'n')
      {
        printf("koniec programu\n");
      }

      else 
      {
        printf("źle wpisana odpowiedź\n ");
      }
 
    }
    while(answer != 'n');

  free(students);

  return 0;
} 
