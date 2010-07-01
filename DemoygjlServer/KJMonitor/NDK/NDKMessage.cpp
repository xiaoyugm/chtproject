////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// NDK 2.0 - Network Development Kit                                          //
//                                                                            //
// Authors: Sebastien Lachance                                                //
//                                                                            //
// E-mail:  netblitz@rocler.qc.ca                                             //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// Permission to use, copy, modify, and distribute this software for any      //
// purpose and without fee is hereby granted. This is no guarantee about the  //
// use of this software. For any comments, bugs or thanks, please email us.   //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// Targeted Platform: Any Windows version                                     //
//                                                                            //
// Compiled with:     Visual C++ 6.0                                          //
//                                                                            //
// Last modification: January 2002                                            //
//                                                                            //
// History:                                                                   //
//                                                                            //
// 1- First release of this file.                                             //
// 2- The class is renamed and some optimizations are applied. Hungarian      //
//    notation is used.                                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes                                                                   //
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "NDKMessage.h"


////////////////////////////////////////////////////////////////////////////////
// Constructors / Destructor                                                  //
////////////////////////////////////////////////////////////////////////////////

// Constructor.
CNDKMessage::CNDKMessage()
{
	m_lCurrentIndex = 0;
}


// Constructor with a unique Id.
CNDKMessage::CNDKMessage(long lId)
{
	m_lId = lId;
	m_lCurrentIndex = 0;
}


// Copy-Constructor.
CNDKMessage::CNDKMessage(const CNDKMessage& message)
{
	m_lId = message.m_lId;
	m_lCurrentIndex = message.m_lCurrentIndex;
	m_elements.RemoveAll();

	m_elements.Append(message.m_elements);
}


// Destructor.
CNDKMessage::~CNDKMessage()
{
}


////////////////////////////////////////////////////////////////////////////////
// Attributes                                                                 //
////////////////////////////////////////////////////////////////////////////////
 
// Sets a unique identifier to each message.
void CNDKMessage::SetId(long lId)
{ 
	m_lId = lId;
}


// Gets the identifier of this message.
long CNDKMessage::GetId() const
{ 
	return m_lId; 
}


// Gets the number of elements in the array of this message.
int CNDKMessage::GetNbElements() const
{
	return m_elements.GetSize();
}


////////////////////////////////////////////////////////////////////////////////
// Operations                                                                 //
////////////////////////////////////////////////////////////////////////////////

// The following methods are used to add at the end an element in the 
// internal array of the CNDKMessage to any value.

void CNDKMessage::Add(UCHAR ucData)
{
	m_elements.Add(CNDKMessageData(ucData));
}


void CNDKMessage::Add(char cData)
{
	m_elements.Add(CNDKMessageData(cData));
}


void CNDKMessage::Add(USHORT usData)
{
	m_elements.Add(CNDKMessageData(usData));
}


void CNDKMessage::Add(short sData)
{
	m_elements.Add(CNDKMessageData(sData));
}


void CNDKMessage::Add(UINT unData)
{
	m_elements.Add(CNDKMessageData(unData));
}


void CNDKMessage::Add(int nData)
{
	m_elements.Add(CNDKMessageData(nData));
}


void CNDKMessage::Add(ULONG ulData)
{
	m_elements.Add(CNDKMessageData(ulData));
}


void CNDKMessage::Add(long lData)
{
	m_elements.Add(CNDKMessageData(lData));
}


void CNDKMessage::Add(float fData)
{
	m_elements.Add(CNDKMessageData(fData));
}


void CNDKMessage::Add(double dData)
{
	m_elements.Add(CNDKMessageData(dData));
}


void CNDKMessage::Add(const CString& strData)
{
	m_elements.Add(CNDKMessageData(strData));
}


void CNDKMessage::Add(LPVOID pData, UINT unLength)
{
	m_elements.Add(CNDKMessageData(pData, unLength));
}


// The following methods are used to set an element at the specified index
// in the internal array of the CNDKMessage to any value. Index is 
// zero-indexed.

void CNDKMessage::SetAt(long lIndex, unsigned char ucData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(ucData));
}


void CNDKMessage::SetAt(long lIndex, char cData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(cData));
}


void CNDKMessage::SetAt(long lIndex, unsigned short usData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(usData));
}


void CNDKMessage::SetAt(long lIndex, short sData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(sData));
}


void CNDKMessage::SetAt(long lIndex, unsigned int unData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(unData));
}


void CNDKMessage::SetAt(long lIndex, int nData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(nData));
}


void CNDKMessage::SetAt(long lIndex, unsigned long ulData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(ulData));
}


void CNDKMessage::SetAt(long lIndex, long lData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(lData));
}


void CNDKMessage::SetAt(long lIndex, float fData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(fData));
}


void CNDKMessage::SetAt(long lIndex, double dData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(dData));
}


void CNDKMessage::SetAt(long lIndex, const CString& strData)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(strData));
}


void CNDKMessage::SetAt(long lIndex, LPVOID pData, UINT unLength)
{
	if (IsValidSetIndex(lIndex))
		m_elements.SetAtGrow(lIndex, CNDKMessageData(pData, unLength));
}


// Gets the data type at the specified index.
NDKDataType CNDKMessage::GetDataTypeAt(long lIndex) const
{
	NDKDataType dataType = NDKDataString;

	if (IsValidGetIndex(lIndex))
		dataType = m_elements.GetAt(lIndex).GetDataType();
	
	return  dataType;
}


