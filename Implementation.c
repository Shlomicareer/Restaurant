#include "Header.h"

void Get_Lost(char *ch)  //function that print and exit.
{
	printf("\n%s", ch);
	exit(1);
}

void Get_Print(char *ch) //function that print. 
{
	printf("\n%s", ch);
}

void printlistable(manatable *list)  //the function that print a table list. 
{
	manatable *temp;
	temp = list;
	while (temp != NULL)
	{
		printf("plate: %s\t price : %d\t quantity : %d\t\n", temp->name, temp->price, temp->Quantity);  // print the serving info
		temp = temp->next;
	}
}

void printlist(pmana list) //the function that print the kitchen list. 
{
	pmana temp;
	temp = list;
	while (temp != NULL)
	{
		if (temp->Quantity >= 0)
			printf("plate: %s\t price: %d\t quantity: %d\t\n", temp->name, temp->price, temp->Quantity);  // print the kitchen info
		temp = temp->next;
	}
}

void deleteList(pmana head)   //delete a list using recurcion 
{
	if (head->next != NULL) {
		deleteList(head->next);
		free(head);
	}
}


struct mana* CreateProduct(FILE *in, struct mana *head)   //gets the kitchen info from a file and creates a list. 
{
	int countok = 0, i, j, holdprice, holdquantity, flag = 1, countnotok = 0;
	char name[N];
	mana *temp, *temp1, *temp2;
	temp = (mana*)malloc(sizeof(mana));

	if (temp == NULL) // checks the allocation call. 
	{
		Get_Lost("Error");
	}
	temp->next = NULL;


	while (fscanf(in, "%s %d %d", name, &temp->Quantity, &temp->price) != EOF)
	{
		temp->countmax = 0;
		flag = 1;
		if ((temp->price < 0) || (temp->Quantity < 0))
		{
			Get_Print("The price or Quantity is negative.\n");
			flag = 0;
			countnotok++;
		}
		else
		{
			if (head == NULL)   //check is the list is empty 
			{
				temp->name = ((char*)malloc(strlen(name) * sizeof(char) + 1));
				if (temp->name == NULL) // checks the allocation call. 
				{
					free(temp->name);
					free(temp);
					Get_Lost("Error");
				}
				strcpy(temp->name, name);
				temp->next = head;
				head = temp;
				countok++;
			}
			else
			{
				temp2 = head;
				while (temp2 != NULL)
				{
					if (strcmp(name, temp2->name) == 0)
					{
						printf("The plate:%s already exists.\n", name);
						flag = 0;
						countnotok++;
					}
					temp2 = temp2->next;
				}
				if (flag)
				{
					temp->name = ((char*)malloc(strlen(name) * sizeof(char) + 1));
					if (temp->name == NULL) // checks the allocation call. 
					{
						temp2 = head;
						while (temp2 != NULL) //we must free all the allocation we made till now. 
						{
							head = temp2->next;
							free(temp2->name);
							free(temp2);
						}
						free(temp->name);
						free(temp);
						Get_Lost("Error");
					}

					strcpy(temp->name, name);
					temp->next = head;
					head = temp;
					countok++;
				}
			}
		}

		temp = (mana*)malloc(sizeof(mana));
		if (temp == NULL) // checks the allocation call. 
		{
			temp2 = head;
			while (temp2 != NULL) //we must free all the allocation we made till now. 
			{
				head = temp2->next;
				free(temp2->name);
				free(temp2);
			}
			free(temp);
			Get_Lost("Error");
		}
	}

