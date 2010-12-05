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

class CAxDrawfile :
    public CAxRecordset
{
public:
  CAxDrawfile() { _SetDefaultValues(); }
  ~CAxDrawfile() { }

//  CString     m_szName,m_szupwd;
  int  m_szDRAWID;
  CString m_szD1024,m_szD1280,m_szD1360,m_szD1366,m_szD1400,m_szD1440,m_szD1600,m_szD1680,m_szD1920
	  ,m_szD2048,m_szD2560
	  ,m_szD11,m_szD12,m_szD13,m_szD14,m_szD15,m_szD16,m_szD17,m_szD18,m_szD19;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szD1024=m_szD1280=m_szD1360=m_szD1366=m_szD1400=m_szD1440=m_szD1600=m_szD1680=m_szD1920=m_szD2048
	  =m_szD2560
	  =m_szD11=m_szD12=m_szD13=m_szD14=m_szD15=m_szD16=m_szD17=m_szD18=m_szD19 = "";
    m_szDRAWID = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("DRAWID"),        m_szDRAWID);
    FX_VarChar           (bSave, _T("D1024"),       m_szD1024);
    FX_VarChar           (bSave, _T("D1280"),       m_szD1280);
    FX_VarChar           (bSave, _T("D1360"),       m_szD1360);
    FX_VarChar           (bSave, _T("D1366"),       m_szD1366);
    FX_VarChar           (bSave, _T("D1400"),       m_szD1400);
    FX_VarChar           (bSave, _T("D1440"),       m_szD1440);
    FX_VarChar           (bSave, _T("D1600"),       m_szD1600);
    FX_VarChar           (bSave, _T("D1680"),       m_szD1680);
    FX_VarChar           (bSave, _T("D1920"),       m_szD1920);
    FX_VarChar           (bSave, _T("D2048"),       m_szD2048);
    FX_VarChar           (bSave, _T("D2560"),       m_szD2560);
    FX_VarChar           (bSave, _T("D11"),       m_szD11);
    FX_VarChar           (bSave, _T("D12"),       m_szD12);
    FX_VarChar           (bSave, _T("D13"),       m_szD13);
    FX_VarChar           (bSave, _T("D14"),       m_szD14);
    FX_VarChar           (bSave, _T("D15"),       m_szD15);
    FX_VarChar           (bSave, _T("D16"),       m_szD16);
    FX_VarChar           (bSave, _T("D17"),       m_szD17);
    FX_VarChar           (bSave, _T("D18"),       m_szD18);
    FX_VarChar           (bSave, _T("D19"),       m_szD19);
  };
};

class CAxDrawjpg1024 :
    public CAxRecordset
{
public:
  CAxDrawjpg1024() { _SetDefaultValues(); }
  ~CAxDrawjpg1024() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};

class CAxDrawjpg1280 :
    public CAxRecordset
{
public:
  CAxDrawjpg1280() { _SetDefaultValues(); }
  ~CAxDrawjpg1280() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};

class CAxDrawjpg1360 :
    public CAxRecordset
{
public:
  CAxDrawjpg1360() { _SetDefaultValues(); }
  ~CAxDrawjpg1360() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};

