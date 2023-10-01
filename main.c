#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "tree.h"

void clear_console(void);
int run_all_test(void);

int main(int argc, char* argv[]) {
  if (run_all_tests() != 0) exit(1);
  clear_console();

  return 0;
}

void clear_console() { system("cls"); }

int run_all_tests() {
  run_test("constants", test_constants());
  run_test("is_empty()", test_is_empty());
  run_test("initialize_tree()", test_initialize_tree());
  run_test("free_node()", test_free_node());
  run_test("generate_registration()", test_generate_registration());
  run_test("create_node()", test_create_node());

  return 0;
}
