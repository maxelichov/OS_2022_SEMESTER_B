


#include "ex1_q1.h"




studentsList* initList() {
	
	
				printf("inside initList\n");
		
	studentsList* stdList = (studentsList*)malloc(sizeof(studentsList));
	
	stdList->next = NULL;
	stdList->head = NULL;
	
	
	
	printf("exiting initList\n");
	
	return stdList;

}

student*  getStudent(char* studentName, studentsList* list ){
	
	
			printf("inside getStudent\n");
	
	listNode* current = list->head;
	
	while(current != NULL) {
		
		if(!(strcmp(studentName, current->stdnt->name)))
		{
			
			return current->stdnt;
		
		}
	
		current = current->next;
	
	}
	
	printf("exiting getStudent\n");
	
	return NULL;
}

int checkIfStudentExists(char* studentName, studentsList* list ){
	
	
		printf("inside checkIfStudentExists\n");
	
	
	listNode* current = list->head;
	
	while(current != NULL) {
		
		
		printf("%s\n", current->stdnt->name);
		
		if((strcmp(studentName, current->stdnt->name)) == 0)
		{
			
			return 1;
		
		}
	
		current = current->next;
	
	}
	
	
		printf("exiting checkIfStudentExists\n");
	
	return 0;
}



void insertNodeToTail(studentsList* studentsList, listNode* stdntNode){

		
		printf("inside insertNodeToTail\n");

	if(studentsList->tail == NULL)
	{
		studentsList->tail = studentsList->head = stdntNode;
	
	
	}
	
	else{
	
		studentsList->tail->next = stdntNode;


		studentsList->tail = stdntNode;	
	
	}	



	studentsList->tail->next = NULL;

	printf("exiting insertNodeToTail\n");
}

student* addNewStudentToList(studentsList* studentsList, char* studentName) {
	
	printf("inside %s, addNewStudentToList\n");
	
	listNode* stdntNode = (listNode*)malloc(sizeof(listNode)); 
	student* newstdnt = (student*)malloc(sizeof(student));
	
	stdntNode->stdnt = newstdnt;
	strcpy(stdntNode->stdnt->name , studentName);	
	
	insertNodeToTail(studentsList, stdntNode);
	
	printf("student name: %s\n", stdntNode->stdnt->name);
	
	printf("exiting addNewStudentToList\n");
	

	return stdntNode->stdnt;

}




void addGrade(int gradesArr[], int gradeToAdd, int index) {
	
	
	
	printf("inside addGrade. grade is: %d at index: %d\n", gradeToAdd, index);
	gradesArr[index] = gradeToAdd;
	
	
	printf("exiting addGrade\n");
	
	
}

void handleRow(char* buffer, studentsList* stdntList) {
	
	printf("inside handleRow\n");
	
	const char delimiter[2] = " ";
	
	//now we will use strtok
	
	char* token = strtok(buffer, delimiter);
	char* studentName;
	
	student* stdnt;
	int i = 0;
	
	while(token != NULL) 
	{
		
		
		
			printf("token : %s\n", token);
		
			if(i == 0) 
			{
			
		
				studentName = token;
				if(checkIfStudentExists(studentName, stdntList)) {
				
				
						stdnt = getStudent(studentName, stdntList);
						
				
				}
	
				else {
					
					stdnt = addNewStudentToList(stdntList, studentName);
				}

	
			}
	
		
			else 
			{
			
			
				
				
				
				// add grade to grades arr;
				int grade = atoi(token);
				printf("grade is: %d\n", grade);
					
					
					addGrade(stdnt->grades, grade, stdnt->numOfGrades);
					stdnt->numOfGrades++;
		
			
			}
		
			
		
			token = strtok(NULL, delimiter);
			i++;
		}
	
	printf("exiting handleRow\n");
}

void handleFile(char* fileName, studentsList* StudentsList) {
	
	printf("inside handlefile\n");
	printf("file name is: %s\n",fileName);
	FILE* filePointer = fopen(fileName, "r");
	
	
	char* buffer = NULL;
	
	
	int size =0;	
	int i = 1;
	
	int lineSize = getline(&buffer, &size, filePointer);
	
	printf("line size : %d\n", lineSize);
	
     
     	while(lineSize >= 0) 
      {
		//close the file at the end
		
		
		
		
		printf("line from the file: %s\n", buffer);
		
		
		if(lineSize > 0) { // could be an empty line;
				
				
		handleRow(buffer, StudentsList);
			 
		}
		
		
		
		printf("%d iteration in handleFile\n", i);
		lineSize = getline(&buffer, &size, filePointer);
		
	}

	
	
	fclose(filePointer);
	
	printf("exiting handleFile\n");
}




void calcAverage(studentsList* StudentsList) {



	printf("inside calcAverage\n");

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


	printf("exiting calcAverage\n");
	
	
	

}




void printList(studentsList* studentList){

listNode* currentStudent=studentList->head;
int i = 1;

while(currentStudent!=NULL){
printf("student number %d, name: %s\nstudent grades: ",i, currentStudent->stdnt->name);
for(int i=0;i<currentStudent->stdnt->numOfGrades;i++){
printf(" %d ",currentStudent->stdnt->grades[i]);


}

printf("\naverage: %lf\n",currentStudent->stdnt->average);
currentStudent=currentStudent->next;
i++;

}


}


int main(int argc, char* argv[]) 
{


studentsList* SudentsList = initList();


for(int i =1; i < argc; i++){
	
	printf("the number of arguments: %d\n", argc);
	printf("%s\n", argv[i]);
	handleFile(argv[i], SudentsList);
	
	
	
}


	calcAverage(SudentsList);
	
	printList(SudentsList);
	


//TODO

free(SudentsList);


};
