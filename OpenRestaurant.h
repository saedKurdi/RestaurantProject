#pragma once

#include<iostream>

#include<fstream>

#include<string>

#include<string.h>

#include"MenuFunctions.h"

#include"Classes.h"

#include"Exceptions.h"



using namespace std;






Ingredient* tomato = new Ingredient("Tomato", 2.5, 25, 70);
Ingredient* cucumber = new Ingredient("Cucumber", 1.5, 15, 70);
Ingredient* potato = new Ingredient("Potato", 1.5, 160, 75);
Ingredient* onion = new Ingredient("Onion", 1.5, 40, 50);
Ingredient* garlic = new Ingredient("Garlic", 1.5, 111, 50);
Ingredient* cheese = new Ingredient("Cheese", 2, 402, 55);


Meal* chicken = new Meal("Chicken", 8, 120);
Meal* caesar_salad = new Meal("Caesar Salad", 12, 70);
Meal* capital_salad = new Meal("Capital Salad", 7, 40);
Meal* steak = new Meal("Steak", 15, 30);
Meal* spaghetti = new Meal("Spaghetti", 7.5, 100);
Meal* sushi = new Meal("Sushi", 8.5, 70);
Meal* pizza = new Meal("Pizza", 13.5, 85);
Meal* soup = new Meal("Merci-Soup", 4.5, 35);
Meal* hot_dog = new Meal("HotDog", 3.5, 150);
Meal* burger = new Meal("Burger", 5.5, 120);







Restaurant* restaurant = new Restaurant("Saed's Restaurant", "Lokbatan Qesebesi", "Baku");

Kitchen* kitchen = new Kitchen;
Stock* stock1 = new Stock;


Admin* admin = new Admin("Saed", "Mamedov", 25, "SaedSad2005", "saedjacob445");

LoggedClients* LC = new LoggedClients;






#pragma region WritingExceptionsToFile

void WriteExceptionsToFile(const Exception& ex) {
	ofstream fout("logs.txt", ios::out);
	fout << "Error Info : " << ex.text << endl;
	fout << "File : " << ex.source << endl;
	fout << "Line NO : " << ex.line << endl;
	fout << "Date : " << ex.date << endl;
	fout.close();
}

#pragma endregion



#pragma region Writing Stock To File
class Stock;
void WritingStockToFile(Stock* stock) {
	ofstream fout("ingredients.txt", ios::out);
	fout << stock->GetIngredientCountFromStock();
	for (int i = 0; i < stock->GetIngredientCountFromStock(); i++)
	{
		fout << stock->GetIngredientsFromStock()[i]->GetName() << ' ' << stock->GetIngredientsFromStock()[i]->GetCount() << ' ';
	}
	fout.close();
}

#pragma endregion



#pragma region Reading Stock From File 

Stock* ReadStock() {
	Stock* stock = new Stock;
	ifstream fin("ingredients.txt", ios::in);


	if (fin.is_open()) {
		int count;
		fin >> count;
		for (int i = 0; i < count; i++)
		{
			Ingredient* ingredient = new Ingredient;
			string name;
			int Count;

			fin >> name >> Count;

			ingredient->SetName(name);
			ingredient->SetCount(Count);

			stock->AddIngredientToStock(ingredient);
		}
	}

	else {
		throw InvalidArgumentException("File Did Not Exist ! ", __FILE__, __LINE__, __DATE__);
	}


	fin.close();

	return stock;
}

#pragma endregion











