// Double pointers
// Needs commenting

#include<stdio.h>

int main() {

    // Prototype
    void print_array(char **a);

    // Create char array.
    char * arr[4] = {
        "university",
        "of",
        "mary",
        "washington"
    };

    // Create pointer to array.
    char ** ptr_to_arr = arr;

    // See what value is at *ptr_to_arr. (it is the 'string' "university")
    printf("Value at ptr_to_arr is: %s \n", *ptr_to_arr);

    // See address of *ptr_to_arr ("university"), same as arr[0]
    printf("ptr_to_arr is: %x \n", &*ptr_to_arr);
    printf("arr[0] is: %x \n", &arr[0]);

    print_array(ptr_to_arr);

    return 0;

}

// Function to print out array, using pointer.
void print_array(char **a) {
    int length = sizeof(a) / 2;
    printf("length of arr is: %d \n", length);
    int i;
    for (i = 0; i < length; i++) {
        printf("printing... %s (%x) \n", a[0], &a[0]);
        ++a;
    }

}