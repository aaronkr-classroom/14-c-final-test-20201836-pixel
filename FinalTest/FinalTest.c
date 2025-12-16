#include <stdio.h>
#include <malloc.h>

typedef struct Student{
	unsigned char name[50];
	int kor;
	int eng;
	int math;
	int total;
	float avg;
	int rank;
	struct Student* next;

	 // 다음 노드를 가리킬 포인터
} Student;
struct Student* head = NULL;
void OpenFiles() {
	FILE *fp = fopen("students.dat", "rb");
	if (NULL == fp) {
		printf("입력 파일 열기 실패\n");
		return;
	}
	Student* temp = head;
	while (temp != NULL) {
		fwrite(temp, sizeof(Student), 1, fp);
		temp = temp->next;	
	}
	fclose(fp);
	
}	

void saveToFile() {
	FILE* fp = fopen("students.dat", "wb");
	if (fp == NULL) {
		printf("출력 파일 열기 실패\n");
		return;
	}
	Student* temp = head;
	while (temp != NULL) {
		fwrite(temp, sizeof(Student), 1, fp);
		temp = temp->next;
	}
	fclose(fp);
}

void loadFromFile() {
	FILE* fp = fopen("students.dat", "rb");
	if (fp == NULL) {
				printf("입력 파일 열기 실패\n");
				return;	
	}
	while (1) {
		Student* newNode = (Student*)malloc(sizeof(Student));
		if(fread(newNode, sizeof(Student), 1, fp) != 1) {
			free(newNode);
			break;
		}
		newNode->next = NULL;

		if(head == NULL) {
			head = newNode;
		} else {
			Student* temp = head;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		fclose(fp);	

	}
	
}
void insertStudent(char* name, int kor, int eng, int math) {
	Student* newNode = (Student*)malloc(sizeof(Student));
	printf("이름: ");
	scanf_s("%s", newNode->name, sizeof(newNode->name));
	printf("국어: ");
	scanf_s("%d", &newNode->kor);
	printf("영어: ");
	scanf_s("%d", &newNode->eng);
	printf("수학: ");
	scanf_s("%d", &newNode->math);
	newNode->total = newNode->kor + newNode->eng + newNode->math;
	newNode->avg = newNode->total / 3.0f;
	newNode->rank = 1;
	newNode->next = NULL;

	
	if(head == NULL) {
		head = newNode;
	} else {
		Student* temp = head;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}
void calculateRanks() {
	if (head == NULL) {
		return;
	}
	Student* p1 = head;
	while (p1 != NULL) {
		p1->rank = 1;
		Student* p2 = head;
		while (p2 != NULL) {
			if (p1 != p2 && p1->total < p2->total) {
				p1->rank++;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}
void printStudents() {
	
	if(head == NULL) {
		printf("학생 정보가 없습니다.\n");
		return;
	}
	calculateRanks();
	Student* temp = head;
	
	printf("이름\t국어\t영어\t수학\t총점\t평균\t순위\n");
	printf("------------------------------------------------------\n");
	while(temp != NULL) {
		printf("%s\t%d\t%d\t%d\t%d\t%.2f\t%d\n", temp->name, temp->kor, temp->eng, temp->math, temp->total, temp->avg, temp->rank);
		temp = temp->next;
	}
}


int main(){
	
	int choice;
	char name[50];
	int kor = 0, eng = 0, math = 0;
	while(1) {
		printf("[Menu]\n");
		printf("1. .dat 파일에서 학생 정보 불러오기\n");
		printf("2. 추가 학생 정보 입력\n");
		printf("3. .dat파일 저장\n");
		printf("4. 성적 확인\n");
		printf("5. 종료\n");
		printf("선택: ");
		scanf_s("%d", &choice);
		switch(choice) {
			case 1:
				loadFromFile();
				break;
			case 2:
				insertStudent(name, kor, eng, math);
				break;
			case 3:
				saveToFile();
				printf(".dat파일 저장 완료\n");

			case 4:
				printStudents();
				break;
			case 5:
				printf("프로그램 종료\n");	
			default:
				printf("잘못된 선택입니다. 다시 시도하세요.\n");
		}
	}
	return 0;
}