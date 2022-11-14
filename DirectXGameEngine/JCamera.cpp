#include "JCamera.h"
#include "JWriter.h"

void JCamera::setTarget(JVector<3> vTarget) {
	switch (cameraType) {
	case TOP_VIEW:
		m_vTarget = vTarget;
		m_vPosition = vTarget;
		m_vPosition[2] += 100;
		break;
	case QUARTER_VIEW:
		m_vTarget = vTarget;
		m_vPosition = vTarget;
		m_vPosition[1] -= 100;
		m_vPosition[2] += 100;
		break;
	case FIRST_PERSON_VIEW:
		break;
	}
}

bool JCamera::init()
{
	m_fNearPlane = 1.0f;
	m_fFarPlane = 1000.0f;
	m_fovy = T_PI * 0.25f;
	m_Aspect = (float)I_Window.m_rtClient.right / (float)I_Window.m_rtClient.bottom;
	return true;
}

bool JCamera::frame()
{
	if (I_Input.GetKey('P') == KEY_PUSH) {
		cameraType = static_cast<CAMERA_TYPE>((cameraType + 1) % NUM_OF_CAMERA_TYPE);
	}

	std::cout << cameraType << '\n';

	if (cameraType != FIRST_PERSON_VIEW) {
		return true;
	}

	JVector<3> vPosMovement = { 0,0,0 };
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		vPosMovement[2] += 30.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		vPosMovement[2] -= 30.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		vPosMovement[0] -= 30.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		vPosMovement[0] += 30.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		vPosMovement[1] -= 30.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		vPosMovement[1] += 30.0f * I_Timer.m_fElapseTimer;
	}

	if (I_Input.GetKey(VK_SPACE) == KEY_HOLD) {
		vPosMovement *= 50.0f;
	}

	m_vPosition += vPosMovement;

	return true;
}

void JCamera::updateWindowSize()
{
	m_Aspect = (float)I_Window.m_rtClient.right / (float)I_Window.m_rtClient.bottom;
}

inline JMatrix<4, 4> JCamera::ViewLookAt()
{
	JMatrix<4, 4> viewMatrix;
	JVector<3> vTarget = m_vTarget;
	JVector<3> vPosition = m_vPosition;
	JVector<3> vDirection = normalized(m_vTarget - m_vPosition);
	JVector<3> vRightVector = normalized(cross(m_vUp, vDirection));
	JVector<3> vUpVector = normalized(cross(vDirection, vRightVector));

	viewMatrix[0][0] = vRightVector[0];	viewMatrix[0][1] = vUpVector[0];	viewMatrix[0][2] = vDirection[0];
	viewMatrix[1][0] = vRightVector[1];	viewMatrix[1][1] = vUpVector[1];	viewMatrix[1][2] = vDirection[1];
	viewMatrix[2][0] = vRightVector[2];	viewMatrix[2][1] = vUpVector[2];	viewMatrix[2][2] = vDirection[2];

	viewMatrix[3][0] = -(m_vPosition[0] * viewMatrix[0][0] + m_vPosition[1] * viewMatrix[1][0] + m_vPosition[2] * viewMatrix[2][0]);
	viewMatrix[3][1] = -(m_vPosition[0] * viewMatrix[0][1] + m_vPosition[1] * viewMatrix[1][1] + m_vPosition[2] * viewMatrix[2][1]);
	viewMatrix[3][2] = -(m_vPosition[0] * viewMatrix[0][2] + m_vPosition[1] * viewMatrix[1][2] + m_vPosition[2] * viewMatrix[2][2]);
	return viewMatrix;
}

inline JMatrix<4, 4> JCamera::PerspectiveFovLH()
{
	float    h, w, Q;

	h = 1 / tan(m_fovy * 0.5f);
	w = h / m_Aspect;

	Q = m_fFarPlane / (m_fFarPlane - m_fNearPlane);

	JMatrix<4, 4> rotationMatrix;

	rotationMatrix[0][0] = w;
	rotationMatrix[1][1] = h;
	rotationMatrix[2][2] = Q;
	rotationMatrix[3][2] = -Q * m_fNearPlane;
	rotationMatrix[2][3] = 1;
	rotationMatrix[3][3] = 0;

	return rotationMatrix;
}
