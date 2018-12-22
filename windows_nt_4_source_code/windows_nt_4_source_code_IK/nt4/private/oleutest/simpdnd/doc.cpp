//**********************************************************************
// File name: DOC.CPP
//
//      Implementation file for CSimpleDoc.
//
// Functions:
//
//      See DOC.H for Class Definition
//
// Copyright (c) 1992 - 1993 Microsoft Corporation. All rights reserved.
//**********************************************************************

#include "pre.h"
#include "iocs.h"
#include "ias.h"
#include "app.h"
#include "site.h"
#include "doc.h"
#include "idt.h"
#include "dxferobj.h"

//**********************************************************************
//
// CSimpleDoc::Create
//
// Purpose:
//
//      Creation for the CSimpleDoc Class
//
// Parameters:
//
//      CSimpleApp FAR * lpApp  -   Pointer to the CSimpleApp Class
//
//      LPRECT lpRect           -   Client area rect of "frame" window
//
//      HWND hWnd               -   Window Handle of "frame" window
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      StgCreateDocfile            OLE API
//      RegisterDragDrop            OLE API
//      CoLockObjectExternal        OLE API
//      CreateWindow                Windows API
//      ShowWindow                  Windows API
//      UpdateWindow                Windows API
//      EnableMenuItem              Windows API
//
// Comments:
//
//      This routine was added so that failure could be returned
//      from object creation.
//
//********************************************************************

CSimpleDoc FAR * CSimpleDoc::Create(CSimpleApp FAR *lpApp, LPRECT lpRect,
                                    HWND hWnd)
{
    CSimpleDoc FAR * lpTemp = new CSimpleDoc(lpApp, hWnd);

    if (!lpTemp)
    {
        TestDebugOut("Memory allocation error\n");
        return NULL;
    }

    // create storage for the doc.
    HRESULT hErr = StgCreateDocfile (
        NULL,       // generate temp name
        STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE,
        0, &lpTemp->m_lpStorage);

    if (hErr != NOERROR)
        goto error;

    // create the document Window
    lpTemp->m_hDocWnd = CreateWindow(
            TEXT("SimpDndDocWClass"),
            NULL,
            WS_CHILD | WS_CLIPCHILDREN,
            lpRect->left,
            lpRect->top,
            lpRect->right,
            lpRect->bottom,
            hWnd,
            NULL,
            lpApp->m_hInst,
            NULL);

    if (!lpTemp->m_hDocWnd)
        goto error;

    ShowWindow(lpTemp->m_hDocWnd, SW_SHOWNORMAL);  // Show the window
    UpdateWindow(lpTemp->m_hDocWnd);               // Sends WM_PAINT message

#ifdef NOTREADY
    // Ensable InsertObject menu choice
    EnableMenuItem( lpApp->m_hEditMenu, 0, MF_BYPOSITION | MF_ENABLED);
#else
    // Ensable InsertObject menu choice
    EnableMenuItem( lpApp->m_hEditMenu, 1, MF_BYPOSITION | MF_ENABLED);
    // Disable Copy menu choice
    EnableMenuItem( lpApp->m_hEditMenu, 0, MF_BYPOSITION | MF_DISABLED |
                                           MF_GRAYED);
#endif // NOTREADY

    HRESULT  hRes;

    // It is *REQUIRED* to hold a strong LOCK on the object that is
    // registered as drop target. this call will result in at least one
    // ref count held on our document. later in CSimpleDoc::Close we will
    // unlock this lock which will make our document's ref count go to 0.
    // when the document's ref count goes to 0, it will be deleted.
    if ( (hRes=CoLockObjectExternal (&lpTemp->m_DropTarget, TRUE, 0))
         != ResultFromScode(S_OK) )
    {
       /* CoLockObjectExternal should never fail. If it fails, we don't want
        * to carry on since we don't have a guaranteed object lock.
        */
       goto error;
    }

    // Register our window as a DropTarget
    if (((hRes=RegisterDragDrop(lpTemp->m_hDocWnd, &lpTemp->m_DropTarget))
          !=ResultFromScode(S_OK))
          && (hRes != ResultFromScode(DRAGDROP_E_ALREADYREGISTERED)))
    {
       lpTemp->m_fRegDragDrop = FALSE;
    }
    else
    {
       lpTemp->m_fRegDragDrop = TRUE;
    }

    return (lpTemp);

error:
    TestDebugOut("Fail in CSimpleDoc::Create\n");
    delete (lpTemp);
    return NULL;

}

