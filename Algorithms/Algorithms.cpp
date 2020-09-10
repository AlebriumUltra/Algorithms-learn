#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

#define SIZE 3


typedef struct students {
	char LastName[20];
	char Name[20];
	int NumberBook;
	int Number;
};

void SearchStruct(students students[]) {
	char SearchName[20];
	printf("Enter name to search: ");
	scanf("%s", SearchName);
	bool flag = false;
	for (int i = 0; i < SIZE; i++) {
		if (strcmp(SearchName, students[i].Name) == 0) { // Поиск в структурах по имени
			flag = true;
			printf("Search success. Number struct is: %d\n", students[i].Number);
			printf(" Name: %s\n Last name: %s\n Number book: %d", students[i].LastName, students[i].Name, students[i].NumberBook);
		}
	}
	if (!flag) {
		printf("Search failed.");
	}
}









int main() {
	students students[SIZE];
	for (int i = 0; i < SIZE; i++) { // Инициализируем структуры
		printf("Enter name: ");
		scanf("%s", students[i].Name);

		printf("Enter last name: ");
		scanf("%s", students[i].LastName);

		printf("Enter number book: ");
		scanf("%d", &students[i].NumberBook);

		students[i].Number = i + 1;
		printf("\n");
	}
	printf("\n\n");
	SearchStruct(students);
	_getch();
}