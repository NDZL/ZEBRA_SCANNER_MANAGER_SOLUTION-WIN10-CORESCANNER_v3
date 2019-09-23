/*******************************************************************************
* FILENAME:  RouterDefn.h
*
* © 2005-2007 Symbol Technologies, Inc., A Motorola Company. All Rights Reserved.
*
* DESCRIPTION:  
*
* 
********************************************************************************/

#ifndef __ROUTERDEFN_H
#define __ROUTERDEFN_H


//Event Types  
const short SCANNER_DEVICE_FOUND	   = 4;
const short SCANNER_DEVICE_LOST		= 5;
const short SCANNER_UF_SESS_START	= 6;
const short SCANNER_UF_DL_START		= 7;
const short SCANNER_UF_DL_PROGRESS	= 8;
const short SCANNER_UF_DL_END		   = 9;
const short SCANNER_UF_SESS_END		= 10;
const short SCANNER_DECODE_GOOD		= 11;
const short SCANNER_DECODE_FAILURE	= 12;
const short SCANNER_GENERAL_ERROR	= 50;


//Event Ccategories
const short SCAN_DATA_EVENT			= 1;
const short SCAN_CMDRESPONSE_EVENT	= 2;
const short SCAN_RMD_EVENT			   = 3;

//Bit values used in Registering for events
const short ENABLE_DATA_EVENT			= 1;
const short ENABLE_RESPONSE_EVENT	= 2;
const short ENABLE_RMD_EVENT			= 4;


//Command status values
const short SR_S_CMD_SUCCESSFUL		= 0;

const short SR_E_NO_CONNECTION		=  -1;
const short SR_E_RMDINIT_ERROR		=  -2; // Initialization error RMDTrans Init() failed

const short SR_E_DIFF_CONNECTION	   = 101;
const short SR_E_OPEN_CONNECTION	   = 102;
const short SR_E_HANDLE_INVALID		= 103;
const short SR_E_CONN_ALREADY_OPEN	= 104;
const short SR_E_INVALID_DEVICE		= 105;
const short SR_E_INVALID_FILEPATH	= 106;
const short SR_E_MGMT_FAILURE		   = 107;
const short SR_E_UPLOAD_FAILURE		= 108;
const short SR_E_FWUPDATE_FAILURE   = 108; // SR_E_UPLOAD_FAILURE
const short SR_E_FILE_CHECKSUM		= 109;
const short SR_E_FIRMWARE_RESIDENT	= 110;
const short SR_E_FIRMWARE_UNKNOWN	= 111;
const short SR_E_TUNNEL_FAILURE		= 112;
const short SR_E_TUNNEL_EMPTY		   = 113;
const short SR_E_INVALID_PARAMETER	= 114;  
const short SR_E_SERVER_BUSY		   = 115;
const short SR_E_SCHEMA_NOTFOUND	   = 116;
const short SR_E_INVALID_METAFILE	= 117;
const short SR_E_DOWNLOAD_UNDERWAY  = 118;
const short SR_E_UNKNOWN_COMMAND    = 119;
const short SR_E_NO_PACKETSIZE      = 120;



#endif 