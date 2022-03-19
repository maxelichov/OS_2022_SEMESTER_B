





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW_SIZE 80
#define rr "//"
 

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

void free_list(studentsList* SudentsList);
void write_to_file(studentsList* SudentsList);
void print_all_avg(studentsList* studList);
void report_input_file(const char* file_name, int num_stud);
void report_data_summary(int num_stud, double avg);
int cmpfunc (const void * a, const void * b);
//void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));
void calcAverage(studentsList* StudentsList);
void printList(studentsList* studentList);
studentsList* initList();
student*  getStudent(char* studentName, studentsList* list );
int checkIfStudentExists(char* studentName, studentsList* list );
student* addNewStudentToList(studentsList* StudentsList, char* studentName) ;
void addGrade(int gradesArr[], int gardeToAdd, int index);
int handleRow(char* buffer, studentsList* stdntList);
int handleFile(char* fileName, studentsList* studentsList);
