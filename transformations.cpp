#include "transformations.h"

/**
* Перемещение
*/
IMovable::IMovable() {

}

IMovable::~IMovable() {

}

FLOAT3 IMovable::getPosition() {
	return m_Position;
}

void IMovable::setPosition(float x, float y, float z) {
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void IMovable::Move(float x, float y, float z) {
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void IMovable::getMatrix(D3DXMATRIX* matrix) {
	D3DXMatrixTranslation(matrix, m_Position.x, m_Position.y, m_Position.z);
}

/**
* Масштабирование
*/
IScalable::IScalable() {
	m_Scale = FLOAT3(1, 1, 1);
}

IScalable::~IScalable() {

}

FLOAT3 IScalable::getScale() {
	return m_Scale;
}

void IScalable::setScale(float x, float y, float z) {
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void IScalable::Scale(float x, float y, float z) {
	m_Scale.x += x;
	m_Scale.y += y;
	m_Scale.z += z;
}

void IScalable::getMatrix(D3DXMATRIX* matrix) {
	D3DXMatrixScaling(matrix, m_Scale.x, m_Scale.y, m_Scale.z);	
}

/**
* Повороты
*/
IRotatable::IRotatable() {
	m_RotateX = 0;
	m_RotateY = 0;
	m_RotateZ = 0;
}

IRotatable::~IRotatable() {

}

float IRotatable::getRotateX() {
	return m_RotateX;
}

float IRotatable::getRotateY() {
	return m_RotateY;
}

float IRotatable::getRotateZ() {
	return m_RotateZ;
}

void IRotatable::setRotateX(float angle) {
	m_RotateX = angle;
	if (m_RotateX > 360) {
		m_RotateX = m_RotateX-360;
	}
}

void IRotatable::setRotateY(float angle) {
	m_RotateY = angle;

	if (m_RotateY > 360) {
		m_RotateY = m_RotateY-360;
	}
}

void IRotatable::setRotateZ(float angle) {
	m_RotateZ = angle;

	if (m_RotateZ > 360) {
		m_RotateZ = m_RotateZ-360;
	}
}

void IRotatable::Rotate(float x, float y, float z) {
	setRotateX(m_RotateX+x);
	setRotateY(m_RotateY+y);
	setRotateZ(m_RotateZ+z);
}

void IRotatable::getMatrix(D3DXMATRIX* matrix) {
	const float PI = 3.14159265358979323846;

	float angleX = m_RotateX*(PI/180);
	float angleY = m_RotateY*(PI/180);
	float angleZ = m_RotateZ*(PI/180);

	D3DXMATRIX RotationX, RotationY, RotationZ, RotationXY;

	D3DXMatrixRotationX(&RotationX, angleX);
	D3DXMatrixRotationY(&RotationY, angleY);
	D3DXMatrixRotationZ(&RotationZ, angleZ);

	RotationXY = RotationX * RotationY;

	//matrix = &Rotation;
	D3DXMatrixMultiply(matrix, &RotationXY, &RotationZ);
}