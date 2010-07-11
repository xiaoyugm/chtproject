/**************************************************************************
    File: AxLogin.hpp
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

class CAxLogin :
    public CAxRecordset
{
public:
  CAxLogin() { _SetDefaultValues(); }
  ~CAxLogin() { }

  CString     m_szName,m_szupwd;
  int  m_szUID,   m_szclasser;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName =m_szupwd = _T("");
    m_szUID  =m_szclasser = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("UID"),        m_szUID);
    FX_VarChar           (bSave, _T("Name"),       m_szName);
    FX_VarChar           (bSave, _T("upwd"),       m_szupwd);
    FX_Integer           (bSave, _T("classer"),       m_szclasser);
  };
};
