


#include "ex1_q1.h"



studentsList* initList() {
	
	
				//rr printf("inside initList\n");
		
	studentsList* stdList = (studentsList*)malloc(sizeof(studentsList));
	
	stdList->next = NULL;
	stdList->head = NULL;
	
	
	
	 //rr printf("exiting initList\n");
	
	return stdList;

}

student*  getStudent(char* studentName, studentsList* list ){
	
	
		//rr	printf("inside getStudent\n");
	
	listNode* current = list->head;
	
	while(current != NULL) {
		
		if(!(strcmp(studentName, current->stdnt->name)))
		{
			
			return current->stdnt;
		
		}
	
		current = current->next;
	
	}
	
	//rr	printf("exiting getStudent\n");
	
	return NULL;
}

int checkIfStudentExists(char* studentName, studentsList* list ){
	
	
	//rr	printf("inside checkIfStudentExists\n");
	
	
	listNode* current = list->head;
	
	while(current != NULL) {
		
		
	//rr	printf("%s\n", current->stdnt->name);
		
		if((strcmp(studentName, current->stdnt->name)) == 0)
		{
			
			return 1;
		
		}
	
		current = current->next;
	
	}
	
	
	//rr	printf("exiting checkIfStudentExists\n");
	
	return 0;
}



void insertNodeToTail(studentsList* studentsList, listNode* stdntNode){

		
	//rr	printf("inside insertNodeToTail\n");

	if(studentsList->tail == NULL)
	{
	
	//	printf("inserting %s to head of list\n", stdntNode->stdnt->name);
		
		studentsList->tail = studentsList->head = stdntNode;
	
	
	}
	
	else{
	
	//rr	printf("inserting %s to tail of list\n", stdntNode->stdnt->name);	
		studentsList->tail->next = stdntNode;


		studentsList->tail = stdntNode;	
	
	}	



	studentsList->tail->next = NULL;

	//rr printf("exiting insertNodeToTail\n");
}

student* addNewStudentToList(studentsList* studentsList, char* studentName) {
	
	//rr printf("inside addNewStudentToList\n");
	
	listNode* stdntNode = (listNode*)malloc(sizeof(listNode)); 
	student* newstdnt = (student*)malloc(sizeof(student));
	
	stdntNode->stdnt = newstdnt;
	strcpy(stdntNode->stdnt->name , studentName);	
	
	insertNodeToTail(studentsList, stdntNode);
	
	//rr printf("student name: %s was added to the list\n", stdntNode->stdnt->name);
	
	//rr printf("exiting addNewStudentToList\n");
	

	return stdntNode->stdnt;

}




void addGrade(int gradesArr[], int gradeToAdd, int index) {
	
	
	
	//rr printf("inside addGrade. grade is: %d at index: %d\n", gradeToAdd, index);
	gradesArr[index] = gradeToAdd;
	
	
	//rr printf("exiting addGrade\n");
	
	
}

int handleRow(char* buffer, studentsList* stdntList) {
	
	
	int num_stud = 0;
	//rr printf("inside handleRow\n");
	
	const char delimiter[2] = " ";
	
	//now we will use strtok
	
	char* token = strtok(buffer, delimiter);
	char* studentName;
	
	student* stdnt;
	int i = 0;
	
	while(token != NULL) 
	{
		
		
		
			//rr printf("token: %s\n", token);
		
			if(i == 0) 
			{
			
		
				studentName = token;
				if(checkIfStudentExists(studentName, stdntList)) {
				
				
						stdnt = getStudent(studentName, stdntList);
						
				
				}
	
				else {
					
					stdnt = addNewStudentToList(stdntList, studentName);
					
				}

			//TODO: check if a name can apear twice in a file
		
			num_stud++;
			
			}
	
		
			else 
			{
			
			
				
				
				
				// add grade to grades arr;
				int grade = atoi(token);
			//rr	printf("grade is: %d\n", grade);
					
					
					addGrade(stdnt->grades, grade, stdnt->numOfGrades);
					stdnt->numOfGrades++;
		
			
			
			
			}
		
			
		
			token = strtok(NULL, delimiter);
			i++;
	
	
		}
	
	//rr printf("exiting handleRow\n");
	return num_stud;
}

int handleFile(char* fileName, studentsList* StudentsList) {
	
	
	int num_students = 0;
	//rr printf("inside handlefile\n");
	//rr printf("file name is: %s\n",fileName);
	FILE* filePointer = fopen(fileName, "r");
	
	
	char* buffer = NULL;
	
	
	int size =0;	
	int i = 1;
	
	int lineSize = getline(&buffer, &size, filePointer);
	
	//rr printf("line size : %d\n", lineSize);
	
     
     	while(lineSize >= 0) 
      {
		//close the file at the end
		
		
		
		
	//	rr printf("line from the file: %s\n", buffer);
		
		
		if(lineSize > 2) { // could be an empty line;
				
				
		num_students += handleRow(buffer, StudentsList);
			 
		}
		
		
		
	//	rr printf("%d iteration in handleFile\n", i);
		
		lineSize = getline(&buffer, &size, filePointer);
		
	}

	
	
	fclose(filePointer);
	buffer = NULL;
	
	//rr printf("exiting handleFile\n");
	return num_students;
}




void calcAverage(studentsList* StudentsList) {



	//rr printf("inside calcAverage\n");

	listNode* curr = StudentsList->head;
	student* tempStud;
	int sum  = 0;
	while(curr != NULL) {
	
	
		tempStud = curr->stdnt;
		
		for(int i = 0; i < tempStud->numOfGrades; i++)
		{
		
			
			sum += tempStud->grades[i];
		
		
		}
	
	
		
		tempStud->average = (float)sum/(tempStud->numOfGrades);
		sum = 0;
		curr = curr->next;
	
	}


	//rr printf("exiting calcAverage\n");
	
	
	

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









void printList(studentsList* studentList){

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


int main(int argc, char* argv[]) 
{


studentsList* SudentsList = initList();


for(int i =1; i < argc; i++){
	
	//printf("the number of arguments: %d\n", argc);
	//printf("%s\n", argv[i]);
	
	
	
int num_students = handleFile(argv[i], SudentsList);

	report_input_file(argv[i],num_students);
	
}


	sort_grades(SudentsList);
	calcAverage(SudentsList);	
	//printList(SudentsList);
	
	print_all_avg(SudentsList);
	

	write_to_file(SudentsList);



//TODO

free(SudentsList);


};
