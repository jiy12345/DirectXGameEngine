#pragma once
#include "stdafx.h"

enum CAMERA_TYPE {
	TOP_VIEW,
	QUARTER_VIEW,
	FIRST_PERSON_VIEW,
	NUM_OF_CAMERA_TYPE
};

class JCamera: public JSingleton<JCamera>
{
	friend class JSingleton<JCamera>;
public:
	CAMERA_TYPE			cameraType = TOP_VIEW;
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
	bool				init();
	bool				frame();
public:
	void				setTarget(JVector<3> vTarget);
	void				updateWindowSize();
public:
	JMatrix<4, 4>		ViewLookAt();
	JMatrix<4, 4>		PerspectiveFovLH();
private:
	JCamera() {};
	~JCamera() = default;
	JCamera(const JCamera&) = delete;
	JCamera& operator=(const JCamera&) = delete;
};
#define I_Camera JCamera::GetInstance()