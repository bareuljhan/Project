#pragma once
class ShopScene : public Scene
{
public:
	ShopScene();
	virtual ~ShopScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;


private:
	shared_ptr<Shop> _shop;

};

