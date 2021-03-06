/***********************************************************************
 *
 *  Copyright (c) 2013  Broadcom Corporation
 *  All Rights Reserved
 *
<:label-BRCM:2013:proprietary:standard

 This program is the proprietary software of Broadcom and/or its
 licensors, and may only be used, duplicated, modified or distributed pursuant
 to the terms and conditions of a separate, written license agreement executed
 between you and Broadcom (an "Authorized License").  Except as set forth in
 an Authorized License, Broadcom grants no license (express or implied), right
 to use, or waiver of any kind with respect to the Software, and Broadcom
 expressly reserves all rights in and to the Software and all intellectual
 property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
 NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
 BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.

 Except as expressly set forth in the Authorized License,

 1. This program, including its structure, sequence and organization,
    constitutes the valuable trade secrets of Broadcom, and you shall use
    all reasonable efforts to protect the confidentiality thereof, and to
    use this information only in connection with your use of Broadcom
    integrated circuit products.

 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
    PERFORMANCE OF THE SOFTWARE.

 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
    LIMITED REMEDY.
:>
 *
 ************************************************************************/

#include "cms.h"
#include "cms_util.h"
#include "mdm.h"
#include "mdm_private.h"

/*
 * This file contains functions related to multiple data model support.
 */

extern void mdm_getPtrs_oidInfoArray_igd(const MdmOidInfoEntry **begin, const MdmOidInfoEntry **end);
extern void mdm_getPtrs_oidInfoArray_dev2(const MdmOidInfoEntry **begin, const MdmOidInfoEntry **end);

void mdm_getOidInfoPtrs(const MdmOidInfoEntry **begin, const MdmOidInfoEntry **end)
{
#if defined(SUPPORT_DM_LEGACY98)
   return (mdm_getPtrs_oidInfoArray_igd(begin, end));
#elif defined(SUPPORT_DM_HYBRID)
   return (mdm_getPtrs_oidInfoArray_igd(begin, end));
#elif defined(SUPPORT_DM_PURE181)
   return (mdm_getPtrs_oidInfoArray_dev2(begin, end));
#elif defined(SUPPORT_DM_DETECT)
   if (cmsMdm_isDataModelDevice2())
      return (mdm_getPtrs_oidInfoArray_dev2(begin, end));
   else
      return (mdm_getPtrs_oidInfoArray_igd(begin, end));
#endif
}

const MdmOidInfoEntry *cmsMdm_getAllOidInfoEntries(UINT32 *numEntries)
{
   const MdmOidInfoEntry *begin=NULL;
   const MdmOidInfoEntry *end=NULL;
   
   mdm_getOidInfoPtrs(&begin, &end);
   // end points to the beginning of the last entry.  Need to increment to
   // make the pointer arithmetic work.
   end++;
   *numEntries = end - begin;
   return begin;
}

const MdmOidInfoEntry *cmsMdm_getOidInfoEntry(UINT16 oid)
{
   return mdm_getOidInfo(oid);
}
