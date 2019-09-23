/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 24 14:26:28 2007
 */
/* Compiler settings for D:\Scanner\Source\ScannerManagementSuite\Components\CommandRouter\CmdRouter\CmdRouter.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __CmdRouter_h__
#define __CmdRouter_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISblRouter_FWD_DEFINED__
#define __ISblRouter_FWD_DEFINED__
typedef interface ISblRouter ISblRouter;
#endif 	/* __ISblRouter_FWD_DEFINED__ */


#ifndef ___ISblRouterEvents_FWD_DEFINED__
#define ___ISblRouterEvents_FWD_DEFINED__
typedef interface _ISblRouterEvents _ISblRouterEvents;
#endif 	/* ___ISblRouterEvents_FWD_DEFINED__ */


#ifndef __SblRouter_FWD_DEFINED__
#define __SblRouter_FWD_DEFINED__

#ifdef __cplusplus
typedef class SblRouter SblRouter;
#else
typedef struct SblRouter SblRouter;
#endif /* __cplusplus */

#endif 	/* __SblRouter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISblRouter_INTERFACE_DEFINED__
#define __ISblRouter_INTERFACE_DEFINED__

/* interface ISblRouter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISblRouter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8A44E00-395B-4037-AD73-D98236431C2C")
    ISblRouter : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenDevice( 
            long reserved,
            BSTR logicalDeviceName,
            long __RPC_FAR *sHandle,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            long sHandle,
            long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterForEvents( 
            long sHandle,
            long eventsInterested,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnregisterEvents( 
            long sHandle,
            long eventsUnInterested,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllAttributes( 
            /* [in] */ long sHandle,
            /* [out] */ BSTR __RPC_FAR *attributes,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAttributes( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR attNumberList,
            /* [out] */ BSTR __RPC_FAR *attValueList,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextAttribute( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR startAtt,
            /* [out] */ BSTR __RPC_FAR *nextAtt,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAttributes( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR attributeSettings,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StoreAttributes( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR attributeSettings,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateAttribMetaFile( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR filePath,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateFirmware( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR filePath,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartNewFirmware( 
            /* [in] */ long sHandle,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecCommand( 
            /* [in] */ long sHandle,
            /* [in] */ long command,
            /* [in] */ BSTR inparam,
            /* [out] */ BSTR __RPC_FAR *outparam,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanEnable( 
            /* [in] */ long sHandle,
            /* [in] */ BOOL enableAll,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanDisable( 
            /* [in] */ long sHandle,
            /* [in] */ BOOL disableAll,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanReboot( 
            /* [in] */ long sHandle,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDeviceTopology( 
            /* [in] */ long sHandle,
            /* [out] */ BSTR __RPC_FAR *topoStruct,
            /* [out] */ long __RPC_FAR *status) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetupTunnel( 
            /* [in] */ long sHandle,
            /* [in] */ BSTR identity,
            /* [out] */ long __RPC_FAR *status) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISblRouterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISblRouter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISblRouter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISblRouter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDevice )( 
            ISblRouter __RPC_FAR * This,
            long reserved,
            BSTR logicalDeviceName,
            long __RPC_FAR *sHandle,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            ISblRouter __RPC_FAR * This,
            long sHandle,
            long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterForEvents )( 
            ISblRouter __RPC_FAR * This,
            long sHandle,
            long eventsInterested,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterEvents )( 
            ISblRouter __RPC_FAR * This,
            long sHandle,
            long eventsUnInterested,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllAttributes )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [out] */ BSTR __RPC_FAR *attributes,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR attNumberList,
            /* [out] */ BSTR __RPC_FAR *attValueList,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextAttribute )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR startAtt,
            /* [out] */ BSTR __RPC_FAR *nextAtt,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAttributes )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR attributeSettings,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StoreAttributes )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR attributeSettings,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateAttribMetaFile )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR filePath,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateFirmware )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR filePath,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartNewFirmware )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecCommand )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ long command,
            /* [in] */ BSTR inparam,
            /* [out] */ BSTR __RPC_FAR *outparam,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanEnable )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BOOL enableAll,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanDisable )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BOOL disableAll,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanReboot )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BOOL synchronous,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceTopology )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [out] */ BSTR __RPC_FAR *topoStruct,
            /* [out] */ long __RPC_FAR *status);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetupTunnel )( 
            ISblRouter __RPC_FAR * This,
            /* [in] */ long sHandle,
            /* [in] */ BSTR identity,
            /* [out] */ long __RPC_FAR *status);
        
        END_INTERFACE
    } ISblRouterVtbl;

    interface ISblRouter
    {
        CONST_VTBL struct ISblRouterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISblRouter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISblRouter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISblRouter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISblRouter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISblRouter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISblRouter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISblRouter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISblRouter_OpenDevice(This,reserved,logicalDeviceName,sHandle,status)	\
    (This)->lpVtbl -> OpenDevice(This,reserved,logicalDeviceName,sHandle,status)

#define ISblRouter_Close(This,sHandle,status)	\
    (This)->lpVtbl -> Close(This,sHandle,status)

#define ISblRouter_RegisterForEvents(This,sHandle,eventsInterested,status)	\
    (This)->lpVtbl -> RegisterForEvents(This,sHandle,eventsInterested,status)

#define ISblRouter_UnregisterEvents(This,sHandle,eventsUnInterested,status)	\
    (This)->lpVtbl -> UnregisterEvents(This,sHandle,eventsUnInterested,status)

#define ISblRouter_GetAllAttributes(This,sHandle,attributes,synchronous,status)	\
    (This)->lpVtbl -> GetAllAttributes(This,sHandle,attributes,synchronous,status)

#define ISblRouter_GetAttributes(This,sHandle,attNumberList,attValueList,synchronous,status)	\
    (This)->lpVtbl -> GetAttributes(This,sHandle,attNumberList,attValueList,synchronous,status)

#define ISblRouter_GetNextAttribute(This,sHandle,startAtt,nextAtt,synchronous,status)	\
    (This)->lpVtbl -> GetNextAttribute(This,sHandle,startAtt,nextAtt,synchronous,status)

#define ISblRouter_SetAttributes(This,sHandle,attributeSettings,synchronous,status)	\
    (This)->lpVtbl -> SetAttributes(This,sHandle,attributeSettings,synchronous,status)

#define ISblRouter_StoreAttributes(This,sHandle,attributeSettings,synchronous,status)	\
    (This)->lpVtbl -> StoreAttributes(This,sHandle,attributeSettings,synchronous,status)

#define ISblRouter_UpdateAttribMetaFile(This,sHandle,filePath,status)	\
    (This)->lpVtbl -> UpdateAttribMetaFile(This,sHandle,filePath,status)

#define ISblRouter_UpdateFirmware(This,sHandle,filePath,synchronous,status)	\
    (This)->lpVtbl -> UpdateFirmware(This,sHandle,filePath,synchronous,status)

#define ISblRouter_StartNewFirmware(This,sHandle,synchronous,status)	\
    (This)->lpVtbl -> StartNewFirmware(This,sHandle,synchronous,status)

#define ISblRouter_ExecCommand(This,sHandle,command,inparam,outparam,synchronous,status)	\
    (This)->lpVtbl -> ExecCommand(This,sHandle,command,inparam,outparam,synchronous,status)

#define ISblRouter_ScanEnable(This,sHandle,enableAll,status)	\
    (This)->lpVtbl -> ScanEnable(This,sHandle,enableAll,status)

#define ISblRouter_ScanDisable(This,sHandle,disableAll,status)	\
    (This)->lpVtbl -> ScanDisable(This,sHandle,disableAll,status)

#define ISblRouter_ScanReboot(This,sHandle,synchronous,status)	\
    (This)->lpVtbl -> ScanReboot(This,sHandle,synchronous,status)

#define ISblRouter_GetDeviceTopology(This,sHandle,topoStruct,status)	\
    (This)->lpVtbl -> GetDeviceTopology(This,sHandle,topoStruct,status)

#define ISblRouter_SetupTunnel(This,sHandle,identity,status)	\
    (This)->lpVtbl -> SetupTunnel(This,sHandle,identity,status)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_OpenDevice_Proxy( 
    ISblRouter __RPC_FAR * This,
    long reserved,
    BSTR logicalDeviceName,
    long __RPC_FAR *sHandle,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_OpenDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_Close_Proxy( 
    ISblRouter __RPC_FAR * This,
    long sHandle,
    long __RPC_FAR *status);


void __RPC_STUB ISblRouter_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_RegisterForEvents_Proxy( 
    ISblRouter __RPC_FAR * This,
    long sHandle,
    long eventsInterested,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_RegisterForEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_UnregisterEvents_Proxy( 
    ISblRouter __RPC_FAR * This,
    long sHandle,
    long eventsUnInterested,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_UnregisterEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_GetAllAttributes_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [out] */ BSTR __RPC_FAR *attributes,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_GetAllAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_GetAttributes_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR attNumberList,
    /* [out] */ BSTR __RPC_FAR *attValueList,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_GetNextAttribute_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR startAtt,
    /* [out] */ BSTR __RPC_FAR *nextAtt,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_GetNextAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_SetAttributes_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR attributeSettings,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_SetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_StoreAttributes_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR attributeSettings,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_StoreAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_UpdateAttribMetaFile_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR filePath,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_UpdateAttribMetaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_UpdateFirmware_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR filePath,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_UpdateFirmware_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_StartNewFirmware_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_StartNewFirmware_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_ExecCommand_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ long command,
    /* [in] */ BSTR inparam,
    /* [out] */ BSTR __RPC_FAR *outparam,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_ExecCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_ScanEnable_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BOOL enableAll,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_ScanEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_ScanDisable_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BOOL disableAll,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_ScanDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_ScanReboot_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BOOL synchronous,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_ScanReboot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_GetDeviceTopology_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [out] */ BSTR __RPC_FAR *topoStruct,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_GetDeviceTopology_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISblRouter_SetupTunnel_Proxy( 
    ISblRouter __RPC_FAR * This,
    /* [in] */ long sHandle,
    /* [in] */ BSTR identity,
    /* [out] */ long __RPC_FAR *status);


void __RPC_STUB ISblRouter_SetupTunnel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISblRouter_INTERFACE_DEFINED__ */



#ifndef __CMDROUTERLib_LIBRARY_DEFINED__
#define __CMDROUTERLib_LIBRARY_DEFINED__

/* library CMDROUTERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CMDROUTERLib;

#ifndef ___ISblRouterEvents_DISPINTERFACE_DEFINED__
#define ___ISblRouterEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISblRouterEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISblRouterEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B0DDE032-C39F-4D1A-A9D1-EC1DBB197A94")
    _ISblRouterEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISblRouterEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ISblRouterEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ISblRouterEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ISblRouterEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ISblRouterEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ISblRouterEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ISblRouterEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ISblRouterEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ISblRouterEventsVtbl;

    interface _ISblRouterEvents
    {
        CONST_VTBL struct _ISblRouterEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISblRouterEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISblRouterEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISblRouterEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISblRouterEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISblRouterEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISblRouterEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISblRouterEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISblRouterEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SblRouter;

#ifdef __cplusplus

class DECLSPEC_UUID("1E028705-30F3-4644-B42D-6999BCD2A257")
SblRouter;
#endif
#endif /* __CMDROUTERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
