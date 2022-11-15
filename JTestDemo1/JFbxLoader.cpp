#include "JFbxLoader.h"
#include "JDataLocations.h"

bool JFbxLoader::init()
{
    m_pFbxManager = FbxManager::Create();
    m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
    m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

	FbxSystemUnit::cm.ConvertScene(m_pFbxScene);
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
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

	FbxAMatrix geom;
	FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);
	geom.SetR(rot);
	geom.SetS(scale);

	FbxAMatrix normalLocalMatrix = geom;
	normalLocalMatrix = normalLocalMatrix.Inverse();
	normalLocalMatrix = normalLocalMatrix.Transpose();

	FbxVector4 Translation;
	if (pNode->LclTranslation.IsValid())
		Translation = pNode->LclTranslation.Get();

	FbxVector4 Rotation;
	if (pNode->LclRotation.IsValid())
		Rotation = pNode->LclRotation.Get();

	FbxVector4 Scale;
	if (pNode->LclScaling.IsValid())
		Scale = pNode->LclScaling.Get();

	FbxAMatrix matWorldTransform(Translation, Rotation, Scale);
	FbxAMatrix normalWorldMatrix = matWorldTransform;
	normalWorldMatrix = normalWorldMatrix.Inverse();
	normalWorldMatrix = normalWorldMatrix.Transpose();

	FbxLayerElementUV* VertexUVSet = nullptr;
	FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
	if (pFbxLayer->GetUVs() != nullptr)
	{
		VertexUVSet = pFbxLayer->GetUVs();
	}

	FbxLayerElementNormal* VertexNormalSet = nullptr;
	if (pFbxLayer->GetNormals() != nullptr)
	{
		VertexNormalSet = pFbxLayer->GetNormals();
	}

	FbxLayerElementVertexColor* VertexColorSet = nullptr;
	if (pFbxLayer->GetVertexColors() != nullptr)
	{
		VertexColorSet = pFbxLayer->GetVertexColors();
	}

	FbxLayerElementMaterial* MaterialSet = nullptr;
	if (pFbxLayer->GetMaterials() != nullptr)
	{
		MaterialSet = pFbxLayer->GetMaterials();
	}

	std::string szFileName;
	int iNumMtrl = pNode->GetMaterialCount();
	std::vector<C_STR>   texList;
	texList.resize(iNumMtrl);
	for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
	{
		FbxSurfaceMaterial* pSurface = pNode->GetMaterial(iMtrl);
		if (pSurface)
		{
			auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid())
			{
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
				szFileName = tex->GetFileName();
				texList[iMtrl] = szFileName;
			}
		}
	}
	
	if (iNumMtrl == 1)
	{
		pObject->m_wstrTextureName = FBX_LOCATION + JUtil::getSplitName(to_mw(szFileName));
	}
	if (iNumMtrl > 1)
	{
		pObject->vbDataList.resize(iNumMtrl);
		pObject->vbTexList.resize(iNumMtrl);
		for (int iTex = 0; iTex < iNumMtrl; iTex++)
		{
			pObject->vbTexList[iTex] = FBX_LOCATION + JUtil::getSplitName(to_mw(texList[iTex]));
		}
	}

	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	int iNumFace = 0;
	int iBasePolyIndex = 0;
	int iSubMtrl = 0;

	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
		iNumFace = iPolySize - 2;

		if (MaterialSet)
		{
			iSubMtrl = getSubMaterialIndex(iPoly, MaterialSet);
		}

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

			int VertexColor[3] = { 0, iFace + 2, iFace + 1 };

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int vertexID = iCornerIndex[iIndex];
				FbxVector4 v2 = pVertexPositions[vertexID];
				SimpleVertex tVertex;
				FbxVector4 v = geom.MultT(v2);
				v = matWorldTransform.MultT(v);
				tVertex.p[0] = v.mData[0];
				tVertex.p[1] = v.mData[2];
				tVertex.p[2] = v.mData[1];

				if (VertexNormalSet)
				{
					FbxVector4 n = ReadNormal(
						pFbxMesh,
						VertexNormalSet,
						iCornerIndex[iIndex],
						iBasePolyIndex + VertexColor[iIndex]);
					n = normalLocalMatrix.MultT(n);
					n = normalWorldMatrix.MultT(n);
					tVertex.n[0] = n.mData[0];
					tVertex.n[1] = n.mData[2];
					tVertex.n[2] = n.mData[1];
				}

				tVertex.c = { 1,1,1,1 };
				if (VertexColorSet)
				{
					FbxColor c = ReadColor(
						pFbxMesh,
						VertexColorSet,
						iCornerIndex[iIndex],
						iBasePolyIndex + VertexColor[iIndex]);
					tVertex.c[0] = c.mRed;
					tVertex.c[1] = c.mGreen;
					tVertex.c[2] = c.mBlue;
					tVertex.c[3] = 1.0f;
				}

				if (VertexUVSet)
				{
					FbxVector2 t = readTextureCoord(pFbxMesh,
						VertexUVSet,
						iCornerIndex[iIndex],
						iUVIndex[iIndex]);
					tVertex.t[0] = t.mData[0];
					tVertex.t[1] = 1.0f - t.mData[1];
				}

				if (iNumMtrl <= 1)
				{
					pObject->m_VertexList.push_back(tVertex);
				}
				else
				{
					pObject->vbDataList[iSubMtrl].push_back(tVertex);
				}
			}
		}
		iBasePolyIndex += iPolySize;
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

FbxColor JFbxLoader::ReadColor(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* VertexColorSet, int vertexIndex, int colorIndex)
{
	FbxColor c;
	FbxLayerElement::EMappingMode mode = VertexColorSet->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (VertexColorSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			c = VertexColorSet->GetDirectArray().GetAt(vertexIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexColorSet->GetIndexArray().GetAt(vertexIndex);
			c = VertexColorSet->GetDirectArray().GetAt(index);
		}break;
		}
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (VertexColorSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			c = VertexColorSet->GetDirectArray().GetAt(colorIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexColorSet->GetIndexArray().GetAt(colorIndex);
			c = VertexColorSet->GetDirectArray().GetAt(index);
		}break;
		}
	}break;
	}
	return c;
}

FbxVector4 JFbxLoader::ReadNormal(FbxMesh* pFbxMesh,
	FbxLayerElementNormal* VertexNormalSet,
	int posIndex,
	int normalIndex)
{
	FbxVector4 normal(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = VertexNormalSet->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (VertexNormalSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = VertexNormalSet->GetDirectArray().GetAt(posIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexNormalSet->GetIndexArray().GetAt(posIndex);
			normal = VertexNormalSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (VertexNormalSet->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = VertexNormalSet->GetDirectArray().GetAt(normalIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = VertexNormalSet->GetIndexArray().GetAt(normalIndex);
			normal = VertexNormalSet->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	}
	return normal;
}

int JFbxLoader::getSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
{
	int iSubMtrl = 0;
	if (pMaterialSetList != nullptr)
	{
		switch (pMaterialSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			switch (pMaterialSetList->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = iPoly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;
}