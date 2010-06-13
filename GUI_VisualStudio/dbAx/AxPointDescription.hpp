/**************************************************************************
    File: AxPointDescription.hpp
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

class CAxPointDescription :
    public CAxRecordset
{
public:
  CAxPointDescription() { _SetDefaultValues(); }
  ~CAxPointDescription() { }

  CString     m_szName,m_szpointnum,m_szutype,m_szUseridadd,m_szUseriddel;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel,m_szsubOpr;
  int m_szPID,m_szptype,m_sztypeID,m_szpositionid,m_szfds,m_szchan;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName=m_szpointnum  =m_szutype=m_szUseridadd=m_szUseriddel= _T("");
    m_szPID =m_szptype =m_sztypeID= m_szpositionid= m_szfds=m_szchan=  0;
	m_szfdel =m_szsubOpr = false;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("PID"),  m_szPID);
    FX_VarChar           (bSave, _T("Name"),  m_szName);
    FX_VarChar           (bSave, _T("pointnum"),  m_szpointnum);
    FX_Integer           (bSave, _T("ptype"),       m_szptype);
    FX_VarChar           (bSave, _T("utype"),    m_szutype);
    FX_Integer           (bSave, _T("typeID"),     m_sztypeID);
    FX_Integer           (bSave, _T("positionid"),     m_szpositionid);
    FX_Integer           (bSave, _T("fds"),      m_szfds);
    FX_Integer              (bSave, _T("chan"),       m_szchan);
    FX_Bool              (bSave, _T("subOpr"),     m_szsubOpr);
    FX_Bool              (bSave, _T("fdel"),  m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
  };
};
