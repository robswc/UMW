// Pointers can at first be a bit disconcerting.
// However, after breaking the concept down, it can eventually be better understood.

// Lets start by just creating a pointer.

main() {
    // This is a simple int.
    int i; 
    // This is a simple int pointer.  See [1] for more on * with pointers.
    int *p; 

    // Set i.
    i = 1337;
    // Set pointer p to point to i.
    p = &i;

    // Keep in mind, the value of p is set to the *address* of i.
    // The pointer should also always be of the same type.
    // Similar to how we set ints to '12' or '3' we set pointers to addresses.

    // Now, let's print w/ *p.
    // The * operator means "value at address". (note, it looks similar to when it is first declared)
    printf("value of i is %d \n", *p);

    printf("p is pointing to address %x (value of p) \n", p);
    printf("address of i is %x \n", &i);
    printf("address of p is %x \n", &p);

}

// References
// [1] http://www.it.uc3m.es/pbasanta/asng/course_notes/pointers_indirection_with_pointers_en.html