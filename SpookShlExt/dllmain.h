// dllmain.h : Declaration of module class.

class CSpookShlExtModule : public ATL::CAtlDllModuleT< CSpookShlExtModule >
{
public :
	DECLARE_LIBID(LIBID_SpookShlExtLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SPOOKSHLEXT, "{8F04D4D4-3D19-4384-9F85-085B368EE59A}")
};

extern class CSpookShlExtModule _AtlModule;
