#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _person
{
    struct _person *mother;
    struct _person *father;
    char bloodType[3];
}
Person;

Person* generatePerson(int generations);
void deleteTree(Person* human);
void makeBlood(Person *human);
void printFamily(Person *human, int gen);

int main(void)
{
    srand(time(NULL));
    
    int generations = 0;

    scanf("%i", &generations);

    Person *p = generatePerson(generations);
    if(p == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printFamily(p, 0);

    deleteTree(p);

    return 0;
}

Person* generatePerson(int generations)
{
    if (generations < 1)
        return NULL;

    //Create the new person
    Person *human = malloc(sizeof(Person));
    if (human == NULL)
        return NULL;
    human->bloodType[2] = '\0';
    if (generations == 1)
    {
        // Generate blood type
        makeBlood(human);
        human->mother = NULL;
        human->father = NULL;

        return human;

    }
    else
    {

        // Generate parents
        human->mother = generatePerson(generations - 1);
        if (human->mother == NULL)
        {
            free(human);
            return NULL;
        }

        human->father = generatePerson(generations - 1);
        if (human->father == NULL)
        {
            // Delete mother's tree
            if (human->mother != NULL)
                deleteTree(human->mother);
            free(human);
            return NULL;
        }

        //Generate blood type
        human->bloodType[0] = human->father->bloodType[rand() % 2];
        human->bloodType[1] = human->mother->bloodType[rand() % 2];

        return human;

    }
}

void deleteTree(Person* human)
{
    if (human->mother == NULL && human->father == NULL)
    {
        free(human);
    }
    else
    {
        if (human->mother != NULL)
            deleteTree(human->mother);
        if (human->father != NULL)
            deleteTree(human->father);
        free(human);
    }
    return;
}

void makeBlood(Person *human)
{
    for (int i = 0; i < 2; i++)
    {
        char type = rand() % 3;
        switch(type)
        {
            case 0:
                human->bloodType[i] = 'A';
                break;
            case 1:
                human->bloodType[i] = 'B';
                break;
            case 2:
                human->bloodType[i] = 'O';
                break;
        }
    }
    return;
}

void printFamily(Person *human, int gen)
{
    if (human->mother == NULL && human->father == NULL)
    {
        printf("Generation %i\n", gen);
        printf("%c%c\n", human->bloodType[0], human->bloodType[1]);
    }
    else
    {
        printFamily(human->mother, gen + 1);
        printFamily(human->father, gen + 1);
        printf("Generation %i\n", gen);
        printf("%c%c\n", human->bloodType[0], human->bloodType[1]);
    }

    printf("\n");

    return;
}
