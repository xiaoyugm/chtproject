/**************************************************************************
    File: AxFeedE.hpp
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

class CAxFeedE :
    public CAxRecordset
{
public:
  CAxFeedE() { _SetDefaultValues(); }
  ~CAxFeedE() { }

  CString     m_szName,m_szecpointnum,m_szepointnum,m_szcpointnum,m_szUseridadd,m_szUseriddel;
  int  m_szEID;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel ;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName = m_szecpointnum =m_szcpointnum= m_szepointnum =m_szUseridadd =m_szUseriddel = _T("");
    m_szEID = 0;
	m_szfdel =false;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("EID"),        m_szEID);
    FX_VarChar           (bSave, _T("Name"),       m_szName);
    FX_VarChar           (bSave, _T("cpointnum"),       m_szcpointnum);
    FX_VarChar           (bSave, _T("epointnum"),           m_szepointnum);
    FX_VarChar           (bSave, _T("ecpointnum"),           m_szecpointnum);
    FX_Bool              (bSave, _T("fdel"),        m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
  };
};
