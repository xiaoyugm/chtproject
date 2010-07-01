////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// NDK 2.0 - Network Development Kit                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// Includes                                                                   //
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxsock.h>

////////////////////////////////////////////////////////////////////////////////
// Forward declarations                                                       //
////////////////////////////////////////////////////////////////////////////////
class CNDKClient;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CNDKClientSocket (concrete class)                                          //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// This class is based on CSocket. It overrides the method OnReceive to       //
// notify CNDKClient when data is received.                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CNDKClientSocket : public CSocket
{
public:
	////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor                                              //
	////////////////////////////////////////////////////////////////////////////

	// Constructor.
	CNDKClientSocket(CNDKClient* pClient);

	// Destructor.
	virtual ~CNDKClientSocket();

	////////////////////////////////////////////////////////////////////////////
	// Overrides from CSocket                                                 //
	////////////////////////////////////////////////////////////////////////////
		
	//{{AFX_VIRTUAL(CNDKClientSocket)
public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CNDKClientSocket)
	//}}AFX_MSG
	
private:
	CNDKClient*	m_pClient;
};