void OpenRestaurant() {
	while (true)
	{
		int back = 0;
		system("cls");
		MainMenu();
		string select = " ";
		cout << "\t\t\t\tEnter Your Option : "; cin >> select;
		if (select == "1") {
			//admin
			string username = " ";
			string password = " ";
			int attempt = 0;
			while (true)
			{
				if (back == 1) { back = 0; break; }
				system("cls");
				cout << "\t\t\t\t\tEnter Admin Username : "; cin >> username; cout << endl << endl;
				cout << "\t\t\t\t\tEnter Admin Password : "; cin >> password; cout << endl << endl;
				if (username == admin->GetUsername() && password == admin->GetPassword()) {
					while (true)
					{
						system("cls");
						AdminMenu();
						string option = " ";
						cout << "\t\t\t\tEnter Your Option : "; cin >> option;
						if (option == "1") { // enter to kitchen
							while (true)
							{
								system("cls");
								KitchenMenu();
								cout << "\t\t\t\tEnter Your Option : "; cin >> option;
								if (option == "1") { // view orders
									system("cls");
									if (restaurant->GetTableCountWhichHasOrder() == 0) {
										SetConsoleColor(4);
										cout << "Nothing To Show ! " << endl << endl << endl;
										SetConsoleColor(7);
										system("pause");
										continue;
									}
									restaurant->ShowTablesWhichHasOrders();
									int table_no = 0;
									cout << "Enter Table NO Which You Wanna Watch "; cin >> table_no;
									Table* tableFromRestaurant = restaurant->FindTableWhichHasOrderFromRestaurant(table_no);
									system("cls");
									tableFromRestaurant->ShowTable();
									cout << endl << endl;
									cout << "1.Accept Order " << endl << endl;
									cout << "2.Reject Order " << endl << endl << endl;
									cout << "Enter Your Option : "; cin >> option;
									if (option == "1") {
										if (restaurant->FindIsThereEnoughMealIngredientInKitchenAndStock(tableFromRestaurant)) {
											restaurant->IncreaseRestaurantBudgetByOrder(tableFromRestaurant); 
											restaurant->DecreaseMealAndIngredientsFromRestaurantByOrder(tableFromRestaurant); 
											tableFromRestaurant->SetMessageFromKitchen("Your Order Was Succesfully Accepted By Admin / Kitchen");
											WritingStockToFile(restaurant->GetStock());
											system("pause");
											continue;
										}
										else {
											system("cls");
											SetConsoleColor(4);
											cout << "Can Not Accept The Message Because Of There Is Not Any Ingredients Or Meals In Your Restaurant ! " << endl << endl << endl;
											SetConsoleColor(7);
											system("pause");
											continue;
										}

									}

									else if (option == "2") {
										system("cls");
										tableFromRestaurant->SetMessageFromKitchen("Sorry But We Able To Decline Your Order : ( ");
										SetConsoleColor(2);
										cout << "The Message Were Sent ! " << endl << endl << endl;
										SetConsoleColor(7);
										system("pause");
										continue;
										
									}

									else {
										throw InvalidArgumentException("You Can Only Choose Around 1 and 2 ! ", __FILE__, __LINE__, __DATE__);
									}
								}

								else if (option == "2") { // view all meal - ready
									system("cls");
									kitchen->ShowAllMealInTheKitchen();
									system("pause");
									continue;
								}

								else if (option == "3") { // add meal - ready
									system("cls");
									string mealName = " ";
									double mealPrice = 0;
									int mealCount = 0;
									cout << "Enter Meal Name To Add : "; cin >> mealName;
									cout << "Enter Meal Price To Add : "; cin >> mealPrice;
									cout << "Enter Meal Count To Add : "; cin >> mealCount;
									Meal* newMeal = new Meal(mealName, mealPrice, mealCount);
									kitchen->AddNewMealToKitchen(newMeal);
									cout << "New Meal Was Adden ! " << endl << endl << endl << endl;
									system("pause");
									continue;
								}

								else if (option == "4") { // delete meal - ready
									system("cls");
									string mealName = " ";
									cout << "Enter Meal Name To Delete : "; cin >> mealName;
									Meal* meal = kitchen->FindMealFromKitchenByName(mealName);
									int count = 0;
									cout << "Enter Meal Count To Delete : "; cin >> count;
									kitchen->DeleteMealFromKitchen(mealName, count);
									cout << "Item " << mealName << '-' << count << "  Deleted Succesfully ! " << endl << endl << endl;
									system("pause");
									continue;

								}

								else if (option == "5") { // back - ready
									break;
								}
								else {
									throw InvalidArgumentException("You Must Choose Only Around 1 and 5 ! ", __FILE__, __LINE__, __DATE__);
								}

							}
						}

						else if (option == "2") { // enter to stock
							while (true)
							{
								system("cls");
								StockMenu();
								cout << "\t\t\t\tEnter Your Option : "; cin >> option;
								if (option == "1") { // view all ingredients - ready
									system("cls");
									cout << "\t\t\t\t1.From File " << endl << endl;
									cout << "\t\t\t\t2.From Console " << endl << endl;
									cout << "Enter Option : "; cin >> option;
									if (option == "1") {
										system("cls");
										ReadStock()->ShowAllIngredientsFromFile();
										system("pause");
										continue;
									}

									else if (option == "2") {
										system("cls");
										stock1->ShowAllIngredientsFromStock();
										system("pause");
										continue;
									}

									else {
										throw InvalidArgumentException("You Can Choose Only Around 1 and 2 ! ", __FILE__, __LINE__, __DATE__);
									}
								}

								else if (option == "2") { // add new ingredient - ready 
									system("cls");
									string ingredientName = " ";
									double ingredientPrice = 0;
									double ingredientCalorie = 0;
									int ingredientCount = 0;
									cout << "Enter Ingredient Name To Add : "; cin >> ingredientName;
									cout << "Enter Ingredient Price To Add : "; cin >> ingredientPrice;
									cout << "Enter Ingredient Calorie To Add :"; cin >> ingredientCalorie;
									cout << "Enter Ingredient Count To Add : "; cin >> ingredientCount;
									Ingredient* i = new Ingredient(ingredientName, ingredientPrice, ingredientCalorie, ingredientCount);
									stock1->AddIngredientToStock(i);
									cout << "New Ingredient Was Adden ! " << endl << endl << endl << endl;
									WritingStockToFile(stock1);
									system("pause");
									continue;
								}

								else if (option == "3") { // delete ingredient - ready
									system("cls");
									string ingredientName = " ";
									cout << "Enter Ingredient Name To Delete : "; cin >> ingredientName;
									Ingredient * i = stock1->FindIngredientByNameFromStock(ingredientName);
									int count = 0;
									cout << "Enter Ingredient Count To Delete : "; cin >> count;
									stock1->DeleteIngredientFromStock(ingredientName, count);
									cout << "Item " << ingredientName << '-' << count << "  Deleted Succesfully ! " << endl << endl << endl;
									WritingStockToFile(stock1);
									system("pause");
									continue;
								}

								else if (option == "4") { // back - ready
									break;
								}

								else {
									throw InvalidArgumentException("You Must Choose Only Around 1 and 4 ! ", __FILE__, __LINE__, __DATE__);
								}
							}
						}

						else if (option == "3") { // back to main menu - ready
							system("cls");
							back++;
							break;
						}

						else if (option == "4") {
							system("cls");
							restaurant->ShowRestaurantInfo();
							system("pause");
							continue;
						}

						else {
							throw InvalidArgumentException("You Must Choose Only Around 1 and 3 ! ", __FILE__, __LINE__, __DATE__);
						}
					}
				}

				else {
					if (attempt == 3) {
						throw InvalidArgumentException("You Only Had 3 chances ! ", __FILE__, __LINE__, __DATE__);
					}
					SetConsoleColor(4);
					cout << "\t\t\t\tWrong Password Or Username Total Attempts Left - " << 3 - attempt << endl << endl << endl;
					SetConsoleColor(7);
					attempt++;
					system("pause");
					continue;
				}


			}

		}

		else if (select == "2") {
			int back = 0;
			// davam client /////////
			while (true)
			{
				if (back == 1) { back = 0; break; }
				system("cls");
				string clientName = " ";
				cout << "Enter Name : "; cin >> clientName;
				Client * client = LC->FindClientByName(clientName);
				Order* order = new Order;
				if (client == nullptr) {  // if client is new 
					client = new Client(clientName, 350);
					system("cls");
					ShowTables(tables);
					int table_no = 0;
					cout << "\t\t\t\tEnter Table NO Which You Wanna Select : "; cin >> table_no;
					client->SetTableForClient(table_no);
					LC->AddClient(client);
					Table* clientTable = client->GetTable();

					

					while (true)
					{
						system("cls");
						cout << "1.Order " << endl << endl;
						cout << "2.<-- Back " << endl << endl << endl;
						cout << "Enter Your Option : "; cin >> select;
						if (select == "1") {
							system("cls");
							restaurant->ShowAllMealForClient();
							int select_meal = 0;
							cout << "Enter Your Option To Choose : "; cin >> select_meal;
							Meal* meal = kitchen->FindMealFromKitchenByIndex(select_meal - 1);
							Meal* copymeal = new Meal(meal->GetName(), meal->GetPrice(), meal->GetMealCount());
							while (true)
							{
								system("cls");
								cout << "1.Add Ingredient To Meal" << endl << endl;
								cout << "2. Do Not Add " << endl << endl;
								cout << "3. Order Your Meal " << endl << endl;
								cout << "4.<-- Back " << endl << endl << endl;
								cout << "Enter Your Option : "; cin >> select;
								if (select == "1") { // order meal with ingredients 
									system("cls");
									cout << "Please Select Your Ingredients For Your " << meal->GetName() << endl << endl;
									stock1->ShowAllIngredientsForClient(); cout << endl;
									int ingredient_select = 0;
									cout << "Enter Your Option : "; cin >> ingredient_select;
									Ingredient* ingredient_add_meal = stock1->FindIngredientIndex(ingredient_select - 1);
									system("cls");
									cout << "How Many You Wanna Add " << ingredient_add_meal->GetName() << " To Your " << meal->GetName() << endl << endl;
									int count_of_ingredient = 0;
									cout << "Enter : "; cin >> count_of_ingredient;
									copymeal->AddIngredientToMeal(ingredient_add_meal, count_of_ingredient);
									cout <<"How Many " << copymeal->GetName() << " You Want With " <<ingredient_add_meal->GetName() << " Ingredients ? " << endl << endl;
									int count_of_meal = 0;
									cout << "Enter : "; cin >> count_of_meal;

									Meal* addToOrder = new Meal(copymeal->GetName(), copymeal->GetPrice(), count_of_meal);
									addToOrder->AddIngredientToMeal(ingredient_add_meal, count_of_ingredient);
									order->AddMealToOrder(addToOrder);
									
									system("cls");

									order->ShowOrder();

									cout << "Added ! To Your Order ! " << endl << endl << endl;
									system("pause");
									continue;
								}

								else if (select == "2") {// order meal without ingreedient
									system("cls");
									cout << "How Many " << meal->GetName()  << " (Without Ingredients) You Wanna Order ? " << endl;
									int meal_count = 0;
									cin >> meal_count;


									system("cls");
										Meal* addToOrder = new Meal(meal->GetName(), meal->GetPrice(),meal_count);
										order->AddMealToOrder(addToOrder);
										order->ShowOrder();

									cout << "Added ! To Your Order ! " << endl << endl << endl;
									system("pause");
									continue;
								}

								else if (select == "3") {
									if (order->GetMealCount() == 0) {
										throw InvalidArgumentException("You Can Not Order Empty Order ! ", __FILE__, __LINE__, __DATE__);
									}
									system("cls");
									
									clientTable->SetOrder(order);
									restaurant->AddClientTableWhichHasOrder(clientTable);
									

									cout << "Your Order Was Sent To Kitchen  Wait For Answer From Kitchen ! " << endl << endl << endl;
									system("pause");
									break;
								}

								else if (select == "4") { // back 
									break;
								}

								else {
									throw InvalidArgumentException("You Can Choose Only Around 1 and 2 ! ", __FILE__, __LINE__, __DATE__);
								}
							}
						}

						else if (select == "2") {
							back++;
							break;
						}

						else {
							throw InvalidArgumentException("You Can Only Choose Around 1 and 2 ! ", __FILE__, __LINE__, __DATE__);
						}
					}

				}

				else { // if client is in the system 
					while (true)
					{
						system("cls");
						AddedClientMenu();
						cout << "\t\t\t\tEnter Your Option : "; cin >> select;
						if (select == "1") { // view your own order - ready
							system("cls");
							restaurant->FindTableWhichHasOrderFromRestaurant(client->GetTable()->GetTableNO())->ShowTable();
							cout << endl << endl; system("pause");
							continue;
						}

						else if (select == "2") { // view message from kitchen ready
							system("cls");
							string message = restaurant->FindTableWhichHasOrderFromRestaurant(client->GetTable()->GetTableNO())->GetMessageFromKitchen();
							cout << "Message From Kitchen Below Note : If You Were Rejected Please Leave The Restaurant  " << endl <<endl;
							cout << message << endl << endl << endl;
							system("pause");
							continue;
						}

						else if (select == "3") { // clear all data of adden client from logged clients - ready 
							system("cls");
							
							restaurant->DeleteTableFromOrdererList(client->GetTable()->GetTableNO());
							tables[client->GetTable()->GetTableNO() - 1] = nullptr;
							
							
							LC->DeleteClientFromLoggedClients(clientName);
							
							cout << "You Leaved From Restaurant As a Client " << endl << endl << endl;
							Sleep(500);
							back++;
							break;
						}

						else if (select == "4") { // back - ready
							back++;
							break;
						}

						else {
							throw InvalidArgumentException("You Must Only Choose Around 1 and 4 ! ", __FILE__, __LINE__, __DATE__);
						}
					}
					
				
				} 
			}



			////////////////
		}

		else if (select == "3") {
			Sleep(1500);
			system("cls");
			cout << endl << endl;
			cout << "\t\t\t\t\tLEAVED FROM RESTAURANT ! " << endl << endl << endl;
			break;
		}

		else {
			throw InvalidArgumentException("You Must Select Your Option Around 1 and 3 ! ", __FILE__, __LINE__, __DATE__);
		}
	}

}

