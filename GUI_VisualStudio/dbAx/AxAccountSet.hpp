/**************************************************************************
    File: AxAccountSet.hpp
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
#include "dbAx\AxLib.h"

using namespace dbAx;

class CAxAccountSet :
    public CAxRecordset
{
public:
  CAxAccountSet() { _SetDefaultValues(); }
  ~CAxAccountSet() { }

  CString     m_szAccountID;
  CString     m_szName;
  CString     m_szAddress;
  CString     m_szPhone1;
  CString     m_szPhone2;
  CString     m_szEmail;
  CString     m_szNote;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szAccountID  = _T("");
    m_szName       = _T("");
    m_szAddress    = _T("");
    m_szPhone1     = _T("");
    m_szPhone2     = _T("");
    m_szEmail      = _T("");
    m_szNote       = _T("");
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_VarChar           (bSave, _T("AccountID"),  m_szAccountID);
    FX_VarChar           (bSave, _T("Name"),       m_szName);
    FX_Text              (bSave, _T("Address"),    m_szAddress);
    FX_VarChar           (bSave, _T("Phone1"),     m_szPhone1);
    FX_VarChar           (bSave, _T("Phone2"),     m_szPhone2);
    FX_VarChar           (bSave, _T("Email"),      m_szEmail);
    FX_Text              (bSave, _T("Note"),       m_szNote);
  };
};
