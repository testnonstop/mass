#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура студента
typedef struct {
    int curs;
    int age;
    int marks_counts;
    int* marks;
    const char* full_name;
} Student;

// 1. Функция ввода данных студента
Student input_student() {
    Student student;

    printf("Введите ФИО студента: ");
    char name_buffer[256];
    fgets(name_buffer, sizeof(name_buffer), stdin);
    // Удаляем символ перевода строки, если он есть
    size_t len = strlen(name_buffer);
    if (len > 0 && name_buffer[len - 1] == '\n') {
        name_buffer[len - 1] = '\0';
    }
    student.full_name = strdup(name_buffer); // Выделяем память и копируем строку

    printf("Введите курс: ");
    scanf_s("%d", &student.curs);

    printf("Введите возраст: ");
    scanf_s("%d", &student.age);

    printf("Введите количество оценок: ");
    scanf_s("%d", &student.marks_counts);

    // Выделяем память для массива оценок
    student.marks = (int*)malloc(student.marks_counts * sizeof(int));
    if (student.marks == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для оценок!\n");
        exit(1);
    }

    printf("Введите оценки через пробел: ");
    for (int i = 0; i < student.marks_counts; i++) {
        scanf_s("%d", &student.marks[i]);
    }

    return student;
}

// 2. Функция вывода данных студента
void print_student(const Student* student) {
    printf("\n--- Данные студента ---\n");
    printf("ФИО: %s\n", student->full_name);
    printf("Курс: %d\n", student->curs);
    printf("Возраст: %d\n", student->age);
    printf("Количество оценок: %d\n", student->marks_counts);
    printf("Оценки: ");
    for (int i = 0; i < student->marks_counts; i++) {
        printf("%d ", student->marks[i]);
    }
    printf("\n");
}

// 3. Функция очистки памяти студента
void free_student(Student* student) {
    if (student->full_name != NULL) {
        free((void*)student->full_name); // Приводим к void*, т.к. full_name — const char*
        student->full_name = NULL;
    }

    if (student->marks != NULL) {
        free(student->marks);
        student->marks = NULL;
    }

    // Обнуляем остальные поля для безопасности
    student->curs = 0;
    student->age = 0;
    student->marks_counts = 0;
}

// Пример использования
int main() {
    Student stu = input_student();
    print_student(&stu);
    free_student(&stu);

    return 0;
}


