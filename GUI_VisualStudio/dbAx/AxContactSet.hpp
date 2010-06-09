/**************************************************************************
    File: AxContactSet.hpp
    Date: 10/21/2007
      By: Data Management Systems (www.dmsic.com)

    DESCRIPTION
    The following source code was generated using the AxGen utility and is
    intended to be used in conjunction with the dbAx library. This class
    facilitates the exchange of data with the ADO data source from which
    it was derived.

    Table: (local)\CardFile\Contact

    Include this file in your project.

    DISCLAIMER
    This source code is provided AS-IS with no warranty as to its
    suitability or usefulness in any application in which it may be used.
**************************************************************************/

#pragma once
#include "AxLib.h"

using namespace dbAx;

class CAxContactSet :
    public CAxRecordset
{
public:
  CAxContactSet() { _SetDefaultValues(); }
  ~CAxContactSet() { }

  CString     m_szName,m_szfalm,m_szUseridadd,m_szUseriddel,m_szpunit;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel;
  int m_szAID,m_szpico;
  REAL m_szltop,m_szlbom,m_szpalmu,m_szpalmd,m_szpbrk,m_szprtn;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName =m_szpunit =m_szfalm=m_szUseridadd=m_szUseriddel= _T("");
    m_szAID =m_szpico =m_szltop= m_szlbom= m_szpalmu=m_szpalmd=m_szpbrk= m_szprtn = 0;
	m_szfdel = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("AID"),  m_szAID);
    FX_VarChar           (bSave, _T("Name"),  m_szName);
    FX_Real           (bSave, _T("ltop"),       m_szltop);
    FX_Real           (bSave, _T("lbom"),    m_szlbom);
    FX_Real           (bSave, _T("palmu"),     m_szpalmu);
    FX_Real           (bSave, _T("palmd"),     m_szpalmd);
    FX_VarChar           (bSave, _T("punit"),      m_szpunit);
    FX_VarChar              (bSave, _T("falm"),       m_szfalm);
    FX_Bool              (bSave, _T("fdel"),  m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
    FX_Real           (bSave, _T("pbrk"),     m_szpbrk);
    FX_Real           (bSave, _T("prtn"),     m_szprtn);
    FX_Integer           (bSave, _T("pico"),  m_szpico);
  };
};
