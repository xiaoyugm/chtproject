////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// NDK 2.0 - Network Development Kit                                          //
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
