#pragma once
#include"stdafx.h"

template <size_t Dimension>
class JConversionMatrix
{
	static JMatrix<3, 3> Rotation(float fRadian);
	static JMatrix<4, 4> RotationX(float fRadian);
	static JMatrix<4, 4> RotationY(float fRadian);
	static JMatrix<4, 4> RotationZ(float fRadian);
	static JMatrix<Dimension + 1, Dimension + 1> Scale(JVector<Dimension> vScale);
	static JMatrix<Dimension + 1, Dimension + 1> Translation(JVector<Dimension> vDelta);
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
