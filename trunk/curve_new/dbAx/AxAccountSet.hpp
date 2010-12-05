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
#include "AxLib.h"

using namespace dbAx;

class CAxAccountSet :
    public CAxRecordset
{
public:
  CAxAccountSet() { _SetDefaultValues(); }
  ~CAxAccountSet() { }

  CString     m_szName,m_szname0,m_szname1,m_szname2,m_szfalm,m_szUseridadd,m_szUseriddel;
  int  m_szDID,   m_szpalms,m_szptype;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel ;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName =m_szname0 =m_szname1 =m_szname2 =m_szfalm =m_szUseridadd =m_szUseriddel = _T("");
    m_szDID  =m_szptype =m_szpalms   = 0;
	m_szfdel =false;
//    m_szrecdate    = _T("");
//    m_szdeldate     = _T("");
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("DID"),  m_szDID);
    FX_VarChar           (bSave, _T("Name"),  m_szName);
    FX_Integer           (bSave, _T("ptype"),       m_szptype);
    FX_VarChar              (bSave, _T("name0"),    m_szname0);
    FX_VarChar           (bSave, _T("name1"),     m_szname1);
    FX_VarChar           (bSave, _T("name2"),     m_szname2);
    FX_Integer           (bSave, _T("palms"),      m_szpalms);
    FX_VarChar              (bSave, _T("falm"),       m_szfalm);
    FX_Bool              (bSave, _T("fdel"),  m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
  };
};
