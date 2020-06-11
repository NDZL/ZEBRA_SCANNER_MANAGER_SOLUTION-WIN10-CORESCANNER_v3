/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 24 14:26:28 2007
 */
/* Compiler settings for D:\Scanner\Source\ScannerManagementSuite\Components\CommandRouter\CmdRouter\CmdRouter.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISblRouter = {0xF8A44E00,0x395B,0x4037,{0xAD,0x73,0xD9,0x82,0x36,0x43,0x1C,0x2C}};

const IID LIBID_CMDROUTERLib = {0xB25FED99,0xBCB6,0x457F,{0xAB,0x03,0x0B,0x5F,0xF3,0x47,0xED,0x13}};

const IID DIID__ISblRouterEvents = {0xB0DDE032,0xC39F,0x4D1A,{0xA9,0xD1,0xEC,0x1D,0xBB,0x19,0x7A,0x94}};

//CLSID "{0x1E028705,.." ONLY REGISTERED WITH  “OPOS_MS_1.05.10.exe” - N.DZL 11-JUNE-2020
const CLSID CLSID_SblRouter = {0x1E028705,0x30F3,0x4644,{0xB4,0x2D,0x69,0x99,0xBC,0xD2,0xA2,0x57}};


#ifdef __cplusplus
}
#endif

