// BoxFinder.h : CBoxFinder 的声明

#pragma once
#include "resource.h"       // 主符号

#include "BoxManager_i.h"
#include "DeviceEnumerator.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CBoxFinder

class ATL_NO_VTABLE CBoxFinder :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBoxFinder, &CLSID_BoxFinder>,
	public IConnectionPointContainerImpl<CBoxFinder>,
	public IDispatchImpl<IBoxFinder, &IID_IBoxFinder, &LIBID_BoxManagerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CBoxFinder()
	{
	}

	~CBoxFinder()
	{
		CDeviceEnumerator::GetInstance().WindowDetached(m_szCableName.c_str(), m_attachHwnd);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BOXFINDER)


BEGIN_COM_MAP(CBoxFinder)
	COM_INTERFACE_ENTRY(IBoxFinder)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CBoxFinder)
END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(GetCable)(DWORD *nCableId, BSTR* bstrCableName);
	STDMETHOD(AttachDevice)(BSTR bstrCableId, LONG hWnd);
	STDMETHOD(DetachDevice)(BSTR lpszCableName, LONG hWnd);

private:
	String					m_szCableName;
	HWND					m_attachHwnd;
};

OBJECT_ENTRY_AUTO(__uuidof(BoxFinder), CBoxFinder)
