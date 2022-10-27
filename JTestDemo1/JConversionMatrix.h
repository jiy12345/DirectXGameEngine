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
	static JMatrix<4, 4> PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
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
	JVector<3> vDirection = (I_Camera.vTarget - I_Camera.vPosition);
	JVector<3> vRightVector = cross(I_Camera.vUp, vDirection);
	JVector<3> vUpVector = cross(vDirection, vRightVector);

	vDirection;
	normalized(vRightVector);
	normalized(vUpVector);

	viewMatrix[0][0] = vRightVector[0];	viewMatrix[0][1] = vUpVector[0];	viewMatrix[0][2] = vDirection[0];
	viewMatrix[1][0] = vRightVector[1];	viewMatrix[1][1] = vUpVector[1];	viewMatrix[1][2] = vDirection[1];
	viewMatrix[2][0] = vRightVector[2];	viewMatrix[2][1] = vUpVector[2];	viewMatrix[2][2] = vDirection[2];

	viewMatrix[3][0] = -(I_Camera.vPosition[0] * viewMatrix[0][0] + I_Camera.vPosition[1] * viewMatrix[1][0] + I_Camera.vPosition[1] * viewMatrix[2][0]);
	viewMatrix[3][1] = -(I_Camera.vPosition[0] * viewMatrix[0][1] + I_Camera.vPosition[1] * viewMatrix[1][1] + I_Camera.vPosition[1] * viewMatrix[2][1]);
	viewMatrix[3][2] = -(I_Camera.vPosition[0] * viewMatrix[0][2] + I_Camera.vPosition[1] * viewMatrix[1][2] + I_Camera.vPosition[1] * viewMatrix[2][2]);
	return viewMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float    h, w, Q;

	h = 1 / tan(fovy * 0.5f);
	w = h / Aspect;

	Q = fFarPlane / (fFarPlane - fNearPlane);

	JMatrix<4, 4> rotationMatrix;

	rotationMatrix[0][0] = w;
	rotationMatrix[1][1] = h;
	rotationMatrix[2][2] = Q;
	rotationMatrix[3][2] = -Q * fNearPlane;
	rotationMatrix[2][3] = 1;
	rotationMatrix[3][3] = 0;

	return rotationMatrix;
}
