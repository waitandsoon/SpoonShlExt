

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Sep 25 01:05:53 2013
 */
/* Compiler settings for SpookShlExt.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SpookShlExt_i_h__
#define __SpookShlExt_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISpookShlExt_FWD_DEFINED__
#define __ISpookShlExt_FWD_DEFINED__
typedef interface ISpookShlExt ISpookShlExt;
#endif 	/* __ISpookShlExt_FWD_DEFINED__ */


#ifndef __SpookShlExt_FWD_DEFINED__
#define __SpookShlExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class SpookShlExt SpookShlExt;
#else
typedef struct SpookShlExt SpookShlExt;
#endif /* __cplusplus */

#endif 	/* __SpookShlExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISpookShlExt_INTERFACE_DEFINED__
#define __ISpookShlExt_INTERFACE_DEFINED__

/* interface ISpookShlExt */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISpookShlExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E089A475-2A3C-4AFB-B238-9E1AAA8509AE")
    ISpookShlExt : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TestMethod( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpookShlExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpookShlExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpookShlExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpookShlExt * This);
        
        HRESULT ( STDMETHODCALLTYPE *TestMethod )( 
            ISpookShlExt * This);
        
        END_INTERFACE
    } ISpookShlExtVtbl;

    interface ISpookShlExt
    {
        CONST_VTBL struct ISpookShlExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpookShlExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpookShlExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpookShlExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpookShlExt_TestMethod(This)	\
    ( (This)->lpVtbl -> TestMethod(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpookShlExt_INTERFACE_DEFINED__ */



#ifndef __SpookShlExtLib_LIBRARY_DEFINED__
#define __SpookShlExtLib_LIBRARY_DEFINED__

/* library SpookShlExtLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SpookShlExtLib;

EXTERN_C const CLSID CLSID_SpookShlExt;

#ifdef __cplusplus

class DECLSPEC_UUID("DFA87FB0-45C6-48C5-896E-591DF0CAEDB7")
SpookShlExt;
#endif
#endif /* __SpookShlExtLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


