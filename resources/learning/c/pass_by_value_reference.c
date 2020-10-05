// Passing by value means you are giving the value of the variable to the function.
// Passing by reference means that you are giving a reference (variable itself) to the function.

// Main
main() {

    // Create simple int, set to 100.
    int i = 100;
    
    // Use a function that is given a value.
    printf("Pass by value: \n");
    pbv(i);
    // Check that i has not changed.
    printf("i is: %d\n", i);
    // Use a function that is given a reference.
    printf("Pass by reference: \n");
    pbr(&i);
    // Check that i has now changed, 
    printf("i is: %d\n", i);
}

// Function that is given a value.
pbv(x) int x; {
        printf("function was given: %d\n", x);
        // increment x by one.
        ++x;
    }

// Function that is given a reference (pointer to an int).
pbr(x) int *x; {
        printf("function was given: %d\n", *x);
        // increment the value x points to, by one.
        ++*x;
    }