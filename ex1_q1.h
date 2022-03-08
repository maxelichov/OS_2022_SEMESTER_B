





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW_SIZE 80


typedef struct Student {
	
	
	char name[10];
	float average;
	int numOfGrades;
	int grades[10];
	
	
}student;


typedef struct ListNode {
	
	
	struct ListNode* next;
	student* stdnt;
	
}listNode;

typedef struct StudentsList {
	
	listNode*	head;	
	listNode*	tail;
	listNode* next;
	
	
}studentsList;

void calcAverage(studentsList* StudentsList);
void printList(studentsList* studentList);
studentsList* initList();
student*  getStudent(char* studentName, studentsList* list );
int checkIfStudentExists(char* studentName, studentsList* list );
student* addNewStudentToList(studentsList* StudentsList, char* studentName) ;
void addGrade(int gradesArr[], int gardeToAdd, int index);
void handleRow(char* buffer, studentsList* stdntList);
void handleFile(char* fileName, studentsList* studentsList);