class CAxDrawjpg1366 :
    public CAxRecordset
{
public:
  CAxDrawjpg1366() { _SetDefaultValues(); }
  ~CAxDrawjpg1366() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg1400 :
    public CAxRecordset
{
public:
  CAxDrawjpg1400() { _SetDefaultValues(); }
  ~CAxDrawjpg1400() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg1440 :
    public CAxRecordset
{
public:
  CAxDrawjpg1440() { _SetDefaultValues(); }
  ~CAxDrawjpg1440() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg1600 :
    public CAxRecordset
{
public:
  CAxDrawjpg1600() { _SetDefaultValues(); }
  ~CAxDrawjpg1600() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg1680 :
    public CAxRecordset
{
public:
  CAxDrawjpg1680() { _SetDefaultValues(); }
  ~CAxDrawjpg1680() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg1920 :
    public CAxRecordset
{
public:
  CAxDrawjpg1920() { _SetDefaultValues(); }
  ~CAxDrawjpg1920() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg2048 :
    public CAxRecordset
{
public:
  CAxDrawjpg2048() { _SetDefaultValues(); }
  ~CAxDrawjpg2048() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
class CAxDrawjpg2560 :
    public CAxRecordset
{
public:
  CAxDrawjpg2560() { _SetDefaultValues(); }
  ~CAxDrawjpg2560() { }

//  CString     m_szName,m_szupwd;
    int m_szJPGID, m_szDVer;
    CString m_szJ0,m_szJ1,m_szJ2,m_szJ3,m_szJ4,m_szJ5,m_szJ6,m_szJ7,m_szJ8,m_szJ9
    ,m_szJ10,m_szJ11,m_szJ12,m_szJ13,m_szJ14,m_szJ15,m_szJ16,m_szJ17,m_szJ18,m_szJ19
    ,m_szJ20,m_szJ21,m_szJ22,m_szJ23,m_szJ24,m_szJ25,m_szJ26,m_szJ27,m_szJ28,m_szJ29
    ,m_szJ30,m_szJ31,m_szJ32,m_szJ33,m_szJ34,m_szJ35,m_szJ36,m_szJ37,m_szJ38,m_szJ39
    ,m_szJ40,m_szJ41,m_szJ42,m_szJ43,m_szJ44,m_szJ45,m_szJ46,m_szJ47,m_szJ48,m_szJ49
    ,m_szJ50,m_szJ51,m_szJ52,m_szJ53,m_szJ54,m_szJ55,m_szJ56,m_szJ57,m_szJ58,m_szJ59
    ,m_szJ60,m_szJ61,m_szJ62,m_szJ63,m_szJ64,m_szJ65,m_szJ66,m_szJ67,m_szJ68,m_szJ69
    ,m_szJ70,m_szJ71,m_szJ72,m_szJ73,m_szJ74,m_szJ75,m_szJ76,m_szJ77,m_szJ78,m_szJ79
    ,m_szJ80,m_szJ81,m_szJ82,m_szJ83,m_szJ84,m_szJ85,m_szJ86,m_szJ87,m_szJ88,m_szJ89
    ,m_szJ90,m_szJ91,m_szJ92,m_szJ93,m_szJ94,m_szJ95,m_szJ96,m_szJ97,m_szJ98,m_szJ99
	,m_szDF;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szJ0=m_szJ1=m_szJ2=m_szJ3=m_szJ4=m_szJ5=m_szJ6=m_szJ7=m_szJ8=m_szJ9
    =m_szJ10=m_szJ11=m_szJ12=m_szJ13=m_szJ14=m_szJ15=m_szJ16=m_szJ17=m_szJ18=m_szJ19
    =m_szJ20=m_szJ21=m_szJ22=m_szJ23=m_szJ24=m_szJ25=m_szJ26=m_szJ27=m_szJ28=m_szJ29
    =m_szJ30=m_szJ31=m_szJ32=m_szJ33=m_szJ34=m_szJ35=m_szJ36=m_szJ37=m_szJ38=m_szJ39
    =m_szJ40=m_szJ41=m_szJ42=m_szJ43=m_szJ44=m_szJ45=m_szJ46=m_szJ47=m_szJ48=m_szJ49
    =m_szJ50=m_szJ51=m_szJ52=m_szJ53=m_szJ54=m_szJ55=m_szJ56=m_szJ57=m_szJ58=m_szJ59
    =m_szJ60=m_szJ61=m_szJ62=m_szJ63=m_szJ64=m_szJ65=m_szJ66=m_szJ67=m_szJ68=m_szJ69
    =m_szJ70=m_szJ71=m_szJ72=m_szJ73=m_szJ74=m_szJ75=m_szJ76=m_szJ77=m_szJ78=m_szJ79
    =m_szJ80=m_szJ81=m_szJ82=m_szJ83=m_szJ84=m_szJ85=m_szJ86=m_szJ87=m_szJ88=m_szJ89
    =m_szJ90=m_szJ91=m_szJ92=m_szJ93=m_szJ94=m_szJ95=m_szJ96=m_szJ97=m_szJ98=m_szJ99
	= m_szDF ="";
    m_szJPGID = m_szDVer =0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("JPGID"),        m_szJPGID);
    FX_VarChar           (bSave, _T("DF"),           m_szDF);
    FX_Integer           (bSave, _T("DVer"),         m_szDVer);
    FX_VarChar           (bSave, _T("J0"),       m_szJ0);
    FX_VarChar           (bSave, _T("J1"),       m_szJ1);
    FX_VarChar           (bSave, _T("J2"),       m_szJ2);
    FX_VarChar           (bSave, _T("J3"),       m_szJ3);
    FX_VarChar           (bSave, _T("J4"),       m_szJ4);
    FX_VarChar           (bSave, _T("J5"),       m_szJ5);
    FX_VarChar           (bSave, _T("J6"),       m_szJ6);
    FX_VarChar           (bSave, _T("J7"),       m_szJ7);
    FX_VarChar           (bSave, _T("J8"),       m_szJ8);
    FX_VarChar           (bSave, _T("J9"),       m_szJ9);
    FX_VarChar           (bSave, _T("J10"),       m_szJ10);
    FX_VarChar           (bSave, _T("J11"),       m_szJ11);
    FX_VarChar           (bSave, _T("J12"),       m_szJ12);
    FX_VarChar           (bSave, _T("J13"),       m_szJ13);
    FX_VarChar           (bSave, _T("J14"),       m_szJ14);
    FX_VarChar           (bSave, _T("J15"),       m_szJ15);
    FX_VarChar           (bSave, _T("J16"),       m_szJ16);
    FX_VarChar           (bSave, _T("J17"),       m_szJ17);
    FX_VarChar           (bSave, _T("J18"),       m_szJ18);
    FX_VarChar           (bSave, _T("J19"),       m_szJ19);
    FX_VarChar           (bSave, _T("J20"),       m_szJ20);
    FX_VarChar           (bSave, _T("J21"),       m_szJ21);
    FX_VarChar           (bSave, _T("J22"),       m_szJ22);
    FX_VarChar           (bSave, _T("J23"),       m_szJ23);
    FX_VarChar           (bSave, _T("J24"),       m_szJ24);
    FX_VarChar           (bSave, _T("J25"),       m_szJ25);
    FX_VarChar           (bSave, _T("J26"),       m_szJ26);
    FX_VarChar           (bSave, _T("J27"),       m_szJ27);
    FX_VarChar           (bSave, _T("J28"),       m_szJ28);
    FX_VarChar           (bSave, _T("J29"),       m_szJ29);
    FX_VarChar           (bSave, _T("J30"),       m_szJ30);
    FX_VarChar           (bSave, _T("J31"),       m_szJ31);
    FX_VarChar           (bSave, _T("J32"),       m_szJ32);
    FX_VarChar           (bSave, _T("J33"),       m_szJ33);
    FX_VarChar           (bSave, _T("J34"),       m_szJ34);
    FX_VarChar           (bSave, _T("J35"),       m_szJ35);
    FX_VarChar           (bSave, _T("J36"),       m_szJ36);
    FX_VarChar           (bSave, _T("J37"),       m_szJ37);
    FX_VarChar           (bSave, _T("J38"),       m_szJ38);
    FX_VarChar           (bSave, _T("J39"),       m_szJ39);
    FX_VarChar           (bSave, _T("J40"),       m_szJ40);
    FX_VarChar           (bSave, _T("J41"),       m_szJ41);
    FX_VarChar           (bSave, _T("J42"),       m_szJ42);
    FX_VarChar           (bSave, _T("J43"),       m_szJ43);
    FX_VarChar           (bSave, _T("J44"),       m_szJ44);
    FX_VarChar           (bSave, _T("J45"),       m_szJ45);
    FX_VarChar           (bSave, _T("J46"),       m_szJ46);
    FX_VarChar           (bSave, _T("J47"),       m_szJ47);
    FX_VarChar           (bSave, _T("J48"),       m_szJ48);
    FX_VarChar           (bSave, _T("J49"),       m_szJ49);
    FX_VarChar           (bSave, _T("J50"),       m_szJ50);
    FX_VarChar           (bSave, _T("J51"),       m_szJ51);
    FX_VarChar           (bSave, _T("J52"),       m_szJ52);
    FX_VarChar           (bSave, _T("J53"),       m_szJ53);
    FX_VarChar           (bSave, _T("J54"),       m_szJ54);
    FX_VarChar           (bSave, _T("J55"),       m_szJ55);
    FX_VarChar           (bSave, _T("J56"),       m_szJ56);
    FX_VarChar           (bSave, _T("J57"),       m_szJ57);
    FX_VarChar           (bSave, _T("J58"),       m_szJ58);
    FX_VarChar           (bSave, _T("J59"),       m_szJ59);
    FX_VarChar           (bSave, _T("J60"),       m_szJ60);
    FX_VarChar           (bSave, _T("J61"),       m_szJ61);
    FX_VarChar           (bSave, _T("J62"),       m_szJ62);
    FX_VarChar           (bSave, _T("J63"),       m_szJ63);
    FX_VarChar           (bSave, _T("J64"),       m_szJ64);
    FX_VarChar           (bSave, _T("J65"),       m_szJ65);
    FX_VarChar           (bSave, _T("J66"),       m_szJ66);
    FX_VarChar           (bSave, _T("J67"),       m_szJ67);
    FX_VarChar           (bSave, _T("J68"),       m_szJ68);
    FX_VarChar           (bSave, _T("J69"),       m_szJ69);
    FX_VarChar           (bSave, _T("J70"),       m_szJ70);
    FX_VarChar           (bSave, _T("J71"),       m_szJ71);
    FX_VarChar           (bSave, _T("J72"),       m_szJ72);
    FX_VarChar           (bSave, _T("J73"),       m_szJ73);
    FX_VarChar           (bSave, _T("J74"),       m_szJ74);
    FX_VarChar           (bSave, _T("J75"),       m_szJ75);
    FX_VarChar           (bSave, _T("J76"),       m_szJ76);
    FX_VarChar           (bSave, _T("J77"),       m_szJ77);
    FX_VarChar           (bSave, _T("J78"),       m_szJ78);
    FX_VarChar           (bSave, _T("J79"),       m_szJ79);
    FX_VarChar           (bSave, _T("J80"),       m_szJ80);
    FX_VarChar           (bSave, _T("J81"),       m_szJ81);
    FX_VarChar           (bSave, _T("J82"),       m_szJ82);
    FX_VarChar           (bSave, _T("J83"),       m_szJ83);
    FX_VarChar           (bSave, _T("J84"),       m_szJ84);
    FX_VarChar           (bSave, _T("J85"),       m_szJ85);
    FX_VarChar           (bSave, _T("J86"),       m_szJ86);
    FX_VarChar           (bSave, _T("J87"),       m_szJ87);
    FX_VarChar           (bSave, _T("J88"),       m_szJ88);
    FX_VarChar           (bSave, _T("J89"),       m_szJ89);
    FX_VarChar           (bSave, _T("J90"),       m_szJ90);
    FX_VarChar           (bSave, _T("J91"),       m_szJ91);
    FX_VarChar           (bSave, _T("J92"),       m_szJ92);
    FX_VarChar           (bSave, _T("J93"),       m_szJ93);
    FX_VarChar           (bSave, _T("J94"),       m_szJ94);
    FX_VarChar           (bSave, _T("J95"),       m_szJ95);
    FX_VarChar           (bSave, _T("J96"),       m_szJ96);
    FX_VarChar           (bSave, _T("J97"),       m_szJ97);
    FX_VarChar           (bSave, _T("J98"),       m_szJ98);
    FX_VarChar           (bSave, _T("J99"),       m_szJ99);
  };
};
