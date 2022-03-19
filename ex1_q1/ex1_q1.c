


#include "ex1_q1.h"



studentsList* init_list() {
	
	studentsList* stdList = (studentsList*)malloc(sizeof(studentsList));
	stdList->next = NULL;
	stdList->head = NULL;
	return stdList;
}

student*  get_student(char* studentName, studentsList* list ){
		
	listNode* current = list->head;
	
	while(current != NULL) {
		
		if(!(strcmp(studentName, current->stdnt->name))){
			return current->stdnt;
		}
	
		current = current->next;
	}
	return NULL;
}


int is_student_exist(char* studentName, studentsList* list ){
	
	listNode* current = list->head;
	
	while(current != NULL) {
		
		if((strcmp(studentName, current->stdnt->name)) == 0)
		{

			return 1;
		}
		
		current = current->next;
	}
		
	return 0;
}



void insert_to_tail(studentsList* studentsList, listNode* stdntNode){

	if(studentsList->tail == NULL){
		studentsList->tail = studentsList->head = stdntNode;
	}
	
	else{
		studentsList->tail->next = stdntNode;
		studentsList->tail = stdntNode;	
	}	
	studentsList->tail->next = NULL;
}

student* add_new_student(studentsList* studentsList, char* studentName) {
	
	listNode* stdntNode = (listNode*)malloc(sizeof(listNode)); 
	student* newstdnt = (student*)malloc(sizeof(student));
	stdntNode->stdnt = newstdnt;
	strcpy(stdntNode->stdnt->name , studentName);	
	insert_to_tail(studentsList, stdntNode);
	return stdntNode->stdnt;
}




void add_grade(int gradesArr[], int gradeToAdd, int index) {
	
	gradesArr[index] = gradeToAdd;
}

int handle_row(char* buffer, studentsList* stdntList) {
	
	int num_stud = 0;
	char delimiter[]=" \t\r\n\v\f";
	char* token = strtok(buffer, delimiter);
	char* studentName;
	student* stdnt;
	int i = 0;
	
	while(token != NULL) 
	{
				
			if(i == 0) 
			{
				studentName = token;
				
				if(is_student_exist(studentName, stdntList)) {
					stdnt = get_student(studentName, stdntList);
				}
	
				else {
					stdnt = add_new_student(stdntList, studentName);	
				}

			num_stud++;
			
			}
	
		
			else {
				int grade = atoi(token);
				add_grade(stdnt->grades, grade, stdnt->numOfGrades);
				stdnt->numOfGrades++;		
			}
		
			token = strtok(NULL, delimiter);
			i++;
	}
	return num_stud;
}

int handle_file(char* fileName, studentsList* StudentsList) {
	
	int num_students = 0;
	FILE* filePointer = fopen(fileName, "r");
	char* buffer = NULL;
	int size =0;	
	int i = 1;	
	int lineSize = getline(&buffer, &size, filePointer);

     	while(lineSize >= 0) {
	
			if(lineSize > 2) { 	
			num_students += handle_row(buffer, StudentsList);		 
		}
		
		lineSize = getline(&buffer, &size, filePointer);	
	}
	
	fclose(filePointer);
	buffer = NULL;	
	return num_students;
}

void calc_avg(studentsList* StudentsList) {

	listNode* curr = StudentsList->head;
	student* tempStud;
	int sum  = 0;
	while(curr != NULL) {
	
		tempStud = curr->stdnt;
		
		for(int i = 0; i < tempStud->numOfGrades; i++) {
			sum += tempStud->grades[i];	
		}
	
		tempStud->average = (float)sum/(tempStud->numOfGrades);
		sum = 0;
		curr = curr->next;
	}
}

void print_all_avg(studentsList* studList){
	listNode* curr = studList->head;
	int num_of_students=0;
	int sum_of_grades=0;
	int num_of_all_grades = 0;
	
	while(curr!=NULL){
	num_of_students++;
	num_of_all_grades+= curr->stdnt->numOfGrades;
	sum_of_grades+=(curr->stdnt->average)*(curr->stdnt->numOfGrades);
	curr = curr->next;
      }

   report_data_summary(num_of_students, (double) sum_of_grades/num_of_all_grades);
}


void print_list(studentsList* studentList){

	listNode* currentStudent=studentList->head;
	int i = 1;

	while(currentStudent!=NULL){
		printf("%s",currentStudent->stdnt->name);
	
		for(int i=0;i<currentStudent->stdnt->numOfGrades;i++){
		printf(" %d ",currentStudent->stdnt->grades[i]);

		}

		currentStudent=currentStudent->next;
		i++;
		printf("\n");
   	}
}




void report_input_file(const char* file_name, int num_stud){

 fprintf(stderr, "process: %d file: %s number of students: %d\n",
 getpid(), file_name, num_stud);

}
//-----------------------------------------------
void report_data_summary(int num_stud, double avg){
 	fprintf(stderr, "process: %d data summary - number of students:"
 		" %d grade average: %.2f\n",
	getpid(), num_stud, avg);
}



void sort_grades(studentsList* student_list) {

	listNode* curr = student_list->head;
	student* tmp_student;	
	while(curr != NULL) {
		tmp_student = curr->stdnt;
		qsort(tmp_student->grades, tmp_student->numOfGrades, sizeof(int), cmpfunc);
		curr = curr->next;		
	}
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}


void write_to_file(studentsList* SudentsList) {

	FILE* merged_file = fopen("merged.txt","w");
	dup2(stdout,merged_file);
	listNode* currentStudent=SudentsList->head;
	int i = 1;

	while(currentStudent!=NULL){
		
		fprintf(merged_file,"%s",currentStudent->stdnt->name);
	
		for(int i=0;i<currentStudent->stdnt->numOfGrades;i++){
			fprintf(merged_file," %d ",currentStudent->stdnt->grades[i]);
		}

		currentStudent=currentStudent->next;
		i++;
		fprintf(merged_file,"\n");
	}

 	fclose(merged_file);
}



void free_list(studentsList* SudentsList) {

	listNode* curr = SudentsList->head;
	listNode* tmp;
	
	while(curr != NULL) {
	
		free(curr->stdnt);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	
	free(SudentsList);
}



int main(int argc, char* argv[]) 
{
	studentsList* SudentsList = init_list();
	
	for(int i =1; i < argc; i++){
	
		int num_students = handle_file(argv[i], SudentsList);
		report_input_file(argv[i],num_students);
}
	sort_grades(SudentsList);
	calc_avg(SudentsList);	
	print_all_avg(SudentsList);
	write_to_file(SudentsList);
	free_list(SudentsList);
};
