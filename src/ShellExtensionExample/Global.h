#ifndef GLOBAL_H
#define GLOBAL_H

#include <WinSock2.h>
#include <windows.h>
#include <vector>
#include <string>

typedef HRESULT (*FPCOMPCREATOR) (const IID&, void**);

enum FactoryType {
    FactoryMenu,
    FactoryOverlay,
};

struct FactoryInfo {
    const CLSID m_CLSID;
    FPCOMPCREATOR m_Func;
    std::wstring m_friendlyName;
    FactoryType m_type;
    FactoryInfo(const CLSID id, FPCOMPCREATOR func, const std::wstring& friendlyName, FactoryType type):
        m_CLSID(id), m_Func(func), m_friendlyName(friendlyName), m_type(type)
    {}
};

class Global
{
public:
    Global();
    HINSTANCE DllInst() const;
    void DllInst(HINSTANCE val);
    long DllRef() const;
    int ShellIdList() const;
    std::vector<FactoryInfo>& FactoryData();
    void IncrementDllRef();
    void DecrementDllRef();
    ~Global();

private:
    void InitializeExtensionsData();
    Global(const Global&);
    Global& operator= (const Global&);

private:
    std::vector<FactoryInfo> m_FactoryData;
    HINSTANCE   m_hInst;
    long        m_cDllRef;
    int         m_shellIdList;
};
#endif