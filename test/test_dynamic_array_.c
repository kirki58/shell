#include "unity.h"
#include "dynamic_array.h"

void setUp(){
    
}

void tearDown(){

}
// Test Initialization of the Dynamic Array
void test_init_dynamic_array(void) {
    Dynamic_Array *dyn_arr = init_dynamic_array(5);
    
    TEST_ASSERT_NOT_NULL(dyn_arr);  // Array should not be NULL
    TEST_ASSERT_EQUAL_UINT(5, dyn_arr->capacity);  // Initial capacity should be 5
    TEST_ASSERT_EQUAL_UINT(0, dyn_arr->len);  // Length should be 0 initially

    free_dynamic_array(dyn_arr);  // Clean up after the test
}

// Test Pushing to Dynamic Array
void test_dynamic_array_push(void) {
    Dynamic_Array *dyn_arr = init_dynamic_array(2);

    // Push first value
    int result = dynamic_array_push(dyn_arr, "Hello");
    TEST_ASSERT_EQUAL_INT(SUCCESS, result);  // Should succeed
    TEST_ASSERT_EQUAL_UINT(1, dyn_arr->len);  // Length should be 1
    TEST_ASSERT_EQUAL_STRING("Hello", dyn_arr->arr[0]);  // Value should be "Hello"

    // Push second value
    result = dynamic_array_push(dyn_arr, "World");
    TEST_ASSERT_EQUAL_INT(SUCCESS, result);  // Should succeed
    TEST_ASSERT_EQUAL_UINT(2, dyn_arr->len);  // Length should be 2
    TEST_ASSERT_EQUAL_STRING("World", dyn_arr->arr[1]);  // Value should be "World"

    // Push third value, which should trigger reallocation
    result = dynamic_array_push(dyn_arr, "Test");
    TEST_ASSERT_EQUAL_INT(SUCCESS, result);  // Should succeed
    TEST_ASSERT_EQUAL_UINT(3, dyn_arr->len);  // Length should be 3 after expansion
    TEST_ASSERT_EQUAL_STRING("Test", dyn_arr->arr[2]);  // Value should be "Test"

    free_dynamic_array(dyn_arr);  // Clean up after the test
}

// Test Free Dynamic Array
void test_free_dynamic_array(void) {
    Dynamic_Array *dyn_arr = init_dynamic_array(3);

    // Push some values
    dynamic_array_push(dyn_arr, "Hello");
    dynamic_array_push(dyn_arr, "World");

    // Free the array
    free_dynamic_array(dyn_arr);  // Should not cause any memory leak or crash
}

// Run all tests
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_init_dynamic_array);
    RUN_TEST(test_dynamic_array_push);
    RUN_TEST(test_free_dynamic_array);

    return UNITY_END();
}
