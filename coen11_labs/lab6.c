/* Patricia Ornelas 
	COEN 11L
	October 16, 2017
	Monday Lab
    Lab 6
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

// Global variables for arrays and size of array
struct reservation
{
	char name[MAX];
	int number;
	struct reservation *next;    
};

// Array of structs
struct reservation *heads[] = {NULL, NULL, NULL, NULL};
struct reservation *tails[] = {NULL, NULL, NULL, NULL};

// Prototypes for functions
void show_list();
int insert();
void remove_reservation(int, char *);
void change_size();


int main(void) {
	int validity = 0;
    
	// Lists options for user
	// Loop checks for valid user input
    while(validity != 1) {
		printf("Insert '1'. Delete '2'. Show list '3'. Change size '4'. Quit '5'. \n");
		int choice;
		int check;

		// Takes input from user to determine function
		scanf("%d", &choice);
		switch(choice){
			case 1:
				// adds name and number of people to bottom of list
				check = insert();

				// While-loop checks if the name is a duplicate
				while(check == 0)
				{
					printf("That name is taken. Try again.\n");
					check = insert();
				}
                
				break;
			
			case 2:
				// deletes an entry
				show_list();
                // Ask user who to remove
                int search;
                printf("What table size do you want to remove?\n");
                scanf("%d", &search);
				remove_reservation(search, NULL);
				break;
			
            case 3:
                // shows the list
                show_list();
                break;
                
			case 4:
				// changes size of reservation
				show_list();
                change_size();
				break;
				
			case 5:
				// quit
				validity = 1;
				break;
                
            default:
                validity = 0;
		}
	}
	
	return 0;
}

void show_list()
{
    struct reservation *ptr;
    // If the list is empty, print message
    if((heads[0] == NULL) && (heads[1] == NULL) && (heads[2] == NULL) && (heads[3] == NULL))
        printf("List is empty.\n");
    else
    {
        for(int i = 0; i < 4; i++)
        {
            ptr = heads[i];
            printf("List %d:\n", i);
            while(ptr != NULL)
            {
                printf("Name: %s, Size: %d\n", ptr->name, ptr->number);
                ptr = ptr->next;                
            }
        }
    }
}

int insert()
{
	// ask for name
	char name_entered[MAX];
	printf("Enter Name: (in 20 characters or less) \n");
	scanf("%s", name_entered);
	
	// check if name is already taken
	struct reservation *ptr;
	int taken = 1;
	for(int i = 0; i < 4; i++)
	{
        ptr = heads[i];
		while(ptr != NULL)
		{
			taken = strcmp(name_entered, ptr->name);
			if(taken == 0)
			{
				// if name is taken, returns 0 to exit function
				return 0; 
			}
			ptr = ptr->next;
		}
	}
	
	// ask for number of people
	int people;
	printf("Enter number of people:\n");
	scanf("%d", &people);
	
    int t;
	// Find which list it is in
	if(people <= 2)
        t=0;
	else if(people <= 4)
        t=1;
	else if(people <= 6)
        t=2;
    else if(people >= 7)
        t=3;
		
	struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
	
	// Sanity check
	if(newr == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }
    else
    {
       // add name and number
		strcpy(newr->name, name_entered);
		newr->number = people;
		newr->next = NULL;
		
        // check if it's the first node to be inserted
        if((heads[t] == NULL) && (tails[t] == NULL))
        {
            heads[t] = newr;
            tails[t] = newr;
            return 1;
        }
        
		// insert new node at end & update tail
        tails[t]->next = newr;
        tails[t] = newr;
		return 1;
    }
}

void remove_reservation(int search, char *str)
{
    int counter = 0, found = 0;
	struct reservation *p, *q;
	
    int t;
	// Find which list it is in
	if(search <= 2)
        t = 0;
	else if(search <= 4)
        t = 1;
	else if(search <= 6)
        t = 2;
	else if(search >= 7)
        t = 3;
    if(str == NULL)
    {
        p = heads[t];
        q = heads[t];
        for(int i = t; i >= 0; i--)
        {
            while(p != NULL)
            {
                // if list is empty, exit function
                if(heads[i] == NULL)
                    break;
                // Check if current node contains number
                if(p->number <= search)
                {
                    // if it's the only node
                    if((p == heads[i]) && (p == tails[i]))
                    {
                        heads[i] = NULL, tails[i] = NULL;
                        return;
                    }
                    else if(p == heads[i])
                        heads[i] = heads[i]->next;
                    else if(p == tails[i])
                    {
                        q->next = p->next;
                        tails[i] = p;
                        tails[i]->next = NULL;
                    }
                    else
                        q->next = p->next;
                    free(p);
                    return;
                }
                q = p;
                p = p->next;
            }
            // switch to check previous list
            p = heads[i-1];
            q = heads[i-1];
        }
        printf("No tables of size %d found.\n", search);
    }
    else
    {
        p = heads[t];
        q = heads[t];
        while(p != NULL)
        {
            // Check if current node contains name
            found = strcmp(p->name, str);
            if(found == 0)
            {
                if((p == heads[t]) && (p == tails[t]))
                {
                    heads[t] = NULL, tails[t] = NULL;
                    return;
                }
                else if(p == heads[t])
                    heads[t] = heads[t]->next;
                else if(p == tails[t])
                {
                    q->next = p->next;
                    tails[t] = p;
                    tails[t]->next = NULL;
                }
                else
                    q->next = p->next;
                free(p);
                return;
            }
            q = p;
            p = p->next;
        }
        printf("No tables found.\n");
    }
}

void change_size()
{
    char search[MAX];
    int check, newnumber, t;
    // ask user who to remove
    printf("What name is the reservation under?\n");
    scanf("%s", search);
    struct reservation *p;
    // loop through and find name
    for(int i = 0; i < 4; i++) {
        p = heads[i];
        while(p != NULL) {
            check = strcmp(p->name, search);
            if(check == 0) {
                // name has been found
                printf("%s has a reservation for %d people. What do you want to change it to?\n", p->name, p->number);
                scanf("%d", &newnumber);
                // move that reservation to other list
                if(i == 0)
                {
                    if(newnumber <= 2)
                    {
                        p->number = newnumber;
                        return;
                    }
                    else
                    {
                        if(newnumber <= 4)
                            t = 1;
                        else if(newnumber <= 6)
                            t = 2;
                        else if(newnumber >= 7)
                            t = 3;
                        
                        // insert node in other list
                        struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
                        strcpy(newr->name, search);
                        newr->number = newnumber;
                        newr->next = NULL;
                        
                        // delete original node
                        remove_reservation(p->number, search);
                        
                        
                        // check if it's the first node to be inserted
                        if((heads[t] == NULL) && (tails[t] == NULL))
                        {
                            heads[t] = newr;
                            tails[t] = newr;
                            return;
                        }
                        
                        // insert new node at end & update tail
                        tails[t]->next = newr;
                        tails[t] = newr;
                    }
                }
                else if(i == 1)
                {
                    if((newnumber <= 4) && (newnumber < 6) && (newnumber > 2) && (newnumber < 7))
                    {
                        p->number = newnumber;
                        return;
                    }
                    else
                    {
                        if(newnumber <= 2)
                            t = 0;
                        else if(newnumber <= 6)
                            t = 2;
                        else if(newnumber >= 7)
                            t = 3;
                        
                        // insert node in other list
                        struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
                        strcpy(newr->name, search);
                        newr->number = newnumber;
                        newr->next = NULL;
                        
                        // delete original node
                        remove_reservation(p->number, search);
                        
                        // check if it's the first node to be inserted
                        if((heads[t] == NULL) && (tails[t] == NULL))
                        {
                            heads[t] = newr;
                            tails[t] = newr;
                            return;
                        }
                        
                        // insert new node at end & update tail
                        tails[t]->next = newr;
                        tails[t] = newr;
                    }
                }
                else if(i == 2)
                {
                    if((newnumber <= 6) && (newnumber > 4) && (newnumber > 2) && (newnumber < 7))
                    {
                        p->number = newnumber;
                        return;
                    }
                    else
                    {
                        if(newnumber <= 2)
                            t = 0;
                        else if(newnumber <= 4)
                            t = 1;
                        else if(newnumber >= 7)
                            t = 3;
                        
                        // insert node in other list
                        struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
                        strcpy(newr->name, search);
                        newr->number = newnumber;
                        newr->next = NULL;
                        
                        // delete original node
                        remove_reservation(p->number, search);
                        
                        
                        // check if it's the first node to be inserted
                        if((heads[t] == NULL) && (tails[t] == NULL))
                        {
                            heads[t] = newr;
                            tails[t] = newr;
                            return;
                        }
                        
                        // insert new node at end & update tail
                        tails[t]->next = newr;
                        tails[t] = newr;
                    }
                }
                
                else if(i == 3)
                {
                    if(newnumber > 7)
                    {
                        p->number = newnumber;
                        return;
                    }
                    else
                    {
                        if(newnumber <= 2)
                            t = 0;
                        else if(newnumber <= 4)
                            t = 1;
                        else if(newnumber <= 6)
                            t = 2;
                        
                        // insert node in other list
                        struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
                        strcpy(newr->name, search);
                        newr->number = newnumber;
                        newr->next = NULL;
                        
                        // delete original node
                        remove_reservation(p->number, search);
                        
                        
                        // check if it's the first node to be inserted
                        if((heads[t] == NULL) && (tails[t] == NULL))
                        {
                            heads[t] = newr;
                            tails[t] = newr;
                            return;
                        }
                        
                        // insert new node at end & update tail
                        tails[t]->next = newr;
                        tails[t] = newr;
                    }
                }
                // break out of function
                return;
            }
            p = p->next;
        }
    }
    printf("Name was not found in list\n");
}
