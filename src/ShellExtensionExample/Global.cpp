#include "Global.h"

#include "OverlayIconExt.h"
#include "MenuExt.h"


const CLSID CLSID_MenuExt = // ÓÒ¼ü²Ëµ¥¡£
{ 0x95fb130, 0x783f, 0x43d7, { 0xb4, 0xd5, 0xd2, 0x7d, 0xcf, 0xf3, 0x83, 0xc3 } };
const wchar_t* FRIENDLY_NAME_MenuExt = L"FastPdfContextMenu";

const CLSID CLSID_OverlayIconExt = // Í¼±êµþ¼Ó
{ 0x461b9859, 0x6952, 0x47ed, { 0x93, 0x63, 0x69, 0x86, 0xda, 0xec, 0x39, 0xeb } };
const wchar_t* FRIENDLY_NAME_OverlayIconExt = L"FastPdfOverlayIcon";

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
            FRIENDLY_NAME_OverlayIconExt
        )
    );

    m_FactoryData.push_back(
        FactoryInfo(CLSID_MenuExt, 
        &example::MenuExt::ComponentCreator,
            FRIENDLY_NAME_MenuExt
        )
    );
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