//**********************************************************************
//
// CSimpleDoc::Close
//
// Purpose:
//
//      Close CSimpleDoc object.
//      when the document's reference count goes to 0, the document
//      will be destroyed.
//
// Parameters:
//
//      None
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      RevokeDragDrop              OLE API
//      CoLockObjectExternal        OLE API
//      OleFlushClipboard           OLE API
//      ShowWindow                  Windows API
//      CSimpleSite::CloseOleObject SITE.CPP
//
//
//********************************************************************

void CSimpleDoc::Close(void)
{
    TestDebugOut("In CSimpleDoc::Close\r\n");

    HRESULT hRes;

    ShowWindow(m_hDocWnd, SW_HIDE);  // Hide the window

    // Remove our data transfer object from clipboard if it is there.
    // this will leave HGLOBAL based data behind on the clipboard
    // including OLE 1.0 compatibility formats.

    if (OleFlushClipboard() != ResultFromScode(S_OK))
    {
       TestDebugOut("Fail in OleFlushClipBoard\n");
    }

    // Revoke our window as a DropTarget
    if (m_fRegDragDrop)
    {
        if (((hRes=RevokeDragDrop(m_hDocWnd)) != ResultFromScode(S_OK)) &&
             (hRes!=ResultFromScode(DRAGDROP_E_NOTREGISTERED)))
        {
           /* if we fail in revoking the drag-drop, we will probably be
            * having memory leakage.
            */
           TestDebugOut("Fail in RevokeDragDrop\n");
        }
        else
        {
           m_fRegDragDrop = FALSE;
        }
    }

    // Close the OLE object in our document
    if (m_lpSite)
        m_lpSite->CloseOleObject();

    // Unlock the lock added in CSimpleDoc::Create. this will make
    // the document's ref count go to 0, and the document will be deleted.
    if ((hRes=CoLockObjectExternal (&m_DropTarget, FALSE, TRUE))
        !=ResultFromScode(S_OK))
    {
        /* if CoLockObjectExternal fails, this means that we cannot release
         * the reference count to our destinated object. This will cause
         * memory leakage.
         */
        TestDebugOut("Fail in CoLockObjectExternal\n");
    }
}

//**********************************************************************
//
// CSimpleDoc::CSimpleDoc
//
// Purpose:
//
//      Constructor for the CSimpleDoc Class
//
// Parameters:
//
//      CSimpleApp FAR * lpApp  -   Pointer to the CSimpleApp Class
//
//      HWND hWnd               -   Window Handle of "frame" window
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      TestDebugOut           Windows API
//      GetMenu                     Windows API
//      GetSubMenu                  Windows API
//
//
//********************************************************************
#pragma warning(disable : 4355)  // turn off this warning.  This warning
                                 // tells us that we are passing this in
                                 // an initializer, before "this" is through
                                 // initializing.  This is ok, because
                                 // we just store the ptr in the other
                                 // constructor

CSimpleDoc::CSimpleDoc(CSimpleApp FAR * lpApp,HWND hWnd)
        : m_DropTarget(this), m_DropSource(this)
#pragma warning (default : 4355)  // Turn the warning back on
{
    TestDebugOut("In CSimpleDoc's Constructor\r\n");
    m_lpApp = lpApp;
    m_lpSite = NULL;
    m_nCount = 0;
    // set up menu handles
    lpApp->m_hMainMenu = GetMenu(hWnd);
    lpApp->m_hFileMenu = GetSubMenu(lpApp->m_hMainMenu, 0);
    lpApp->m_hEditMenu = GetSubMenu(lpApp->m_hMainMenu, 1);
    lpApp->m_hHelpMenu = GetSubMenu(lpApp->m_hMainMenu, 2);
    lpApp->m_hCascadeMenu = NULL;
    m_fModifiedMenu = FALSE;

    // drag/drop related stuff
    m_fRegDragDrop = FALSE;       // is doc registered as drop target?
    m_fLocalDrag = FALSE;         // is doc source of the drag
    m_fLocalDrop = FALSE;         // was doc target of the drop
    m_fCanDropCopy = FALSE;       // is Drag/Drop copy/move possible?
    m_fCanDropLink = FALSE;       // is Drag/Drop link possible?
    m_fDragLeave = FALSE;         // has drag left
    m_fPendingDrag = FALSE;       // LButtonDown--possible drag pending
    m_ptButDown.x = m_ptButDown.y = 0; // LButtonDown coordinates

}

