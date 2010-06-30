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
#include "NDKUser.h"

////////////////////////////////////////////////////////////////////////////////
// Forward declarations                                                       //
////////////////////////////////////////////////////////////////////////////////
class CNDKServerSocket;

////////////////////////////////////////////////////////////////////////////////
// Defines                                                                    //
////////////////////////////////////////////////////////////////////////////////
typedef CArray<long, long>                CLongArray;
typedef CList<CNDKUser, CNDKUser &>       CUserList;
typedef CList<long, long>                 CLongList;
typedef CList<CNDKMessage, CNDKMessage &> CMessageList;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CNDKUserManager (concrete class)                                           //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// This class manages all connected user to the user. It can add and remove   //
// user and send/receive message.                                             //
//                                                                            //                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CNDKUserManager  
{
public:
	////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor                                              //
	////////////////////////////////////////////////////////////////////////////

	// Constructor.
	CNDKUserManager();

	// Destructor.
	virtual ~CNDKUserManager();

	////////////////////////////////////////////////////////////////////////////
	// Attributes                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Gets the number of users.
	long GetNbUsers() const;

	// Returns the Ids of all users.
	void GetUserIds(CLongArray& alIds) const;

	////////////////////////////////////////////////////////////////////////////
	// Operations                                                             //
	////////////////////////////////////////////////////////////////////////////

	// Adds a user then returns its new Id.
	long AddUser(CNDKServerSocket* pServerSocket);

	// Removes a user.
	BOOL RemoveUser(long lUserId);

	// Removes all users.
	void RemoveAllUsers();
	
	// Sends a message to a specified user.
	BOOL SendMessage(long lUserId, CNDKMessage& message);

	// Sends a message to all users.
	BOOL SendMessageToAllUsers(CNDKMessage& message, CLongList& listIds);

	// Sends a message to all users except for user specified in alUserIds.
	BOOL SendMessageToAllUsersExceptFor(const CLongArray& alUserIds, 
										CNDKMessage& message, CLongList& listIds);

	// Processes pending read.
	BOOL ProcessPendingRead(CNDKServerSocket* pSocket, long lErrorCode, 
							long& lUserId, CMessageList& messages);
	
private:
	////////////////////////////////////////////////////////////////////////////
	// Private Operations                                                     //
	////////////////////////////////////////////////////////////////////////////

	// Gets a user from an Id.
	CNDKUser GetUserFromId(long lUserId) const;

	// Gets a user from a socket.
	CNDKUser GetUserFromSocket(CNDKServerSocket*) const;

private:
	CUserList m_users;
	long	  m_lNextId;
};
