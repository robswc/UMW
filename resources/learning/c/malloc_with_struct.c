// Malloc is a function in stdlib that allocates a block of memory and then returns a pointer to this memory.
// The memory can then be used however you want.
// More on malloc [1] in references.

// Includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Create a car struct, with basic member variables.
typedef struct {
    int year;
    char make[16];
    char model[16];
} car;

// Create a prototype for a 'new_car' func.
car* new_car();

// Main
int main(){

    // Create a pointer of type car.
    // This no different than:
    // Int *p; or float *p;
    car *ptcar;

    // Set ptcar to the return of new_car.
    // We can do this because new_car returns a pointer.
    ptcar = new_car();

    // Create a variable 'mycar' of type car.
    // Set mycar to 'the var that ptcar points to'.
    // AKA, a new mem allocated car strcut.
    car mycar = *ptcar;

    // We can now act upon 'mycar' like a normal struct.
    // Set year
    mycar.year = 1996;
    // Set make and model, using strcpy
    strcpy(mycar.make, "Honda");
    strcpy(mycar.model, "Civic");

    //Print utilizing new struct.
    printf("My car is a %d %s %s", mycar.year, mycar.make, mycar.model);

    // Exit
    return 0;
}

// Create a 'new_car' function that returns a pointer to type 'car'.
car* new_car() {
    // Create a pointer of type 'car' set to malloc(size of *p).
    // malloc itself returns a pointer to the allocated memory. [1]
    car *p = malloc(sizeof *p);
    return p;
}

// References
// [1] https://man7.org/linux/man-pages/man3/malloc.3.html