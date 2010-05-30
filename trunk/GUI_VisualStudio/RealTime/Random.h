// random.h: interface for the RndGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDOM_H__1C2B0E68_B9A7_440B_98B9_21BFCB46C2D6__INCLUDED_)
#define AFX_RANDOM_H__1C2B0E68_B9A7_440B_98B9_21BFCB46C2D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RndGen 
{
	int     n;  
	float   *oldrand;
	void    advance_random();

public:  
	RndGen() { oldrand = 0; }
	~RndGen();
	float   randm();        
	void    init_random(const float randomseed = 0.1f);
};

#endif // !defined(AFX_RANDOM_H__1C2B0E68_B9A7_440B_98B9_21BFCB46C2D6__INCLUDED_)
