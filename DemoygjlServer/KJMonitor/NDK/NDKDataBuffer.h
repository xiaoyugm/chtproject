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
// Include directive                                                          //
////////////////////////////////////////////////////////////////////////////////
#pragma once


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CNDKDataBuffer (concrete class)                                            //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// This class contains untyped data. It stores an array of any C++ basic      //
// types. Serialization is supported.                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CNDKDataBuffer
{
public:
	////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor                                              //
	////////////////////////////////////////////////////////////////////////////

	// Constructor.
	CNDKDataBuffer();

	// Constructor with untyped data.
	CNDKDataBuffer(LPVOID pData, UINT unLength);

	// Destructor.
	virtual ~CNDKDataBuffer();

	////////////////////////////////////////////////////////////////////////////
	// Attributes                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Sets the buffer.
	void SetBuffer(LPVOID pData, UINT unLength);

	// Gets the buffer.
	LPVOID GetBuffer() const;
	
	// Gets the length of the buffer.
	UINT GetLength() const;

	////////////////////////////////////////////////////////////////////////////
	// Operations                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Serializes this object.
	void Serialize(CArchive& archive);

private:
	LPVOID m_pData;
	UINT   m_unLength;
};
