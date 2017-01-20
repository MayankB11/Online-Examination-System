/* 
	Name : Mayank Bhushan
	Roll No : 15CS30019
	Online Examination System
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define EXAM_TIME  600 // in seconds
#define MAX_QUESTIONS 10
#define INVALID printf("\nInvalid choice. Try again.\n");
#define CLEAR system("clear");

typedef struct sMarks{
	char roll_no[50];
	char sub_code[50];
	time_t t;
	double percentage_marks;
}marks;

typedef struct studentDetails{
	char name[50];
	char roll_no[50];
	char email[50];
	char contact[50];
	char password[50];
}student_details;
 
typedef struct adminDetails{
	char email[50];
	char password[50];
}admin_details;
 
typedef struct subjectDetails{
 	char sub_name[50];
 	char sub_code[50];
}subject_details;

typedef struct quest{
	char sub_code[50];
	char ques[100];
	char options[4][50];
	int correct_ans;
}questions;

 void add_subjects(){
 	FILE *f;
 	subject_details s,s1;
 	char c='Y',*temp;
 	f=fopen("subjects.bin","ab+");
 	fseek(f,0,SEEK_SET);
 	CLEAR
 	do{
		fflush(stdin);
		getchar();
 		printf("\nEnter Subject Name : ");
 		fgets(s.sub_name,50,stdin);
 		printf("\nEnter Subject Code : ");
 		fgets(s.sub_code,50,stdin);
 		fseek(f,0,SEEK_SET);
 		do{
 			fread(&s1,sizeof(s1),1,f);
 			if(feof(f)){
 				break;
 			}
 			if(strcmp(s1.sub_name,s.sub_name)==0||strcmp(s.sub_code,s1.sub_code)==0){
 				break;
 			}
 		}
 		while(1);
 		if(feof(f)){
 			fwrite(&s,sizeof(s),1,f);
 			printf("\nSubject succesfully added.\n\nDo you wish to add more subjects ? <Y/N> : ");
 		}
 		else{
 			if(strcmp(s1.sub_name,s.sub_name)==0){
 				printf("\nSubject Name already exists.\n\nDo you want to try again ? <Y/N> : " );
 			}
 			else{
 				printf("\nSubject Code already exists.\n\nDo you want to try again ? <Y/N> : ");
 			}
 		}
		scanf("%c",&c);
 	}
 	while(c!='N'&&c!='n');
 	fclose(f);
 }

void add_questions(){
	FILE *f,*f1;
	subject_details s,s1;
	int i,flag=0;
	questions q;

	f=fopen("subjects.bin","rb");
	CLEAR
	do{
		printf("\nEnter Subject Code : ");
		fflush(stdin);
		getchar();
		fgets(s1.sub_code,50,stdin);
		do{
			fread(&s,sizeof(s),1,f);
			if(feof(f)){
				break;
			}
			if(strcmp(s.sub_code,s1.sub_code)==0){
				flag=1;
				break;				
			}
		}
		while(1);
		if(flag==0){
			CLEAR
			printf("\nSubject Code doesn't exists.\n");
			fseek(f,0,SEEK_SET);
			printf("\n** List of registered subjects ** \n");
			do{
				fread(&s,sizeof(s),1,f);
				if(feof(f)){
					break;
				}
				printf("\t%s",s.sub_code);
			}
			while(1);
			fclose(f);
			break;
		}
		else{
			fclose(f);
			char ch1='Y';
			f1=fopen("questions.bin","ab");
			do{
				strcpy(q.sub_code,s1.sub_code);
				printf("\nEnter question : ");
				fflush(stdin);
				getchar();
				fgets(q.ques,100,stdin);
				for(i=0;i<4;i++){
					printf("\nEnter Option %d : ",i+1);
					fgets(q.options[i],100,stdin);
				}
				printf("\nEnter the correct option(1-4) : ");
				scanf("%d",&q.correct_ans);
				CLEAR
				printf("\nQuestion successfully added.\n\nDo you wish to add more questions to this subject ? <Y/N> : ");
				fflush(stdin);
				getchar();
				scanf("%c",&ch1);
				fwrite(&q,sizeof(q),1,f1);
			}
			while(ch1!='N'&&ch1!='n');
			fclose(f1);
			break;
		}
	}	
	while(1);
}

void marks_students(){	
	FILE *f;
	marks s;
	struct tm * timeinfo;
	char roll[50];
	f=fopen("marks.bin","rb");
	CLEAR
	printf("\n** List of Students and their Marks** \n");
	while(fread(&s,sizeof(s),1,f)){
		{
			timeinfo=localtime(&s.t);		
			printf("\nRoll No : %sSubject Code : %sDate of Test Taken : %sPercentage Marks : %lf%%\n",s.roll_no,s.sub_code,asctime(timeinfo),s.percentage_marks);
		}
	}
	fclose(f);
	fflush(stdin);
	getchar();
}

void admin_functions(){
	FILE *f;
	int ch;
	CLEAR
	do{
		printf("\n1. Add Subject\n2. Add Questions \n3. Check Marks of Students\n4. LogOut!\n\nEnter your choice (1-4) : ");
		scanf("%d",&ch);

		switch(ch){
			case 1: 
				add_subjects();
				break;
			case 2:
				add_questions();
				break;
			case 3:
				marks_students();
				break;
			case 4:
				CLEAR
				break;
			default :
				CLEAR
				INVALID
		}
	}
	while(ch!=4);
}

void admin_login(){
	FILE *f;
	f=fopen("admin.bin","rb");
	admin_details ad,ad1;
	int ch,flag=0;
	CLEAR
	do{	
		fseek(f, 0, SEEK_SET);
		printf("\nEnter email-id : ");
		scanf("%s",ad.email);
		do{
			fread(&ad1,sizeof(ad1),1,f);
			if(feof(f)){
				break;
			}
			if(strcmp(ad1.email,ad.email)==0){
				flag=1;
				break;
			}
		}
		while(1);
		if(flag==1){
			break;
		}
		else{
			flag=1;
			printf("\nEmail-id not found in record.\n");
			fclose(f);
			return;
		}
	}
	while(ch!=2);
	if(flag==0){
		return;
	}
	printf("\nEnter your password for email-id %s : ",ad.email);
	scanf("%s",ad.password);
	do{
		if(strcmp(ad.password,ad1.password)==0){
			admin_functions();
			break;
		}
		else{
			flag=1;
			printf("\nPassword doesn't match.\n1. Enter password again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
			do{
				scanf("%d",&ch);
				switch(ch){
					case 1 :
						printf("\nEnter your password for email-id %s : ",ad.email);
						scanf("%s",ad.password);
						break;
					case 2 :
						CLEAR
						flag=0;
						break;
					default :
						CLEAR
						INVALID
						printf("\n1. Enter password again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
				}
				if(strcmp(ad.password,ad1.password)==0){
					admin_functions();
					break;
				}
			}
			while(ch!=2);
			if(flag==0){
				break;
			}
		}
	}
	while(1);
	fclose(f);
}
 
void add_admin(){
	FILE *f;
	admin_details ad,ad1;
	int ch,flag=0;
	char v[10],v1[10];
	f=fopen("passkey.bin","rb");
	fread(&v,sizeof(v),1,f);
	fclose(f);
	CLEAR
	do{
		printf("\n\n1. Enter Security Key\n2. Back to Previous Menu\n\nEnter your choice (1-2) : ");
		scanf("%d",&ch);
		flag=1;
		switch(ch){
			case 1:
				printf("\nEnter Security Key : ");
				scanf("%s",v1);
				if(strcmp(v,v1)!=0){
					CLEAR
					printf("\n\nInvalid Security Key. Try again.\n\n");
					flag=0;	
				}				
				break;
			case 2:
				CLEAR
				break;
			default : 
				CLEAR
				INVALID
		}
	}
	while(!(ch==1&&flag==1)&&ch!=2);
	if(ch==2){
		return;
	}

	f=fopen("admin.bin","rb+");
	printf("\nEnter email-id : "); // add to check if it already exists
	scanf("%s",ad.email);
	
	while(fread(&ad1,sizeof(ad1),1,f)){
		if(strcmp(ad1.email,ad.email)==0){
			CLEAR
			printf("\nAdministrator already registered. Try logging in. \n");
			fclose(f);
			return;
		}
	}

	printf("\nEnter your password : ");
	scanf("%s",ad.password);
	//ad.password=getpass("\nEnter your password : ");
	fwrite(&ad, sizeof(admin_details), 1, f);
	fclose(f);
	CLEAR
	printf("\nNew Administrator has been succesfully added into the system.\n");
}

/* 
void delete_admin(){
 	FILE *f;
	admin_details ad;
	int ch,flag=0;
	char v[10],v1[10];
	f=fopen("passkey.bin","rb");
	fread(&v,sizeof(v),1,f);
	fclose(f);
	do{
		printf("\n\n1. Enter Security Key\n2. Back to Previous Menu\n\nEnter your choice : ");
		scanf("%d",&ch);
		flag=1;
		switch(ch){
			case 1:
				printf("\nEnter Security Key : ");
				scanf("%s",v1);
				if(strcmp(v,v1)!=0){
					printf("\n\nInvalid Security Key. Try again.\n\n");
					flag=0;	
				}				
				break;
			case 2:
				break;
			default : INVALID
		}
	}
	while(!(ch==1&&flag==1)&&ch!=2);
	if(ch==2){
		return;
	}

	f=fopen("admin.bin","ab");
	printf("Enter email-id : "); // add to check if it already exists
	scanf("%s",ad.email);
	printf("\nEnter your password : ");
	scanf("%s",ad.password);
	//ad.password=getpass()
	//fwrite(&ad, sizeof(admin_details), 1, f); to delete the admin from here.
	fclose(f);
	CLEAR
	printf("\nNew Administrator has been succesfully added into the system.\n");
}*/
 