// The following methods are used to get an element at the specified index
// in the internal array of the CNDKMessage. The parameter passed by 
// reference will be filled with the appropriate data. The type of data 
// extracted must match the type of data set with a previous call to 
// SetAt or Add. Index is zero-indexed.

void CNDKMessage::GetAt(long lIndex, UCHAR& ucData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(ucData));
}


void CNDKMessage::GetAt(long lIndex, char& cData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(cData));
}


void CNDKMessage::GetAt(long lIndex, USHORT& usData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(usData));
}


void CNDKMessage::GetAt(long lIndex, short& sData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(sData));
}


void CNDKMessage::GetAt(long lIndex, UINT& unData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(unData));
}


void CNDKMessage::GetAt(long lIndex, int& nData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(nData));
}


void CNDKMessage::GetAt(long lIndex, ULONG& ulData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(ulData));
}


void CNDKMessage::GetAt(long lIndex, long& lData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(lData));
}


void CNDKMessage::GetAt(long lIndex, float& fData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(fData));
}


void CNDKMessage::GetAt(long lIndex, double& dData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(dData));
}


void CNDKMessage::GetAt(long lIndex, CString& strData) const
{
	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(strData));
}


void CNDKMessage::GetAt(long lIndex, LPVOID pData, UINT unLength) const
{
	ASSERT((pData != NULL) && (unLength > 0));

	if (IsValidGetIndex(lIndex))
		VERIFY(m_elements.GetAt(lIndex).Get(pData, unLength));
}


// Resets the current index. The current index is used by GetNext method.
void CNDKMessage::ResetCurrentIndex()
{
	m_lCurrentIndex = 0;
}


// Gets the current index.
long CNDKMessage::GetCurrentIndex() const
{
	return m_lCurrentIndex;
}


// Returns if the current index is the last.
BOOL CNDKMessage::IsLastCurrentIndex()
{
	return m_lCurrentIndex >= m_elements.GetSize();	
}


// The following methods are used to get an element in the internal array of 
// the CNDKMessage using the current index. The parameter passed by 
// reference will be filled with the appropriate data. The type of data 
// extracted must match the type of data set with a previous call to 
// SetAt or Add. 
void CNDKMessage::GetNext(UCHAR& ucData)
{
	GetAt(m_lCurrentIndex++, ucData);
}


void CNDKMessage::GetNext(char& cData)
{
	GetAt(m_lCurrentIndex++, cData);
}


void CNDKMessage::GetNext(USHORT& usData)
{
	GetAt(m_lCurrentIndex++, usData);
}


void CNDKMessage::GetNext(short& sData)
{
	GetAt(m_lCurrentIndex++, sData);
}


void CNDKMessage::GetNext(UINT& unData)
{
	GetAt(m_lCurrentIndex++, unData);
}


void CNDKMessage::GetNext(int& nData)
{
	GetAt(m_lCurrentIndex++, nData);
}


void CNDKMessage::GetNext(ULONG& ulData)
{
	GetAt(m_lCurrentIndex++, ulData);
}


void CNDKMessage::GetNext(long& lData)
{
	GetAt(m_lCurrentIndex++, lData);
}


void CNDKMessage::GetNext(float& fData)
{
	GetAt(m_lCurrentIndex++, fData);
}


void CNDKMessage::GetNext(double& dData)
{
	GetAt(m_lCurrentIndex++, dData);
}


void CNDKMessage::GetNext(CString& strData)
{
	GetAt(m_lCurrentIndex++, strData);
}


void CNDKMessage::GetNext(LPVOID pData, UINT unLength)
{
	GetAt(m_lCurrentIndex++, pData, unLength);
}


// Serializes a CNDKMessage object to a CArchive
IMPLEMENT_SERIAL(CNDKMessage, CObject, 1)
void CNDKMessage::Serialize(CArchive& archive)
{	
	if (archive.IsStoring())
	{
		archive << m_lId;
		archive << m_elements.GetSize();

		for (int nIndex = 0; nIndex < m_elements.GetSize(); nIndex++)
			m_elements.GetAt(nIndex).Serialize(archive);
	}
	else
	{
		int nNbElements = 0;

		archive >> m_lId;
		archive >> nNbElements;

		if (nNbElements > 0)
		{
			m_elements.SetSize(nNbElements);

			for (int nIndex = 0; nIndex < nNbElements; nIndex++)
			{
				CNDKMessageData	messageData;

				messageData.Serialize(archive);
			
				m_elements.SetAt(nIndex, messageData);
			}
		}
	}

	ResetCurrentIndex();
}


////////////////////////////////////////////////////////////////////////////////
// Operators                                                                  //
////////////////////////////////////////////////////////////////////////////////

// Assignment operator.
const CNDKMessage& CNDKMessage::operator=(const CNDKMessage& message)
{
	if (&message != this)
	{
		m_lId = message.m_lId;
		m_lCurrentIndex = message.m_lCurrentIndex;
		m_elements.RemoveAll();

		m_elements.Append(message.m_elements);
	}

	return *this;
}


////////////////////////////////////////////////////////////////////////////////
// Private Attributes                                                         //
////////////////////////////////////////////////////////////////////////////////

// Returns if the index is valid for the array of elements when setting a
// value.
BOOL CNDKMessage::IsValidSetIndex(long lIndex) const
{
	ASSERT(lIndex >= 0);

	return lIndex >= 0;
}


// Returns if the index is valid for the array of elements when getting a
// value.
BOOL CNDKMessage::IsValidGetIndex(long lIndex) const
{
	ASSERT((lIndex >= 0) && (lIndex < m_elements.GetSize()));

	return (lIndex >= 0) && (lIndex < m_elements.GetSize());
}
