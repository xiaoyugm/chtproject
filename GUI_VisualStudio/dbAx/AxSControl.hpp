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

  bool     m_szSpeCtrol;
  int  m_szSID ,m_szSerialnum;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szSID =m_szSpeCtrol = m_szSerialnum = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("SID"),        m_szSID);
    FX_Bool              (bSave, _T("SpeCtrol"),       m_szSpeCtrol);
    FX_Integer           (bSave, _T("Serialnum"),       m_szSerialnum);
  };
};

class CAdjustdata :
    public CAxRecordset
{
public:
  CAdjustdata() { _SetDefaultValues(); }
  ~CAdjustdata() { }

  int  m_szADID ,m_szCDValue,m_szADStatus,m_szptype,m_szfds,m_szchan;
  CString     m_szName,m_szUseridadd;
  COleDateTime   m_szrecdate;
  REAL m_szAValue;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName = m_szUseridadd = _T("");
    m_szADID =m_szCDValue=m_szAValue =m_szADStatus= m_szptype=m_szfds=m_szchan=0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("ADID"),        m_szADID);
    FX_VarChar           (bSave, _T("Name"),        m_szName);
    FX_Integer           (bSave, _T("ptype"),       m_szptype);
    FX_Integer           (bSave, _T("fds"),         m_szfds);
    FX_Integer           (bSave, _T("chan"),         m_szchan);
    FX_Integer           (bSave, _T("CDValue"),       m_szCDValue);
    FX_Real              (bSave, _T("AValue"),           m_szAValue);
    FX_Integer           (bSave, _T("ADStatus"),       m_szADStatus);
    FX_DateTime          (bSave, _T("recdate"),       m_szrecdate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
  };
};

class CRealtimedata :
    public CAxRecordset
{
public:
  CRealtimedata() { _SetDefaultValues(); }
  ~CRealtimedata() { }

  int  m_szRTID ,m_szCDValue,m_szADStatus,m_szptype,m_szfds,m_szchan;
  CString     m_szName,m_szUseridadd,m_szsafemtext;
  COleDateTime   m_szrecdate,m_szsafemdate;
  REAL m_szAValue;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName = m_szUseridadd = m_szsafemtext =_T("");
    m_szRTID =m_szCDValue=m_szAValue =m_szADStatus= m_szptype=m_szfds=m_szchan=0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("RTID"),        m_szRTID);
    FX_VarChar           (bSave, _T("Name"),        m_szName);
    FX_Integer           (bSave, _T("ptype"),       m_szptype);
    FX_Integer           (bSave, _T("fds"),         m_szfds);
    FX_Integer           (bSave, _T("chan"),         m_szchan);
    FX_Integer           (bSave, _T("CDValue"),       m_szCDValue);
    FX_Real              (bSave, _T("AValue"),           m_szAValue);
    FX_Integer           (bSave, _T("ADStatus"),       m_szADStatus);
    FX_DateTime          (bSave, _T("recdate"),       m_szrecdate);
    FX_VarChar           (bSave, _T("Useridadd"),     m_szUseridadd);
    FX_DateTime          (bSave, _T("safemdate"),       m_szsafemdate);
    FX_VarChar           (bSave, _T("safemtext"),     m_szsafemtext);
  };
};