//**********************************************************************
//
// CSimpleDoc::~CSimpleDoc
//
// Purpose:
//
//      Destructor for CSimpleDoc
//
// Parameters:
//
//      None
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                     Location
//
//      TestDebugOut            Windows API
//      GetMenuItemCount             Windows API
//      RemoveMenu                   Windows API
//      DestroyMenu                  Windows API
//      DestroyWindow                Windows API
//      CSimpleSite::Release         SITE.CPP
//      CSimpleSite::UnloadOleObject SITE.CPP
//      IStorage::Release            OLE API
//
//
//********************************************************************

CSimpleDoc::~CSimpleDoc()
{
    TestDebugOut("In CSimpleDoc's Destructor\r\n");

    // Release all pointers we hold to the OLE object, also release
    // the ref count added in CSimpleSite::Create. this will make
    // the Site's ref count go to 0, and the Site will be deleted.
    if (m_lpSite)
    {
        m_lpSite->UnloadOleObject();
        m_lpSite->Release();
        m_lpSite = NULL;
    }

    // Release the Storage
    if (m_lpStorage)
    {
        m_lpStorage->Release();
        m_lpStorage = NULL;
    }

    // if the edit menu was modified, remove the menu item and
    // destroy the popup if it exists
    if (m_fModifiedMenu)
    {
        int nCount = GetMenuItemCount(m_lpApp->m_hEditMenu);
        RemoveMenu(m_lpApp->m_hEditMenu, nCount-1, MF_BYPOSITION);
        if (m_lpApp->m_hCascadeMenu)
            DestroyMenu(m_lpApp->m_hCascadeMenu);
    }

    DestroyWindow(m_hDocWnd);
}


//**********************************************************************
//
// CSimpleDoc::QueryInterface
//
// Purpose:
//
//      Used for interface negotiation at the Document level.
//
// Parameters:
//
//      REFIID riid         -   ID of interface to be returned
//      LPVOID FAR* ppvObj  -   Location to return the interface
//
// Return Value:
//
//      S_OK                -   Interface supported
//      E_NOINTERFACE       -   Interface NOT supported
//
// Function Calls:
//      Function                    Location
//
//      TestDebugOut           Windows API
//      ResultFromScode             OLE API
//
//
//********************************************************************

STDMETHODIMP CSimpleDoc::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    TestDebugOut("In CSimpleDoc::QueryInterface\r\n");

    *ppvObj = NULL;     // must set out pointer parameters to NULL

    // looking for IUnknown
    if (IsEqualIID( riid, IID_IUnknown))
    {
        AddRef();
        *ppvObj = this;
        return ResultFromScode(S_OK);
    }

    // looking for IDropTarget
    if (IsEqualIID( riid, IID_IDropTarget))
    {
        m_DropTarget.AddRef();
        *ppvObj=&m_DropTarget;
        return ResultFromScode(S_OK);
    }

    // looking for IDropSource
    if (IsEqualIID( riid, IID_IDropSource))
    {
        m_DropSource.AddRef();
        *ppvObj=&m_DropSource;
        return ResultFromScode(S_OK);
    }

    // Not a supported interface
    return ResultFromScode(E_NOINTERFACE);
}

//**********************************************************************
//
// CSimpleDoc::AddRef
//
// Purpose:
//
//      Increments the document reference count
//
// Parameters:
//
//      None
//
// Return Value:
//
//      UINT    -   The new reference count on the document object
//
// Function Calls:
//      Function                    Location
//
//      TestDebugOut           Windows API
//      CSimpleApp::AddRef          APP.CPP
//
//
//********************************************************************

STDMETHODIMP_(ULONG) CSimpleDoc::AddRef()
{
    TestDebugOut("In CSimpleDoc::AddRef\r\n");
    return ++m_nCount;
}

//**********************************************************************
//
// CSimpleDoc::Release
//
// Purpose:
//
//      Decrements the document reference count
//
// Parameters:
//
//      None
//
// Return Value:
//
//      UINT    -   The new reference count on the document
//
// Function Calls:
//      Function                    Location
//
//      TestDebugOut           Windows API
//
//
//********************************************************************

STDMETHODIMP_(ULONG) CSimpleDoc::Release()
{
    TestDebugOut("In CSimpleDoc::Release\r\n");

    if (--m_nCount == 0)
    {
        delete this;
        return 0;
    }
    return m_nCount;
}

