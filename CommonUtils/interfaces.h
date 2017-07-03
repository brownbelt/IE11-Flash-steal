#pragma once

#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <Shtypes.h>
#include <DocObj.h>

struct __declspec(uuid("1AC7516E-E6BB-4A69-B63F-E841904DC5A6")) IIEUserBroker : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE Initialize(HWND *, LPCWSTR, LPDWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateProcessW(DWORD pid, LPWSTR appName, LPWSTR cmdline, DWORD, DWORD, LPCSTR, WORD*, /* _BROKER_STARTUPINFOW*/ void *, /* _BROKER_PROCESS_INFORMATION */ void*) = 0;
	virtual HRESULT STDMETHODCALLTYPE WinExec(DWORD pid, LPCSTR, DWORD, DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE BrokerCreateKnownObject(_GUID const &, _GUID const &, IUnknown * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE BrokerCoCreateInstance() = 0;
	virtual HRESULT STDMETHODCALLTYPE BrokerCoCreateInstanceEx(DWORD pid, _GUID const &, IUnknown *, DWORD, _COSERVERINFO *, DWORD, /* tagBROKER_MULTI_QI */ void *) = 0;
	virtual HRESULT STDMETHODCALLTYPE BrokerCoGetClassObject(DWORD pid, _GUID const &, DWORD, _COSERVERINFO *, _GUID const &, IUnknown * *) = 0;
};

struct __declspec(uuid("BDB57FF2-79B9-4205-9447-F5FE85F37312")) CIEAxInstallBroker
{
};

struct __declspec(uuid("B2103BDB-B79E-4474-8424-4363161118D5")) IIEAxInstallBrokerBroker : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE BrokerGetAxInstallBroker(REFCLSID rclsid, REFIID riid, int unknown, int type, HWND, IUnknown** ppv) = 0;
};

_COM_SMARTPTR_TYPEDEF(IIEAxInstallBrokerBroker, __uuidof(IIEAxInstallBrokerBroker));

struct _internet_shortcut_params {
	/* 64bit  32bit */
	/* 0      0     */ LPITEMIDLIST pidl; // Parsed URL
	/* 8      4     */ LPCWSTR shortcut_name; // Without ".url" extension
	/* 10     8     */ LPCWSTR shortcut_dir; // Without terminating slash.
	/* 18     c     */ LPCWSTR str; // empty string -- maybe a buffer of some kind?
	/* 20     10    */ DWORD path_size; // set to MAX_PATH
	/* 24     14    */ DWORD unk0; // set to 0
	/* 28     18    */ DWORD unk1; // set to 0
	/* 2c     1c    */ DWORD unk2; // set to 1
	/* 30     20    */ PVOID cmd_target; // NULL works for us. Really an IOleCommandTarget*.
	/* 38     24    */ DWORD unk3; // set to 0
	/* 40     28    */ DWORD unk4; // set to 0
};

struct ERF
{
	//+0x000 erfOper          : Int4B
	//	+ 0x004 erfType : Int4B
	//	+ 0x008 fError : Int4B

	int erfOper;
	int erfType;
	int fError;
};

struct FNAME
{
	/*+0x000 pszFilename      : Ptr32 Char
	+ 0x004 pNextName : Ptr32 sFNAME
	+ 0x008 status : Uint4B*/

	char* pszFilenane;
	FNAME* pNextName;
	UINT status;
};

struct SESSION
{
	/*+0x000 cbCabSize        : Uint4B
	+ 0x004 erf : ERF
	+ 0x010 pFileList : Ptr32 sFNAME
	+ 0x014 cFiles : Uint4B
	+ 0x018 flags : Uint4B
	+ 0x01c achLocation : [260] Char
	+ 0x120 achFile : [260] Char
	+ 0x224 achCabPath : [260] Char
	+ 0x328 pFilesToExtract : Ptr32 sFNAME*/

	UINT cbCabSize;
	ERF erf;
	FNAME* pFileList;
	UINT cFiles;
	UINT flags;
	char achLocation[260];
	char achFile[260];
	char achCabPath[260];
	FNAME* pFilesToExtract;
};

struct __declspec(uuid("BC0EC710-A3ED-4F99-B14F-5FD59FDACEA3")) IIeAxiInstaller2 : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE VerifyFile(BSTR, HWND__ *, BSTR, BSTR, BSTR, unsigned int, unsigned int, _GUID const &, BSTR*, unsigned int *, unsigned char **) = 0;
	virtual HRESULT STDMETHODCALLTYPE RunSetupCommand(BSTR, HWND__ *, BSTR, BSTR, BSTR, BSTR, unsigned int, unsigned int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE InstallFile(BSTR sessionGuid, HWND__ *, BSTR sourcePath, BSTR sourceFile, BSTR destPath, BSTR destFile, unsigned int unk) = 0;
	virtual HRESULT STDMETHODCALLTYPE RegisterExeFile(BSTR sessionGuid, BSTR cmdline, int unk, _PROCESS_INFORMATION *) = 0;
	virtual HRESULT STDMETHODCALLTYPE RegisterDllFile(BSTR, BSTR, int) = 0;
	virtual HRESULT STDMETHODCALLTYPE InstallCatalogFile(BSTR, BSTR) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateLanguageCheck(BSTR, unsigned short const *, _FILETIME) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateDistributionUnit(BSTR, unsigned short const *, unsigned short const *, unsigned int, unsigned int *, unsigned short const *, int, unsigned short const *, unsigned short const *, long, unsigned short const *, unsigned short const *, unsigned short const *, unsigned int, unsigned short const * *, unsigned int, unsigned short const * *, unsigned int, unsigned short const * *, unsigned short const * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateModuleUsage(BSTR, char const *, char const *, char const *, char const *, unsigned int) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumerateFiles(BSTR sessionGuid, char const * cabPath, SESSION *session) = 0;
	virtual HRESULT STDMETHODCALLTYPE ExtractFiles(BSTR sessionGuid, char const * cabPath, SESSION *session) = 0;
	virtual HRESULT STDMETHODCALLTYPE RemoveExtractedFilesAndDirs(BSTR, SESSION *) = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateExtensionsManager(BSTR, _GUID const &, IUnknown * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE RegisterDllFile2(BSTR, BSTR, int, int) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateDistributionUnit2(BSTR, unsigned short const *, unsigned short const *, unsigned int, unsigned int *, unsigned short const *, int, unsigned short const *, unsigned short const *, long, unsigned short const *, unsigned short const *, unsigned short const *, unsigned int, unsigned short const * *, int *, unsigned int, unsigned short const * *, unsigned int, unsigned short const * *, unsigned short const * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateAllowedDomainsList(_GUID const &, BSTR, int) = 0;
	virtual HRESULT STDMETHODCALLTYPE DeleteExtractedFile(char const *) = 0;
};

_COM_SMARTPTR_TYPEDEF(IIeAxiInstaller2, __uuidof(IIeAxiInstaller2));

struct __declspec(uuid("9AEA8A59-E0C9-40F1-87DD-757061D56177")) IIeAxiAdminInstaller : IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE  InitializeAdminInstaller(BSTR, BSTR, BSTR*) = 0;
};

_COM_SMARTPTR_TYPEDEF(IIeAxiAdminInstaller, __uuidof(IIeAxiAdminInstaller));

struct __declspec(uuid("A4AAAE00-22E5-4742-ABB7-379D9493A3B7")) IShdocvwBroker : IUnknown {
	// 0x102dcd60
	virtual HRESULT __stdcall RedirectUrl(const wchar_t *, unsigned long, struct _BROKER_REDIRECT_DETAIL *, struct IXMicTestMode *) = 0;
	// 0x102dcc20
	virtual HRESULT __stdcall RedirectShortcut(const wchar_t *, const wchar_t *, unsigned long, struct _BROKER_REDIRECT_DETAIL *) = 0;
	// 0x102dce90
	virtual HRESULT __stdcall RedirectUrlWithBindInfo(struct _BROKER_BIND_INFO *, struct _BROKER_REDIRECT_DETAIL *, struct IXMicTestMode *) = 0;
	// 0x102dbae0
	virtual HRESULT __stdcall NavigateUrlInNewTabInstance(struct _BROKER_BIND_INFO *, struct _BROKER_REDIRECT_DETAIL *) = 0;
	// 0x102e1d60
	virtual HRESULT __stdcall ShowInternetOptions(struct HWND__ *, const wchar_t *, const wchar_t *, long, struct _ITEMIDLIST_ABSOLUTE * *, unsigned long, int *) = 0;
	// 0x102e1e50
	virtual HRESULT __stdcall ShowInternetOptionsZones(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102e1e10
	virtual HRESULT __stdcall ShowInternetOptionsLanguages(struct HWND__ *) = 0;
	// 0x102e21b0
	virtual HRESULT __stdcall ShowPopupManager(struct HWND__ *, const wchar_t *) = 0;
	// 0x102e1bd0
	virtual HRESULT __stdcall ShowCachesAndDatabases(struct HWND__ *) = 0;
	// 0x102d7600
	virtual HRESULT __stdcall ConfigurePopupExemption(struct HWND__ *, int, const wchar_t *, int *) = 0;
	// 0x102d7660
	virtual HRESULT __stdcall ConfigurePopupMgr(struct HWND__ *, int) = 0;
	// 0x102dd530
	virtual HRESULT __stdcall RemoveFirstHomePage(void) = 0;
	// 0x102e1560
	virtual HRESULT __stdcall SetHomePage(struct HWND__ *, long, struct _ITEMIDLIST_ABSOLUTE * *, long) = 0;
	// 0x102dd5a0
	virtual HRESULT __stdcall RemoveHomePage(struct HWND__ *, int) = 0;
	// 0x102d8e40
	virtual HRESULT __stdcall FixInternetSecurity(struct HWND__ *, int *) = 0;
	// 0x102e1eb0
	virtual HRESULT __stdcall ShowManageAddons(struct HWND__ *, unsigned long, struct _GUID *, unsigned int, int) = 0;
	// 0x102d7000
	virtual HRESULT __stdcall CacheExtFileVersion(struct _GUID const &, const wchar_t *) = 0;
	// 0x102e1ac0
	virtual HRESULT __stdcall ShowAxApprovalDlg(struct HWND__ *, struct _GUID const &, int, const wchar_t *, const wchar_t *, const wchar_t *) = 0;
	// 0x102e10c0
	virtual HRESULT __stdcall SendLink(struct _ITEMIDLIST_ABSOLUTE const *, const wchar_t *) = 0;
	// 0x101e33c0
	virtual HRESULT __stdcall OnStopBinding(long, const wchar_t *) = 0;
	// 0x102e1100
	virtual HRESULT __stdcall SendPage(struct HWND__ *, struct IDataObject *) = 0;
	// 0x102dbd00
	virtual HRESULT __stdcall NewMessage(void) = 0;
	// 0x102dcbf0
	virtual HRESULT __stdcall ReadMail(struct HWND__ *) = 0;
	// 0x102e1230
	virtual HRESULT __stdcall SetAsBackground(const wchar_t *) = 0;
	// 0x102e2200
	virtual HRESULT __stdcall ShowSaveBrowseFile(struct HWND__ *, const wchar_t *, const wchar_t *, int, int, wchar_t * *, unsigned long *, unsigned long *) = 0;
	// 0x102e0a70
	virtual HRESULT __stdcall SaveAsComplete(void) = 0;
	// 0x102e0c20
	virtual HRESULT __stdcall SaveAsFile(void) = 0;
	// 0x102e2cb0
	virtual HRESULT __stdcall StartImportExportWizard(int, struct HWND__ *) = 0;
	// 0x102d8600
	virtual HRESULT __stdcall EditWith(struct HWND__ *, unsigned long, unsigned __int64, unsigned long, const wchar_t *, const wchar_t *, const wchar_t *) = 0;
	// 0x102e28b0
	virtual HRESULT __stdcall ShowSaveImage(struct HWND__ *, const wchar_t *, unsigned long, wchar_t * *) = 0;
	// 0x102e0ed0
	virtual HRESULT __stdcall SaveImage(const wchar_t *) = 0;
	// 0x102d77a0
	virtual HRESULT __stdcall CreateShortcutOnDesktop(struct _internet_shortcut_params *, struct HWND__ *, wchar_t *, int) = 0;
	// 0x102d8420
	virtual HRESULT __stdcall DownloadAndAddIcon(const wchar_t *, const wchar_t *, struct IOleCommandTarget *, unsigned long) = 0;
	// 0x102e2b50
	virtual HRESULT __stdcall ShowSynchronizeUI(void) = 0;
	// 0x102dbd70
	virtual HRESULT __stdcall OpenFolderAndSelectItem(const wchar_t *) = 0;
	// 0x101dbf90
	virtual HRESULT __stdcall RatingSetupUI(struct HWND__ *) = 0;
	// 0x102d8150
	virtual HRESULT __stdcall DoGetOpenFileNameDialog(struct _SOpenDlg *) = 0;
	// 0x102d8110
	virtual HRESULT __stdcall DoGetLocationPlatformConsent(struct HWND__ *, unsigned long *) = 0;
	// 0x102e26e0
	virtual HRESULT __stdcall ShowSaveFileName(struct HWND__ *, const wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, wchar_t *, unsigned long, const wchar_t *, wchar_t * *) = 0;
	// 0x102e0d10
	virtual HRESULT __stdcall SaveFile(struct HWND__ *, unsigned int, unsigned long) = 0;
	// 0x102e2fa0
	virtual HRESULT __stdcall VerifyTrustAndExecute(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102d97b0
	virtual HRESULT __stdcall GetFeedByUrl(const wchar_t *, wchar_t * *) = 0;
	// 0x102d61d0
	virtual HRESULT __stdcall BrokerAddToFavoritesEx(struct HWND__ *, struct _ITEMIDLIST_ABSOLUTE const *, const wchar_t *, unsigned long, struct IOleCommandTarget *, wchar_t *, unsigned long, const wchar_t *) = 0;
	// 0x102e2db0
	virtual HRESULT __stdcall Subscribe(struct HWND__ *, const wchar_t *, const wchar_t *, int, int, int) = 0;
	// 0x102db0e0
	virtual HRESULT __stdcall MarkAllItemsRead(const wchar_t *) = 0;
	// 0x102db320
	virtual HRESULT __stdcall MarkItemsRead(const wchar_t *, unsigned int *, unsigned int) = 0;
	// 0x102dc6a0
	virtual HRESULT __stdcall Properties(struct HWND__ *, const wchar_t *) = 0;
	// 0x102d7ec0
	virtual HRESULT __stdcall DeleteFeedItem(struct HWND__ *, const wchar_t *, unsigned int) = 0;
	// 0x102d7e80
	virtual HRESULT __stdcall DeleteFeed(struct HWND__ *, const wchar_t *) = 0;
	// 0x102d7f00
	virtual HRESULT __stdcall DeleteFolder(struct HWND__ *, const wchar_t *) = 0;
	// 0x102dd0e0
	virtual HRESULT __stdcall Refresh(const wchar_t *) = 0;
	// 0x102db3b0
	virtual HRESULT __stdcall MoveFeed(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102db440
	virtual HRESULT __stdcall MoveFeedFolder(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102dd5f0
	virtual HRESULT __stdcall RenameFeed(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102dd680
	virtual HRESULT __stdcall RenameFeedFolder(struct HWND__ *, const wchar_t *, const wchar_t *) = 0;
	// 0x102dbc80
	virtual HRESULT __stdcall NewFeedFolder(const wchar_t *) = 0;
	// 0x102d8dc0
	virtual HRESULT __stdcall FeedRefreshAll(void) = 0;
	// 0x102e1cd0
	virtual HRESULT __stdcall ShowFeedAuthDialog(struct HWND__ *, const wchar_t *, enum  tagFEEDTASKS_AUTHTYPE) = 0;
	// 0x102e1a00
	virtual HRESULT __stdcall ShowAddSearchProvider(struct HWND__ *, const wchar_t *, const wchar_t *, int) = 0;
	// 0x102d8360
	virtual HRESULT __stdcall DoShowDeleteBrowsingHistoryDialog(struct HWND__ *) = 0;
	// 0x102e2ca0
	virtual HRESULT __stdcall StartAutoProxyDetection(void) = 0;
	// 0x102d8530
	virtual HRESULT __stdcall EditAntiPhishingOptinSetting(struct HWND__ *, unsigned long, int *) = 0;
	// 0x102e1f10
	virtual HRESULT __stdcall ShowMyPictures(void) = 0;
	// 0x102d7310
	virtual HRESULT __stdcall ChangeIntranetSettings(struct HWND__ *, int) = 0;
	// 0x102d8e80
	virtual HRESULT __stdcall FixProtectedModeSettings(void) = 0;
	// 0x102e1a40
	virtual HRESULT __stdcall ShowAddService(struct HWND__ *, const wchar_t *, const wchar_t *, int) = 0;
	// 0x102e1a80
	virtual HRESULT __stdcall ShowAddWebFilter(struct HWND__ *, const wchar_t *, const wchar_t *, const wchar_t *) = 0;
	// 0x1012dd80
	virtual HRESULT __stdcall DoBrowserRegister(struct IDispatch *, long, int, long *) = 0;
	// 0x1012dc80
	virtual HRESULT __stdcall DoBrowserRevoke(long) = 0;
	// 0x1012db20
	virtual HRESULT __stdcall DoOnNavigate(long, struct tagVARIANT *) = 0;
	// 0x101d63c0
	virtual HRESULT __stdcall BrokerGetPersistentPolicyForUrl(const wchar_t *, int, int, unsigned long, unsigned long *, int *) = 0;
	// 0x102d8190
	virtual HRESULT __stdcall DoOnCreated(long, struct IUnknown *) = 0;
	// 0x102d9d50
	virtual HRESULT __stdcall GetShellWindows(struct IUnknown * *) = 0;
	// 0x101e30c0
	virtual HRESULT __stdcall TranslateUrl(unsigned long, wchar_t *, wchar_t * *) = 0;
	// 0x101dbf90
	virtual HRESULT __stdcall RatingSetupUIa(struct HWND__ *) = 0;
	// 0x102da800
	virtual HRESULT __stdcall IsProtectedModeUrl(const wchar_t *) = 0;
	// 0x102d80d0
	virtual HRESULT __stdcall DoDiagnoseConnectionProblems(struct HWND__ *, wchar_t *, wchar_t *) = 0;
	// 0x102dbda0
	virtual HRESULT __stdcall PerformDoDragDrop(struct HWND__ *, struct IEDataObjectWrapper *, struct IEDropSourceWrapper *, unsigned long, unsigned long, unsigned long *, long *) = 0;
	// 0x102e2e90
	virtual HRESULT __stdcall TurnOnFeedSyncEngine(struct HWND__ *) = 0;
	// 0x102da780
	virtual HRESULT __stdcall InternetSetPerSiteCookieDecisionW(const wchar_t *, unsigned long) = 0;
	// 0x101dfe20
	virtual HRESULT __stdcall put_StatusText(wchar_t *) = 0;
	// 0x102e3040
	virtual HRESULT __stdcall WriteClassesOfCategory(struct _GUID const &, int, int) = 0;
	// 0x102d6b20
	virtual HRESULT __stdcall BrokerSetFocus(unsigned long, struct HWND__ *) = 0;
	// 0x102d6ea0
	virtual HRESULT __stdcall BrokerShellNotifyIconA(unsigned long, struct _BROKER_NOTIFYICONDATAA *) = 0;
	// 0x102d6f40
	virtual HRESULT __stdcall BrokerShellNotifyIconW(unsigned long, struct _BROKER_NOTIFYICONDATAW *) = 0;
	// 0x102d7f90
	virtual HRESULT __stdcall DisplayVirtualizedFolder(void) = 0;
	// 0x102d6c70
	virtual HRESULT __stdcall BrokerSetWindowPos(struct HWND__ *, struct HWND__ *, int, int, int, int, unsigned int) = 0;
	// 0x102e30f0
	virtual HRESULT __stdcall WriteUntrustedControlDetails(struct _GUID const &, const wchar_t *, const wchar_t *, unsigned long, unsigned char *) = 0;
	// 0x102e1280
	virtual HRESULT __stdcall SetComponentDeclined(char const *, char const *) = 0;
	// 0x102d8390
	virtual HRESULT __stdcall DoShowPrintDialog(struct _BROKER_PRINTDLG *) = 0;
	// 0x102db4d0
	virtual HRESULT __stdcall NavigateHomePages(void) = 0;
	// 0x102e1b40
	virtual HRESULT __stdcall ShowAxDomainApprovalDlg(struct HWND__ *, struct _GUID const &, int, const wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *) = 0;
	// 0x102d5d70
	virtual HRESULT __stdcall ActivateExtensionFromCLSID(struct HWND__ *, const wchar_t *, unsigned long, unsigned int, unsigned int) = 0;
	// 0x102d6280
	virtual HRESULT __stdcall BrokerCoCreateNewIEWindow(unsigned long, struct _GUID const &, void * *, int, unsigned long, wchar_t *, int, long, long) = 0;
	// 0x1012df70
	virtual HRESULT __stdcall BeginFakeModalityForwardingToTab(struct HWND__ *, long) = 0;
	// 0x102d6660
	virtual HRESULT __stdcall BrokerEnableWindow(int, int *) = 0;
	// 0x102d8700
	virtual HRESULT __stdcall EndFakeModalityForwardingToTab(struct HWND__ *, long) = 0;
	// 0x102d7420
	virtual HRESULT __stdcall CloseOldTabIfFailed(void) = 0;
	// 0x102d86c0
	virtual HRESULT __stdcall EnableSuggestedSites(struct HWND__ *, int) = 0;
	// 0x102e1600
	virtual HRESULT __stdcall SetProgressValue(struct HWND__ *, unsigned long, unsigned long) = 0;
	// 0x102d6fe0
	virtual HRESULT __stdcall BrokerStartNewIESession(void) = 0;
	// 0x102d74c0
	virtual HRESULT __stdcall CompatDetachInputQueue(struct HWND__ *) = 0;
	// 0x102d7470
	virtual HRESULT __stdcall CompatAttachInputQueue(void) = 0;
	// 0x102e1700
	virtual HRESULT __stdcall SetToggleKeys(unsigned long) = 0;
	// 0x101e30c0
	virtual HRESULT __stdcall TranslateUrla(unsigned long, wchar_t *, wchar_t * *) = 0;
	// 0x102dd710
	virtual HRESULT __stdcall RepositionInfrontIE(struct HWND__ *, int, int, int, int, unsigned int) = 0;
	// 0x102e2160
	virtual HRESULT __stdcall ShowOpenSafeOpenDialog(struct HWND__ *, struct _BROKER_SAFEOPENDLGPARAM *, unsigned int *, unsigned int *) = 0;
	// 0x102d6160
	virtual HRESULT __stdcall BrokerAddSiteToStart(struct HWND__ *, wchar_t *, const wchar_t *, long, unsigned long) = 0;
	// 0x102e2bb0
	virtual HRESULT __stdcall SiteModeAddThumbnailButton(unsigned int *, struct HWND__ *, wchar_t *, const wchar_t *) = 0;
	// 0x102e2b80
	virtual HRESULT __stdcall SiteModeAddButtonStyle(int *, struct HWND__ *, unsigned int, wchar_t *, const wchar_t *) = 0;
	// 0x102da870
	virtual HRESULT __stdcall IsSiteModeFirstRun(int, wchar_t *) = 0;
	// 0x102d9b60
	virtual HRESULT __stdcall GetImmersivePinnedState(unsigned long, int, int *) = 0;
	// 0x102d63c0
	virtual HRESULT __stdcall BrokerDoSiteModeDragDrop(unsigned long, long *, unsigned long *) = 0;
	// 0x102d87d0
	virtual HRESULT __stdcall EnterUILock(long) = 0;
	// 0x102daa00
	virtual HRESULT __stdcall LeaveUILock(long) = 0;
	// 0x102d7b10
	virtual HRESULT __stdcall CredentialAdd(struct _IECREDENTIAL *) = 0;
	// 0x102d7be0
	virtual HRESULT __stdcall CredentialGet(const wchar_t *, const wchar_t *, struct _IECREDENTIAL * *) = 0;
	// 0x102d7b70
	virtual HRESULT __stdcall CredentialFindAllByUrl(const wchar_t *, unsigned long *, struct _IECREDENTIAL * *) = 0;
	// 0x102d7c50
	virtual HRESULT __stdcall CredentialRemove(const wchar_t *, const wchar_t *) = 0;
	// 0x102e1f20
	virtual HRESULT __stdcall ShowOpenFile(struct HWND__ *, unsigned long, unsigned long, wchar_t *, wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *, struct _OPEN_FILE_RESULT * *) = 0;
	// 0x102e1d10
	virtual HRESULT __stdcall ShowFileOpenPicker(int, const wchar_t *, struct IUnknown * *, struct _OPEN_FILE_RESULT * *) = 0;
	// 0x102e1d40
	virtual HRESULT __stdcall Freeze(unsigned long, long, void *, unsigned long *) = 0;
	// 0x102dd290
	virtual HRESULT __stdcall RegisterFileDragDrop(struct HWND__ *, unsigned long, unsigned char *) = 0;
	// 0x102dd870
	virtual HRESULT __stdcall RevokeFileDragDrop(struct HWND__ *) = 0;
	// 0x102d9960
	virtual HRESULT __stdcall GetFileTokensForDragDropA(struct HWND__ *, unsigned long, char * *, struct _OPEN_FILE_RESULT * *) = 0;
	// 0x102d9a40
	virtual HRESULT __stdcall GetFileTokensForDragDropW(struct HWND__ *, unsigned long, wchar_t * *, struct _OPEN_FILE_RESULT * *) = 0;
	// 0x102e1c10
	virtual HRESULT __stdcall ShowEPMCompatDocHostConsent(struct HWND__ *, const wchar_t *, const wchar_t *, int *) = 0;
	// 0x102d9c00
	virtual HRESULT __stdcall GetModuleInfoFromSignature(const wchar_t *, wchar_t * *, unsigned int, wchar_t * *, wchar_t * *, wchar_t * *) = 0;
	// 0x102e18e0
	virtual HRESULT __stdcall ShellExecWithActivationHandler(struct HWND__ *, const wchar_t *, const wchar_t *, unsigned long, enum  _MSLAUNCH_HANDLER_STATUS *) = 0;
	// 0x102e1810
	virtual HRESULT __stdcall ShellExecFolderUri(const wchar_t *) = 0;
	// 0x101e33c0
	virtual HRESULT __stdcall OnStopBindinga(long, const wchar_t *) = 0;
	// 0x101d63c0
	virtual HRESULT __stdcall BrokerGetPersistentPolicyForUrla(const wchar_t *, int, int, unsigned long, unsigned long *, int *) = 0;
	// 0x102d9880
	virtual HRESULT __stdcall GetFileHandle(struct HWND__ *, wchar_t *, unsigned char *, unsigned long, unsigned long *) = 0;
	// 0x102dab00
	virtual HRESULT __stdcall MOTWCreateFileW(unsigned long, const wchar_t *, unsigned long, unsigned long, unsigned long, unsigned long, unsigned __int64 *, unsigned long *) = 0;
	// 0x102dad10
	virtual HRESULT __stdcall MOTWFindFileW(unsigned long, unsigned long, const wchar_t *, struct _WIN32_FIND_DATAW *, unsigned __int64 *, unsigned long *) = 0;
	// 0x102dae60
	virtual HRESULT __stdcall MOTWGetFileDataW(unsigned long, const wchar_t *, unsigned long, unsigned long, wchar_t *, unsigned long *, unsigned long *, unsigned long *) = 0;
	// 0x101e33c0
	virtual HRESULT __stdcall OnStopBindingb(long, const wchar_t *) = 0;
	// 0x102d8300
	virtual HRESULT __stdcall DoProvisionNetworks(struct HWND__ *, const wchar_t *, unsigned int *) = 0;
	// 0x102d90b0
	virtual HRESULT __stdcall GetAccessibilityStylesheet(unsigned long, unsigned __int64 *) = 0;
	// 0x102d91e0
	virtual HRESULT __stdcall GetAppCacheUsage(const wchar_t *, unsigned __int64 *, unsigned __int64 *) = 0;
	// 0x102d9f20
	virtual HRESULT __stdcall HiddenTabRequest(struct _BROKER_BIND_INFO *, struct _BROKER_REDIRECT_DETAIL *, struct _HIDDENTAB_REQUEST_INFO *) = 0;
	// 0x102d9cd0
	virtual HRESULT __stdcall GetProofOfPossessionTokensForUrl(const wchar_t *, const wchar_t *, unsigned long *, struct _IEProofOfPossessionToken * *) = 0;
	// 0x1012daf0
	virtual HRESULT __stdcall GetLoginUrl(wchar_t * *) = 0;
	// 0x1012dad0
	virtual HRESULT __stdcall GetAadLoginUrl(wchar_t * *) = 0;
	// 0x102e0f60
	virtual HRESULT __stdcall ScheduleDeleteEncryptedMediaData(void) = 0;
	// 0x102da7d0
	virtual HRESULT __stdcall IsDeleteEncryptedMediaDataPending(int *) = 0;
	// 0x102d9b20
	virtual HRESULT __stdcall GetFrameAppDataPathA(char *, unsigned long) = 0;
	// 0x102d67f0
	virtual HRESULT __stdcall BrokerHandlePrivateNetworkFailure(struct tagSAFEARRAY *, const wchar_t *) = 0;
	// 0x102d9090
	virtual HRESULT __stdcall GenerateWebCryptoIEKey(unsigned int, unsigned char const *, unsigned int *, unsigned char * *) = 0;
	// 0x101dfb20
private: virtual long __stdcall msSiteModeShowButtonStyle(struct tagVARIANT, struct tagVARIANT) = 0;
		 // 0x101da5e0
		 virtual HRESULT __stdcall FireBeforeNavigate4(struct IHTMLWindow2 *, struct IDispatch *, struct IUri *, const wchar_t *, int, unsigned long, const wchar_t *, unsigned char *, unsigned long, const wchar_t *, int, int *) = 0;
		 // 0x1012d9d0
		 virtual HRESULT __stdcall IsVersionAllowed(const wchar_t *, const wchar_t *, const wchar_t *, int, wchar_t * *, wchar_t * *, int *, int *) = 0;
		 // 0x102da8f0
		 virtual HRESULT __stdcall LaunchIE(const wchar_t *, int) = 0;
		 // 0x102d7330
		 virtual HRESULT __stdcall ClearCache(unsigned long) = 0;
		 // 0x102e17a0
		 virtual HRESULT __stdcall SetUserInputId(struct _GUID) = 0;
		 // 0x101d63c0
		 virtual HRESULT __stdcall BrokerGetPersistentPolicyForUrlb(const wchar_t *, int, int, unsigned long, unsigned long *, int *) = 0;
		 // 0x104a6790
		 virtual HRESULT __stdcall Inverse(struct IMoniker * *) = 0;
		 // 0x102d96f0
		 virtual HRESULT __stdcall GetEDPHostPolicyForFile(const wchar_t *, wchar_t * *) = 0;
		 // 0x102d8570
		 virtual HRESULT __stdcall EditUriOnEMIEUserList(wchar_t *, int) = 0;
		 // 0x10263170

};

_COM_SMARTPTR_TYPEDEF(IIEUserBroker, __uuidof(IIEUserBroker));
_COM_SMARTPTR_TYPEDEF(IShdocvwBroker, __uuidof(IShdocvwBroker));


struct __declspec(uuid("A729AC6C-EE15-4599-99DE-A54AD734C950")) ITabWindowManager : IUnknown
{
};

struct __declspec(uuid("BFB070CE-95F2-4EDB-BAB5-4DAD9E6A2905")) ITabRecoveryData : IUnknown
{
public:

	virtual HRESULT STDMETHODCALLTYPE  GetTabId(_GUID *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetCurrentLocation(BSTR) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetCurrentLocation(unsigned short * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetCurrentTitle(BSTR) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetCurrentTitle(unsigned short**) = 0;;
	virtual HRESULT STDMETHODCALLTYPE  SetIsInPrivate(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFlags(unsigned long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Recovery(ITabWindowManager *, unsigned long, long, long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  RecoveryByPosition(ITabWindowManager *, long, unsigned long, long, long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteSelf(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Copy(ITabRecoveryData *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetStorage(IStorage * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetRecoveryTime(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetRecoveryCount(unsigned long) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetRecoveryCount(unsigned long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  ShouldRecover(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetCurrentGroup(long) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetCurrentGroup(long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetCurrentDecoration(long) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetCurrentDecoration(long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetLastVisibleTime(_FILETIME) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetLastVisibleTime(_FILETIME *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetTabImage(IStream *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetTabImage(IStream * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  FlushTabImage() = 0;
	virtual HRESULT STDMETHODCALLTYPE  Flush(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CloseStorage(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetIsIMPinnedSite(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetIsIMPinnedSite(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetHasLaunched(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetHasLaunched(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetIsHidden(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetNavigateCount(unsigned long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetReuseTabId() = 0;
	virtual HRESULT STDMETHODCALLTYPE  RemoveReuseTabId() = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetReuseTabId(unsigned short const *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetReadingModeData(IStream * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetReadingModeData() = 0;
	virtual HRESULT STDMETHODCALLTYPE  GeneratePartialTravelLogEntryForCurrentLocationIfNecessary(void const *, int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetShouldRecoverToHalfTab(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetShouldRecoverToHalfTab(int *) = 0;
};

struct __declspec(uuid("5C333B75-A015-4564-8BF3-998CCC4FF9F5")) IRecoveryStore : IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE  Initialize(DWORD dwProcessId, int, int, BSTR url) = 0;
	virtual HRESULT STDMETHODCALLTYPE  InitializeFromFile() = 0;
	virtual HRESULT STDMETHODCALLTYPE  CreateFrame(REFGUID, void*, void*) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CloseFrame() = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFrameCount(unsigned int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFrameId() = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFrameIESession(unsigned int, unsigned long *, unsigned long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetType(void *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CreateTab(_GUID const &, BSTR name, ITabRecoveryData * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CreateTabByPosition() = 0;
	virtual HRESULT STDMETHODCALLTYPE  AddTabEntry(_GUID const &, _GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CloseTab(_GUID const &, _GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  RemoveTabEntry(_GUID const &, _GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetTabCount(_GUID const &, unsigned int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetTab(_GUID const &, int, ITabRecoveryData * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetTabByGuid(_GUID const &, _GUID const &, ITabRecoveryData * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetOrderedTab(_GUID const &, unsigned int, ITabRecoveryData * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetOrderedTabPosition(_GUID const &, _GUID const &, unsigned int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetClosedTabCount(unsigned int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetClosedTab(_GUID const &, ITabRecoveryData * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteClosedTab(_GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Recover() = 0;
	virtual HRESULT STDMETHODCALLTYPE  RecoverSession(ITabWindowManager *, unsigned long) = 0;
	virtual HRESULT STDMETHODCALLTYPE  RecoverFrame(_GUID const &, ITabWindowManager *, unsigned long) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Flush(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteSelf() = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteAllTabs() = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteOnLastRelease(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Shutdown(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  Restart(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  IsShutdown(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetCompID(unsigned long *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  IsInPrivate(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  IsExtOff(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFrameCLSID(_GUID *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  UpdateFrameActivatedTime(_GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetActiveTab(_GUID const &, _GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetActiveTab(_GUID const &, _GUID *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SwitchTabFrame(_GUID const &, _GUID const &, _GUID const &) = 0;
	virtual HRESULT STDMETHODCALLTYPE  DeleteExistingStores(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetClearDataSessionFlag(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  FindAndInitializeCrashedSessions(int, int, int *, int *, int *, int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetIsSuspended(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  IsSuspended(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetHasPrivateTabs(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  HasPrivateTabs(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetSiteModeAppId() = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetSiteModeAppId(unsigned short * *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CleanUnusedSiteModeRecoveryData(int) = 0;
	virtual HRESULT STDMETHODCALLTYPE  HasCrashData(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  GetFrameLastActivatedTime(unsigned int, _FILETIME *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  CleanActiveRecoveryStores() = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetNoPrompt(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE  IsNoPrompt(int *) = 0;
	virtual HRESULT STDMETHODCALLTYPE  SetRecoveryPending(int) = 0;

};

_COM_SMARTPTR_TYPEDEF(IRecoveryStore, __uuidof(IRecoveryStore));
_COM_SMARTPTR_TYPEDEF(ITabRecoveryData, __uuidof(ITabRecoveryData));
