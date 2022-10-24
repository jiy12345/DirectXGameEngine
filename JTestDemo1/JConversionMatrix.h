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

	static JMatrix<4, 4> ViewLookAt(JVector<4>& vPosition, JVector<4>& vTarget, JVector<4>& vUp);
	static JMatrix<4, 4> PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
};

template<size_t Dimension>
inline JMatrix<3, 3> JConversionMatrix<Dimension>::Rotation(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<3, 3> m;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][1] = fSinTheta;
	RotationMatrix[1][0] = -fSinTheta; RotationMatrix[1][1] = fCosTheta;
	return m;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationX(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[1][1] = fCosTheta; RotationMatrix[1][2] = fSinTheta;
	RotationMatrix[2][1] = -fSinTheta; RotationMatrix[2][2] = fCosTheta;
	return m;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationY(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][2] = fSinTheta;
	RotationMatrix[2][0] = -fSinTheta; RotationMatrix[2][2] = fCosTheta;
	return m;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::RotationZ(float fRadian)
{
	float fCosTheta = cos(fRadian);
	float fSinTheta = sin(fRadian);
	JMatrix<4, 4> RotationMatrix;
	RotationMatrix[0][0] = fCosTheta; RotationMatrix[0][1] = fSinTheta;
	RotationMatrix[1][0] = -fSinTheta; RotationMatrix[1][1] = fCosTheta;
	return m;
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
	return ScaleMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::ViewLookAt(JVector<3>& vPosition, JVector<3>& vTarget, JVector<3>& vUp)
{
	JMatrix<4, 4> viewMatrix;
	TVector vDirection = (vTarget - vPosition).normalize();
	TVector vRightVector = cross(vUp, vDirection).normalize();
	TVector vUpVector = cross(vDirection, vRightVector).normalize();

	viewMatrix[0][0] = vRightVector.x;	viewMatrix[0][1] = vUpVector.x;	viewMatrix[0][2] = vDirection.x;
	viewMatrix[1][0] = vRightVector.y;	viewMatrix[1][1] = vUpVector.y;	viewMatrix[1][2] = vDirection.y;
	viewMatrix[2][0] = vRightVector.z;	viewMatrix[2][1] = vUpVector.z;	viewMatrix[2][2] = vDirection.z;

	viewMatrix[3][0] = -(vPosition.x * viewMatrix[0][0] + vPosition.y * viewMatrix[1][0] + vPosition.z * viewMatrix[2][0]);
	viewMatrix[3][1] = -(vPosition.x * viewMatrix[0][1] + vPosition.y * viewMatrix[1][1] + vPosition.z * viewMatrix[2][1]);
	viewMatrix[3][2] = -(vPosition.x * viewMatrix[0][2] + vPosition.y * viewMatrix[1][2] + vPosition.z * viewMatrix[2][2]);
	return viewMatrix;
}

template<size_t Dimension>
inline JMatrix<4, 4> JConversionMatrix<Dimension>::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float    h, w, Q;

	h = cot(fovy * 0.5f);
	w = h / Aspect;

	Q = fFarPlane / (fFarPlane - fNearPlane);

	JMatrix<4, 4> rotationMatrix;
	ZeroMemory(this, sizeof(rotationMatrix));

	rotationMatrix[0][0] = w;
	rotationMatrix[1][1] = h;
	rotationMatrix[2][2] = Q;
	rotationMatrix[3][2] = -Q * fNearPlane;
	rotationMatrix[2][3] = 1;

	return rotationMatrix;
}
