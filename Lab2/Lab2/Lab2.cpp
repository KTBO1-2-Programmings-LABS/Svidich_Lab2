#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#pragma warning(disable : 4996)

#define MAX_SIZE 50

// Структура для хранения информации о студенте
typedef struct student {
    char name[50];
    int student_id;
    float gpa;
    struct student* next; // указатель на следующий элемент
} Student;

// Функция для создания нового элемента списка
Student* createStudent(const char name[], int student_id, float gpa) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->name, name);
    newStudent->student_id = student_id;
    newStudent->gpa = gpa;
    newStudent->next = NULL;
    return newStudent;
}

// Функция для вывода списка студентов
void printStudents(Student* head) {
    if (head == NULL) {
        printf("Список студентов пуст\n");
    }
    else {
        Student* current = head;
        while (current != NULL) {
            printf("%s (ID: %d, GPA: %.2f)\n", current->name, current->student_id, current->gpa);
            current = current->next;
        }
    }
}

////////// Включение

// Функция для включения нового элемента в конец списка
void appendStudent(Student** head, const char name[], int student_id, float gpa) {
    Student* newStudent = createStudent(name, student_id, gpa);
    if (*head == NULL) {
        *head = newStudent;
    }
    else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

// Функция для включения нового элемента на заданное пользователем место списка
void insertAtPosition(Student** head, const char name[], int student_id, float gpa, int position) {
    
    if (position < 0) {
        printf("Позиция должна быть неотрицательным числом.\n");
        return;
    }

    Student* newStudent = createStudent(name, student_id, gpa);

    if (position == 0) {
        newStudent->next = *head;
        *head = newStudent;
        return;
    }

    Student* current = *head;
    int currentPosition = 0;

    while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL) {
        printf("В списке меньше элементов, чем заданная позиция.\n");
        return;
    }

    newStudent->next = current->next;
    current->next = newStudent;
}

// Функция для включения нового элемента после элемента с заданной информационной частью
void insertAfter(Student* head, const char targetName[], const char name[], int student_id, float gpa) {
    Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, targetName) == 0) {
            Student* newStudent = createStudent(name, student_id, gpa);
            newStudent->next = current->next;
            current->next = newStudent;
            return;
        }
        current = current->next;
    }

    printf("Элемент с заданным именем не найден.\n");
}

// Функция для включения нового элемента перед элементом с заданной информационной частью
void insertBefore(Student** head, const char targetName[], const char name[], int student_id, float gpa) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    if (strcmp((*head)->name, targetName) == 0) {
        Student* newStudent = createStudent(name, student_id, gpa);
        newStudent->next = *head;
        *head = newStudent;
        return;
    }

    Student* current = *head;

    while (current->next != NULL) {
        if (strcmp(current->next->name, targetName) == 0) {
            Student* newStudent = createStudent(name, student_id, gpa);
            newStudent->next = current->next;
            current->next = newStudent;
            return;
        }
        current = current->next;
    }

    printf("Элемент с заданным именем не найден.\n");
}

// Функция для включения нового элемента в середину списка
void insertInMiddle(Student** head, const char name[], int student_id, float gpa) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    Student* slow = *head;
    Student* fast = (*head)->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Student* newStudent = createStudent(name, student_id, gpa);
    newStudent->next = slow->next;
    slow->next = newStudent;
}

////////// Удаление

// Функция для удаления элемента из конца списка
void deleteFromEnd(Student** head) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Student* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