//**********************************************************************
//
// CSimpleDoc::InsertObject
//
// Purpose:
//
//      Inserts a new object to this document
//
// Parameters:
//
//      None
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      CSimpleSite::Create         SITE.CPP
//      CSimpleSite::InitObject     SITE.CPP
//      CSimpleSite::Release        SITE.CPP
//      CSimpleSite::Revert         SITE.CPP
//      memset                      C Runtime
//      OleUIInsertObject           OLE2UI function
//      CSimpleDoc::DisableInsertObject DOC.CPP
//
// Comments:
//
//      This implementation only allows one object to be inserted
//      into a document.  Once the object has been inserted, then
//      the Insert Object menu choice is greyed out, to prevent
//      the user from inserting another.
//
//********************************************************************

void CSimpleDoc::InsertObject()
{
    OLEUIINSERTOBJECT io;
    UINT iret;
    TCHAR szFile[OLEUI_CCHPATHMAX];

    HRESULT hRes;

    m_lpSite = CSimpleSite::Create(this);

    if (!m_lpSite)
    {
       /* memory allocation problem. cannot continue.
        */
       TestDebugOut("Memory allocation error\n");
       return;
    }

    // clear the structure
    _fmemset(&io, 0, sizeof(OLEUIINSERTOBJECT));

    // fill the structure
    io.cbStruct = sizeof(OLEUIINSERTOBJECT);
    io.dwFlags = IOF_SELECTCREATENEW      | IOF_DISABLELINK     |
                 IOF_DISABLEDISPLAYASICON | IOF_CREATENEWOBJECT |
                 IOF_CREATEFILEOBJECT;
    io.hWndOwner = m_hDocWnd;
    io.lpszCaption = (LPTSTR)TEXT("Insert Object");
    io.iid = IID_IOleObject;
    io.oleRender = OLERENDER_DRAW;
    io.lpIOleClientSite = &m_lpSite->m_OleClientSite;
    io.lpIStorage = m_lpSite->m_lpObjStorage;
    io.ppvObj = (LPVOID FAR *)&m_lpSite->m_lpOleObject;
    io.lpszFile = szFile;
    io.cchFile = sizeof(szFile)/sizeof(TCHAR);
                                      // cchFile is the number of characters
    _fmemset((LPTSTR)szFile, 0, sizeof(szFile));

    // call OUTLUI to do all the hard work
    iret = OleUIInsertObject(&io);

    if (iret == OLEUI_OK)
    {
        m_lpSite->InitObject((BOOL)(io.dwFlags & IOF_SELECTCREATENEW));
        // disable Insert Object menu item
        DisableInsertObject();
    }
    else
    {
        m_lpSite->Release();
        m_lpSite = NULL;
        if (((hRes=m_lpStorage->Revert()) != ResultFromScode(S_OK)) &&
             (hRes!=ResultFromScode(STG_E_REVERTED)))
        {
           TestDebugOut("Fail in IStorage::Revert\n");
        }
    }
}

//**********************************************************************
//
// CSimpleDoc::lResizeDoc
//
// Purpose:
//
//      Resizes the document
//
// Parameters:
//
//      LPRECT lpRect   -   The size of the client are of the "frame"
//                          Window.
//
// Return Value:
//
//      NULL
//
// Function Calls:
//      Function                                Location
//
//      MoveWindow                              Windows API
//
//
//********************************************************************

long CSimpleDoc::lResizeDoc(LPRECT lpRect)
{
    MoveWindow(
            m_hDocWnd,
            lpRect->left, lpRect->top,
            lpRect->right, lpRect->bottom, TRUE);

    return NULL;
}

//**********************************************************************
//
// CSimpleDoc::lAddVerbs
//
// Purpose:
//
//      Adds the objects verbs to the edit menu.
//
// Parameters:
//
//      None
//
// Return Value:
//
//      NULL
//
// Function Calls:
//      Function                    Location
//
//      GetMenuItemCount            Windows API
//      OleUIAddVerbMenu            OLE2UI function
//
//
//********************************************************************

long CSimpleDoc::lAddVerbs(void)
{
    // m_fModifiedMenu is TRUE if the menu has already been modified
    // once.  Since we only support one obect every time the application
    // is run, then once the menu is modified, it doesn't have
    // to be done again.
    if (m_lpSite && !m_fModifiedMenu)
    {
        int nCount = GetMenuItemCount(m_lpApp->m_hEditMenu);

        if (!OleUIAddVerbMenu ( m_lpSite->m_lpOleObject,
                           NULL,
                           m_lpApp->m_hEditMenu,
                           nCount + 1,
                           IDM_VERB0,
                           0,           // no maximum verb IDM enforced
                           FALSE,
                           1,
                           &m_lpApp->m_hCascadeMenu) )
        {
            TestDebugOut("Fail in OleUIAddVerbMenu\n");
        }

        m_fModifiedMenu = TRUE;
    }
    return (NULL);
}

