#include <list>
#include <concepts>
#include "DbModelItem.h"

#ifndef DB_TABLE_H
#define DB_TABLE_H

// Concepto utilizado para asegurarse de que el tipo T en DbTable herede de DbModelItem
template<typename T>
concept ClassDerivedFromDbModelItem = std::derived_from<T, DbModelItem>;

template <ClassDerivedFromDbModelItem T> class DbTable
{
	typedef	bool(*Predicade)(T*);
private:
	std::list<T*> listItems;
	int tableItemLastIndex;
public:
	DbTable();
	~DbTable();

	void Get();
	const std::list<T*> GetAllItems() const;
	void Add(T* itemToAdd);
	void Remove(T itemToRemove);
	void Remove(std::list<T*> itemToRemove);
	void RemoveItemsWich(Predicade func);
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
void DbTable<T>::Get()
{

}

/// <summary>
/// Get all items of the table
/// </summary>
/// <typeparam name="T">Class derived from DbModelItem</typeparam>
/// <returns>A const list with all the items</returns>
template<ClassDerivedFromDbModelItem T>
const std::list<T*> DbTable<T>::GetAllItems() const
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
	
	//listItems.remove_if()
	listItems.remove_if([&](T* const& p) { return p->modelID == itemToRemove.modelID; });
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Remove(std::list<T*> itemToRemove)
{
	for (const T* item : itemToRemove)
	{
		this->Remove(*item);
	}
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::RemoveItemsWich(Predicade func)
{
	listItems.remove_if([&](T* const& p) { return func(p); });
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::ClearTable()
{
	listItems.clear();
}
#endif