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
//                                                                            //                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes                                                                   //
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "NDKDataBuffer.h"


////////////////////////////////////////////////////////////////////////////////
// Constructors / Destructor                                                  //
////////////////////////////////////////////////////////////////////////////////

// Constructor.
CNDKDataBuffer::CNDKDataBuffer()
{
	m_pData = NULL;
	m_unLength = 0;
}


// Constructor with untyped data.
CNDKDataBuffer::CNDKDataBuffer(LPVOID pData, UINT unLength)
{
	m_unLength = unLength;

	if (m_unLength == 0)
	{
		m_pData = NULL;
	}
	else
	{
		m_pData = malloc(unLength);
		memcpy(m_pData, pData, unLength);
	}
}


// Destructor.
CNDKDataBuffer::~CNDKDataBuffer()
{
	if (m_pData != NULL)
	{
		free(m_pData);
		m_pData = NULL;
	}
}


////////////////////////////////////////////////////////////////////////////////
// Attributes                                                                 //
////////////////////////////////////////////////////////////////////////////////

// Sets the buffer.
void CNDKDataBuffer::SetBuffer(LPVOID pData, UINT unLength)
{
	if (m_pData != NULL)
	{
		free(m_pData);
		m_pData = NULL;
	}

	m_unLength = unLength;

	if (m_unLength == 0)
	{
		m_pData = NULL;
	}
	else
	{
		m_pData = malloc(unLength);
		memcpy(m_pData, pData, unLength);
	}
}


// Gets the buffer.
LPVOID CNDKDataBuffer::GetBuffer() const
{
	return m_pData;
}


// Gets the length of the buffer.
UINT CNDKDataBuffer::GetLength() const
{
	return m_unLength;
}


////////////////////////////////////////////////////////////////////////////////
// Operation.                                                                 //
////////////////////////////////////////////////////////////////////////////////

// Serializes this object.
void CNDKDataBuffer::Serialize(CArchive& archive)
{
	if (archive.IsStoring())
	{
		archive << m_unLength;

		if (m_unLength > 0)
			archive.Write(m_pData, m_unLength);
	}
	else
	{
		if (m_pData != NULL)
			free(m_pData);

		archive >> m_unLength;

		if (m_unLength > 0)
		{
			m_pData = malloc(m_unLength);

			archive.Read(m_pData, m_unLength);
		}
	}	
}
