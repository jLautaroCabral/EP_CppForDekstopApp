#include <list>
#include <concepts>
#include "DbModelItem.h"

#ifndef DB_TABLE_H
#define DB_TABLE_H

// Concepto utilizado para asegurarse de que el tipo T en DbList herede de DbModelItem
template<typename T>
concept ClassDerivedFromDbModelItem = std::derived_from<T, DbModelItem>;

template <ClassDerivedFromDbModelItem T> class DbTable
{
private:
	std::list<T*> listItems;
public:
	DbTable();
	~DbTable();

	void Get();
	const std::list<T*> GetAllItems() const;
	void Add(T itemToAdd);
	void Remove(T itemToRemove);
};

// TODO: Move this to DbTable.cpp

template<ClassDerivedFromDbModelItem T>
DbTable<T>::DbTable()
{
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
void DbTable<T>::Add(T itemToAdd)
{
	listItems.push_back(&itemToAdd);
}

template<ClassDerivedFromDbModelItem T>
void DbTable<T>::Remove(T itemToRemove)
{
	listItems.remove(itemToRemove);
}
#endif