#include "framework.h"
#include "InvenManager.h"

InvenManager* InvenManager::_instance = nullptr;

InvenManager::InvenManager()
{
	_inven = make_shared<Inventory>();
}

InvenManager::~InvenManager()
{
}
