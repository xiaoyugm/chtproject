#pragma once
#include "AxLib.h"

using namespace dbAx;

class CAccountSetEvents :
    public CAxRecordsetEvents
{
public:

   //Here is our override of the RecordsetChangeComplete event
   STDMETHOD(RecordsetChangeComplete)( EventReasonEnum adReason,
                                       ADOError *pError,
                                       EventStatusEnum  *adStatus,
                                       _ADORecordset  *pRecordset)
   {
      AfxMessageBox(_T("Recordset changed"));
      return S_OK;
   }
};
