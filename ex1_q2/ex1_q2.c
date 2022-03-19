


#include "ex1_q2.h"



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
				
		if((strcmp(studentName, current->stdnt->name)) == 0){
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

student* add_to_list(studentsList* studentsList, char* studentName) {
	
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
	const char delimiter[]=" \t\r\n\v\f";
	char* token = strtok(buffer, delimiter);
	char* studentName;
	student* stdnt;
	int i = 0;
	
	while(token != NULL) {
		
		if(i == 0){
			studentName = token;
			if(is_student_exist(studentName, stdntList)) {
				stdnt = get_student(studentName, stdntList);		
			}
			else {
			  stdnt = add_to_list(stdntList, studentName);	
			}
	
				num_stud++;
		}
			
		else{
			int grade = atoi(token);			
			add_grade(stdnt->grades, grade, stdnt->numOfGrades);
			stdnt->numOfGrades++;
		}
		
	token = strtok(NULL, delimiter);
	i++;
  }
  
  return num_stud;
}

void calc_avg(studentsList* StudentsList) {

	listNode* curr = StudentsList->head;
	student* tempStud;
	int sum  = 0;
	while(curr != NULL) {
		
		tempStud = curr->stdnt;		
		
		for(int i = 0; i < tempStud->numOfGrades; i++){
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

void report_input_file(const char* file_name, int num_stud)
{
 fprintf(stderr, "process: %d file: %s number of students: %d\n",
 getpid(), file_name, num_stud);
}
//-----------------------------------------------
void report_data_summary(int num_stud, double avg)
{
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

int read_and_write(char* inputFile,char* writeFile, int child, studentsList* studentLst) {

	FILE* filePointer = fopen(inputFile, "r");
	int num_students = 0;
	char* buffer = NULL;
	int size =0;	
	int i = 1;
	int lineSize = getline(&buffer, &size, filePointer);     
     	
		while(lineSize >= 0) {
			if(lineSize > 2) { 			
				num_students += handle_row(buffer, studentLst);
			}
			
			lineSize = getline(&buffer, &size, filePointer);
	}

	fclose(filePointer);
	write_to_file(writeFile, child, studentLst);
	buffer = NULL;
	return num_students;
}

void write_to_file(char* writeFile, int child, studentsList* studentLst) {

	FILE* merged_file;
	int saved_stdout = dup(1);
	
	if(child == 0){
		 merged_file = fopen("merged.txt","a");
	}
	else {
	 merged_file = fopen("merged.txt","w");	
	}
	
	dup2(stdout,merged_file);
	listNode* currentStudent=studentLst->head;
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
	dup2(saved_stdout, 1);
	close(saved_stdout);
}

void free_list(studentsList* studentLst) {
	
	listNode* curr = studentLst->head;
	listNode* tmp;
	
	while(curr != NULL) {
	
		free(curr->stdnt);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}

	free(studentLst);
}

int main(int argc, char* argv[]) 
{
	
	char* writeFile = "merged.txt";
	studentsList* studentLst = init_list();
	int saved_stdout = dup(1);
	char* merged_file = "merged.txt";

	for(int i =1; i < argc; i++){
	
		if(fork() == 0) {
			int num_students = read_and_write(argv[i],writeFile, 0, studentLst);
			report_input_file(argv[i],num_students);	
			free_list(studentLst);
			exit(0);
		}
		wait(NULL);	
	}

	read_and_write(writeFile, writeFile , 1, studentLst);
	sort_grades(studentLst);
	calc_avg(studentLst);	
	print_all_avg(studentLst);
	write_to_file(writeFile, 1, studentLst);
	free_list(studentLst);
};
