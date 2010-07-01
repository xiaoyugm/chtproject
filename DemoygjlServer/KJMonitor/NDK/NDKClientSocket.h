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
