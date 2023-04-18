#pragma once
class ShopScene : public Scene
{
public:
	ShopScene();
	virtual ~ShopScene();
	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void NextScene() { SCENE->SetScene("OverWorld"); }
	
private:
	shared_ptr<Shop> _shop;

	shared_ptr<Inventory> _inven;
	shared_ptr<Button> _button;
};

