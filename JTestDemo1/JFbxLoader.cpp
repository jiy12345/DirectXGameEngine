#include "JFbxLoader.h"

bool JFbxLoader::init()
{
    m_pFbxManager = FbxManager::Create();
    m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
    m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
    return true;
}

bool JFbxLoader::frame()
{
    for (auto obj : m_pDrawObjList)
    {
        obj->frame();
    }
    return true;
}

bool JFbxLoader::render()
{
    for (auto obj : m_pDrawObjList)
    {
        obj->render();
    }
    return true;
}

bool JFbxLoader::release()
{
    for (auto obj : m_pDrawObjList)
    {
        obj->release();
    }

    m_pFbxScene->Destroy();
	if (m_pFbxImporter != nullptr)
	{
		m_pFbxImporter->Destroy();
		m_pFbxImporter = nullptr;
	}
	if (m_pFbxManager != nullptr)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = nullptr;
	}
    return true;
}

bool JFbxLoader::load(C_STR filename)
{
    m_pFbxImporter->Initialize(filename.c_str());
    m_pFbxImporter->Import(m_pFbxScene);
    m_pRootNode = m_pFbxScene->GetRootNode();
    preProcess(m_pRootNode);

    for (auto mesh : m_pFbxMeshList)
    {
        parseMesh(mesh);
    }
    return true;
}

void JFbxLoader::preProcess(FbxNode* pFbxNode)
{
	if (pFbxNode == nullptr) return;
	FbxMesh* pFbxMesh = pFbxNode->GetMesh();
	if (pFbxMesh)
	{
		m_pFbxMeshList.push_back(pFbxMesh);
	}
	int iNumChild = pFbxNode->GetChildCount();
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		FbxNode* pChild = pFbxNode->GetChild(iChild);
		preProcess(pChild);
	}
}

void JFbxLoader::parseMesh(FbxMesh* pFbxMesh)
{
	FbxNode* pNode = pFbxMesh->GetNode();
	JFbxObject* pObject = new JFbxObject;
	pObject->m_VertexList.clear();
	pObject->m_IndexList.clear();

	FbxLayerElementUV* VertexUVSet = nullptr;
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
	if (pFbxLayer->GetUVs() != nullptr)
	{
		VertexUVSet = pFbxLayer->GetUVs();
	}

	W_STR szDefaultDir = L"../data/fbx/";

	std::string szFileName;
	{
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(0);
		if (pSurface)
		{
			auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid())
			{
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
				szFileName = tex->GetFileName();
			}
		}
	}
	
	pObject->m_wstrTextureName = L"../data/fbx/" + JUtil::getSplitName(to_mw(szFileName));

	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	int iNumFace = 0;

	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;
		for (int iFace = 0; iFace < iNumFace; iFace++)
		{
			int iCornerIndex[3];
			iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
			iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);

			int iUVIndex[3];
			iUVIndex[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
			iUVIndex[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
			iUVIndex[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				SimpleVertex tVertex;

				int vertexID = iCornerIndex[iIndex];
				FbxVector4 v = pVertexPositions[vertexID];

				tVertex.p[0] = v.mData[0];
				tVertex.p[1] = v.mData[2];
				tVertex.p[2] = v.mData[1];
				tVertex.c = { 1,1,1,1 };
				FbxVector2 t = readTextureCoord(pFbxMesh,
					VertexUVSet,
					iCornerIndex[iIndex],
					iUVIndex[iIndex]);
				tVertex.t[0] = t.mData[0];
				tVertex.t[1] = 1.0f - t.mData[1];

				pObject->m_VertexList.push_back(tVertex);
			}
		}
	}

	m_pDrawObjList.push_back(pObject);
}

FbxVector2 JFbxLoader::readTextureCoord(FbxMesh* pFbxMesh,
	FbxLayerElementUV* pUVSet,
	int vertexIndex,
	int uvIndex)
{
	FbxVector2 t;
	FbxLayerElement::EMappingMode mode = pUVSet->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (pUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			t = pUVSet->GetDirectArray().GetAt(vertexIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = pUVSet->GetIndexArray().GetAt(vertexIndex);
			t = pUVSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (pUVSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		case FbxLayerElementUV::eIndexToDirect:
		{
			t = pUVSet->GetDirectArray().GetAt(uvIndex);
		}break;
		}break;
	}break;
	}
	return t;
}
