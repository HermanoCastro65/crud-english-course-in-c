#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

void clear_console() { system("cls"); }

int run_all_tests() {
  printf("\nRUNING ALL TESTS: \n\n");
  run_test("constants", test_constants());
  run_test("is_empty()", test_is_empty());
  run_test("initialize_tree()", test_initialize_tree());
  run_test("free_tree()", test_free_tree());
  run_test("generate_registration()", test_generate_registration());
  run_test("create_node()", test_create_node());
  run_test("include_student()", test_include_student());
  run_test("list_all_students()", test_list_all_students());
  run_test("search_student()", test_search_student());
  run_test("show_student()", test_show_student());

  return 0;
}

void main_menu() {
  Node* students = initialize_tree();
  students = read_file_and_insert_into_tree(students);

  int option = 0, get_out = 0;

  do {
    clear_console();

    printf("\n(1) List students");
    printf("\n(2) Add student");
    printf("\n(3) Change student");
    printf("\n(4) Consult student");
    printf("\n(5) Delete student");
    printf("\n(6) Exit");
    printf("\n\nChoose option: ");
    scanf("%d", &option);

    switch (option) {
      case 1:
      	clear_console();
        printf("\nREGISTERED STUDENTS: \n\n");
        list_all_students(students);
        getch();
        break;
      case 2:
        printf("\nADD NEW STUDENT: \n\n");
        Student new_student = add_student_menu();
        if (new_student.registration) {
          students = include_student(students, new_student);
          printf("\nSTUDENT SUCCESSFULY INCLUDED \n\n");
        }
          
        getch();
        break;
      case 3:
        printf("\nCHANGE STUDENT: \n\n");
        getch();
        break;
      case 4:
      	clear_console();
        printf("\nCONSULT STUDENT: \n\n");
        print_student_names(students);
        char student_name[25];
        printf("\nSearch student by name: ");
        scanf("%s", &student_name);
        clear_console();
        printf("\nSTUDENT: \n\n");
        Node* consult_student = search_student(students, student_name);
        if (consult_student)
          show_student(consult_student->student);
        else
          printf("NOT FOUND ");
        getch();
        break;
      case 5:
        printf("\nDELETE STUDENT: \n\n");
        getch();
        break;
      case 6:
        printf("\nEXIT\n\n");
        get_out = 1;
        break;
      default:
        printf("\nINVALID OPTION! \n");
        getch();
        get_out = 0;
    }
  } while (!get_out);
}

Student add_student_menu() {
  Student new_student;

  int option = 0, get_out = 0, get_out_language = 0, get_out_level = 0, i = 0,
      language = 0, level = 0;

  do {
    clear_console();

    get_out_language = 0;
    get_out_level = 0;

    printf("\nName: ");
    scanf("%s", &new_student.name);

    printf("\nAvailable languages: ");
    for (i = 0; i < 4; i++) printf("\n(%d) %s", i + 1, language_types[i]);
    printf("\n(5) Cancel\n");
    printf("\nLanguage: ");
    scanf("%d", &language);

    switch (language) {
      case 1:
        strncpy(new_student.language, language_types[0],
                sizeof(new_student.language));
        break;
      case 2:
        strncpy(new_student.language, language_types[1],
                sizeof(new_student.language));
        break;
      case 3:
        strncpy(new_student.language, language_types[2],
                sizeof(new_student.language));
        break;
      case 4:
        strncpy(new_student.language, language_types[3],
                sizeof(new_student.language));
        break;
      case 5:
        printf("\nOPERATION CANCELED \n");
        new_student.registration = 0;
        return new_student;
      default:
        printf("\nINVALID OPTION! \n");
        get_out_language = 1;
        getch();
    }

    if (!get_out_language) {
      printf("\nClass level: ");
      for (i = 0; i < 3; i++) printf("\n(%d) %s", i + 1, class_level_types[i]);
      printf("\n(4) Cancel\n");
      printf("\nLevel: ");
      scanf("%d", &level);

      switch (level) {
        case 1:
          strncpy(new_student.class_level, class_level_types[0],
                  sizeof(new_student.class_level));
          break;
        case 2:
          strncpy(new_student.class_level, class_level_types[1],
                  sizeof(new_student.class_level));
          break;
        case 3:
          strncpy(new_student.class_level, class_level_types[2],
                  sizeof(new_student.class_level));
          break;
        case 4:
          printf("\nOPERATION CANCELED \n");
          new_student.registration = 0;
          return new_student;
        default:
          printf("\nINVALID OPTION! \n");
          get_out_level = 1;
          getch();
      }
    }

    if (!get_out_language && !get_out_level) {
      new_student.registration = generate_registration();
      return new_student;
    }

  } while (!get_out_language || !get_out_level);
}
