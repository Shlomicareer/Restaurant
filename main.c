#include "Header.h"

int main()
{
	int i, flag = 0; 
	char name[N], ch, term; //  Auxiliary variables
	int quan, tablenum, sitable; // Auxiliary variables
	table *activeroom;
	mana *head = NULL;
	manatable *temp;
	FILE *in;
	in = fopen("Manot.txt", "r");
	head = CreateProduct(in, head);
	fclose(in);
	printf("Please enter number of tables that will be active today :\n");
	while (scanf("%d", &tablenum) == 0 || tablenum<1)  //check user input
	{
		printf("The table number is not a number Try again .\n");
		printf("Please enter number of tables that will be active today :\n");
		while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars.  
	}
	activeroom = createarr(tablenum);
	while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
	do                                //the menu for the userinput. 
	{
		printf("_________________________________________________________________\n");
		printf("Enter 'a' to add quantity to the kitchen.\nEnter 'b' to get an order.\n");
		printf("Enter 'c' to cancel an order.\nEnter 'd' to get recipt and close table.\n");
		printf("Enter 'e' to get the reports menu of the restaurant.\nEnter 'f' to close the day.\n");
		printf("_________________________________________________________________\n");
		scanf(" %c", &ch);
		switch (ch)
		{
		case'a':
			printf("_________________________________________________________________\n");
			printf("The Actual kitchen list is:\n");
			printlist(head);
			printf("_________________________________________________________________\n");
			printf("Please enter the item 'name' and 'quantity' that you want to add to the kitchen:\n");
			scanf("%s", name);
			if (scanf("%d%c", &quan, &term) != 2 || term != '\n')
			{
				printf("The Quantity is not a number.\n");
				while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
			}
			else
			{
				AddItems(name, quan, head);
				printf("_________________________________________________________________\n");
				printf("The Updated kitchen list is:\n");
				printlist(head);
				printf("_________________________________________________________________\n");
			}

			break;
		case'b':
			printf("**************************THE MENU IS**************************\n");
			printlist(head);
			printf("***************************************************************\n");
			printf("Please enter the 'table number' you want to sit, also the serving 'name' and how many 'plates':\n");
			if (scanf("%d", &sitable) == 0)
			{
				printf("The table number is not a number =(.\n");
				while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 

			}
			else
			{
				scanf("%s", name);
				if (scanf("%d", &quan) == 0)
				{
					while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
					printf("The Quantity number is not a number =(.\n");
				}
				else
				{

					OrderItem(sitable-1, name, quan, head, activeroom, tablenum);
				}
			}

			break;
		case'c':
			printf("Please enter the 'table number', also the serving 'name' and Quantity to delete:\n");
			if (scanf("%d", &sitable) == 0)
			{
				printf("The table number is not a number =(.\n");
				while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
				 
			}
			else
			{
				scanf("%s", name);
				if (scanf("%d", &quan) == 0)
				{
					while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
					printf("The Quantity number is not a number =(.\n");
				}
				else
				{
					RemoveItem(sitable-1, name, quan, activeroom, head, tablenum);
				}
			}

			break;
		case'd':
			printf("Please enter the table number the you want to get the recipt:\n");
			if (scanf("%d%c", &sitable, &term) != 2 || term != '\n')
			{
				printf("The table number is not an interger.\n");
				while (getchar() != '\n'); //need to clear the buffer from chars so it does not remembers old chars. 
			}
			else
			{
				printf("The list is:\n");
				RemoveTable(sitable-1, activeroom, tablenum);
				activeroom[sitable - 1].tableserving = NULL;  //just to be sure that the table gets initializated. 
			}
			break;
		case'e':
			Report(head, activeroom, tablenum);
			break;
		case'f':
			printf("Thank you very much, have a good day $$$ ;).\n");
			for (i = 0; i < tablenum;i++)
			{
				if((activeroom[i].tableserving)!=NULL)   //free the servinglist from every table. 
				DeleteAll(&activeroom[i].tableserving);
			}

			break;
		default:
			printf("wrong input\n");
		}

	} while (ch != 'f');
	free(activeroom); // free the array.
	deleteList(head); //free the kitchen list.
	getch();
	return 0;
}







