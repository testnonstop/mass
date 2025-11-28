#define _CRT_SECURE_NO_DEPRECATE
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

    // Ввод ФИО (без strdup — выделяем память вручную)
    printf("Введите ФИО студента: ");
    char name_buffer[256];
    fgets(name_buffer, sizeof(name_buffer), stdin);

    // Удаляем символ перевода строки, если есть
    size_t len = strlen(name_buffer);
    if (len > 0 && name_buffer[len - 1] == '\n') {
        name_buffer[len - 1] = '\0';
        len--;
    }

    // Выделяем память под full_name и копируем строку
    student.full_name = (char*)malloc(len + 1);  // +1 для '\0'
    if (student.full_name == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для ФИО!\n");
        exit(1);
    }
    strcpy((char*)student.full_name, name_buffer);  // копируем в выделенную память

    // Ввод остальных полей
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
        free((void*)student.full_name);  // освобождаем уже выделенную память
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
    // Освобождаем full_name (приводим к void*, т.к. full_name — const char*)
    if (student->full_name != NULL) {
        free((void*)student->full_name);
        student->full_name = NULL;
    }

    // Освобождаем массив оценок
    if (student->marks != NULL) {
        free(student->marks);
        student->marks = NULL;
    }

    // Обнуляем остальные поля (хорошая практика)
    student->curs = 0;
    student->age = 0;
    student->marks_counts = 0;
}

// Пример использования
int main() {
    setlocale(LC_ALL, "rus");

    Student stu = input_student();
    print_student(&stu);
    free_student(&stu);

    return 0;
}



