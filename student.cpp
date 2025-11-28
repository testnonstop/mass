#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Ñòðóêòóðà ñòóäåíòà
typedef struct {
    int curs;
    int age;
    int marks_counts;
    int* marks;
    const char* full_name;
} Student;

// 1. Ôóíêöèÿ ââîäà äàííûõ ñòóäåíòà
Student input_student() {
    Student student;

    printf("Ââåäèòå ÔÈÎ ñòóäåíòà: ");
    char name_buffer[256];
    fgets(name_buffer, sizeof(name_buffer), stdin);
    // Óäàëÿåì ñèìâîë ïåðåâîäà ñòðîêè, åñëè îí åñòü
    size_t len = strlen(name_buffer);
    if (len > 0 && name_buffer[len - 1] == '\n') {
        name_buffer[len - 1] = '\0';
    }
    student.full_name = strdup(name_buffer); // Âûäåëÿåì ïàìÿòü è êîïèðóåì ñòðîêó

    printf("Ââåäèòå êóðñ: ");
    scanf_s("%d", &student.curs);

    printf("Ââåäèòå âîçðàñò: ");
    scanf_s("%d", &student.age);

    printf("Ââåäèòå êîëè÷åñòâî îöåíîê: ");
    scanf_s("%d", &student.marks_counts);

    // Âûäåëÿåì ïàìÿòü äëÿ ìàññèâà îöåíîê
    student.marks = (int*)malloc(student.marks_counts * sizeof(int));
    if (student.marks == NULL) {
        fprintf(stderr, "Îøèáêà âûäåëåíèÿ ïàìÿòè äëÿ îöåíîê!\n");
        exit(1);
    }

    printf("Ââåäèòå îöåíêè ÷åðåç ïðîáåë: ");
    for (int i = 0; i < student.marks_counts; i++) {
        scanf_s("%d", &student.marks[i]);
    }

    return student;
}

// 2. Ôóíêöèÿ âûâîäà äàííûõ ñòóäåíòà
void print_student(const Student* student) {
    printf("\n--- Äàííûå ñòóäåíòà ---\n");
    printf("ÔÈÎ: %s\n", student->full_name);
    printf("Êóðñ: %d\n", student->curs);
    printf("Âîçðàñò: %d\n", student->age);
    printf("Êîëè÷åñòâî îöåíîê: %d\n", student->marks_counts);
    printf("Îöåíêè: ");
    for (int i = 0; i < student->marks_counts; i++) {
        printf("%d ", student->marks[i]);
    }
    printf("\n");
}

// 3. Ôóíêöèÿ î÷èñòêè ïàìÿòè ñòóäåíòà
void free_student(Student* student) {
    if (student->full_name != NULL) {
        free((void*)student->full_name); // Ïðèâîäèì ê void*, ò.ê. full_name — const char*
        student->full_name = NULL;
    }

    if (student->marks != NULL) {
        free(student->marks);
        student->marks = NULL;
    }

    // Îáíóëÿåì îñòàëüíûå ïîëÿ äëÿ áåçîïàñíîñòè
    student->curs = 0;
    student->age = 0;
    student->marks_counts = 0;
}

// Ïðèìåð èñïîëüçîâàíèÿ
int main() {
    setlocale(LC_ALL, "rus");
    Student stu = input_student();
    print_student(&stu);
    free_student(&stu);

    return 0;
}



