//
//  people.h
//  database
//
//  Created by hs
//
//

#ifndef people_h
#define people_h

typedef struct p
{
    int month;
    int year;
    int date;
    char *name;
    char **password;
}person;

typedef struct{
    int num;
    person **p;
}db;


person *p_construction(int y, int m, int d, char *name,char *passhash1,char *passhash2, char*passhash3);
void p_destruction(person *ptr);
void person_display(person *ptr);
int db_hash(char *password);
void alloc_test(void *ptr);
void sort_by_name(db*p);
void sort_by_date(db*p);
db * db_read(char *filename);

#endif /* people_h */
