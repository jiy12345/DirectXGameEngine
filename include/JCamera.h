#pragma once
#include "stdafx.h"

class JCamera: public JSingleton<JCamera>
{
	friend class JSingleton<JCamera>;
public:
	JVector<3> vPosition;
	JVector<3> vTarget; 
	const JVector<3> vUp = { 0.0f, 1.0f, 0.0f };
private:
	JCamera() {};
	~JCamera() = default;
	JCamera(const JCamera&) = delete;
	JCamera& operator=(const JCamera&) = delete;
};
#define I_Camera JCamera::GetInstance()