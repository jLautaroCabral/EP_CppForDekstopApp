#include "DbModelItem.h"

bool DbModelItem::operator==(const DbModelItem& other) const
{
    return this->modelID == other.modelID;
}