void admin(){
	int ch;
	CLEAR
	do{
		printf("\n **ADMIN MENU**\n\n1. Login\n2. Add Administrator\n3. Back to Previous Menu\n\nEnter your choice (1-4) : ");
		scanf("%d",&ch);
		switch(ch){
			case 1: 
				admin_login();
				break;
			case 2:
				add_admin();
				break;
			case 3:
				CLEAR
				break;
			default :
				CLEAR
				INVALID
		}
	}
	while(ch!=3);
}

void take_exam(char* roll_no){
	
	time_t start_time,cur_time;
	FILE *f;
	int i=0,flag=0,correct=0,ch;
	subject_details s,s1;
	questions q;
	marks m;
	f=fopen("subjects.bin","rb");
	printf("\n** List of registered subjects ** \n");
	do{
		fread(&s,sizeof(s),1,f);
		if(feof(f)){
			break;
		}
		printf("\t%d - %s\n",i+1,s.sub_code);
		i++;
	}
	while(1);
	i=0;
	printf("\nEnter Subject Code : ");
	fflush(stdin);
	getchar();
	fgets(s1.sub_code,50,stdin);
	fseek(f,0,SEEK_SET);
	while(fread(&s,sizeof(s),1,f)){
		if(strcmp(s.sub_code,s1.sub_code)==0){
			flag=1;
			break;
		}
	}
	fclose(f);
	if(flag==0){
		printf("\nYou have entered an invalid Subject Code.\n");
	}
	else{
		f=fopen("questions.bin","rb");
		time(&start_time);
		while(i<MAX_QUESTIONS&&(fread(&q,sizeof(q),1,f))){
			if(strcmp(q.sub_code,s1.sub_code)==0){
				printf("\nQuestion %d :\n%s\n1. %s\n2. %s\n3. %s\n4. %s\n\nEnter your choice (1-4) : ",i+1,q.ques,q.options[0],q.options[1],q.options[2],q.options[3]);
				scanf("%d",&ch);
				time(&cur_time);
				if(ch==q.correct_ans&&cur_time-start_time<=EXAM_TIME){
					correct++;
				}
				if(cur_time-start_time>=EXAM_TIME){
					printf("\nTime Up.\n");
					break;
				}
				i++;	
				printf("\nInit1 %d\n",i );
			}
			time(&cur_time);
			if(cur_time-start_time>=EXAM_TIME){
				printf("\nTime Up.\n");
				break;
			}
		}
		fclose(f);
		if(i==0){
			printf("\nAt present there are no questions for this subject.\nSorry for the inconvenience caused.\n");
		}
		else{
			m.t=start_time;
			f=fopen("marks.bin","ab+");
			strcpy(m.roll_no,roll_no);
			strcpy(m.sub_code,s1.sub_code);
			m.percentage_marks=((double)correct/i)*100;
			printf("\nPercentage Marks Scored : %lf ",m.percentage_marks);
			fwrite(&m,sizeof(m),1,f);
			fclose(f);
		}
	}
}

