#include <string>

#ifndef DB_MODEL_ITEM_H
#define DB_MODEL_ITEM_H
class DbModelItem
{
public:
	virtual ~DbModelItem() = default;
	int modelID;
};
#endif