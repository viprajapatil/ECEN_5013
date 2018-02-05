#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include "linkedlist.h"

void test_insert_at_beginning(void **state)
{ struct info* head = (struct info*)malloc(sizeof(struct info));
  head = insert_at_beginning(head,2);
  uint32_t status = head->data;
  assert_int_equal(status,peak(head,1));
}

void test_insert_at_end(void **state)
{ struct info* head = (struct info*)malloc(sizeof(struct info));
  head = insert_at_beginning(head,2);
  head = insert_at_beginning(head,1);
  head = insert_at_end(head,3);
  assert_int_equal(3,peak(head,3));
}

void test_insert_at_position(void **state)
{ struct info* head = (struct info*)malloc(sizeof(struct info));
  head = insert_at_beginning(head,2);
  head = insert_at_beginning(head,1);
  head = insert_at_end(head,3);
  head = insert_at_position(head,4,2);
  assert_int_equal(4,peak(head,2));
}

void test_delete_from_beginning(void **state)
{ struct info* head = (struct info*)malloc(sizeof(struct info));
  head = insert_at_beginning(head,2);
  head = insert_at_beginning(head,3);
  head = delete_from_beginning(head);
  assert_int_equal(2,peak(head,1));
}

void test_delete_from_end(void **state)
{ struct info* head = (struct info*)malloc(sizeof(struct info));
  head = insert_at_beginning(head,2);
  head = insert_at_beginning(head,3);
  head = insert_at_beginning(head,1);
  head = delete_from_end(head);
  uint32_t status = head->data;
  assert_int_equal(3,peak(head,2));
}



int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(test_insert_at_beginning),
  cmocka_unit_test(test_insert_at_end),
  cmocka_unit_test(test_insert_at_position),
  cmocka_unit_test(test_delete_from_beginning),
  cmocka_unit_test(test_delete_from_end),
  
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}