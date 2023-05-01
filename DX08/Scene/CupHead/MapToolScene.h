#pragma once 
class MapToolScene : public Scene
{
public:
	MapToolScene();
	~MapToolScene();
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	shared_ptr<Quad> _floor;
	shared_ptr<Quad> _sky;
	shared_ptr<Quad> _cloud;
};

