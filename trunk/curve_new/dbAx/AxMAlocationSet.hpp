/**************************************************************************
    File: CAxMAlocationSet.hpp
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

class CAxMAlocationSet :
    public CAxRecordset
{
public:
  CAxMAlocationSet() { _SetDefaultValues(); }
  ~CAxMAlocationSet() { }

  CString     m_szName;
  int m_szlocationID;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szName  = _T("");
    m_szlocationID      = 0;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_Integer           (bSave, _T("locationID"),  m_szlocationID);
    FX_VarChar           (bSave, _T("Name"),  m_szName);
  };
};
