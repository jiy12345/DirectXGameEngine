#pragma once
#include "stdafx.h"
#include "fbxsdk.h"
#include "JUtil.h"
#include "JFbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class JFbxLoader
{
public:
	FbxManager*					m_pFbxManager;
	FbxImporter*				m_pFbxImporter;
	FbxScene*					m_pFbxScene;
	FbxNode*					m_pRootNode;
	std::vector<FbxMesh*>		m_pFbxMeshList;
	std::vector<JFbxObject*>	m_pDrawObjList;
	ID3D11DeviceContext*		m_pContext = nullptr;
public:
	bool		init();
	bool		frame();
	bool		render();
	bool		release();
public:
	bool		load(C_STR filename);
	void		preProcess(FbxNode* pFbxNode);
	void		parseMesh(FbxMesh* pFbxMesh);
	FbxVector2  readTextureCoord(FbxMesh* pFbxMesh,
		FbxLayerElementUV* pUVSet,
		int vertexIndex,
		int uvIndex);
	FbxColor ReadColor(FbxMesh* pFbxMesh, 
		FbxLayerElementVertexColor* VertexColorSet, 
		int vertexIndex, 
		int colorIndex);
	FbxVector4 ReadNormal(FbxMesh* pFbxMesh, 
		FbxLayerElementNormal* VertexNormalSet, 
		int posIndex, 
		int normalIndex);
	int getSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
};

