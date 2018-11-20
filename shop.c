#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 5
#define LENGTH 30
#define DISCOUNT_PERCENTAGE 10
#define DISCOUNT_QUANTITY 12

// Ако ENTER_ALL не е дефининан ще иска да се въведе броя на елементите между 2 и SIZE включително,
// иначе ще се въвеждат всички елементи в масива (от [0] до [SIZE - 1])
// Изкоментирай един от двата реда: 
#define ENTER_ALL 
// #undef ENTER_ALL


// Ако е дефиниран ще проверява дали въведеният номер на продукт не съвпада с този на
// някой от вече въведените продукти и ще поиска въвеждане на нов номер
// Изкоментирай един от двата реда:
#define CHECK_FOR_UNIQUE_ID
//#undef CHECK_FOR_UNIQUE_ID

int input(struct PRODUCT products[], int max_size);
void output(struct PRODUCT products[], int count);
void show_all(struct PRODUCT products[], int count);

struct PRODUCT
{
	int id;
	char name[LENGTH];
	int quantity;
	double single_price;
	double total_price;
};

void main()
{
	int n;
	struct PRODUCT products[SIZE];
	char choice;
	int has_input = 0;

	// The Menu:
	while (1)
	{
		system("cls");
		printf("Menu:\r\n");
		printf("\t0 - Exit.\r\n");
		printf("\t1 - Enter new list of products.\r\n");
		if (has_input == 1)
		{
			printf("\t2 - Show all products.\r\n\t3 - Show 
                            the products with quantity < 10.\r\n");
		}
		printf("Choice: ");
		choice = _getch();
		switch (choice)
		{
		case '0':
		{
			return;
		}
		case '1':
		{
			n = input(products, _countof(products));
			has_input = 1;
			break;
		}
		case '2':
		{
			if (has_input == 0)
			{
				continue;
			}
			show_all(products, n);
			break;
		}
		case '3':
		{
			if (has_input == 0)
			{
				continue;
			}
			output(products, n);
			break;
		}
		default:
		{
			continue;
		}
		}
		printf("\r\n\r\n");
		system("pause");
	}
}


int input(struct PRODUCT products[], int max_size)
{
	int i;
#ifdef CHECK_FOR_UNIQUE_ID
	int j;
#endif
#ifndef ENTER_ALL
	int n;
	system("cls");
	printf("Enter the number of the products from 2 to %d: ", max_size);
	scanf_s("%d", &n);
	while (n < 2 || n > max_size)
	{
		system("cls");
		printf("Erroe!\r\nEnter the number from 2 to %d: ", max_size);
		scanf_s("%d", &n);
	}
	max_size = n;
#endif
	for (i = 0; i < max_size; i++)
	{
		system("cls");
		printf("Product %d/%d\r\n", i + 1, max_size);

		// Въвеждане на номер
		printf("ID: ");
		scanf_s("%d", &products[i].id);
#ifdef CHECK_FOR_UNIQUE_ID
		do
		{
			for (j = 0; j < i; j++)
			{
				if (products[j].id == products[i].id)
				{
					break;
				}
			}
			if (i != j)
			{
				system("cls");
				printf("Error! The ID is associated with product %d.
                                    \r\nProduct %d/%d\r\nID: ", j + 1, i + 1, max_size);
				scanf_s("%d", &products[i].id);
			}
		} while (i != j);
#endif
		// Въвеждане на име
		printf("Name: ");
		fflush(stdin);
		gets_s(products[i].name, _countof(products[0].name));

		// Въвеждане на наличност
		printf("Quantity: ");
		scanf_s("%d", &products[i].quantity);
		while (products[i].quantity < 0)
		{
			system("cls");
			printf("Error! The quantity must be a non-negative integer.
                            \r\nProduct %d/%d\r\nID: %d\r\nName: ", i + 1, max_size, products[i].id);
			puts(products[i].name);
			printf("Quantity: ");
			scanf_s("%d", &products[i].quantity);
		}

		// Въвеждане на единична цена
		printf("Single price: ");
		scanf_s("%lf", &products[i].single_price);
		while (products[i].single_price <= 0.0)
		{
			system("cls");
			printf("Error! The single price must be a possitive value.
                            \r\nProduct %d/%d\r\nID: %d\r\nName: ", i + 1, max_size, products[i].id);
			puts(products[i].name);
			printf("Quantity: %d\r\nSingle price: ", products[i].quantity);
			scanf_s("%lf", &products[i].single_price);
		}

		// Изчисляване на общата стойност за продукта
		// ако количеството < DISCOUNT_QUANTITY => няма отстъпка => количество * цена,
		// иначе има отстъпка => количество * цена * (100 - DISCOUNT_PERCENTAGE) / 100
		products[i].total_price = (products[i].quantity < DISCOUNT_QUANTITY) ?
                    products[i].quantity * products[i].single_price :
                    products[i].quantity * products[i].single_price * (100 - DISCOUNT_PERCENTAGE) / 100;
	}

	// Връщаме броя на действително въведените елементи от масива
	return max_size;
}

void output(struct PRODUCT products[], int count)
{
	int i;
	int nothing_to_print = 1;
	system("cls");
	printf("List of the products with quantity less than 10:\r\n\r\n");
	printf("||==================================================================||\r\n");
	printf("||      ID      ||               Name                 ||  Quantity  ||\r\n");
	printf("||--------------||------------------------------------||------------||\r\n");
	for (i = 0; i < count; i++)
	{
		if (products[i].quantity < 10)
		{
			nothing_to_print = 0;
			printf("||  %10d  ||  %-32s  ||  %8d  ||\r\n", products[i].id,
                            products[i].name, products[i].quantity);
		}
	}
	if (nothing_to_print == 1)
	{
		system("cls");
		printf("There are no products with quantity less than 10.\r\n");
	}
	else
	{
		printf("||==================================================================||\r\n\r\n");
	}
}


void show_all(struct PRODUCT products[], int count)
{
	int i;
	system("cls");
	printf("List of all products:\r\n\r\n");
	printf("||===========================================================================||\r\n");
	printf("||     ID     ||          Name          || Quantity || Single $ ||  Total $  ||\r\n");
	printf("||------------||------------------------||----------||----------||-----------||\r\n");
	for (i = 0; i < count; i++)
	{
		printf("|| %10d || %-22s || %8d || %8.2lf || %9.2lf ||\r\n", products[i].id, products[i].name,     
                    products[i].quantity, products[i].single_price, products[i].total_price);
	}
	printf("||===========================================================================||\r\n");
}
