/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2009 FedICT.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.

**************************************************************************** */
#ifndef __GLOBMDRV__H__
#define __GLOBMDRV__H__

#include <cardmod.h>
#include <stdio.h>

//#include "Log.h"
//#include "util.h"
#include "stdafx.h"
#include "ListMgr.h"

#define CLEANUP(i)                        {dwReturn=(i);goto cleanup;}

#define MINIDRIVER_VERSION                "1.0.A"

#define ROLE_DIGSIG                       ROLE_USER
#define ROLE_NONREP                       3

#define SIGN_TYPE_NONREP		            1
#define SIGN_TYPE_DIGSIG		            2

#define FILE_OBJECT_DIRECTORY_TYPE        1
#define FILE_OBJECT_FILE_TYPE             2

#define MAX_CONTAINERS                    5

typedef struct _CARD_ATR
{
   BYTE     pbAtr[32];
   DWORD    cbAtr;
} CARD_ATR, *PCARD_ATR;

typedef struct _VIRTUAL_FILE_OBJECT
{
   BYTE                          szDirectoryName [8 + 1];
   BYTE                          szFileName      [8 + 1];
   BYTE                          bObjectType;
   BYTE                          bAccessCondition;
   LPVOID                        pObjectData;
   DWORD                         ObjectDataSize;

   struct _VIRTUAL_FILE_OBJECT   *pNext;
} VIRTUAL_FILE_OBJECT, *PVIRTUAL_FILE_OBJECT;


typedef struct _VFO_CONTAINER_INFO
{
   PIN_ID         dwPinId;
   CONTAINER_INFO ContainerInfo;
} VFO_CONTAINER_INFO, *PVFO_CONTAINER_INFO;

/************************************************************************************************************************/

typedef struct _OBJECT_LIST_TYPE
{
   item_type                     item_link_type;

   BYTE                          szDirectoryName [8 + 1];
   BYTE                          szFileName      [8 + 1];
   BYTE                          bObjectType;
   BYTE                          bAccessCondition;
   LPVOID                        pObjectData;
   DWORD                         ObjectDataSize;
} OBJECT_LIST_TYPE, *POBJECT_LIST_TYPE;

typedef struct _CARD_LIST_TYPE
{
   item_type               item_link_type;

   SCARDHANDLE             hScard;

   VFO_CONTAINER_INFO      ContainerInfo[MAX_CONTAINERS];
   PIN_INFO                PinInfo      [MAX_PINS];

   head_type               ObjectList;
} CARD_LIST_TYPE, *PCARD_LIST_TYPE;

typedef struct _CONTEXT_LIST_TYPE
{
   item_type               item_link_type;

   SCARDCONTEXT            hSCardCtx;

   head_type               CardList;

} CONTEXT_LIST_TYPE, *PCONTEXT_LIST_TYPE;

/************************************************************************************************************************/

#define BEID_READ_BINARY_MAX_LEN    128

#define CERT_AUTH                   1
#define CERT_NONREP                 2
#define CERT_CA                     3
#define CERT_ROOTCA                 4

#define HASH_ALGO_NONE              0
#define HASH_ALGO_MD2               1
#define HASH_ALGO_MD4               2
#define HASH_ALGO_MD5               3
#define HASH_ALGO_SHA1              4
#define HASH_ALGO_SHA_256           5
#define HASH_ALGO_SHA_384           6
#define HASH_ALGO_SHA_512           7

/************************************************************************************************************************/

#endif
