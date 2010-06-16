/**************************************************************************
    File: AxControl.hpp
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

class CAxControl :
    public CAxRecordset
{
public:
  CAxControl() { _SetDefaultValues(); }
  ~CAxControl() { }

  CString     m_szName,m_szpointnum,m_szcpointnum,m_szUseridadd,m_szUseriddel;
  int  m_szCID,   m_szPID,m_szcPID;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel,m_szByFds ;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName =m_szpointnum =m_szcpointnum= m_szUseridadd =m_szUseriddel = _T("");
    m_szCID  =m_szPID =m_szcPID   = 0;
	m_szfdel = m_szByFds =false;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("CID"),        m_szCID);
    FX_VarChar           (bSave, _T("Name"),       m_szName);
    FX_VarChar           (bSave, _T("pointnum"),       m_szpointnum);
    FX_Integer           (bSave, _T("PID"),       m_szPID);
    FX_VarChar           (bSave, _T("cpointnum"),           m_szcpointnum);
    FX_Integer              (bSave, _T("cPID"),       m_szcPID);
    FX_Bool              (bSave, _T("ByFds"),       m_szByFds);
    FX_Bool              (bSave, _T("fdel"),        m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
  };
};
