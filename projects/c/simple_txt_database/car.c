#include "car.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static car *db[MAX_CARS];
static int num_cars = 0;

// Helper func, to convert enum int to string.
char *enum_convert(int enum_int) {
    if (enum_int == 0) {return "sedan";} 
    if (enum_int == 1) {return "suv";} 
    if (enum_int == 2) {return "truck";} 
    if (enum_int == 3) {return "hybrid";}
    else {
        // printf("Cannot convert %d to enum!\n", enum_int);
        return 0;
    }
}

// Helper func, to convert enum int to string.
category enum_convert_cat(char *str_category) {
    if ((strcmp(str_category, "suv") == 0)) {return suv;} 
    if ((strcmp(str_category, "sedan") == 0)) {return sedan;} 
    if ((strcmp(str_category, "truck") == 0)) {return truck;} 
    if ((strcmp(str_category, "hybrid") == 0)) {return hybrid;}
    else {
        // printf("Cannot convert %s to enum!\n", str_category);
        return 0;
    }
}

// Read car types into db
int initialize_db(char *filename) {

    FILE *fp;
    fp = fopen(filename, "r");

    // Check if file exists.
    if (fp == NULL) {
        printf("%s not found!", filename);
        return -1;
    }

    // Set vars.
    int carnum, year, miles, cost;
    char make[20], str_category[20];

    // Read file, 
    while (fscanf(fp, "%d %d %s %s %d %d", &carnum, &year, make, str_category, &miles, &cost) != EOF) {
        // Use add_car to add cars from file.
        add_car(carnum, year, make, enum_convert_cat(str_category), miles, cost);
    }

    return 0;

}

// Write db to file.
int write_db(char *filename) {
    FILE *fout = fopen(filename, "w");
    if (fout == NULL) {
        printf("%s not found!", filename);
        return -1;
    } else {
        // Loop through cars, add to database.
        for (int i = 0; i < num_cars; i++) {
            fprintf(fout, "%d %d %s %s %d %d\n", db[i]->carnum, db[i]->year, db[i]->make, enum_convert(db[i]->category), db[i]->miles, db[i]->cost);
        }
    }

    fclose(fout);
    return 0;

}

// Prints car.
void print_car(car *c) {
    printf("%d %d %s %s %d %d\n", c->carnum, c->year, c->make, enum_convert(c->category), c->miles, c->cost);
}

// Show cars, prints all cars currently in db.
void show_cars() {
    for (int i = 0; i < num_cars; i++) {
        print_car(db[i]);
    }
}

// Highlights car in red text, only works on some terminals.
void highlight_car(int car_num) {
    for (int i = 0; i < num_cars; i++) {
        if (i == car_num) {
            printf("\033[0;31m");
            print_car(db[i]);
            printf("\033[0m"); 
        } else {
            print_car(db[i]);
        }
    }
}

// Finds car, given carnum.
car *find_car(int carnum) {
    for(int i = 0; i < num_cars; i++) {
        if (db[i]->carnum == carnum) {
            return db[i];
        }
    }
    return NULL;
}

// Adds car to db.
car *add_car(int carnum, int year, char *make, category category, int miles, int cost) {
    // Check if car is already in db

    for (int i; i < num_cars; i++) {
        if (db[i]->carnum == carnum) {
            return 0;
        }
    }

    // Add car to db
    car *c = malloc(sizeof(*c));
    c->carnum = carnum;
    c->year = year;
    strcpy(c->make, make);
    c->category = category;
    c->miles = miles;
    c->cost = cost;
    db[num_cars] = c;
    num_cars++;

    //Return added car.
    return db[num_cars];

}

// Update cost.
car *update_cost(int carnum, int cost) {
    find_car(carnum)->cost = cost;
    return find_car(carnum);
}

// Update miles.
car *update_miles(int carnum, int miles) {
    find_car(carnum)->miles = miles;
    return find_car(carnum);
}

// Filters cars by year.
int get_year(car **cars, int year) {

    // Filter cars, print them.
    int total = 0;
    for (int i = 0; i < num_cars; i++) {
        if (db[i]->year > year) {
            cars[total] = db[i];
            total++;
        }
    }

    // No results
    if (total == 0) {
        printf("No cars newer than %d!\n", year);
    }

    return total;

}

int get_cost(car **cars, int cost) {

    // Filter cars, print them.
    int total = 0;
    for (int i = 0; i < num_cars; i++) {
        if (db[i]->cost < cost) {
            cars[total] = db[i];
            total++;
        }
    }

    // No results
    if (total == 0) {
        printf("No cars cheaper than %d!\n", cost);
    }

    return total;

}

int get_category(car **cars, category c) {

    // Filter cars, print them.
    int total = 0;
    for (int i = 0; i < num_cars; i++) {
        if (db[i]->category == c) {
            cars[total] = db[i];
            total++;
        }
    }

    // No results
    if (total == 0) {
        printf("No cars of %s!\n", enum_convert(c));
    }

    return total;

}


int get_make(car **cars, char *make) {

    // Filter cars, print them.
    int total = 0;
    for (int i = 0; i < num_cars; i++) {
        if (!strcmp(db[i]->make, make)) {
            cars[total] = db[i];
            total++;
        }
    }

    // No results
    if (total == 0) {
        printf("No cars of %s!\n", make);
    }

    return total;

}

// Purchases car, removes it from current db.
car *purchase(int carnum) {
    
    // Get car 
    car *c = find_car(carnum);
    int head = 0;

    // Find position in array
    for (int i = 0; i < num_cars; i++) {
        if (db[i]->carnum == carnum) {head = i;}   
    }

    // Shift everything by 1
    for (int x = head; x < num_cars; ++x) {db[x] = db[x + 1];}
    
    // Reduce num_cars
    num_cars = num_cars - 1;
    return c;
}
