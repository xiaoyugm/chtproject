/**************************************************************************
    File: AxDisPoint.hpp
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

class CAxDisPoint :
    public CAxRecordset
{
public:
  CAxDisPoint() { _SetDefaultValues(); }
  ~CAxDisPoint() { }

  CString  m_szstr0,m_szstr1,m_szstr2,m_szstr3,m_szstr4,m_szstr5,m_szstr6,m_szstr7,m_szstr8,m_szstr9;
  CString  m_szstr10,m_szstr11,m_szstr12,m_szstr13,m_szstr14,m_szstr15,m_szstr16,m_szstr17,m_szstr18,m_szstr19;
  CString  m_szstr20,m_szstr21,m_szstr22,m_szstr23,m_szstr24,m_szstr25,m_szstr26,m_szstr27,m_szstr28,m_szstr29;
//  CString  m_szstr30,m_szstr31,m_szstr32,m_szstr33,m_szstr34,m_szstr35,m_szstr36,m_szstr37,m_szstr38,m_szstr39;
//  CString  m_szstr40,m_szstr41,m_szstr42,m_szstr43,m_szstr44,m_szstr45,m_szstr46,m_szstr47,m_szstr48,m_szstr49;
//  CString  m_szstr50,m_szstr51,m_szstr52,m_szstr53,m_szstr54,m_szstr55,m_szstr56,m_szstr57,m_szstr58,m_szstr59;
//  CString  m_szstr60,m_szstr61,m_szstr62,m_szstr63,m_szstr64,m_szstr65,m_szstr66,m_szstr67,m_szstr68,m_szstr69;
//  CString  m_szstr70,m_szstr71,m_szstr72,m_szstr73,m_szstr74,m_szstr75,m_szstr76,m_szstr77,m_szstr78,m_szstr79;
  int m_szDISID;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szstr0=m_szstr1=m_szstr2=m_szstr3=m_szstr4=m_szstr5=m_szstr6=m_szstr7=m_szstr8=m_szstr9= _T("");
    m_szstr10=m_szstr11=m_szstr12=m_szstr13=m_szstr14=m_szstr15=m_szstr16=m_szstr17=m_szstr18=m_szstr19= _T("");
    m_szstr20=m_szstr21=m_szstr22=m_szstr23=m_szstr24=m_szstr25=m_szstr26=m_szstr27=m_szstr28=m_szstr29= _T("");
//    m_szstr30=m_szstr31=m_szstr32=m_szstr33=m_szstr34=m_szstr35=m_szstr36=m_szstr37=m_szstr38=m_szstr39= _T("");
//    m_szstr40=m_szstr41=m_szstr42=m_szstr43=m_szstr44=m_szstr45=m_szstr46=m_szstr47=m_szstr48=m_szstr49= _T("");
//    m_szstr50=m_szstr51=m_szstr52=m_szstr53=m_szstr54=m_szstr55=m_szstr56=m_szstr57=m_szstr58=m_szstr59= _T("");
//    m_szstr60=m_szstr61=m_szstr62=m_szstr63=m_szstr64=m_szstr65=m_szstr66=m_szstr67=m_szstr68=m_szstr69= _T("");
//    m_szstr70=m_szstr71=m_szstr72=m_szstr73=m_szstr74=m_szstr75=m_szstr76=m_szstr77=m_szstr78=m_szstr79= _T("");
    m_szDISID =  0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("DISID"),  m_szDISID);
    FX_VarChar           (bSave, _T("LP0"),  m_szstr0);
    FX_VarChar           (bSave, _T("LP1"),  m_szstr1);
    FX_VarChar           (bSave, _T("LP2"),  m_szstr2);
    FX_VarChar           (bSave, _T("LP3"),  m_szstr3);
    FX_VarChar           (bSave, _T("LP4"),  m_szstr4);
    FX_VarChar           (bSave, _T("LP5"),  m_szstr5);
    FX_VarChar           (bSave, _T("LP6"),  m_szstr6);
    FX_VarChar           (bSave, _T("LP7"),  m_szstr7);
    FX_VarChar           (bSave, _T("LP8"),  m_szstr8);
    FX_VarChar           (bSave, _T("LP9"),  m_szstr9);
    FX_VarChar           (bSave, _T("LP10"),  m_szstr10);
    FX_VarChar           (bSave, _T("LP11"),  m_szstr11);
    FX_VarChar           (bSave, _T("LP12"),  m_szstr12);
    FX_VarChar           (bSave, _T("LP13"),  m_szstr13);
    FX_VarChar           (bSave, _T("LP14"),  m_szstr14);
    FX_VarChar           (bSave, _T("LP15"),  m_szstr15);
    FX_VarChar           (bSave, _T("LP16"),  m_szstr16);
    FX_VarChar           (bSave, _T("LP17"),  m_szstr17);
    FX_VarChar           (bSave, _T("LP18"),  m_szstr18);
    FX_VarChar           (bSave, _T("LP19"),  m_szstr19);
    FX_VarChar           (bSave, _T("LP20"),  m_szstr20);
    FX_VarChar           (bSave, _T("LP21"),  m_szstr21);
    FX_VarChar           (bSave, _T("LP22"),  m_szstr22);
    FX_VarChar           (bSave, _T("LP23"),  m_szstr23);
    FX_VarChar           (bSave, _T("LP24"),  m_szstr24);
    FX_VarChar           (bSave, _T("LP25"),  m_szstr25);
    FX_VarChar           (bSave, _T("LP26"),  m_szstr26);
    FX_VarChar           (bSave, _T("LP27"),  m_szstr27);
    FX_VarChar           (bSave, _T("LP28"),  m_szstr28);
    FX_VarChar           (bSave, _T("LP29"),  m_szstr29);
/*    FX_VarChar           (bSave, _T("LP30"),  m_szstr30);
    FX_VarChar           (bSave, _T("LP31"),  m_szstr31);
    FX_VarChar           (bSave, _T("LP32"),  m_szstr32);
    FX_VarChar           (bSave, _T("LP33"),  m_szstr33);
    FX_VarChar           (bSave, _T("LP34"),  m_szstr34);
    FX_VarChar           (bSave, _T("LP35"),  m_szstr35);
    FX_VarChar           (bSave, _T("LP36"),  m_szstr36);
    FX_VarChar           (bSave, _T("LP37"),  m_szstr37);
    FX_VarChar           (bSave, _T("LP38"),  m_szstr38);
    FX_VarChar           (bSave, _T("LP39"),  m_szstr39);
    FX_VarChar           (bSave, _T("LP40"),  m_szstr40);
    FX_VarChar           (bSave, _T("LP41"),  m_szstr41);
    FX_VarChar           (bSave, _T("LP42"),  m_szstr42);
    FX_VarChar           (bSave, _T("LP43"),  m_szstr43);
    FX_VarChar           (bSave, _T("LP44"),  m_szstr44);
    FX_VarChar           (bSave, _T("LP45"),  m_szstr45);
    FX_VarChar           (bSave, _T("LP46"),  m_szstr46);
    FX_VarChar           (bSave, _T("LP47"),  m_szstr47);
    FX_VarChar           (bSave, _T("LP48"),  m_szstr48);
    FX_VarChar           (bSave, _T("LP49"),  m_szstr49);
    FX_VarChar           (bSave, _T("LP50"),  m_szstr50);
    FX_VarChar           (bSave, _T("LP51"),  m_szstr51);
    FX_VarChar           (bSave, _T("LP52"),  m_szstr52);
    FX_VarChar           (bSave, _T("LP53"),  m_szstr53);
    FX_VarChar           (bSave, _T("LP54"),  m_szstr54);
    FX_VarChar           (bSave, _T("LP55"),  m_szstr55);
    FX_VarChar           (bSave, _T("LP56"),  m_szstr56);
    FX_VarChar           (bSave, _T("LP57"),  m_szstr57);
    FX_VarChar           (bSave, _T("LP58"),  m_szstr58);
    FX_VarChar           (bSave, _T("LP59"),  m_szstr59);
    FX_VarChar           (bSave, _T("LP60"),  m_szstr60);
    FX_VarChar           (bSave, _T("LP61"),  m_szstr61);
    FX_VarChar           (bSave, _T("LP62"),  m_szstr62);
    FX_VarChar           (bSave, _T("LP63"),  m_szstr63);
    FX_VarChar           (bSave, _T("LP64"),  m_szstr64);
    FX_VarChar           (bSave, _T("LP65"),  m_szstr65);
    FX_VarChar           (bSave, _T("LP66"),  m_szstr66);
    FX_VarChar           (bSave, _T("LP67"),  m_szstr67);
    FX_VarChar           (bSave, _T("LP68"),  m_szstr68);
    FX_VarChar           (bSave, _T("LP69"),  m_szstr69);
    FX_VarChar           (bSave, _T("LP70"),  m_szstr70);
    FX_VarChar           (bSave, _T("LP71"),  m_szstr71);
    FX_VarChar           (bSave, _T("LP72"),  m_szstr72);
    FX_VarChar           (bSave, _T("LP73"),  m_szstr73);
    FX_VarChar           (bSave, _T("LP74"),  m_szstr74);
    FX_VarChar           (bSave, _T("LP75"),  m_szstr75);
    FX_VarChar           (bSave, _T("LP76"),  m_szstr76);
    FX_VarChar           (bSave, _T("LP77"),  m_szstr77);
    FX_VarChar           (bSave, _T("LP78"),  m_szstr78);
    FX_VarChar           (bSave, _T("LP79"),  m_szstr79);*/

  
  };
};