void check_marks(char* roll_no){
	FILE *f;
	marks s;
	struct tm * timeinfo;
	char roll[50];
	strcpy(roll,roll_no);
	f=fopen("marks.bin","rb");
	printf("\n** List of Subjects Enrolled and Marks **\n");
	while(fread(&s,sizeof(s),1,f)){
		if(strcmp(s.roll_no,roll)==0){
			timeinfo=localtime(&s.t);		
			printf("Subject Code : %sDate of Test Taken : %sPercentage Marks : %lf%%\n",s.sub_code,asctime(timeinfo),s.percentage_marks);
		}
	}
	fclose(f);
	fflush(stdin);
	getchar();
}

void student_functions(char* roll_no){
	FILE *f;
	int ch;

	do{
		printf("\n1. Take Exam\n2. Check Previous Marks\n3. LogOut!\n\nEnter your choice (1-3) : ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				take_exam(roll_no);
				break;
			case 2:
				check_marks(roll_no);
				break;
			case 3:
				CLEAR
				break;
			default:
				CLEAR
				INVALID
		}
	}
	while(ch!=3);
}

void student_login(){
	FILE *f;
	f=fopen("students.bin","rb");
	student_details sd,sd1;
	int ch,flag=1;

	do{
		fseek(f,0,SEEK_SET);	
		printf("\nEnter Roll No : ");
		fflush(stdin);
		getchar();
		fgets(sd.roll_no,50,stdin);
		do{
			if(!fread(&sd1,sizeof(sd1),1,f)){
				break;
			}

			if(strcmp(sd1.roll_no,sd.roll_no)==0){
				break;
			}
		}
		while(1);

		if(strcmp(sd1.roll_no,sd.roll_no)==0){
			break;
		}
		else{
			flag=1;
			printf("\nRoll No not found in record.\n1. Enter Roll No again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
			do{
				scanf("%d",&ch);
				switch(ch){
					case 1 :
						break;
					case 2 :
						CLEAR
						flag=0;
						break;
					default :
						CLEAR
						INVALID
						printf("\n1. Enter Roll No again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
				}
			}
			while(ch!=1&&ch!=2);
		}
	}
	while(ch!=2);
	if(flag==0){
		return;
	}
	printf("\nEnter your password : ");
	fgets(sd.password,50,stdin);
	do{
		if(strcmp(sd.password,sd1.password)==0){
			student_functions(sd.roll_no);
			break;
		}
		else{
			flag=1;
			printf("\nPassword doesn't match.\n1. Enter password again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
			do{
				scanf("%d",&ch);
				switch(ch){
					case 1 :
						printf("\nEnter your password : "	);
						scanf("%s",sd.password);
						break;
					case 2 :
						CLEAR
						flag=0;
						break;
					default :
						CLEAR
						INVALID
						printf("\n1. Enter password again.\n2. Back to Previous Menu.\nEnter your choice (1-2) : ");
				}
				if(strcmp(sd.password,sd1.password)==0){
					student_functions(sd.roll_no);
					break;
				}
			}
			while(ch!=2);
			if(flag==0){
				break;
			}
		}
	}
	while(1);
	fclose(f);
} 

void student_register(){

	FILE *f;
	int flag=1;
	f=fopen("students.bin","ab+");
	fseek(f,0,SEEK_SET);
	student_details sd,sd1;
	fflush(stdin);
	getchar();
	printf("\nEnter Name : ");
	fgets(sd.name,50,stdin);
	printf("\nEnter Roll No : ");
	fgets(sd.roll_no,50,stdin);
	printf("\nEnter Email-id : ");
	fgets(sd.email,50,stdin);
	printf("\nEnter Phone Number : ");
	fgets(sd.contact,50,stdin);
	printf("\nEnter Password : ");
	fgets(sd.password,50,stdin);

	do{
		fread(&sd1,sizeof(sd1),1,f);
		if(feof(f)){
			break;
		}
		if(strcmp(sd1.roll_no,sd.roll_no)==0){
			flag=0;
			break;
		}
	}
	while(1);
	if(flag==0){
		CLEAR
		printf("\nStudent has already registered.\n");
	}
	else{
		fwrite(&sd,sizeof(sd),1,f);
		CLEAR
		printf("\nStudent has been successfully registered.\n");
	}
	fclose(f);
}

void student(){
	int ch;
 	do{
 		printf("\n **STUDENT MENU**\n\n1. Login\n2. Register\n3. Back to Previous Menu\n\nEnter your choice (1-3) : ");
 		scanf("%d",&ch);
 		switch(ch){
 			case 1 :
 				student_login();
 				break;
 			case 2 :
 				student_register();
 				break;
 			case 3:
 				CLEAR
 				break;
 			default :
 				CLEAR
 				INVALID
 		}
 	}
 	while(ch!=3);
}
 
void main_menu(){
	int ch;
	CLEAR
	do{
		printf("\n ** Welcome to Online Examination System **\n\n");
		printf("1. Administrator\n2. Student\n3. Exit\n\nEnter your choice (1-3) : ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				admin();
				break;
			case 2:
				student();
				break;
			case 3:
				break;
			default :
				CLEAR
				INVALID
		}
	}
	while(ch!=3);
}

int main(){
 
	double seconds;
	FILE *f;
	f=fopen("admin.bin","ab+");
	fclose(f);
	f=fopen("students.bin","ab+");
	fclose(f);
	f=fopen("subjects.bin","ab+");
	fclose(f);
	f=fopen("questions.bin","ab+");
	fclose(f);
	f=fopen("marks.bin","ab+");
	fclose(f);
	main_menu();
 
 	marks_students();
 	printf("\n\n ** THANKS FOR USING OUR PROGRAM **\n");
	
	return 0;
}
