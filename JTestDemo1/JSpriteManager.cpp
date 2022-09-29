#include "JSpriteManager.h"

bool JSpriteManager::gameDataLoad(const TCHAR* pszLoad)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };
    TCHAR pTexturePath[256] = { 0 };
    TCHAR pMaskTexturePath[256] = { 0 };
    TCHAR pShaderPath[256] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, pszLoad, _T("rt"));
    if (fp_src == NULL) return false;

    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer, _T("%s"), pTemp, (unsigned int)_countof(pTemp));
    //m_rtSpriteList.resize(iNumSprite);

    while(true)
    {
        int iNumFrame = 0;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d"),
            pTemp, (unsigned int)_countof(pTemp), &iNumFrame);

        W_STR name = pTemp;
        if (name == L"#END")
        {
            break;
        }
        m_rtNameList.push_back(pTemp);

        int iReadFrame = 0;
        std::vector<nCube<2>> rtList;
        nCube<2> rt;
        for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%d %d %d %d %d"),
                &iReadFrame,
                &rt.m_vLeftTop[0], &rt.m_vLeftTop[1], &rt.m_vSize[0], &rt.m_vSize[0]);
            rtList.push_back(rt);
        }
        m_rtSpriteList.push_back(rtList);
    }
    fclose(fp_src);

    return true;
}

bool JSpriteManager::load(std::wstring fileName, std::wstring spriteName)
{
    //if(m_List.find(fileName) == m_List.end())
    //    read
    //m_rtSpriteList.clear();
    //m_rtNameList.clear();

    //if (gameDataLoad(fileName.c_str()) == false)
    //{
    //    return false;
    //}

    //HRESULT hr;
    //UINT iCurrentTexIndex = 0;
    //UINT iCurrentUVIndex = 0;
    //for (int iSp = 0; iSp < m_rtNameList.size(); iSp++)
    //{
    //    auto data = Find(m_rtNameList[iSp]);
    //    if (data != nullptr) continue;

    //    std::unique_ptr<TSprite> pNewData = nullptr;
    //    if (m_iSpriteTypeList[iSp] == 0)
    //        pNewData = std::make_unique<TSprite>();
    //    else
    //        pNewData = std::make_unique<TSpriteTexture>();

    //    pNewData->m_szName = m_rtNameList[iSp];
    //    pNewData->m_szTexturePath = m_TextureNameList[iSp];
    //    pNewData->m_szMaskTexturePath = m_MaskTextureNameList[iSp];
    //    pNewData->m_szShaderPath = m_ShaderNameList[iSp];
    //    pNewData->m_uvArray = m_rtSpriteList[iCurrentUVIndex++];

    //    if (pNewData)
    //    {
    //        m_List.insert(std::make_pair(pNewData->m_szName, std::move(pNewData)));
    //    }
    //}
    return true;
}

bool JSpriteManager::release()
{
    for (const auto& data : m_List)
    {
        data.second->release();
    }
    m_List.clear();
    return true;
}