//**********************************************************************
//
// CSimpleDoc::PaintDoc
//
// Purpose:
//
//      Paints the Document
//
// Parameters:
//
//      HDC hDC -   hDC of the document Window
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      CSimpleSite::PaintObj       SITE.CPP
//
//
//********************************************************************

void CSimpleDoc::PaintDoc (HDC hDC)
{
    // if we supported multiple objects, then we would enumerate
    // the objects and call paint on each of them from here.

    if (m_lpSite)
        m_lpSite->PaintObj(hDC);

}

//**********************************************************************
//
// CSimpleDoc::DisableInsertObject
//
// Purpose:
//
//      Disable the ability to insert a new object in this document.
//
// Parameters:
//
//      None
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      RevokeDragDrop              OLE API
//      EnableMenuItem              Windows API
//
// Comments:
//
//      This implementation only allows one object to be inserted
//      into a document.  Once the object has been inserted, then
//      the Insert Object menu choice is greyed out, to prevent
//      the user from inserting another. Also we revoke ourself as
//      a potential drop target.
//
//********************************************************************

void CSimpleDoc::DisableInsertObject(void)
{
#ifdef NOTREADY
    // Disable InsertObject menu choice
    EnableMenuItem( m_lpApp->m_hEditMenu, 0, MF_BYPOSITION | MF_DISABLED |
                                             MF_GRAYED);
#else
    // Disable InsertObject menu choice
    EnableMenuItem( m_lpApp->m_hEditMenu, 1, MF_BYPOSITION | MF_DISABLED |
                                             MF_GRAYED);
    // Enable Copy menu choice
    EnableMenuItem( m_lpApp->m_hEditMenu, 0, MF_BYPOSITION | MF_ENABLED);
#endif // NOTREADY

    // We no longer accept dropping of objects
    if (m_fRegDragDrop)
    {
        HRESULT hRes;
        if (((hRes=RevokeDragDrop(m_hDocWnd))!=ResultFromScode(S_OK)) &&
             (hRes!=ResultFromScode(DRAGDROP_E_NOTREGISTERED)))
        {
           /* if we fail in revoking the drag-drop, we will probably be
            * having memory leakage.
            */
           TestDebugOut("Fail in RevokeDragDrop\n");
        }
        else
        {
           m_fRegDragDrop = FALSE;
        }
    }
}

//**********************************************************************
//
// CSimpleDoc::CopyObjectToClip
//
// Purpose:
//
//      Copy the embedded OLE object to the clipboard
//
// Parameters:
//
//      None
//
// Return Value:
//
//      None
//
// Function Calls:
//      Function                    Location
//
//      CDataXferObj::Create        DXFEROBJ.CPP
//      CDataXferObj::Release       DXFEROBJ.CPP
//      CDataXferObj::QueryInterface DXFEROBJ.CPP
//      OleSetClipboard             OLE API
//
// Comments:
//
//      This implementation only allows one object to be inserted
//      into a document.  Once the object has been inserted, then
//      the Copy menu choice is enabled.
//
//********************************************************************

void CSimpleDoc::CopyObjectToClip(void)
{
    LPDATAOBJECT lpDataObj;

    // Create a data transfer object by cloning the existing OLE object
    CDataXferObj FAR* pDataXferObj = CDataXferObj::Create(m_lpSite,NULL);
    if (! pDataXferObj)
    {
        /* memory allocation error !
         */
        MessageBox(NULL, TEXT("Out-of-memory"), TEXT("SimpDnD"),
                   MB_SYSTEMMODAL | MB_ICONHAND);
        return;
    }
    // initially obj is created with 0 refcnt. this QI will make it go to 1.
    pDataXferObj->QueryInterface(IID_IDataObject, (LPVOID FAR*)&lpDataObj);

    // put out data transfer object on the clipboard. this API will AddRef.
    if (OleSetClipboard(lpDataObj) != ResultFromScode(S_OK))
    {
       TestDebugOut("Fail in OleSetClipboard\n");
       lpDataObj->Release();
    }

    // Give ownership of data transfer object to clipboard
    pDataXferObj->Release();
}
