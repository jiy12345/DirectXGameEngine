#pragma once
#include "stdafx.h"

class JCamera: public JSingleton<JCamera>
{
	friend class JSingleton<JCamera>;
public:
	JVector<3>			m_vPosition;
	JVector<3>			m_vTarget; 
	const JVector<3>	m_vUp = { 0.0f, 1.0f, 0.0f }; 
public:
	float				m_fNearPlane;
	float				m_fFarPlane; 
	float				m_fovy; 
	float				m_Aspect;
public:
	bool				frame();
private:
	JCamera() {};
	~JCamera() = default;
	JCamera(const JCamera&) = delete;
	JCamera& operator=(const JCamera&) = delete;
};
#define I_Camera JCamera::GetInstance()