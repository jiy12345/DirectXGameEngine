#pragma once
#include"stdafx.h"

template <size_t Dimension>
class JConversionMatrix
{
public:
	static JMatrix<3, 3> Rotation(float fRadian);
	static JMatrix<4, 4> RotationX(float fRadian);
	static JMatrix<4, 4> RotationY(float fRadian);
	static JMatrix<4, 4> RotationZ(float fRadian);
	static JMatrix<Dimension + 1, Dimension + 1> Scale(JVector<Dimension> vScale);
	static JMatrix<Dimension + 1, Dimension + 1> Translation(JVector<Dimension> vDelta);

	static JMatrix<4, 4> ViewLookAt();
	static JMatrix<4, 4> PerspectiveFovLH();
};

template<size_t Dimension>
inline JMatrix<3, 3> JConversionMatrix<Dimension>::Rotation(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<3, 3> RotationMatrix;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][1] = fSinTheta;
	RotationMatrix[1][0] = -fSinTheta; RotationMatrix[1][1] = fCosTheta;
	return RotationMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationX(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[1][1] = fCosTheta; RotationMatrix[1][2] = fSinTheta;
	RotationMatrix[2][1] = -fSinTheta; RotationMatrix[2][2] = fCosTheta;
	return RotationMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationY(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][2] = fSinTheta;
	RotationMatrix[2][0] = -fSinTheta; RotationMatrix[2][2] = fCosTheta;
	return RotationMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationZ(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][1] = fSinTheta;
	RotationMatrix[1][0] = -fSinTheta; RotationMatrix[1][1] = fCosTheta;
	return RotationMatrix;
}

template<size_t Dimension>
inline JMatrix<Dimension + 1, Dimension + 1> JConversionMatrix<Dimension>::Scale(JVector<Dimension> vScale)
{
	JMatrix<Dimension + 1, Dimension + 1> ScaleMatrix;

	for (int i = 0; i < Dimension; i++) {
		ScaleMatrix[i][i] = vScale[i];
	}
	return ScaleMatrix;
}

template<size_t Dimension>
inline JMatrix<Dimension + 1, Dimension + 1> JConversionMatrix<Dimension>::Translation(JVector<Dimension> vDelta)
{
	JMatrix<Dimension + 1, Dimension + 1> TranslationMatrix;

	for (int i = 0; i < Dimension; i++) {
		TranslationMatrix[Dimension][i] = vDelta[i];
	}
	return TranslationMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::ViewLookAt()
{
	JMatrix<4, 4> viewMatrix;
	JVector<3> vTarget = I_Camera.m_vTarget;
	JVector<3> vPosition = I_Camera.m_vPosition;
	JVector<3> vDirection = normalized(I_Camera.m_vTarget - I_Camera.m_vPosition);
	JVector<3> vRightVector = normalized(cross(I_Camera.m_vUp, vDirection));
	JVector<3> vUpVector = normalized(cross(vDirection, vRightVector));

	viewMatrix[0][0] = vRightVector[0];	viewMatrix[0][1] = vUpVector[0];	viewMatrix[0][2] = vDirection[0];
	viewMatrix[1][0] = vRightVector[1];	viewMatrix[1][1] = vUpVector[1];	viewMatrix[1][2] = vDirection[1];
	viewMatrix[2][0] = vRightVector[2];	viewMatrix[2][1] = vUpVector[2];	viewMatrix[2][2] = vDirection[2];

	viewMatrix[3][0] = -(I_Camera.m_vPosition[0] * viewMatrix[0][0] + I_Camera.m_vPosition[1] * viewMatrix[1][0] + I_Camera.m_vPosition[2] * viewMatrix[2][0]);
	viewMatrix[3][1] = -(I_Camera.m_vPosition[0] * viewMatrix[0][1] + I_Camera.m_vPosition[1] * viewMatrix[1][1] + I_Camera.m_vPosition[2] * viewMatrix[2][1]);
	viewMatrix[3][2] = -(I_Camera.m_vPosition[0] * viewMatrix[0][2] + I_Camera.m_vPosition[1] * viewMatrix[1][2] + I_Camera.m_vPosition[2] * viewMatrix[2][2]);
	return viewMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::PerspectiveFovLH()
{
	float    h, w, Q;

	h = 1 / tan(I_Camera.m_fovy * 0.5f);
	w = h / I_Camera.m_Aspect;

	Q = I_Camera.m_fFarPlane / (I_Camera.m_fFarPlane - I_Camera.m_fNearPlane);

	JMatrix<4, 4> rotationMatrix;

	rotationMatrix[0][0] = w;
	rotationMatrix[1][1] = h;
	rotationMatrix[2][2] = Q;
	rotationMatrix[3][2] = -Q * I_Camera.m_fNearPlane;
	rotationMatrix[2][3] = 1;
	rotationMatrix[3][3] = 0;

	return rotationMatrix;
}
