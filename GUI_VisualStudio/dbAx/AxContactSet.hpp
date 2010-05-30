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
#include "dbAx\AxLib.h"

using namespace dbAx;

class CAxContactSet :
    public CAxRecordset
{
public:
  CAxContactSet() { _SetDefaultValues(); }
  ~CAxContactSet() { }

  CString     m_szAccountID;
  CString     m_szName;
  CString     m_szTitle;
  CString     m_szPhone;
  CString     m_szExtn;
  CString     m_szEmail;
  CString     m_szNote;
  BYTE*       m_pimgPhotoID;

  //Set default values of class members
  void _SetDefaultValues()
  {
    m_szAccountID  = _T("");
    m_szName       = _T("");
    m_szTitle      = _T("");
    m_szPhone      = _T("");
    m_szExtn       = _T("");
    m_szEmail      = _T("");
    m_szNote       = _T("");
    m_pimgPhotoID  = NULL;
  };

  //Exchange field values with data provider
  void DoFieldExchange(bool bSave = FALSE)
  {
    FX_VarChar           (bSave, _T("AccountID"),  m_szAccountID);
    FX_VarChar           (bSave, _T("Name"),       m_szName);
    FX_VarChar           (bSave, _T("Title"),      m_szTitle);
    FX_VarChar           (bSave, _T("Phone"),      m_szPhone);
    FX_VarChar           (bSave, _T("Extn"),       m_szExtn);
    FX_VarChar           (bSave, _T("Email"),      m_szEmail);
    FX_Text              (bSave, _T("Note"),       m_szNote);
    FX_Image             (bSave, _T("PhotoID"),    &m_pimgPhotoID);
  };
};
