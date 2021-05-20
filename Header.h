#ifndef _Header
#define _Header
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

#define N 50


typedef struct mana   //struct of the kitchen elements(plates). 
{
	char *name; // name of the element
	int Quantity; // the quantity of the element that is on stock
	int price; // the price
	int countmax;  //counter the times the element (plate) is ordered. 
	struct mana *next;
}mana, *pmana;

typedef struct manatable //struct of the table elements (plates).
{
	char *name;   // name of the element 
	int Quantity;  // the quantity of the element is ordered 
	int price;   // the price
	struct manatable *next; 
	struct manatable *prev;
}manatable;

typedef struct table //struct of a table .
{
	int tablenum;  // table number
	manatable *tableserving; //the table orders list of element.
	int recipt; 
}table, *ptable;


struct mana* CreateProduct(FILE *in, mana *head);     //gets the kitchen info from a file and creates a list. 
void AddItems(char *newname, int newquantity, pmana list);  //the function that update the kitchen list.
struct table* createarr(int n);   //the function that creates an array of table struck.
void OrderItem(int tnum, char *name, int sumana, struct mana *kitchenlist, table *activeroom, int n);   //the function that gets the order from user and connect the new order to the active one of the table. 
struct manatable* Addserving(char *newname, int newquantity, struct manatable* listserving, mana *tempkitchen); //the function that gets a list and a new order(name,quantity), and connects between them.
void  RemoveItem(int tnum, char *name, int sumana, ptable activeroom, mana *kitchenlist, int n); //the function that remove an element from the active servinglist of the table. 
void RemoveTable(int tnum, ptable activeroom, int n); //the function that removes the table.
void DeleteHead(manatable **headlistserving); //the function that deletes the head of the list.
void DeleteAll(manatable **head); //the function that deletes all the list.
void Report(mana *kitchenlist, table *activeroom, int n); // the last function of the task that will hold the reports.

#endif