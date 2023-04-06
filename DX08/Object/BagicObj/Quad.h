#pragma once
class Quad
{
protected:

public:
	enum class Type
	{
		NONE,
		ABLE,
		DISABLE,
	};

	Quad();
	Quad(wstring file);
	Quad(wstring file, Vector2 size);
	Quad(Vector2 size);
	~Quad();

	virtual void Update();
	virtual void Render();

	virtual void CreateMaterial(wstring file);
	virtual void CreateMesh();

	void SetSRV(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv);
	void SetVS(shared_ptr<VertexShader> shader) { _vs = shader; }
	void SetPS(shared_ptr<PixelShader> shader) { _ps = shader; }

	shared_ptr<Transform> GetTransform() { return _transform; }

	Vector2 GetImageSize() { return _size; }

	void SetType(Type type) { _type = type; }
	Type GetType() { return _type; }


	vector<Vertex> GetVertex() { return _vertices; }
protected:
	Type _type = Type::NONE;

	Vector2 _size;

	// Mesh
	vector<UINT> _indices;
	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer>	 _vertexBuffer;
	shared_ptr<IndexBuffer>		 _indexBuffer;

	// Material
	shared_ptr<VertexShader>	 _vs;
	shared_ptr<PixelShader>		 _ps;
	shared_ptr<SRV>				 _srv;


	// 컴포넌트 패턴 : 부품 패턴
	// -> 재사용성 증가
	// -> 안정성
	// => 대포적인 유니티의 구조
	shared_ptr<Transform> _transform;
};

