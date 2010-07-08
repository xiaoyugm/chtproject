#ifndef __SQLDIRECT
#define __SQLDIRECT

#include "sqlcolumn.h"

class CSQLDirect 
{
public:
	void FetchRow(UINT row);
	CSQLDirect();
	CSQLDirect(  CString svSource, CString svUser,  CString svPassword);
	~CSQLDirect();

	void Init( void );
	void GetError( CString& );
	void Close( void );
	int ExecuteSQL( LPCSTR );
	int Connect( LPCSTR svSource , LPCSTR svUser, LPCSTR svPassword);
	int Fetch( void );
	int GetColumnID( CString,CString );
	int GetColumnType( int );
	CString GetCol( int );
	CString GetCol( CString,CString = _T("") );
	CString GetColumnName( int );
	int GetRowCount();

	inline void CSQLDirect::SupressErrors( bool bSupress = true ) { m_bSupressErrors=bSupress; }

private:
	void KillCols( void );
	void AddColumn( int,CString );
	void DisplayError( void );
	int FindColumn( int );
	CSQLColumn* GetColumn( int );

private:
	_TUCHAR* m_psvSQL;
	_TUCHAR* m_psvErrorMsg;
	HENV		m_hEnv;
	HDBC		m_hDBC;
	HSTMT		m_hStmt;
	CPtrArray	m_ColArray;
	bool			m_bSupressErrors;
};

#endif // __SQL




/*
csqldirect::connect</b> - connects to a datasource. </li>
csqldirect::executesql</b> - this is the main function that is used for handling the
    sql statement. </li>
csqldirect::getcol</b> - will return a column from a table in the resulting cursor. </li>
csqldirect::geterror</b> - provides detailed error messages in case something went
    wrong. </li>
csqldirect::getcolumntype</b> - provides information about a cursor's column. </li>
csqldirect::fetch</b> - will properly execute a sqlfetch command with error handling.
  </li>
csqldirect::close</b> - closes the connection to the datasource. </li>
</ul>

<p>the other class csqlcolumn is a support class for csqldirect. since multiple queries to
a cursor's column will result in a null value being returned, i found it necessary to keep
track of the columns as they are used. this is stored in a cptrarray within csqldirect and
is cleaned up after each time the cursor is requeried/closed. </p>

<p>an example of using this class to make sql calls: </p>

<pre><tt><font color="#990000">
csqldirect sqldirect( &quot;testdata&quot; );

if( sqldirect.executesql( &quot;select * from employee&quot; )==sql_success ) {
	while( sqldirect.fetch()==sql_success ) {
		.
		// do some stuff here
		.
	}
}
*/