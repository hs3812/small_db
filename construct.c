//
//  construct.c
//  database
//
//
//

#include <stdio.h>
#include "people.h"
#include <string.h>
#include <stdlib.h>


void alloc_test(void *ptr){
    if (ptr == NULL) {
        printf("No memory available");
        exit(EXIT_FAILURE);
    }
}



person *p_construction(int y, int m, int d, char *name, char *passhash1,char *passhash2, char*passhash3){
    person * p = NULL;
    p = malloc(sizeof(person));
    alloc_test(p);
    p->year = y;
    p->month = m;
    p->date = d;
    p->name = malloc(sizeof(char)*strlen(name)+1);
    alloc_test(p->name);
    p->password = malloc(sizeof(char*)*3);
    alloc_test(p->password);
    strcpy(p->name, name);
    for (int i =0; i<3; i++) {
        p->password[i]=malloc(sizeof(char)*20+1);
        alloc_test(p->password[i]);
        switch (i) {
            case 0:
                strcpy(p->password[i], passhash1);
                break;
            case 1:
                strcpy(p->password[i], passhash2);
                break;
            case 2:
                strcpy(p->password[i], passhash3);
                break;
            default:
                break;
        }
    }
    return p;
}

void p_destruction(person *ptr){
    free(ptr->name);
    for (int i=0; i<3; i++) {
        free(ptr->password[i]);
    }
    free(ptr->password);
    free(ptr);
    
}
void person_display(person *ptr){
    printf("Name: %s \n",ptr->name);
    printf("DOB:%d/%d/%d\n",ptr->date,ptr->month,ptr->year);
    for (int i=0; i<3; i++) {
        printf("%s\n",ptr->password[i]);
    }
}


db * db_read(char *filename){
    FILE * fp = fopen(filename, "r");
    if (fp==NULL) {
        perror("oops:");
    }
    db * ptr = malloc(sizeof(db));
    alloc_test(ptr);
    
    int num_of_people;
    int longest_name;
    while (!feof(fp)) {
        int date;
        if (fscanf(fp, "%d",&date)==1) {
            num_of_people++;
            int namelength = 0;
            while (( !feof(fp)) && (fgetc(fp)!='\n')) {
                namelength++;

            }
            namelength++;
            if (longest_name<namelength) {
                longest_name=namelength;
            }
            
            
            
        }
    }
    ptr->num =num_of_people;
    ptr->p=malloc(sizeof(person*)*num_of_people);
    char * name = malloc(sizeof(char)*longest_name+1);
    int index = 0;
    fseek(fp, 0, SEEK_SET);
    
    
    while (!feof(fp)) {
        int date;
        if (fscanf(fp, "%d",&date)==1) {
            fgetc(fp);
            fgets(name, longest_name, fp);
            char * remover = strchr(name, '\n');
            if(remover!=NULL){
                *remover='\0';
                }
            ptr->p[index]=malloc(sizeof(person));
            ptr->p[index]->date=date;
            ptr->p[index]->name=strdup(name);
            index++;
        }
        
        
        }
    free(name);
    fclose(fp);
    return ptr;
}

static int comparedate(const void *p1, const void *p2){
    const person * * pp1 = ( const person * *) p1 ;
    const person * * pp2 = ( const person * *) p2 ;
    const person * pv1 = * pp1 ;
    const person * pv2 = * pp2 ;
    return (( pv1 -> date ) - ( pv2 -> date ));
}


static int comparename(const void *p1, const void *p2){
    const person * * pp1 = ( const person * *) p1 ;
    const person * * pp2 = ( const person * *) p2 ;
    const person * pv1 = * pp1 ;
    const person * pv2 = * pp2 ;
    return strcmp((pv1->name), (pv2->name));
}


void sort_by_name(db*p){
    qsort(p->p, p->num, sizeof(person*),comparename);
}
void sort_by_date(db*p){
    qsort(p->p,  p->num, sizeof(person*),comparedate);
    
}


static unsigned int string_hash(void *string)
{
    
    unsigned int result = 5381;
    unsigned char *p;
    
    p = (unsigned char *) string;
    
    while (*p != '\0') {
        result = (result << 5) + result + *p;
        ++p;
    }
    
    return result;
}


static unsigned int string_nocase_hash(void *string)
{
    unsigned int result = 5381;
    unsigned char *p;
    
    p = (unsigned char *) string;
    
    while (*p != '\0') {
        result = (result << 5) + result + (unsigned int) tolower(*p);
        ++p;
    }
    
    return result;
}
