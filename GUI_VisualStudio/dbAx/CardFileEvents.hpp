
#pragma once
#include "AxLib.h"

using namespace dbAx;

class CCardFileEvents :
    public CAxConnectionEvents
{
public:

    STDMETHOD(ConnectComplete)(ADOError * pError,
               EventStatusEnum * adStatus,
               _ADOConnection * pConnection)
      {
        AfxMessageBox(_T("����BJygjl���ݿ�"));
//        AfxMessageBox(_T("Connected to BJygjl"));
        return S_OK;
      }
};
