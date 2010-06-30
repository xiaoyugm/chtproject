////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// NDK 2.0 - Network Development Kit                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes                                                                   //
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "NDKMessage.h"

////////////////////////////////////////////////////////////////////////////////
// Forward declarations                                                       //
////////////////////////////////////////////////////////////////////////////////
class CNDKServerSocket;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CNDKUser (concrete class)                                                  //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// This class contains the Id and the socket to represent a connected user of //
// the server.                                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CNDKUser  
{
public:
	////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor                                              //
	////////////////////////////////////////////////////////////////////////////

	// Constructor.
	CNDKUser();

	// Constructor with initialization.
	CNDKUser(long lId, CNDKServerSocket* pServerSocket);

	// Destructor.
	virtual ~CNDKUser();

	////////////////////////////////////////////////////////////////////////////
	// Attributes                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Gets the Id.
	long GetId() const;

	// Returns if the socket is the same as specified.
	BOOL IsSocketEqual(CNDKServerSocket* pServerSocket) const;

	// Returns if the buffer of the socket is empty.
	BOOL IsSocketBufferEmpty() const;

	////////////////////////////////////////////////////////////////////////////
	// Operations                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Sends a message.
	BOOL SendMessage(CNDKMessage& message);

	// Reads a message.
	BOOL ReadMessage(CNDKMessage& message);

	// Closes the socket.
	void CloseSocket();

	////////////////////////////////////////////////////////////////////////////
	// Operators                                                              //
	////////////////////////////////////////////////////////////////////////////

	// Comparison operator.
	BOOL operator==(const CNDKUser& user) const;

private:
	long			  m_lId;
	CNDKServerSocket* m_pServerSocket;
};