// Функция для удаления элемента из заданного пользователем места списка
void deleteAtPosition(Student** head, int position) {

    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    if (position < 0) {
        printf("Позиция должна быть неотрицательным числом.\n");
        return;
    }

    if (position == 0) {
        Student* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Student* current = *head;
    int currentPosition = 0;

    while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL || current->next == NULL) {
        printf("В списке меньше элементов, чем заданная позиция.\n");
        return;
    }

    Student* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

// Функция для удаления элемента из головы списка
void deleteFromHead(Student** head) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    Student* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Функция для удаления элемента с заданной информационной частью
void deleteByInfo(Student** head, const char targetName[]) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    if (strcmp((*head)->name, targetName) == 0) {
        Student* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Student* current = *head;

    while (current->next != NULL) {
        if (strcmp(current->next->name, targetName) == 0) {
            Student* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }

    printf("Элемент с заданным именем не найден.\n");
}

// Функция для удаления элемента из середины списка
void deleteFromMiddle(Student** head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Список пуст или содержит только один элемент.\n");
        return;
    }

    Student* slowPtr = *head; // Медленный указатель
    Student* fastPtr = *head; // Быстрый указатель
    Student* prevPtr = NULL;  // Указатель на предыдущий узел перед серединой

    while (fastPtr != NULL && fastPtr->next != NULL) {
        fastPtr = fastPtr->next->next; // Быстрый указатель двигается на два узла вперед
        prevPtr = slowPtr;             // Сохраняем предыдущее значение медленного указателя
        slowPtr = slowPtr->next;       // Медленный указатель двигается на один узел вперед
    }

    // Удаление узла, на который указывает медленный указатель (это узел в середине списка)
    if (prevPtr == NULL) { // Если prevPtr остался NULL, значит удаляемый элемент - голова списка
        *head = (*head)->next;
    }
    else {
        prevPtr->next = slowPtr->next;
    }
    free(slowPtr);
}

/////////

// Вывод пунктов меню функций
int menu_func() {
    int choise;
    puts("\nМеню функций: ");
    puts("1. Включить новый элемент в конец списка");
    puts("2. Включить новый элемент на заданное пользователем место списка");
    puts("3. Включить новый элемент после элемента с заданной информационной частью");
    puts("4. Включить новый элемент перед элементом с заданной информационной частью");
    puts("5. Включить новый элемент в середину списка");
    puts("6. Исключить элемент из середины списка");
    puts("7. Исключить элемент с заданной информационной частью");
    puts("8. Исключить элемент из конца списка");
    puts("9. Исключить элемент из заданного пользователем места списка");
    puts("10. Исключить элемент из головы списка");
    puts("11. Вывод списка");
    puts("12. Выйти");
    puts("Введите номер функции: ");
    scanf("%i", &choise);
    return choise;
}

///////

int main() {
    setlocale(LC_ALL, "Russian");

    Student* head = NULL; // Инициализация списка студентов

    // Добавление студентов в конец списка
    appendStudent(&head, "Иванов Иван", 123, 3.5);
    appendStudent(&head, "Петров Петр", 456, 4.0);
    appendStudent(&head, "Сидоров Сидор", 789, 3.7);

    printStudents(head);

    // Переменные для меню
    int choise = menu_func();
    char name[MAX_SIZE];
    int student_id;
    float gpa;
    int position;
    char targetName[MAX_SIZE];

    // Меню функций
    while (choise != 12) {
        if (choise < 6) {
            puts("Введите данные студента: ФИО ID GPA");
            scanf("%s", &name);
            scanf("%i", &student_id);
            scanf("%f", &gpa);
        }
        if (choise == 3 || choise == 4 || choise == 7) {
            puts("Введите искомое ФИО:");
            scanf("%s", &targetName);
        }
        if (choise == 2 || choise == 9) {
            puts("Введите искомое место:");
            scanf("%i", &position);
            position--;
        }
        switch (choise) {
        case 1:
            // Включение нового элемента в конец списка
            appendStudent(&head, name, student_id, gpa);
            break;
        case 2:
            // Включение нового элемента на заданное пользователем место списка
            insertAtPosition(&head, name, student_id, gpa, position);
            break;
        case 3:
            // Включение нового элемента после элемента с заданной информационной частью
            insertAfter(head, targetName, name, student_id, gpa);
            break;
        case 4:
            // Включение нового элемента перед элементом с заданной информационной частью
            insertBefore(&head, targetName, name, student_id, gpa);
            break;
        case 5:
            // Включение нового элемента в середину списка
            insertInMiddle(&head, name, student_id, gpa);
            break;
        case 6:
            deleteFromMiddle(&head);
            break;
        case 7:
            // Удаление элемента с заданной информационной частью
            deleteByInfo(&head, targetName);
            break;
        case 8:
            // Удаление элемента из конца списка
            deleteFromEnd(&head);
            break;
        case 9:
            // Удаление элемента из заданного пользователем места списка
            deleteAtPosition(&head, position);
            break;
        case 10:
            // Удаление элемента из головы списка
            deleteFromHead(&head);
            break;
        case 11:
            // Вывод списка студентов
            printf("Список студентов:\n");
            printStudents(head);
            break;
        case 12:
            return 0;
        }
        choise = menu_func();
    }

}