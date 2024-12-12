#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 1000
#define MAX_LINE_LENGTH 256

typedef struct {
    char name[MAX_LINE_LENGTH];
    char phone[MAX_LINE_LENGTH];
    char email[MAX_LINE_LENGTH];
    char course[MAX_LINE_LENGTH];
    char group[MAX_LINE_LENGTH];
} Student;

int is_unique(Student* students, int count, Student new_student) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, new_student.name) == 0 &&
            strcmp(students[i].phone, new_student.phone) == 0 &&
            strcmp(students[i].email, new_student.email) == 0 &&
            strcmp(students[i].course, new_student.course) == 0 &&
            strcmp(students[i].group, new_student.group) == 0) {
            return 0; // Not unique
        }
    }
    return 1; // Unique
}

void read_students_from_file(const char* filename, Student* students, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(students[*count].name, sizeof(students[*count].name), file)) {
        // Remove newline character
        students[*count].name[strcspn(students[*count].name, "\n")] = 0;

        // Read other fields
        fgets(students[*count].phone, sizeof(students[*count].phone), file);
        students[*count].phone[strcspn(students[*count].phone, "\n")] = 0;

        fgets(students[*count].email, sizeof(students[*count].email), file);
        students[*count].email[strcspn(students[*count].email, "\n")] = 0;

        fgets(students[*count].course, sizeof(students[*count].course), file);
        students[*count].course[strcspn(students[*count].course, "\n")] = 0;

        fgets(students[*count].group, sizeof(students[*count].group), file);
        students[*count].group[strcspn(students[*count].group, "\n")] = 0;

        (*count)++;
    }

    fclose(file);
}

void write_students_to_file(const char* filename, Student* students, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n",
            students[i].name,
            students[i].phone,
            students[i].email,
            students[i].course,
            students[i].group);
    }

    fclose(file);
}

int main() {
    Student students[MAX_RECORDS];
    int count = 0;

    // Read students from the first file
    read_students_from_file("students1.txt", students, &count);

    // Read students from the second file
    Student temp_students[MAX_RECORDS];
    int temp_count = 0;
    read_students_from_file("students2.txt", temp_students, &temp_count);

    // Add unique students from the second file
    for (int i = 0; i < temp_count; i++) {
        if (is_unique(students, count, temp_students[i])) {
            students[count++] = temp_students[i];
        }
    }

    // Write unique students to the output file
    write_students_to_file("unique_students.txt", students, count);

    printf("Unique student records have been written to unique_students.txt\n");
    return 0;
}