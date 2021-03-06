/**************************************************************************
    File: AxColorset.hpp
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

class CAxColorset :
    public CAxRecordset
{
public:
  CAxColorset() { _SetDefaultValues(); }
  ~CAxColorset() { }

  int  m_szColorID ,m_szColorrefset;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szColorID =m_szColorrefset = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("ColorID"),        m_szColorID);
    FX_Integer           (bSave, _T("Colorrefset"),       m_szColorrefset);
  };
};
