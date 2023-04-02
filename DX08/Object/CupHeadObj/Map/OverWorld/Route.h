#pragma once
class Route
{
public:
	Route();
	~Route();

	void Update();
	void Render();

	void CreateRoute();

	vector<shared_ptr<Quad>> GetBlocks() { return _blocks; }
private:
	vector<shared_ptr<Quad>> _blocks;
};