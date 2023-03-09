#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{
		
	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		_data.matrix = XMMatrixTranspose(value);
	}

private:
	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color = { 0,1,0,1 };
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ColorBuffer() {}

	Data _data;
};

class SpriteBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 maxFrame = { 0.0f, 0.0f };
		Vector2 curFrame = { 0.0f, 0.0f };
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	SpriteBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~SpriteBuffer() {}

	Data _data;
};

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 imageSize;
		int padding[2];
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	ActionBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ActionBuffer() {}

	Data _data;
};

class ReverseBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int reverse = 0;
		int padding[3];
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	ReverseBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ReverseBuffer() {}

	Data _data;
}; 

class FilterBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		int value1 = 0;
		int value2 = 0;
		int value3 = 0;
		Vector2 imageSize;
		Vector2 radialCenter;
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	FilterBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~FilterBuffer() {}

	Data _data;
};

class CupMosaicBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int value1 = 0;
		int padding[3];
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	CupMosaicBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~CupMosaicBuffer() {}

	Data _data;
};

class ButtonBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int state = 0;
		float hover = 0;
		float click = 0;
		int padding = 0;
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	ButtonBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ButtonBuffer() {}

	Data _data;
};

class HpBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		float ratio = 0;
		int padding[3];
	};

	// 상수버퍼 규칙
	// 16바이트 배수로 올려야한다.
	HpBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~HpBuffer() {}

	Data _data;
};