	temp1 = head;
	temp2 = head->next;
	for (i = 0; i < countok - 1; i++)   //here we sort the list by abc order. using temp1 and temp2 as runners. 
	{
		for (j = i; j < countok - 1; j++)
		{

			if (strcmp(temp1->name, temp2->name) > 0) //using thta bubbel sort trick. 
			{
				strcpy(name, temp1->name);  
				holdquantity = temp1->Quantity;
				holdprice = temp1->price;
				strcpy(temp1->name, temp2->name);
				temp1->Quantity = temp2->Quantity;
				temp1->price = temp2->price;
				strcpy(temp2->name, name);
				temp2->Quantity = holdquantity;
				temp2->price = holdprice;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
		temp2 = temp1->next;
	}
	printf("The kitche got succefully %d serving.\n", countok);
	printf("The kitche got not succefully %d serving.\n", countnotok);
	return head;
}

void AddItems(char *newname, int newquantity, pmana list) //the function that update the kitchen list. 
{
	mana *temp;     
	temp = list;
	int flag = 1;
	if (newquantity > 0)
	{
		while (temp != NULL)
		{
			if (strcmp(newname, temp->name) == 0) //checking if the element exist in the list
			{
				temp->Quantity += newquantity;
				flag = 0;
			}
			temp = temp->next;
		}
		if (flag)
			Get_Print("The name doesn't exists\n");   
	}
	else
		Get_Print("The price of the newitem is negative.\n");
}

struct table* createarr(int n)  //the function that creates an array of table struck.
{
	int i;
	struct table* activeroom;
	activeroom = (struct table*)malloc(n * sizeof(struct table)); //the size n is from the userinput. 
	if (activeroom == NULL)
	{
		printf("Error");
		exit(1);
	}
	for (i = 0; i < n; i++)  //we 
	{
		activeroom[i].recipt = 0;
		activeroom[i].tablenum = i+1;
		activeroom[i].tableserving = NULL;
	}
	return activeroom;
}

void  OrderItem(int tnum, char *name, int sumana, mana *kitchenlist, table *activeroom, int n) //the function that gets the order from user and connect the new order to the active one of the table. 
{

	int i, flag = 0;
	mana *tempkitchen;
	tempkitchen = kitchenlist;
	if (tnum > n)
		Get_Print("There is not such a table.\n");
	else
	{
		if (sumana <= 0)
			Get_Print("The num order is not ok.\n");
		else
		{
			while (flag == 0 && tempkitchen != NULL)  //check if the ordered item exist in the kitchen 
			{
				if (strcmp(name, tempkitchen->name) != 0)
					tempkitchen = tempkitchen->next;
				else
				{
					flag = 1; //flag changes to 1 because we found the correct item (means the order is ok).
					if (sumana > tempkitchen->Quantity)   //check if the kitchen ahs the quantity ordered. 
						Get_Print("The kitchen have not the Quantity.\n");
					else
					{
						tempkitchen->Quantity -= sumana; //update the kitchen list 
						activeroom[tnum].tableserving = Addserving(name, sumana, activeroom[tnum].tableserving, tempkitchen); //we add the new order to the exist one using addserving function. 
						activeroom[tnum].recipt += (tempkitchen->price)*(sumana); //we update the recipt 
						tempkitchen->countmax += sumana; //we update counter of the ordered items. 
					}
				}
			}

			if (flag == 0)
				Get_Print("There is not such a serving.\n");
		}
	}
}

struct manatable* Addserving(char *newname, int newquantity, struct manatable* listserving, mana *tempkitchen) //the function that gets a list and a new order(name,quantity), and connects between them.
{
	int flag = 1;
	int stam;  //the interger that keeps the size of the new name. 
	manatable *temp, *tempcheck;
	tempcheck = listserving;  //we use tempcheck as runner 
	if (tempcheck == NULL) //check if the current list is empty. 
	{
		temp = (manatable*)malloc(sizeof(manatable));
		if (temp == NULL) // checks the allocation call. 
		{
			Get_Lost("Error");
		}
		stam = strlen(newname);
		temp->name = (char*)malloc((stam + 1) * sizeof(char*)); 
		if (temp->name == NULL) // checks the allocation call. 
		{
			free(temp);
			Get_Lost("Error");
		}
		strcpy(temp->name, newname);  //we update the name ,quantity and price.
		temp->Quantity = newquantity;
		temp->price = tempkitchen->price;
		temp->next = NULL;  //we initializate the first node of the servinglist. 
		temp->prev = NULL;
		listserving = temp; //we realloc the head. 
	}
	else
	{
		while (tempcheck != NULL)  
		{
			if (strcmp(newname, tempcheck->name) == 0)  //we check if the new order already have a node in the servinglist. 
			{
				tempcheck->Quantity += newquantity; //if yes we update the quantity  and flag get 0.
				flag = 0;
			}
			tempcheck = tempcheck->next;
		}
		if (flag) //if we did not find a node (in the servinglist of the table) with the same name
		{
			temp = (manatable*)malloc(sizeof(manatable));
			if (temp == NULL) // checks the allocation call. 
			{
				Get_Lost("Error");
			}
			stam = strlen(newname);
			temp->name = (char*)malloc((stam + 1) * sizeof(char*));
			if (temp->name == NULL) // checks the allocation call. 
			{
				free(temp);
				Get_Lost("Error");
			}
			strcpy(temp->name, newname); //we update the name, quantity and price.
			temp->Quantity = newquantity;
			temp->price = tempkitchen->price;
			temp->next = listserving->next;
			temp->prev = listserving;     
			if (listserving->next != NULL)  
				listserving->next->prev = temp;
			listserving->next = temp; //we realloc the new node item in the list. 
		}
	}
	return listserving;
}

void  RemoveItem(int tnum, char *name, int sumana, ptable activeroom, mana *kitchenlist, int n) //the function that remove an element from the active servinglist of the table. 
{
	int i, flag = 0;
	manatable *head;
	mana *temp;
	temp = kitchenlist;  //we use temp as runner of the kitchen list. 
	head = activeroom[tnum].tableserving; //we use head to keep the addres of the first node. 
	if (tnum > n)
		Get_Print("There is not such a table.\n");
	else
	{
		while (activeroom[tnum].tableserving != NULL && flag == 0)
		{
			if (strcmp(name, activeroom[tnum].tableserving->name) != 0)  //we check the plate name that is returned from the servinglist to find the node. 
				activeroom[tnum].tableserving = activeroom[tnum].tableserving->next;
			else
			{
				flag = 1;                                                                     //flags get 1 because the plate name exists in the servinglist
				if ((sumana > 0) && (sumana <= activeroom[tnum].tableserving->Quantity))  //check user input if is ok we update the quantity of the node also the recipt of the table.
				{
					activeroom[tnum].tableserving->Quantity -= sumana;            
					activeroom[tnum].recipt -= ((activeroom[tnum].tableserving->price)*sumana);
					while (temp != NULL)  //we check the plate name that is returned from the kitchen list in order to be able to update the counter.
					{
						if (strcmp(name, temp->name) != 0)
							temp = temp->next;
						else
						{
							temp->countmax -= sumana; //we update the counter.
							temp = temp->next;
						}
					}
					if (activeroom[tnum].tableserving->Quantity == 0)  //if the node quantity gets to 0 after the sub, we free the node from the list. 
					{
						if (activeroom[tnum].tableserving->prev == NULL) //we check if the node is the first in the servinglist. 
						{
							if (activeroom[tnum].tableserving->next == NULL)    //we check if the node is the only one 
							{
								free(activeroom[tnum].tableserving->name);  //if yes we just free
								free(activeroom[tnum].tableserving); 
								activeroom[tnum].tableserving = NULL;  //we uptade it to null 
							}
							else
								DeleteHead(&activeroom[tnum].tableserving);  //else the function delete head will delete the node without harm the list. 
						}
						else
						{
							if (activeroom[tnum].tableserving->next != NULL)               //we check if the node is the last of the list 
								activeroom[tnum].tableserving->next->prev = activeroom[tnum].tableserving->prev;  //if not we connect the list without the deleted node. (before deleting)
							activeroom[tnum].tableserving->prev->next = activeroom[tnum].tableserving->next;  //we connect the prev to the next in order to be able to delete the node whitout harming the list.
							 
							free(activeroom[tnum].tableserving->name);      //we delete the node
							free(activeroom[tnum].tableserving);
							activeroom[tnum].tableserving = head;  //and relloct the head. 
						}
					}
					else
					activeroom[tnum].tableserving = head;  //and relloct the head. 

				}
				else
					Get_Print("The table have not the Quantity.\n");
			}
		}
		if (flag == 0)     //the flag says if we founf the name.
			Get_Print("There is not such a serving.\n");
	}
}

void RemoveTable(int tnum, ptable activeroom, int n) //the function that removes the table.
{
	manatable *head;
	if (tnum > n)  //check the number of table.
		Get_Print("There is not such a table.\n");
	else
	{
		head = activeroom[tnum].tableserving; //we use head as runner. 
		printlistable(head);
		printf("The recipt is: %d $\n", activeroom[tnum].recipt);
		DeleteAll(&head);  //we delete all the list using the function delete all.
	}
}

void DeleteHead(manatable **headlistserving) //the function that deletes the head of the list.
{
	manatable *temp;
	temp = *headlistserving;                      //pointer to head
	*headlistserving = (*headlistserving)->next;    //update the head
	if (*headlistserving != NULL)
		(*headlistserving)->prev = NULL; //update the new head. 
	free(temp->name);
	free(temp);

}

void DeleteAll(manatable **head) //the function that deletes all the list.
{
	while (*head != NULL)  //if head is not null means the list is empty.
		DeleteHead(head);  //we delete the head, and keep doing it till the end.
}

void Report(mana *kitchenlist, table *activeroom, int n) // the last function of the task that will hold the reports. 
{
	int max = 0, i,flag=1; //max will hold the number of the plate that was max ordered from the restaurant.
	mana *tempkitchen;
	table *temptable;
	tempkitchen = kitchenlist; //tempkitchen is our kitchenlist runner 
	temptable = activeroom;   //temptable is our table arr[i] runner 
	char ch;
	printf("_________________________________________________________________\n");
	printf("Please enter The char of the Report A to see the max plate that was ordered\n");
	printf("Please enter The char of the Report B to see the plates that sold out\n");
	printf("Please enter The char of the Report C to see the serving of the active tables\n");
	printf("_________________________________________________________________\n");
	scanf(" %c", &ch);
	switch (ch)
	{
	case 'A':
		while (tempkitchen != NULL) //till the end of the list of elements that exists in the kitchen. 
		{
			if (tempkitchen->countmax > max) //we check from the kitchen list if the plate orders is bigger than max. 
				max = tempkitchen->countmax;
			tempkitchen = tempkitchen->next; //we realloct the pointer to the next node(plate).
		}
		tempkitchen = kitchenlist; // we realloct the pointer to the head. 
		while (tempkitchen != NULL) //till the end of the list of elements that exists in the kitchen.
		{
			if (tempkitchen->countmax == max) //if there are plates with the same number of orders as the max they will be printed. 
			{
				printf("=================================================================\n");
				printf("The name of the max serving is: %s and the quantity is: %d.\n", tempkitchen->name, max);
				printf("=================================================================\n");
			}
			tempkitchen = tempkitchen->next;
		}
		break;
	case 'B':
		tempkitchen = kitchenlist;  //we realloc the pointer to the head. 
		while (tempkitchen != NULL) //till the end of the list of elements that exists in the kitchen. 
		{
			if (tempkitchen->Quantity == 0) //we check which plates are out of stock and print them. 
			{
				printf("=================================================================\n");
				printf("The serving that is out of stock is:%s\n", tempkitchen->name);
				printf("=================================================================\n");
				flag = 0;
			}
			tempkitchen = tempkitchen->next;
		}
		if (flag)
		{
			printf("=================================================================\n");
			printf("There is not a serving that is out of stock is\n");
			printf("=================================================================\n");
		}

		break;
	case 'C':
		printf("=================================================================\n");
		for (i = 0; i < n; i++)
		{
			if (temptable[i].tableserving != NULL) //check if the table have an active order we print the orders. 
			{
				printf("The Table number %d have an active serving of:\n", temptable[i].tablenum);
				printlistable(temptable[i].tableserving); //we print the orders using printlistable function.
				printf("-----------------------------------------------------------------\n");
			}
			
		}
		printf("=================================================================\n");
		break;
	default:
		printf("There is not such of Report.\n");
	}
}