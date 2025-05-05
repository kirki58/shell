#include "unity.h"
#include "fifo.h"

void setUp(void) {}
void tearDown(void) {}

void test_init_fifo_should_initialize_empty_queue(void) {
    Fifo *q = init_fifo();
    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->rear);
    free_fifo(q);
}

void test_enqueue_should_add_first_element(void) {
    Fifo *q = init_fifo();
    int value = 42;
    enqueue(q, &value, sizeof(int));
    TEST_ASSERT_NOT_NULL(q->front);
    TEST_ASSERT_NOT_NULL(q->rear);
    TEST_ASSERT_EQUAL_PTR(q->front, q->rear);
    TEST_ASSERT_EQUAL_INT(42, *(int*)q->front->data);
    free_fifo(q);
}

void test_enqueue_should_add_multiple_elements(void) {
    Fifo *q = init_fifo();
    int a = 1, b = 2;
    enqueue(q, &a, sizeof(int));
    enqueue(q, &b, sizeof(int));

    TEST_ASSERT_NOT_NULL(q->front);
    TEST_ASSERT_NOT_NULL(q->rear);
    TEST_ASSERT_NOT_EQUAL(q->front, q->rear);
    TEST_ASSERT_EQUAL_INT(1, *(int*)q->front->data);
    TEST_ASSERT_EQUAL_INT(2, *(int*)q->rear->data);
    free_fifo(q);
}

void test_dequeue_should_remove_single_element(void) {
    Fifo *q = init_fifo();
    int val = 99;
    enqueue(q, &val, sizeof(int));
    dequeue(q);
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->rear);
    free_fifo(q);
}

void test_dequeue_should_remove_front_of_queue(void) {
    Fifo *q = init_fifo();
    int x = 5, y = 6;
    enqueue(q, &x, sizeof(int));
    enqueue(q, &y, sizeof(int));
    dequeue(q);
    TEST_ASSERT_NOT_NULL(q->front);
    TEST_ASSERT_EQUAL_INT(6, *(int*)q->front->data);
    free_fifo(q);
}

void test_peek_should_return_front_element(void) {
    Fifo *q = init_fifo();
    int val = 123;
    enqueue(q, &val, sizeof(int));
    int *peeked = (int*)peek(q);
    TEST_ASSERT_NOT_NULL(peeked);
    TEST_ASSERT_EQUAL_INT(123, *peeked);
    free_fifo(q);
}

void test_peek_should_return_null_for_empty_queue(void) {
    Fifo *q = init_fifo();
    TEST_ASSERT_NULL(peek(q));
    free_fifo(q);
}

void test_free_fifo_should_free_all_memory(void) {
    Fifo *q = init_fifo();
    int x = 1, y = 2, z = 3;
    enqueue(q, &x, sizeof(int));
    enqueue(q, &y, sizeof(int));
    enqueue(q, &z, sizeof(int));
    free_fifo(q);

    // This part just ensures it doesn't crash.
    TEST_PASS_MESSAGE("free_fifo executed without crash");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_init_fifo_should_initialize_empty_queue);
    RUN_TEST(test_enqueue_should_add_first_element);
    RUN_TEST(test_enqueue_should_add_multiple_elements);
    RUN_TEST(test_dequeue_should_remove_single_element);
    RUN_TEST(test_dequeue_should_remove_front_of_queue);
    RUN_TEST(test_peek_should_return_front_element);
    RUN_TEST(test_peek_should_return_null_for_empty_queue);
    RUN_TEST(test_free_fifo_should_free_all_memory);

    return UNITY_END();
}
