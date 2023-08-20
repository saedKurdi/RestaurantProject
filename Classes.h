#pragma once


#include<iostream>

#include"Exceptions.h"

#include<Windows.h>

#include"OpenRestaurant.h"

#include"MenuFunctions.h"


#include<string>

#include<string.h>


using namespace std;


#pragma region SetColor

void SetConsoleColor(const int& colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

#pragma endregion



class Human;
class Ingredient;
class Meal;
class Stock;
class Kitchen;
class Restaurant;
class Admin;
class LoggedClients;
class Table;
class Order;
class Client;










#pragma region Ingredient

class Ingredient {
private:
	string name;
	double price;
	double calorie;
	int count;
public:
	Ingredient() = default;

	Ingredient(const string& name, const double& price, const double& calorie, const int& count)
	{
		SetName(name);
		SetPrice(price);
		SetCalorie(calorie);
		SetCount(count);
	}

	Ingredient(const string& name, const int& count)
	{
		SetName(name);
		SetCount(count);
	}


	void ShowIngredientInfo()const {
		cout << "+++ INGREDIENT - " << GetName() << " +++ " << endl << endl;
		cout << "Price : " << GetPrice() << '$' << endl << endl;
		cout << "Total Calories : " << GetCalorie() << " kkals" << endl << endl;
		cout << "Count : " << GetCount() << endl << endl << endl;
	}

	void Decrease(const int& count) {
		if (count > this->count) {
			throw InvalidArgumentException("Can Not Decrease ! Because There Are No Ingredient In That Count To Decraese ! ", __FILE__, __LINE__, __DATE__);
		}
		this->count -= count;
	}

	void Increase(const int& count) {
		this->count += count;
	}

#pragma region Setters

	void SetName(const string& name) {
		if (name.length() < 0) {
			throw InvalidArgumentException("Minimum Characthers In Ingredient's Name Must Be Greater Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}
		this->name = name;
	}

	void SetPrice(const double& price) {
		if (price < 1) {
			throw InvalidArgumentException("Minimumv Price In This Restaurant Must Be Greater Than 1$ ! ", __FILE__, __LINE__, __DATE__);
		}
		this->price = price;
	}

	void SetCalorie(const double& calorie) {
		if (calorie < 0) {
			throw InvalidArgumentException("Minimum Calorie Must be Greater Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}
		this->calorie = calorie;
	}

	void SetCount(const int& count) {
		if (count < 0) {
			throw InvalidArgumentException("Minimum Count Must Be Greater Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}
		this->count = count;
	}

#pragma endregion

#pragma region Getters

	string GetName()const {
		return name;
	}

	double GetPrice()const {
		return price;
	}

	double GetCalorie()const {
		return calorie;
	}

	int GetCount()const {
		return count;
	}

#pragma endregion

};

#pragma endregion




#pragma region Stock

class Stock {
private:
	Ingredient** ingredients;
	int ingredientCount = 0;
public:

	Stock() {};


	void AddIngredientToStock(Ingredient* newingredient) {
		auto newingredients = new Ingredient * [GetIngredientCountFromStock() + 1] {};
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			newingredients[i] = ingredients[i];
		}
		newingredients[GetIngredientCountFromStock()] = newingredient;
		ingredients = newingredients;
		ingredientCount++;
		newingredients = nullptr;
	}



	void DeleteIngredientFromStock(const string& ingredientName, const int& count) {


		Ingredient* ingredient = FindIngredientByNameFromStock(ingredientName);

		if (count > ingredient->GetCount() || count < 0) {
			throw InvalidArgumentException("Count Can Not To Be Greater Than Ingredient's Count Or Can Not Be Little Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}

		else if (count < ingredient->GetCount()) {
			int index = FindIngredientIndexByNameFromStock(ingredientName);
			ingredients[index]->SetCount(ingredients[index]->GetCount() - count);
			return;
		}


		else {
			int elementIndex = FindIngredientIndexByNameFromStock(ingredientName);
			auto newingredients = new Ingredient * [GetIngredientCountFromStock() - 1] {};
			if (elementIndex == 0) {
				for (int i = 0; i < GetIngredientCountFromStock() - 1; i++)
				{
					newingredients[i] = ingredients[i + 1];
				}
				ingredients = newingredients;
				ingredientCount--;
				newingredients = nullptr;
			}

			else if (elementIndex == GetIngredientCountFromStock() - 1) {
				for (int i = 0; i < GetIngredientCountFromStock() - 1; i++)
				{
					newingredients[i] = ingredients[i];
				}
				ingredients = newingredients;
				ingredientCount--;
				newingredients = nullptr;
			}

			else {
				for (int i = 0; i < elementIndex; i++)
				{
					newingredients[i] = ingredients[i];
				}
				for (int i = elementIndex; i < GetIngredientCountFromStock() - 1; i++)
				{
					newingredients[i] = ingredients[i + 1];
				}
				ingredients = newingredients;
				ingredientCount--;
				newingredients = nullptr;
			}
		}

	}


	void IncreaseIngredientFromStock(const string& ingredientName, const int& count) {
		Ingredient* newingredient = FindIngredientByNameFromStock(ingredientName);
		newingredient->Increase(count);
	}

	void DecraeseIngredientFromStock(const string& ingredientName, const int& count) {
		Ingredient* newingredient = FindIngredientByNameFromStock(ingredientName);
		newingredient->Decrease(count);
	}


	Ingredient* FindIngredientIndex(const int& index) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (index == i) {
				return GetIngredientsFromStock()[i];
			}
		}
		throw InvalidArgumentException("Can Not Find Ingredient Please Try Again ! ", __FILE__, __LINE__, __DATE__);
	}

	Ingredient* FindIngredientByNameFromStock(const string& ingredientName) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (ingredientName == GetIngredientsFromStock()[i]->GetName()) {
				return GetIngredientsFromStock()[i];
			}
		}
		return nullptr;
	}


	Ingredient* FindIngredientByPointerFromStock(const Ingredient* ingredient) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (ingredient->GetName() == GetIngredientsFromStock()[i]->GetName()) {
				return GetIngredientsFromStock()[i];
			}
		}
		throw InvalidArgumentException("That Ingredient Was Not Found Look At The List At First !", __FILE__, __LINE__, __DATE__);
	}

	int FindIngredientIndexByPointerFromStock(const Ingredient* ingredient) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (ingredient->GetName() == GetIngredientsFromStock()[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException("That Ingredient Was Not Found Look At The List At First !", __FILE__, __LINE__, __DATE__);
	}


	int FindIngredientIndexByNameFromStock(const string& ingredientName) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (ingredientName == GetIngredientsFromStock()[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException("That Ingredient Was Not Found Look At The List At First !", __FILE__, __LINE__, __DATE__);
	}


	bool FindIngredientFromStock(const Ingredient* ingredient) {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			if (ingredient->GetName() == GetIngredientsFromStock()[i]->GetName()) {
				return true;
			}
		}
		throw InvalidArgumentException("Ingredient Has Not Found ! ", __FILE__, __LINE__, __DATE__);
	}

	void ShowAllIngredientsFromStock()const {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			GetIngredientsFromStock()[i]->ShowIngredientInfo();
		}
	}

	void ShowAllIngredientsFromFile()const {
		for (int i = 0; i < GetIngredientCountFromStock(); i++) {
			cout << "Name : " << GetIngredientsFromStock()[i]->GetName() << ' ' << " count : " << GetIngredientsFromStock()[i]->GetCount() << endl;
		}
	}

	void ShowAllIngredientsForClient()const {
		for (int i = 0; i < GetIngredientCountFromStock(); i++)
		{
			cout << i + 1 << " . " << GetIngredientsFromStock()[i]->GetName() << " - " << GetIngredientsFromStock()[i]->GetPrice() << "$" << endl;
		}
	}

#pragma region Getters

	Ingredient** GetIngredientsFromStock()const {
		return ingredients;
	}

	int GetIngredientCountFromStock()const {
		return ingredientCount;
	}

#pragma endregion


};


#pragma endregion





#pragma region Meal

class Meal {
private:
	string name;
	Ingredient** ingredients;
	int ingredient_count = 0;
	double price;
	int mealCount;

public:
	Meal() = delete;

	Meal(const string& name, const double& price, const int& mealCount) {
		SetName(name);
		SetPrice(price);
		SetMealCount(mealCount);
	}

	void ShowMealInfo()const {
		cout << "+++ MEAL - " << GetName() << " +++ " << endl << endl;
		cout << "Count : " << GetMealCount() << endl << endl;
		cout << "Ingredients In Meal : ";
		if (ingredient_count == 0) {
			cout << "There Is No Ingredients Added To This Meal Yet ! " << endl << endl << endl;
			cout << "Total Price : " << GetPrice() << '$' << endl << endl;
			return;
		}
		cout << endl << endl;
		double pricee = 0;
		for (int i = 0; i < GetIngredientCountInMeal(); i++)
		{
			ingredients[i]->ShowIngredientInfo();
			pricee += ingredients[i]->GetPrice() * ingredients[i]->GetCount();
		}
		cout << "Total Price : " << pricee << '$' << endl << endl;
		cout << endl << endl << endl;
	}



	void ShowMealInfoForClient()const {
		cout << "+++ MEAL - " << GetName() << " +++ " << endl << endl;
		cout << "Ingredients In Meal : ";
		if (ingredient_count == 0) {
			cout << "There Is No Ingredients Added To This Meal Yet ! " << endl << endl << endl;
			cout << "Total Price : " << GetPrice() << '$' << endl << endl;
			return;
		}
		cout << endl << endl;
		double pricee = 0;
		for (int i = 0; i < GetIngredientCountInMeal(); i++)
		{
			ingredients[i]->ShowIngredientInfo();
			pricee += ingredients[i]->GetPrice() * ingredients[i]->GetCount();
		}
		cout << "Total Price : " << pricee << '$' << endl << endl;
		cout << endl << endl << endl;
	}




	void AddIngredientToMeal(Ingredient* newingredient, const int& count) {
		if (count > newingredient->GetCount()) {
			throw InvalidArgumentException("Count Is Greater Than Ingredient's Count ! ", __FILE__, __LINE__, __DATE__);
		}

		Ingredient* ingredient = new Ingredient(newingredient->GetName(), newingredient->GetPrice(), newingredient->GetCalorie(), count);

		auto newingredients = new Ingredient * [GetIngredientCountInMeal() + 1] {};
		for (int i = 0; i < GetIngredientCountInMeal(); i++)
		{
			newingredients[i] = ingredients[i];
		}
		newingredients[GetIngredientCountInMeal()] = ingredient;

		ingredients = newingredients;
		newingredients = nullptr;
		ingredient_count++;
		price += ingredient->GetPrice() * count;

		newingredient->SetCount(newingredient->GetCount() - count);
	}

	void DeleteIngredientFromMeal(const string& ingredientName, const int& count) {

		Ingredient* ingredient = FindIngredientByName(ingredientName);

		if (count > ingredient->GetCount() || count < 0) {
			throw InvalidArgumentException("Count Can Not To Be Greater Than Ingredient's Count Or Can Not Be Little Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}

		else if (count < ingredient->GetCount()) {
			int index = FindIndexOfIngredientByName(ingredientName);
			ingredients[index]->SetCount(ingredients[index]->GetCount() - count);
			price -= ingredient->GetPrice() * count;
			return;
		}

		else {
			int elementIndex = FindIndexOfIngredientByName(ingredientName);
			auto newingredients = new Ingredient * [GetIngredientCountInMeal() - 1] {};
			if (elementIndex == 0) {
				for (int i = 0; i < GetIngredientCountInMeal() - 1; i++)
				{
					newingredients[i] = ingredients[i + 1];
				}
				ingredients = newingredients;
				ingredient_count--;
				newingredients = nullptr;
			}

			else if (elementIndex == GetIngredientCountInMeal() - 1) {
				for (int i = 0; i < GetIngredientCountInMeal() - 1; i++)
				{
					newingredients[i] = ingredients[i];
				}
				ingredients = newingredients;
				ingredient_count--;
				newingredients = nullptr;
			}

			else {
				for (int i = 0; i < elementIndex; i++)
				{
					newingredients[i] = ingredients[i];
				}
				for (int i = elementIndex; i < GetIngredientCountInMeal() - 1; i++)
				{
					newingredients[i] = ingredients[i + 1];
				}
				ingredients = newingredients;
				ingredient_count--;
				newingredients = nullptr;
			}
			price -= ingredient->GetCount() * ingredient->GetPrice();
		}

	}


	int FindIndexOfIngredientByName(const string& ingredientName) {
		for (int i = 0; i < GetIngredientCountInMeal(); i++)
		{
			if (ingredientName == GetAllIngredients()[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException("Can Not Find Ingredient By Name : " + ingredientName + '!', __FILE__, __LINE__, __DATE__);
	}

	Ingredient* FindIngredientByName(const string& ingredientName) {
		for (int i = 0; i < GetIngredientCountInMeal(); i++)
		{
			if (ingredientName == GetAllIngredients()[i]->GetName()) {
				return GetAllIngredients()[i];
			}
		}
		throw InvalidArgumentException("Ingredient Has Not Found In This Meal ! ", __FILE__, __LINE__, __DATE__);
	}


	bool HasMealIngredients()const {
		if (GetIngredientCountInMeal() == 0) {
			return false;
		}
		return true;
	}

#pragma region Setters

	void SetName(const string& name) {
		if (name.length() < 3) {
			throw InvalidArgumentException("Minimum Characthers In Meal's Name Must Be Greater Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}
		this->name = name;
	}

	void SetPrice(const double& price) {
		if (price < 3) {
			throw InvalidArgumentException("Minimum Price At Our Restaurant Is Greater Than 2$ ! ", __FILE__, __LINE__, __DATE__);
		}
		this->price = price;
	}

	void SetMealCount(const int& mealCount) {
		if (mealCount < 0) {
			throw InvalidArgumentException("Minimum Count Of Meal Must Be Greater Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}
		this->mealCount = mealCount;
	}

#pragma endregion


#pragma region Getters
	string GetName()const {
		return name;
	}

	int GetIngredientCountInMeal()const {
		return ingredient_count;
	}

	double GetPrice()const {
		return price;
	}

	Ingredient** GetAllIngredients()const {
		return ingredients;
	}

	int GetMealCount()const {
		return mealCount;
	}

#pragma endregion

};

#pragma endregion





#pragma region Kitchen

class Kitchen {
private:
	Meal** meal;
	int meal_count_in_kitchen = 0;
public:

	void ShowAllMealInTheKitchen()const {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			meal[i]->ShowMealInfo();
		}
	}




	void AddNewMealToKitchen(Meal* newmeal) {
		auto newMeal = new Meal * [GetMealCountFromKitchen() + 1] {};

		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			newMeal[i] = meal[i];
		}
		newMeal[GetMealCountFromKitchen()] = newmeal;

		meal = newMeal;
		meal_count_in_kitchen++;
		newMeal = nullptr;
	}







	void DeleteMealFromKitchen(const string& mealName, const int& count) {
		Meal* newmeal = FindMealFromKitchenByName(mealName);

		if (count > newmeal->GetMealCount() || count < 0) {
			throw InvalidArgumentException("Count Can Not To Be Greater Than Meal's Count Or Can Not Be Little Than Zero ! ", __FILE__, __LINE__, __DATE__);
		}

		else if (count < newmeal->GetMealCount()) {
			int index = FindMealIndexFromKitchenByName(mealName);
			meal[index]->SetMealCount(meal[index]->GetMealCount() - count);
			return;
		}


		else {
			int elementIndex = FindMealIndexFromKitchenByName(mealName);
			auto newmeals = new Meal * [GetMealCountFromKitchen() - 1] {};
			if (elementIndex == 0) {
				for (int i = 0; i < GetMealCountFromKitchen() - 1; i++)
				{
					newmeals[i] = meal[i + 1];
				}
				meal = newmeals;
				meal_count_in_kitchen--;
				newmeals = nullptr;
			}

			else if (elementIndex == GetMealCountFromKitchen() - 1) {
				for (int i = 0; i < GetMealCountFromKitchen() - 1; i++)
				{
					newmeals[i] = meal[i];
				}
				meal = newmeals;
				meal_count_in_kitchen--;
				newmeals = nullptr;
			}

			else {
				for (int i = 0; i < elementIndex; i++)
				{
					newmeals[i] = meal[i];
				}
				for (int i = elementIndex; i < GetMealCountFromKitchen() - 1; i++)
				{
					newmeals[i] = meal[i + 1];
				}
				meal = newmeals;
				meal_count_in_kitchen--;
				newmeals = nullptr;
			}
		}
	}

	Meal* FindMealFromKitchenByIndex(const int& index) {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			if (index == i) {
				return GetAllMealFromKitchen()[i];
			}
		}
		throw InvalidArgumentException("Can Not Find Meal Please Try Again ! ", __FILE__, __LINE__, __DATE__);
	}

	int FindMealIndexFromKitchenByName(const string& mealName) {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			if (mealName == GetAllMealFromKitchen()[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException(mealName + " Does Not Excist In The Kitchen ! ", __FILE__, __LINE__, __DATE__);
	}

	int FindMealIndexFromKitchenByPointer(const Meal* meal) {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			if (meal->GetName() == GetAllMealFromKitchen()[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException(meal->GetName() + " Does Not Excist In The Kitchen ! ", __FILE__, __LINE__, __DATE__);
	}

	Meal* FindMealFromKitchenByName(const string& mealName) {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			if (mealName == GetAllMealFromKitchen()[i]->GetName()) {
				return GetAllMealFromKitchen()[i];
			}
		}
		return nullptr;
	}

	Meal* FindMealFromKitchenByPointer(const Meal* meal) {
		for (int i = 0; i < GetMealCountFromKitchen(); i++)
		{
			if (meal->GetName() == GetAllMealFromKitchen()[i]->GetName()) {
				return GetAllMealFromKitchen()[i];
			}
		}
		throw InvalidArgumentException(meal->GetName() + " Does Not Excist In The Kitchen ! ", __FILE__, __LINE__, __DATE__);
	}
	/////




#pragma region Getters 

	Meal** GetAllMealFromKitchen()const {
		return meal;
	}

	int GetMealCountFromKitchen()const {
		return meal_count_in_kitchen;
	}


#pragma endregion

};

#pragma endregion



#pragma region Order

class Order {
private:
	Meal** meal;

public:
	int meal_count = 0;
	Order() = default;

	void ShowOrder()const {
		double total_price = 0;
		for (int i = 0; i < meal_count; i++)
		{
			total_price += meal[i]->GetPrice() * meal[i]->GetMealCount();
				meal[i]->ShowMealInfo();
		}
		cout << "Total Price Of Order : " << total_price << '$' << endl << endl;
	}



	void AddMealToOrder(Meal* newmeal) {
		auto newMeals = new Meal * [GetMealCount() + 1] {};

		for (int i = 0; i < GetMealCount(); i++)
		{
			newMeals[i] = meal[i];
		}
		newMeals[GetMealCount()] = newmeal;

		meal = newMeals;
		meal_count++;
		newMeals = nullptr;
	}



#pragma region Getters

	int GetMealCount()const {
		return meal_count;
	}

	Meal** GetAllMeal()const {
		return meal;
	}


	double GetPriceOfOrder()const {
		double price = 0;
		for (int i = 0; i < GetMealCount(); i++)
		{
			price += GetAllMeal()[i]->GetPrice() * GetAllMeal()[i]->GetMealCount();
		}
		return price;
	}

#pragma endregion

};

#pragma endregion




#pragma region Table

class Table {
private:
	int table_no;
	Order* order;
	string messageFromKitchen = "Still No Message , Wait ...";

public:
	Table(const int& table_no)
	{
		this->table_no = table_no;
	}


	void SetOrder(Order* order) {
		for (int i = 0; i < order->GetMealCount(); i++)
		{
			this->order = order;
		}
	}


	void ShowTable()const {
		cout << "Table NO - " << GetTableNO() << endl << endl;

		if (order == nullptr) {
			cout << "Order : No Order ! " << endl << endl << endl;
		}

		else {
			order->ShowOrder();
		}
	}

	void SetMessageFromKitchen(const string& messageFromKitchen) {
		if (messageFromKitchen.length() < 5) {
			throw InvalidArgumentException("Minimum Message Length Must Be Greater Than 4 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->messageFromKitchen = messageFromKitchen;
	}

	void SetTableNO(const int& NO) {
		this->table_no = NO;
	}

	int GetTableNO()const {
		return table_no;
	}

	Order* GetOrder() const {
		return order;
	}

	string GetMessageFromKitchen()const {
		return messageFromKitchen;
	}

	void AddOrderToTable(Order* order) {
		if (order != nullptr) {
			this->order = order;
		}
		else {
			throw InvalidArgumentException("It is nulll !", __FILE__, __LINE__, __DATE__);
		}

	}
};

Table** tables = new Table * [15] {};


void ShowTables(Table** tables) {
	for (int i = 0; i < 15; i++)
	{
		if (tables[i] == nullptr) {
			SetConsoleColor(2);
			cout << "\t\t\t\t\t\t| TABLE NO - " << i + 1 << " | : FREE " << endl << endl;
		}
		else {
			SetConsoleColor(4);
			cout << "\t\t\t\t\t\t| TABLE NO - " << i + 1 << " | : OCCUPIED " << endl << endl;
		}
	}SetConsoleColor(7);
	cout << endl;
}

void ShowOrdersOfTables(Table** tables) {
	for (int i = 0; i < 15; i++)
	{
		if (tables[i]->GetOrder() != nullptr) {
			cout << "Table NO : " << tables[i]->GetTableNO() << endl;
			cout << "Orders : " << endl;
			tables[i]->GetOrder()->ShowOrder();
		}
		else {
			cout << "No Order added ! " << endl;
		}
	}
}

#pragma endregion



#pragma region Client

class Client {
private:
	string name;
	double money;
	Table* table = nullptr;
public:

	static int ID;

	Client(const string& name, const double& money)
	{
		SetClientName(name);
		SetClientMoney(money);
	}


	Client(const string& name, const double& money, const int& table_no)
	{
		SetClientName(name);
		SetClientMoney(money);
		SetTableForClient(table_no);
	}

	void ExitFromRestaurant() {

		table->SetOrder(nullptr);
		table = nullptr;

	}

	void Show()const {
		cout << "Client - Info " << endl << endl;

		cout << "Name : " << name << endl << endl;

		if (table == nullptr) {
			cout << "Table : No Table ! " << endl << endl << endl;
		}

		else {
			table->ShowTable();
		}
	}

	void SetClientName(const string& name) {
		if (name.length() < 3) {
			throw InvalidArgumentException("Minimum Client Name Length Must Be Greater Than 2 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->name = name;
	}

	void SetClientMoney(const double& money) {
		if (money < 50) {
			throw InvalidArgumentException("Minimum Client Money Must be Greater Than 50$ ! ", __FILE__, __LINE__, __DATE__);
		}
		this->money = money;
	}

	void SetTableForClient(const int& table_no) {
		if (table_no < 1 || table_no > 15) {
			throw InvalidArgumentException("Table NO Must Be Around 1 and 15 ! ", __FILE__, __LINE__, __DATE__);
		}

		else {

			if (tables[table_no - 1] != nullptr) {
				throw InvalidArgumentException("That Table Is Occupied ! ", __FILE__, __LINE__, __DATE__);
			}
			tables[table_no - 1] = new Table(table_no);
			table = tables[table_no - 1];


		}
	}

	int FindTableIndexOfClient(const int& table_no) {
		for (size_t i = 0; i < 15; i++)
		{
			if (table_no - 1 == tables[i]->GetTableNO()) {
				return i;
			}
		}
		return -1;
	}

	void OrderMeal(Meal* meal, const int& count) {
		// doldur
		Meal* mealForOrder = new Meal(meal->GetName(), meal->GetPrice(), count);

		Order* order = new Order;

		order->AddMealToOrder(mealForOrder);

		table->AddOrderToTable(order);

	}

	Table* GetTable()const {
		if (table == nullptr) {
			return nullptr;
		}
		return table;
	}

	string GetName()const {
		return name;
	}
};


#pragma endregion






#pragma region Restaurant

class Restaurant {
private:
	string name;
	string address;
	string city;
	double budget = 0;
	Admin* admin;
	Stock* stock;
	Kitchen* kitchen;
	Table** tables;
	int table_count_which_has_order = 0;

public:
	Restaurant(const string& name, const string& address, const string& city) {
		SetName(name);
		SetAddress(address);
		SetCity(city);
	}


	bool FindIsThereEnoughMealIngredientInKitchenAndStock(Table * table) const {
		for (int i = 0; i < table->GetOrder()->GetMealCount(); i++)
		{
			if (table->GetOrder()->GetAllMeal()[i]->HasMealIngredients()) { // meal have ingredients
				for (int k = 0; k < table->GetOrder()->GetAllMeal()[i]->GetIngredientCountInMeal(); k++)
				{
					Meal* meal_from_kitchen = kitchen->FindMealFromKitchenByName(table->GetOrder()->GetAllMeal()[i]->GetName());
					Ingredient* ingredient_from_stock = stock->FindIngredientByNameFromStock(table->GetOrder()->GetAllMeal()[i]->GetAllIngredients()[k]->GetName());
					if (meal_from_kitchen != nullptr && table->GetOrder()[i].GetAllMeal()[i]->GetMealCount() <= meal_from_kitchen->GetMealCount() && ingredient_from_stock!=nullptr && table->GetOrder()->GetAllMeal()[i]->GetAllIngredients()[k]->GetCount() <= ingredient_from_stock->GetCount()) {
						continue;
					}

					else {
						return false;
					}
				}
				return true;
			}

			else { // meal have not have ingredients 
				Meal* meal_from_kitchen = kitchen->FindMealFromKitchenByName(table->GetOrder()->GetAllMeal()[i]->GetName());
				if (meal_from_kitchen != nullptr && table->GetOrder()[i].GetAllMeal()[i]->GetMealCount() <= meal_from_kitchen->GetMealCount()) {
					continue;
				}
				else {
					return false;
				}
			}
		}
		return true;
	}

	


	void DecreaseMealAndIngredientsFromRestaurantByOrder(Table* table) {
		for (int i = 0; i < table->GetOrder()->GetMealCount(); i++)
		{
			if (table->GetOrder()->GetAllMeal()[i]->HasMealIngredients()) { // meal have ingredients
				for (int k = 0; k < table->GetOrder()->GetAllMeal()[i]->GetIngredientCountInMeal(); k++)
				{
					Meal* meal_from_kitchen = kitchen->FindMealFromKitchenByName(table->GetOrder()->GetAllMeal()[i]->GetName());
					Ingredient* ingredient_from_stock = stock->FindIngredientByNameFromStock(table->GetOrder()->GetAllMeal()[i]->GetAllIngredients()[k]->GetName());

					meal_from_kitchen->SetMealCount(meal_from_kitchen->GetMealCount() - table->GetOrder()->GetAllMeal()[i]->GetMealCount());
					ingredient_from_stock->SetCount(ingredient_from_stock->GetCount() - table->GetOrder()->GetAllMeal()[i]->GetAllIngredients()[k]->GetCount());
				}
			}

			else { // meal have not have ingredients 
				Meal* meal_from_kitchen = kitchen->FindMealFromKitchenByName(table->GetOrder()->GetAllMeal()[i]->GetName());
				meal_from_kitchen->SetMealCount(meal_from_kitchen->GetMealCount() - table->GetOrder()->GetAllMeal()[i]->GetMealCount());
			}
		}
	}

	void IncreaseRestaurantBudgetByOrder(Table* table) {
		system("cls");
		cout << "Previous Budget Of Restaurant - " << GetRestaurantBudget() << '$' << endl;
		Sleep(2500);
		SetConsoleColor(2);
		cout << "Restaurant Budget Was Increased -   " << '+' << table->GetOrder()->GetPriceOfOrder() << '$' << endl;
		SetConsoleColor(7);
		SetBudget(GetRestaurantBudget() + table->GetOrder()->GetPriceOfOrder());
		Sleep(3000);
		cout << "Restaurant Budget Right Now   -   ";
		SetConsoleColor(2);
		cout<< GetRestaurantBudget() << '$' << endl << endl;
		SetConsoleColor(7);
	}




	void AddAdminToRestaurant(Admin* admin) {
		this->admin = admin;
	}

	void AddStockToRestaurant(Stock* stock) {
		this->stock = stock;
	}

	void AddKitchenToRestaurant(Kitchen* kitchen) {
		this->kitchen = kitchen;
	}

	void AddClientTableWhichHasOrder(Table* table) {
		auto newTables = new Table * [table_count_which_has_order + 1] {};
		for (int i = 0; i < table_count_which_has_order; i++)
		{
			newTables[i] = tables[i];
		}
		newTables[table_count_which_has_order] = table;

		tables = newTables;
		table_count_which_has_order++;
		newTables = nullptr;
	}

	void DeleteTableFromOrdererList(const int & table_no){ 
		int index = FindTableByNO(table_no);
		auto newtables = new Table * [table_count_which_has_order - 1] {};
		if (index == 0) {
			for (int i = 0; i < table_count_which_has_order - 2; i++)
			{
				newtables[i] = tables[i+1];
			}
		}

		else if (index == table_count_which_has_order - 1) {
			for (int i = 0; i < table_count_which_has_order - 1; i++)
			{
				newtables[i] = tables[i];
			}
		}

		else {
			for (int i = 0; i < index; i++)
			{
				newtables[i] = tables[i];
			}
			for (int i = index; i < table_count_which_has_order - 2; i++)
			{
				newtables[i] = tables[i + 1];
			}
		}
		tables = newtables;
		table_count_which_has_order--;
		newtables = nullptr;
	}

	int FindTableByNO(const int& table_no) {
		for (int i = 0; i < table_count_which_has_order; i++)
		{
			if (table_no == tables[i]->GetTableNO()) {
				return i;
			}
		}
		throw InvalidArgumentException("There Is No Table By That NO ! ", __FILE__, __LINE__, __DATE__);
	}

	Table* FindTableWhichHasOrderFromRestaurant(const int& table_no) {
		for (int i = 0; i < table_count_which_has_order; i++)
		{
			if (table_no == tables[i]->GetTableNO()) {
				return tables[i];
			}
		}
		throw InvalidArgumentException("That Table Does Not Have Order ! ", __FILE__, __LINE__, __DATE__);
	}

	void ShowTablesWhichHasOrders() {
		for (int i = 0; i < table_count_which_has_order; i++)
		{
			tables[i]->ShowTable();
		}
	}

	void ShowRestaurantInfo()const {
		cout << "Name : " << GetRestaurantName() << endl << endl;
		cout << "City / Address : " << GetRestaurantCity() << '/' << GetRestaurantAddress() << endl  << endl;
		cout << "Budget : " << GetRestaurantBudget() << "$" << endl << endl << endl;
	}

	void ShowAllIngredients()const {
		for (int i = 0; i < stock->GetIngredientCountFromStock(); i++)
		{
			stock->GetIngredientsFromStock()[i]->ShowIngredientInfo();
		}
	}



	void ShowAllMeal()const {
		for (int i = 0; i < kitchen->GetMealCountFromKitchen(); i++)
		{
			cout << i + 1 << " . ";
			kitchen->GetAllMealFromKitchen()[i]->ShowMealInfo();
		}
	}

	void ShowAllMealForClient()const {
		for (int i = 0; i < kitchen->GetMealCountFromKitchen(); i++)
		{
			cout << i + 1 << " . ";
			kitchen->GetAllMealFromKitchen()[i]->ShowMealInfoForClient();
		}
	}

#pragma region Setters

	void SetName(const string& name) {
		if (name.length() < 7) {
			throw InvalidArgumentException("Minimum Restaurant Name Length Must be Greater Than 6 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->name = name;
	}

	void SetAddress(const string& address) {
		if (address.length() < 11) {
			throw InvalidArgumentException("Minimum Address Name Length Must be Greater Than 10 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->address = address;
	}

	void SetCity(const string& city) {
		if (city.length() < 4) {
			throw InvalidArgumentException("Minimum City Name Length Must be Greater Than 3 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->city = city;
	}

	void SetBudget(const double& budget) {
		if (budget < this->budget) {
			throw InvalidArgumentException("Restaurant Budged Can Not Be Increased By Admin ! ", __FILE__, __LINE__, __DATE__);
		}
		this->budget = budget;
	}

#pragma endregion

#pragma region Getters

	string GetRestaurantName()const {
		return name;
	}

	string GetRestaurantAddress()const {
		return address;
	}

	string GetRestaurantCity()const {
		return city;
	}

	double GetRestaurantBudget()const {
		return budget;
	}

	Admin* GetAdmin()const {
		return admin;
	}

	Kitchen* GetKitchen()const {
		return kitchen;
	}

	Stock* GetStock()const {
		return stock;
	}

	Table** GetTablesWhichHaveOrder()const {
		return tables;
	}

	int GetTableCountWhichHasOrder()const {
		return table_count_which_has_order;
	}

#pragma endregion

};

#pragma endregion









#pragma region Human

class Human {
private:
	string name;
	string surname;
	int age;
public:
	Human(const string& name, const string& surname, const int& age) {
		SetName(name);
		SetSurname(surname);
		SetAge(age);
	}

	Human() :name("Anonymous"), surname("Anonymous"), age(0)
	{
	}

	virtual void Show()const {
		cout << "Name : " << GetName() << endl << endl;
		cout << "Surname : " << GetSurname() << endl << endl;
		cout << "Age : " << GetAge() << endl << endl;
	}

#pragma region Setters

	void SetName(const string& name) {
		if (name.length() < 3) {
			throw InvalidArgumentException("Characthers In Name Must Be Greater Than 2 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->name = name;
	}

	void SetSurname(const string& surname) {
		if (surname.length() < 3) {
			throw InvalidArgumentException("Charathers In Surname Must Be Greater Than 2 ! ", __DATE__, __LINE__, __DATE__);
		}
	}

	void SetAge(const int& age) {
		if (age < 0) {
			throw InvalidArgumentException("Minimum Age Must Be Greater Than Zero ! ", __DATE__, __LINE__, __DATE__);
		}
		this->age = age;
	}

#pragma endregion


#pragma region Getters

	string GetName()const {
		return name;
	}

	string GetSurname()const {
		return surname;
	}

	int GetAge()const {
		return age;
	}

#pragma endregion

};

#pragma endregion





#pragma region Admin

class Admin : public Human {
private:
	string username;
	string password;
public:
	Admin() = delete;

	Admin(const string& name, const string& surname, const int& age, const string& username, const string& password)
		:Human(name, surname, age)
	{
		SetUsername(username);
		SetPassword(password);
	}

#pragma region Setters

	void SetUsername(const string& username) {
		if (username.length() < 5) {
			throw InvalidArgumentException("Minimum Characthers In Username Must Be Greater Than 4 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->username = username;
	}

	void SetPassword(const string& password) {
		if (password.length() < 6) {
			throw InvalidArgumentException("Minimum Characthers In Password Must Be Greater Than 5 ! ", __FILE__, __LINE__, __DATE__);
		}
		this->password = password;
	}

#pragma endregion

#pragma region Getters

	string GetUsername()const {
		return username;
	}

	string GetPassword()const {
		return password;
	}

#pragma endregion


};

#pragma endregion



#pragma region Logged Clients

class LoggedClients {
private:
	Client** clients;
	int clientCount = 0;
public:

	LoggedClients() = default;

	void AddClient(Client* newclient) {
		auto newclients = new Client * [clientCount + 1] {};
		for (int i = 0; i < clientCount; i++)
		{
			newclients[i] = clients[i];
		}
		newclients[clientCount] = newclient;
		clients = newclients;
		clientCount++;
		newclients = nullptr;
	}

	void DeleteClientFromLoggedClients(const string& clientName) {

		int index = FindClientIndexByName(clientName);
		auto newClients = new Client * [GetClientCount() - 1] {};

		if (index == 0) {
			for (int i = 0; i < GetClientCount() - 2; i++)
			{
				newClients[i] = clients[i + 1];
			}
		}

		else if (index == clientCount - 1) {
			for (int i = 0; i < GetClientCount() - 1; i++)
			{
				newClients[i] = clients[i];
			}
		}

		else {
			for (int i = 0; i < index; i++)
			{
				newClients[i] = clients[i];
			}
			for (int i = index; i < GetClientCount() - 2; i++)
			{
				newClients[i] = clients[i + 1];
			}
		}

		clients = newClients;
		clientCount--;
		newClients = nullptr;

	}

	int  FindClientIndexByName(const string& clientName) {
		for (int i = 0; i < clientCount; i++)
		{
			if (clientName == clients[i]->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException("Client Has Not Found ! ", __FILE__, __LINE__, __DATE__);
	}

	int FindIndexByPointer(const Client* client) {
		for (int i = 0; i < clientCount; i++)
		{
			if (clients[i]->GetName() == client->GetName()) {
				return i;
			}
		}
		throw InvalidArgumentException("Can Not Find Client ! ", __FILE__, __LINE__, __DATE__);
	}

	Client* FindClientByPointer(const Client* client) {
		for (int i = 0; i < clientCount; i++)
		{
			if (client->GetName() == clients[i]->GetName()) {
				return clients[i];
			}
		}
		return nullptr;
	}

	Client* FindClientByName(const string& clientName) {
		for (int i = 0; i < clientCount; i++)
		{
			if (clientName == clients[i]->GetName()) {
				return clients[i];
			}
		}
		return nullptr;
	}




#pragma region Getters

	Client** GetClients()const {
		return clients;
	}

	int GetClientCount()const {
		return clientCount;
	}

#pragma endregion

};

#pragma endregion














