#include "JSpriteManager.h"

bool JSpriteManager::load(std::vector<JSprite>& m_vSprite, std::wstring fileName)
{
    auto iter = m_List.find(fileName);
    if (iter != m_List.end())
    {
        m_vSprite = iter->second;
        return true;
    }

    TCHAR pBuffer[256] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, fileName.c_str(), _T("rt"));
    if (fp_src == NULL) return false;

    std::vector<JSprite> vJSprites;
    int iIndex = 0;
    while (!feof(fp_src))
    {
        JSprite jSprite;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%d %f"),
            &jSprite.m_iNumFrame, &jSprite.m_totalTime);

        std::vector<nCube<2>> rtList;
        nCube<2> rt;
        for (int iFrame = 0; iFrame < jSprite.m_iNumFrame; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%f %f %f %f"),
                &rt.m_vLeftTop[0], &rt.m_vLeftTop[1], &rt.m_vSize[0], &rt.m_vSize[0]);
            jSprite.m_spriteRtLists.push_back(rt);
        }
        
        vJSprites.push_back(jSprite);
    }
    fclose(fp_src);
    
    m_vSprite = vJSprites;
    m_List.insert({ fileName, vJSprites });;

    return true;
}

bool JSpriteManager::release()
{
    m_List.clear();
    return true;
}
