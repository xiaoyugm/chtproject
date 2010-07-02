/**************************************************************************
    File: AxSControl.hpp
    Date: 11/22/2007
      By: Data Management Systems (www.dmsic.com)

    DESCRIPTION
    The following source code was generated using the AxGen utility and is
    intended to be used in conjunction with the dbAx library. This class
    facilitates the exchange of data with the ADO data source from which
    it was derived.

    Table: (local)\CardFile\ACCOUNT

    Include this file in your project.

    DISCLAIMER
    This source code is provided AS-IS with no warranty as to its
    suitability or usefulness in any application in which it may be used.
**************************************************************************/

#pragma once
#include "AxLib.h"

using namespace dbAx;

class CAxSControl :
    public CAxRecordset
{
public:
  CAxSControl() { _SetDefaultValues(); }
  ~CAxSControl() { }

  bool     m_szSpeCtrol,m_szIsScan;
  int  m_szSID ;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szSID =m_szSpeCtrol = m_szIsScan = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("SID"),        m_szSID);
    FX_Bool           (bSave, _T("SpeCtrol"),       m_szSpeCtrol);
    FX_Bool           (bSave, _T("IsScan"),       m_szIsScan);
  };
};
