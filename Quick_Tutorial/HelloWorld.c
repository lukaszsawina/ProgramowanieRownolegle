#include "stdio.h"
#include "string.h"
#include "Calculator.h"

#define IS_DEBUG 0
#ifdef DEBUG
    #define IS_DEBUG 1
#endif
#define MAX_1 5
#define MAX_2 10

typedef struct Person {
    char name[50];
    int height;
} Person;

void fun1();
void fun2();
void showPerson(Person* person);

static int i = 0;

int main()
{

    // Person p1;

    // strcpy(p1.name, "Janek");
    // p1.height = 183;

    int a;
    int b;

    printf("Number a and b: ");
    scanf("%d%d",&a, &b);

    int output = sum(a, b);

    printf("The output is: %d\n",output);

    // fun1();
    // fun2();

    // showPerson(&p1);

    if(IS_DEBUG)
    {
        printf("Run as DEBUG");
    }

    return 0;
}

void fun1()
{
    for(i; i<MAX_1; i++)
    {
        printf("Fun1: %d\n",i);
    }
}

void fun2()
{
        for(i; i<MAX_2; i++)
    {
        printf("Fun2: %d\n",i);
    }
}

void showPerson(Person* person)
{
    printf("Person with name: %s\n", person->name);
    printf("Person height: %d\n", person->height);
}