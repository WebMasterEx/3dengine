#pragma once

#include "dxu.h"

class CCamera {
private:
	D3DXVECTOR3 m_position; // camera position
	float m_yaw;  // rotation around the y axis
	float m_pitch; // rotation around the x axis
	float m_roll; // rotation around the z axis
	D3DXVECTOR3 m_up,m_look,m_right; // camera axis

	float RestrictAngleTo360Range(float angle) const;
public:
	CCamera(D3DXVECTOR3 startPos);
	~CCamera(void);

	void CalculateViewMatrix(D3DXMATRIX *viewMatrix);

	// Gets
	float GetYaw() const {return m_yaw;}
	float GetPitch() const {return m_pitch;}
	float GetRoll() const {return m_roll;}
	D3DXVECTOR3 GetPosition() const {return m_position;}	

	// Move operations
	void MoveForward(float amount) {m_position+=m_look*amount;}
	void MoveRight(float amount) {m_position+=m_right*amount;}
	void MoveUp(float amount) {m_position+=m_up*amount;}

	// Rotations
	void Yaw(float amount); // rotate around x axis
	void Pitch(float amount); // rotate around x axis
	void Roll(float amount); // rotate around z axis	
};