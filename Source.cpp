#include"OpenRestaurant.h"



#include"Classes.h"

void main() {
	
	stock1->AddIngredientToStock(tomato);
	stock1->AddIngredientToStock(cucumber);
	stock1->AddIngredientToStock(potato);
	stock1->AddIngredientToStock(onion);
	stock1->AddIngredientToStock(garlic);
	stock1->AddIngredientToStock(cheese);

	kitchen->AddNewMealToKitchen(chicken);
	kitchen->AddNewMealToKitchen(caesar_salad);
	kitchen->AddNewMealToKitchen(capital_salad);
	kitchen->AddNewMealToKitchen(steak);
	kitchen->AddNewMealToKitchen(spaghetti);
	kitchen->AddNewMealToKitchen(sushi);
	kitchen->AddNewMealToKitchen(pizza);
	kitchen->AddNewMealToKitchen(soup);
	kitchen->AddNewMealToKitchen(hot_dog);
	kitchen->AddNewMealToKitchen(burger);

	

	restaurant->AddAdminToRestaurant(admin);
	restaurant->AddStockToRestaurant(stock1);
	restaurant->AddKitchenToRestaurant(kitchen);

	WritingStockToFile(stock1);

	while (true)
	{
		try
		{
			OpenRestaurant();
			break;
		}
		catch (const Exception& ex)
		{
			WriteExceptionsToFile(ex);
			SetConsoleColor(4);
			cout << "Exception - Error was written to File by Name : 'logs.txt' go and read " << endl << endl;
			SetConsoleColor(7);
			system("pause");

		}

	}

}