#pragma once
class InvenManager
{
private:
	InvenManager();
	~InvenManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InvenManager();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static InvenManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}
	shared_ptr<Inventory>& GetInven() { return _inven; }

private:
	static InvenManager* _instance;
	shared_ptr<Inventory> _inven;
};

