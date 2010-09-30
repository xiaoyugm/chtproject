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

  CString     m_szName,m_szpointnum,m_szcpointnum,m_szpcpointnum,m_szUseridadd,m_szUseriddel;
  int  m_szCID,   m_szPID,m_szcPID;
  COleDateTime   m_szrecdate,m_szdeldate;
  bool m_szfdel,m_szByFds ;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName =m_szpointnum =m_szcpointnum= m_szpcpointnum =m_szUseridadd =m_szUseriddel = _T("");
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
    FX_VarChar           (bSave, _T("pcpointnum"),           m_szpcpointnum);
    FX_Bool              (bSave, _T("fdel"),        m_szfdel);
    FX_DateTime           (bSave, _T("recdate"),       m_szrecdate);
    FX_DateTime              (bSave, _T("deldate"),    m_szdeldate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_VarChar           (bSave, _T("Useriddel"),     m_szUseriddel);
  };
};

class CAxFans :
    public CAxRecordset
{
public:
  CAxFans() { _SetDefaultValues(); }
  ~CAxFans() { }

  CString     m_szName1,m_szName2,m_szpointnum1,m_szpointnum2;
  int m_szFansID,m_szAStatus;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName1 =m_szName2 =m_szpointnum1= m_szpointnum2 = _T("");
    m_szFansID = m_szAStatus =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("FansID"),         m_szFansID);
    FX_VarChar           (bSave, _T("Name1"),          m_szName1);
    FX_VarChar           (bSave, _T("Name2"),          m_szName2);
    FX_VarChar           (bSave, _T("pointnum1"),           m_szpointnum1);
    FX_VarChar           (bSave, _T("pointnum2"),           m_szpointnum2);
    FX_Integer           (bSave, _T("AStatus"),         m_szAStatus);
  };
};
