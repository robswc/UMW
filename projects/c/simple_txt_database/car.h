#define MAX_CARS 100
#define MAX_MAKE_CHARS 32
typedef enum { sedan, suv, truck, hybrid } category;

typedef struct {
    int carnum;
    int year;
    char make[MAX_MAKE_CHARS];
    category category;
    int miles;
    int cost;
} car;
int initialize_db(char *filename);
int write_db(char *filename); 
void show_cars();
void print_car(car *c);
car *find_car(int carnum);
car *add_car(int carnum, int year, char *make, category category, int miles, int cost);
car *update_cost(int carnum, int cost);
car *update_miles(int carnum, int miles);
int get_year(car **cars, int year);
int get_cost(car **cars, int cost);
int get_category(car **cars, category c);
int get_make(car **cars, char *make);
car *purchase(int carnum);

char *enum_convert(int enum_int);
category enum_convert_cat(char *str_category);
void adds();