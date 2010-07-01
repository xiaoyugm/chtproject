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
#pragma once
#include <afxsock.h>
#include "NDKMessage.h"

////////////////////////////////////////////////////////////////////////////////
// Forward declarations                                                       //
////////////////////////////////////////////////////////////////////////////////
class CNDKServer;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CNDKServerSocket (concrete class)                                          //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// This class is based on CSocket. It overrides the method OnReceive to       //
// inform CNDKServer when data is received or a new connection is made.       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CNDKServerSocket : public CSocket
{
public:
	////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor                                              //
	////////////////////////////////////////////////////////////////////////////

	// Constructor.
	CNDKServerSocket();

	// Constructor with initialization.
	CNDKServerSocket(CNDKServer* pServer);

	// Destructor.
	virtual ~CNDKServerSocket();

	////////////////////////////////////////////////////////////////////////////
	// Attributes                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Return if the buffer is empty.
	BOOL IsBufferEmpty() const;

	////////////////////////////////////////////////////////////////////////////
	// Operations                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Initializes the socket.
	BOOL Initialize();

	// Closes the socket.
	void Close();

	// Sends a message.
	void SendMessage(CNDKMessage& message);

	// Receive a message.
	void ReceiveMessage(CNDKMessage& message);

	////////////////////////////////////////////////////////////////////////////
	// Overrides from CSocket                                                 //
	////////////////////////////////////////////////////////////////////////////
	
	//{{AFX_VIRTUAL(CNDKServerSocket)
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CNDKServerSocket)
	//}}AFX_MSG
	
private:
	////////////////////////////////////////////////////////////////////////////
	// Private Operations                                                     //
	////////////////////////////////////////////////////////////////////////////
	
	// Cleans up
	void CleanUp();

	////////////////////////////////////////////////////////////////////////////
	// Disable Copy-Constructor and Assignment Operator                       //
	////////////////////////////////////////////////////////////////////////////

	CNDKServerSocket(const CNDKServerSocket &);
	void operator=(const CNDKServerSocket &);

private:
	CNDKServer*  m_pServer;
	CSocketFile* m_pFile;
	CArchive*    m_pArchiveIn;
	CArchive*    m_pArchiveOut;
};
