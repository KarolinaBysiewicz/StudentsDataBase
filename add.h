#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void AddStudent (char answer[3]);
void AddIndexNr(const struct DataBase * base, int IndexNr);
void ModifyDataReference(char answer[3]);
void SaveData (struct DataBase *base, const char *name, const char *surname,int IndexNr, float avg);
void AnotherStudent(char answer[3]);
void AddMoreData (int answer);
void MoreData (char answer[3]);
void NewStudent1();
void NewStudent2 ();
void AddAverage (char average[10]);

#endif  // ADD_H
