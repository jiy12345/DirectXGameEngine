#include "JBox.h"

void JBox::setVertexData()
{
	m_VertexList.resize(24);
	m_VertexList[0] = SimpleVertex(JVector<3>(-1.0f, 1.0f, -1.0f), JVector<4>(1.0f, 0.0f, 0.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[1] = SimpleVertex(JVector<3>(1.0f, 1.0f, -1.0f), JVector<4>(1.0f, 0.0f, 0.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[2] = SimpleVertex(JVector<3>(1.0f, -1.0f, -1.0f), JVector<4>(1.0f, 0.0f, 0.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[3] = SimpleVertex(JVector<3>(-1.0f, -1.0f, -1.0f), JVector<4>(1.0f, 0.0f, 0.0f, 1.0f), JVector<2>(0.0f, 1.0f));
							
	m_VertexList[4] = SimpleVertex(JVector<3>(1.0f, 1.0f, 1.0f), JVector<4>(0.0f, 0.0f, 0.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[5] = SimpleVertex(JVector<3>(-1.0f, 1.0f, 1.0f), JVector<4>(0.0f, 1.0f, 0.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[6] = SimpleVertex(JVector<3>(-1.0f, -1.0f, 1.0f), JVector<4>(0.0f, 1.0f, 0.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[7] = SimpleVertex(JVector<3>(1.0f, -1.0f, 1.0f), JVector<4>(0.0f, 1.0f, 0.0f, 1.0f), JVector<2>(0.0f, 1.0f));
					
	m_VertexList[8] = SimpleVertex(JVector<3>(1.0f, 1.0f, -1.0f), JVector<4>(0.0f, 0.0f, 1.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[9] = SimpleVertex(JVector<3>(1.0f, 1.0f, 1.0f), JVector<4>(0.0f, 0.0f, 1.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[10] = SimpleVertex(JVector<3>(1.0f, -1.0f, 1.0f), JVector<4>(0.0f, 0.0f, 1.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[11] = SimpleVertex(JVector<3>(1.0f, -1.0f, -1.0f), JVector<4>(0.0f, 0.0f, 1.0f, 1.0f), JVector<2>(0.0f, 1.0f));

	m_VertexList[12] = SimpleVertex(JVector<3>(-1.0f, 1.0f, 1.0f), JVector<4>(1.0f, 1.0f, 0.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[13] = SimpleVertex(JVector<3>(-1.0f, 1.0f, -1.0f), JVector<4>(1.0f, 1.0f, 0.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[14] = SimpleVertex(JVector<3>(-1.0f, -1.0f, -1.0f), JVector<4>(1.0f, 1.0f, 0.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[15] = SimpleVertex(JVector<3>(-1.0f, -1.0f, 1.0f), JVector<4>(1.0f, 1.0f, 0.0f, 1.0f), JVector<2>(0.0f, 1.0f));

	m_VertexList[16] = SimpleVertex(JVector<3>(-1.0f, 1.0f, 1.0f), JVector<4>(1.0f, 0.5f, 1.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[17] = SimpleVertex(JVector<3>(1.0f, 1.0f, 1.0f), JVector<4>(1.0f, 0.5f, 1.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[18] = SimpleVertex(JVector<3>(1.0f, 1.0f, -1.0f), JVector<4>(1.0f, 0.5f, 1.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[19] = SimpleVertex(JVector<3>(-1.0f, 1.0f, -1.0f), JVector<4>(1.0f, 0.5f, 1.0f, 1.0f), JVector<2>(0.0f, 1.0f));

	m_VertexList[20] = SimpleVertex(JVector<3>(-1.0f, -1.0f, -1.0f), JVector<4>(0.0f, 1.0f, 1.0f, 1.0f), JVector<2>(0.0f, 0.0f));
	m_VertexList[21] = SimpleVertex(JVector<3>(1.0f, -1.0f, -1.0f), JVector<4>(0.0f, 1.0f, 1.0f, 1.0f), JVector<2>(1.0f, 0.0f));
	m_VertexList[22] = SimpleVertex(JVector<3>(1.0f, -1.0f, 1.0f), JVector<4>(0.0f, 1.0f, 1.0f, 1.0f), JVector<2>(1.0f, 1.0f));
	m_VertexList[23] = SimpleVertex(JVector<3>(-1.0f, -1.0f, 1.0f), JVector<4>(0.0f, 1.0f, 1.0f, 1.0f), JVector<2>(0.0f, 1.0f));
}

void JBox::setIndexData()
{
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;
}

bool JBox::init()
{
	J3DObject::init();
	m_cubeArea.Set(JVector<3>(0, 0, 0), JVector<3>(100, 100, 100));
	return true;
}

bool JBox::frame()
{
	JVector<3> vPosMovement = { 0,0,0 };
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		vPosMovement[2] += 10.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		vPosMovement[2] -= 10.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		vPosMovement[0] -= 10.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		vPosMovement[0] += 10.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		vPosMovement[1] += 10.0f * I_Timer.m_fElapseTimer;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		vPosMovement[1] -= 10.0f * I_Timer.m_fElapseTimer;
	}

	if (I_Input.GetKey(VK_SPACE) == KEY_HOLD) {
		vPosMovement *= 100.0f;
	}

	m_cubeArea.m_vLeftTop += vPosMovement;

	UpdateConstantBuffer();

	return true;
}
