#pragma once

#include <cmath>

#include "dxu.h"

class IMovable {
public:
	IMovable();
	~IMovable();

	FLOAT3 getPosition();
	void setPosition(float x, float y, float z);

	void Move(float x, float y=0, float z=0);

	void getMatrix(D3DXMATRIX* matrix);
protected:
	FLOAT3 m_Position;
	D3DXMATRIX m_Matrix;
};

class IScalable {
public:
	IScalable();
	~IScalable();

	FLOAT3 getScale();
	void setScale(float x, float y, float z);
	void Scale(float x, float y=1, float z=1);

	void getMatrix(D3DXMATRIX* matrix);
protected:
	FLOAT3 m_Scale;
	D3DXMATRIX m_Matrix;
};

class IRotatable {
public:
	IRotatable();
	~IRotatable();

	float getRotateX();
	float getRotateY();
	float getRotateZ();

	void setRotateX(float angle);
	void setRotateY(float angle);
	void setRotateZ(float angle);

	void Rotate(float x, float y=0, float z=0);

	void getMatrix(D3DXMATRIX* matrix);
protected:
	float m_RotateX;
	float m_RotateY;
	float m_RotateZ;

	D3DXMATRIX m_Matrix;
};