#include "Global.h"

#include "OverlayIconExt.h"
#include "MenuExt.h"

const CLSID CLSID_MenuExt = // ÓÒ¼ü²Ëµ¥¡£
{ 0xf69e6532, 0xaa05, 0x4631, { 0x80, 0x1d, 0xce, 0x11, 0xd0, 0x87, 0x57, 0x59 } };
const wchar_t* FRIENDLY_NAME_MenuExt = L"FastPdfContextMenuExt";

const CLSID CLSID_OverlayIconExt = // Í¼±êµþ¼Ó
{ 0xdf363528, 0x660b, 0x447b, { 0xb8, 0xb6, 0x8a, 0x93, 0x35, 0x47, 0x74, 0x97 } };
const wchar_t* FRIENDLY_NAME_OverlayIconExt = L"FastPdfOverlayIconExt";

Global::Global(): m_hInst(nullptr), m_cDllRef(0)
{
    InitializeExtensionsData();
    m_shellIdList = RegisterClipboardFormat(CFSTR_SHELLIDLIST);
}

Global::~Global()
{
}

void Global::InitializeExtensionsData()
{
    m_FactoryData.push_back(
        FactoryInfo(CLSID_OverlayIconExt, 
        &example::OverlayIconExt::ComponentCreator,
            FRIENDLY_NAME_OverlayIconExt, FactoryType::FactoryOverlay
        )
    );

#if 0
    m_FactoryData.push_back(
        FactoryInfo(CLSID_MenuExt, 
        &example::MenuExt::ComponentCreator,
            FRIENDLY_NAME_MenuExt, FactoryType::FactoryMenu
        )
    );
#endif
}


long Global::DllRef() const
{
    return m_cDllRef;
}

void Global::DllInst(HINSTANCE val)
{
    m_hInst = val;
}

HINSTANCE Global::DllInst() const
{
    return m_hInst;
}

int Global::ShellIdList() const
{
    return m_shellIdList;
}

std::vector<FactoryInfo>& Global::FactoryData()
{
    return m_FactoryData;
}

void Global::IncrementDllRef()
{
    InterlockedIncrement(&m_cDllRef);
}

void Global::DecrementDllRef()
{
    InterlockedDecrement(&m_cDllRef);
}