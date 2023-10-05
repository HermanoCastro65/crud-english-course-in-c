#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "tree.h"

int is_empty(Node* node) { return node == NULL; }

Node* initialize_tree() { return NULL; }

void free_tree(Node* root) {
  if (root == NULL) return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

void initialize_random_seed() { srand(time(NULL)); }

int generate_registration() {
  int lower_bound = 10000;
  int upper_bound = 99999;
  int random_number = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
  return random_number;
}

void list_all_students(Node* node) {
  if (node == NULL) return;

  list_all_students(node->left);

  printf("Student (%d): %s - Level: %s - Language: %s\n",
         node->student.registration, node->student.name,
         node->student.class_level, node->student.language);

  list_all_students(node->right);
}

Node* create_node(Student student, Node* left, Node* right) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (!new_node) {
    perror("Memory allocation error");
    exit(1);
  }

  Student new_student;

  new_student.registration = student.registration;
  strncpy(new_student.name, student.name, sizeof(new_student.name));
  strncpy(new_student.class_level, student.class_level,
          sizeof(new_student.class_level));
  strncpy(new_student.language, student.language, sizeof(new_student.language));

  new_node->student = new_student;
  new_node->left = left;
  new_node->right = right;

  return new_node;
}

Node* include_student(Node* node, Student student) {
  if (!node) return create_node(student, NULL, NULL);

  int comparison = strcmp(student.name, node->student.name);

  if (comparison <= 0)
    node->left = include_student(node->left, student);
  else
    node->right = include_student(node->right, student);

  return node;
}

Node* search_student(Node* node, const char* name) {
  if (node == NULL) return NULL;

  int comparison = strcmp(name, node->student.name);

  if (comparison == 0)
    return node;
  else if (comparison < 0)
    return search_student(node->left, name);
  else
    return search_student(node->right, name);
}

void show_student(Student student) {
  printf("Registration: %d\nName: %s\nLevel: %s\nLanguage: %s\n",
         student.registration, student.name, student.class_level,
         student.language);
}

void show_students_by_language(Node* students, const char* language) {
  if (students == NULL) {
    return;
  }

  show_students_by_language(students->left, language);

  if (strcmp(students->student.language, language) == 0)
    printf("Name: %s - Level: %s - Language: %s\n", students->student.name,
           students->student.class_level, students->student.language);

  show_students_by_language(students->right, language);
}
