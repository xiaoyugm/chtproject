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

class CAxCommonSet :
    public CAxRecordset
{
public:
  CAxCommonSet() { _SetDefaultValues(); }
  ~CAxCommonSet() { }

//  CString     m_szName,m_szupwd;
  int  m_szCommonID;
  CString m_szstrc1,m_szstrc2,m_szstrc3,m_szstrc4,m_szstrc5,m_szstrc6,m_szstrc7,m_szstrc8,m_szstrc9,m_szstrc10
	  ,m_szstrc11,m_szstrc12,m_szstrc13,m_szstrc14,m_szstrc15,m_szstrc16,m_szstrc17,m_szstrc18,m_szstrc19,m_szstrc20
	  ,m_szstrc21,m_szstrc22,m_szstrc23,m_szstrc24,m_szstrc25,m_szstrc26,m_szstrc27,m_szstrc28,m_szstrc29,m_szstrc30;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szstrc1=m_szstrc2=m_szstrc3=m_szstrc4=m_szstrc5=m_szstrc6=m_szstrc7=m_szstrc8=m_szstrc9=m_szstrc10
	  =m_szstrc11=m_szstrc12=m_szstrc13=m_szstrc14=m_szstrc15=m_szstrc16=m_szstrc17=m_szstrc18=m_szstrc19=m_szstrc20
	  =m_szstrc21=m_szstrc22=m_szstrc23=m_szstrc24=m_szstrc25=m_szstrc26=m_szstrc27=m_szstrc28=m_szstrc29=m_szstrc30 = "";
    m_szCommonID = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("CommonID"),        m_szCommonID);
    FX_VarChar           (bSave, _T("strc1"),       m_szstrc1);
    FX_VarChar           (bSave, _T("strc2"),       m_szstrc2);
    FX_VarChar           (bSave, _T("strc3"),       m_szstrc3);
    FX_VarChar           (bSave, _T("strc4"),       m_szstrc4);
    FX_VarChar           (bSave, _T("strc5"),       m_szstrc5);
    FX_VarChar           (bSave, _T("strc6"),       m_szstrc6);
    FX_VarChar           (bSave, _T("strc7"),       m_szstrc7);
    FX_VarChar           (bSave, _T("strc8"),       m_szstrc8);
    FX_VarChar           (bSave, _T("strc9"),       m_szstrc9);
    FX_VarChar           (bSave, _T("strc10"),       m_szstrc10);
    FX_VarChar           (bSave, _T("strc11"),       m_szstrc11);
    FX_VarChar           (bSave, _T("strc12"),       m_szstrc12);
    FX_VarChar           (bSave, _T("strc13"),       m_szstrc13);
    FX_VarChar           (bSave, _T("strc14"),       m_szstrc14);
    FX_VarChar           (bSave, _T("strc15"),       m_szstrc15);
    FX_VarChar           (bSave, _T("strc16"),       m_szstrc16);
    FX_VarChar           (bSave, _T("strc17"),       m_szstrc17);
    FX_VarChar           (bSave, _T("strc18"),       m_szstrc18);
    FX_VarChar           (bSave, _T("strc19"),       m_szstrc19);
    FX_VarChar           (bSave, _T("strc20"),       m_szstrc20);
    FX_VarChar           (bSave, _T("strc21"),       m_szstrc21);
    FX_VarChar           (bSave, _T("strc22"),       m_szstrc22);
    FX_VarChar           (bSave, _T("strc23"),       m_szstrc23);
    FX_VarChar           (bSave, _T("strc24"),       m_szstrc24);
    FX_VarChar           (bSave, _T("strc25"),       m_szstrc25);
    FX_VarChar           (bSave, _T("strc26"),       m_szstrc26);
    FX_VarChar           (bSave, _T("strc27"),       m_szstrc27);
    FX_VarChar           (bSave, _T("strc28"),       m_szstrc28);
    FX_VarChar           (bSave, _T("strc29"),       m_szstrc29);
    FX_VarChar           (bSave, _T("strc30"),       m_szstrc30);
  };
};
