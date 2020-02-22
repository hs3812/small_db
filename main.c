//
//  main.c
//  database
//
//
//

#include <stdio.h>
#include <stdio.h>
#include "people.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    int y,m,d,num;
    char *name;
    char *passhash1;
    char *passhash2;
    char *passhash3;
    char choice,tmp;
    char *filename;
    person **p;
    db *pp;
    name = malloc(sizeof(char)*30);
    alloc_test(name);
    passhash1=malloc(sizeof(char)*30);
    alloc_test(passhash1);
    passhash2=malloc(sizeof(char)*30);
     alloc_test(passhash2);
    passhash3=malloc(sizeof(char)*30);
     alloc_test(passhash3);
    filename=malloc(sizeof(char)*30);
    alloc_test(filename);
    p=NULL;
    
    printf("Do you have a simple database file to read? y for yes n for no:");
    scanf(" %c",&tmp);
   
    switch (tmp) {
        case 'y':
            printf("enter filename:");
            scanf("%s",filename);
            pp = db_read(filename);
            sort_by_name(pp);
            sort_by_date(pp);
            
            break;
        case 'n':
            goto LOOP;
            break;
    }
    
    
    
    
    printf("every one is required to have 3 passwords!\n");
LOOP:do{
    printf("how many people?:");
    scanf("%d",&num);
        p = malloc(sizeof(person*)*num);
        alloc_test(p);
    
        for (int i =1; i<=num; i++) {
            printf("enter the name of person %d:",i);
            scanf("%s",name);
            printf("enter the date of person %d:",i);
            scanf("%d",&d);
            printf("enter the month of person %d:",i);
            scanf("%d",&m);
            printf("enter the year of person %d:",i);
            scanf("%d",&y);
            printf("enter 3 passwords for person %d:",i);
           scanf("%s",passhash1);
            scanf("%s",passhash2);
           scanf("%s",passhash3);
            p[i-1]=malloc(sizeof(person));
            alloc_test(p[i-1]);
            p[i-1]=p_construction(y, m, d, name, passhash1, passhash2, passhash3);
    }
        
        
        
    printf("thanks, anymore people you wannna add? Type y for yes n for no:");
    scanf("    %c",&choice);
    }while (choice!='n');
    
    
    
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("now printing your database:\n");
    for (int i=0; i<num; i++) {
        person_display(p[i]);
    }
    for (int i=0; i<num; i++) {
        p_destruction(p[i]);
    }
    free(name);
    free(filename);
    free(passhash1);
    free(passhash2);
    free(passhash3);
    free(p);
    if (pp!=NULL) {
        free(pp);
    }
    
    return EXIT_SUCCESS;
}
