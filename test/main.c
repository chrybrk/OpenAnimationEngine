#include <stdio.h>
#include <stdlib.h>

// Custom data structure
typedef struct {
    int value;
    char *message;
} MyData;

// Function to clean up data (called at exit)
void cleanup_data(void *data_ptr) {
    MyData *data = (MyData *)data_ptr;
    if (data) {
        printf("Destructor: Cleaning up data with value = %d, message = %s\n", data->value, data->message);
        free(data->message);  // Free the message
        free(data);            // Free the structure
    }
}

// Constructor function (called before main)
void init_func(void) __attribute__((constructor));
void init_func(void) {
    // Dynamically allocate memory for MyData
    MyData *data = malloc(sizeof(MyData));
    if (!data) {
        perror("Failed to allocate memory for MyData");
        exit(EXIT_FAILURE);
    }

    // Initialize the structure
    data->value = 100;
    data->message = malloc(50 * sizeof(char));
    if (!data->message) {
        free(data);
        perror("Failed to allocate memory for message");
        exit(EXIT_FAILURE);
    }
    snprintf(data->message, 50, "Hello from the constructor!");

    // Register cleanup function with atexit, passing data as an argument
    atexit((void (*)(void))cleanup_data);  // Register cleanup_data to be called at exit
    // Note: Passing the actual data pointer to atexit is tricky in C.
    // So, we use a lambda-like function:
    __extension__ ({ void cleanup_wrapper() { cleanup_data(data); } cleanup_wrapper; });
}

int main() {
    printf("Main function running...\n");
    return 0;
}
