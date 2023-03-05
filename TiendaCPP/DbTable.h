#include <list>
#include <vector>
#include <concepts>
#include "DbModelItem.h"

#ifndef DB_TABLE_H
#define DB_TABLE_H

// Concepto utilizado para asegurarse de que el tipo T en DbTable herede de DbModelItem
template<typename T>
concept ClassDerivedFromDbModelItem = std::derived_from<T, DbModelItem>;

template <ClassDerivedFromDbModelItem T> class DbTable
{
private:
	typedef	bool(*Predicate)(T*);

	std::vector<T*> listItems;
	int tableItemLastIndex;
	std::vector<T> a;
public:
	DbTable();
	~DbTable();

	T* GetElementByID(int id);
	T* GetFirstOrDefaultElementWhich(Predicate func);
	const std::vector<T*> GetElementsWhich(Predicate func);
	const std::vector<T*> GetAllItems() const;
	void Add(T* itemToAdd);
	void Remove(int itemIDToRemove);
	void Remove(T itemToRemove);
	void Remove(std::vector<T*> itemToRemove);
	void RemoveElementsWhich(Predicate func);
	void ClearTable();
};

// TODO: Move this to DbTable.cpp
//template<ClassDerivedFromDbModelItem T>
//int DbTable<T>::tableItemLastIndex = 0;

template<ClassDerivedFromDbModelItem T>
DbTable<T>::DbTable()
{
	tableItemLastIndex = 0;
}

template<ClassDerivedFromDbModelItem T>
DbTable<T>::~DbTable()
{
	
}

template<ClassDerivedFromDbModelItem T>
T* DbTable<T>::GetElementByID(int id)
{
	auto resultIterator = std::find_if(begin(listItems), end(listItems), [&](T* const& p) {  return p->modelID == id; });

	if (resultIterator != end(listItems))
	{
		return *resultIterator;
	}
	return nullptr;
}

template<ClassDerivedFromDbModelItem T>
T* DbTable<T>::GetFirstOrDefaultElementWhich(Predicate func)
{
	auto resultIterator = std::find_if(begin(listItems), end(listItems), [&](T* const& p) { return func(p); });

	if (resultIterator != end(listItems))
	{
		return *resultIterator;
	}

	return nullptr;
}

template<ClassDerivedFromDbModelItem T>
const std::vector<T*> DbTable<T>::GetElementsWhich(Predicate func)
{
	std::vector<T*> vectorToReturn;
	auto resultIterator = std::find_if(begin(listItems), end(listItems), [&](T* const& p) { return func(p); });

	while (resultIterator != end(listItems))
	{
		vectorToReturn.push_back(*resultIterator);
		resultIterator++;
		resultIterator = std::find_if(resultIterator, end(listItems), [&](T* const& p) { return func(p); });
	}

	return vectorToReturn;
}

/// <summary>
/// Get all items of the table
/// </summary>
/// <typeparam name="T">Class derived from DbModelItem</typeparam>
/// <returns>A const list with all the items</returns>
template<ClassDerivedFromDbModelItem T>
const std::vector<T*> DbTable<T>::GetAllItems() const
{
	return listItems;
}

/// <summary>
/// Add an item in the table
/// </summary>
/// <typeparam name="T">Class derived from DbModelItem</typeparam>
/// <param name="itemToAdd">Item to add in the table</param>
template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Add(T* itemToAdd)
{
	itemToAdd->modelID = tableItemLastIndex;
	listItems.push_back(itemToAdd);
	tableItemLastIndex++;
}



template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Remove(T itemToRemove)
{
	Remove(itemToRemove.modelID);
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Remove(int itemIDToRemove)
{
	listItems.erase(
		std::remove_if(listItems.begin(), listItems.end(),
			[&](T* const& p) { return p->modelID == itemIDToRemove; }),
		listItems.end());
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Remove(std::vector<T*> itemToRemove)
{
	for (const T* item : itemToRemove)
	{
		Remove(*item);
	}
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::RemoveElementsWhich(Predicate func)
{
	listItems.erase(
		std::remove_if(listItems.begin(), listItems.end(),
			[&](T* const& p) { return func(p); }),
		listItems.end());
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::ClearTable()
{
	listItems.clear();
}
#endif