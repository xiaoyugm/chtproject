
CREATE DATABASE BJygjl
Go

USE BJygjl

CREATE TABLE [BJygjl].[dbo].[fixlocation] (
	[locationID] [int]  NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name] [varchar] (20)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[analogtype] (
	[AID] [int]  NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name] [char] (20) NOT NULL ,
	[ltop] [float] (8) ,
	[lbom] [float] (8) ,
	[palmu] [float] (8) ,
	[palmd] [float] (8) ,
	[pbrk] [float] (8) ,
	[prtn] [float] (8) ,
	[punit] [char] (20)  ,
	[pico] [int] ,
	[falm] [char] (50)  ,
	[fdel] [bit]  ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (20)  ,
	[Useriddel] [char] (20)  
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[digitaltype] (
	[DID] [int]  NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name] [char] (20) NOT NULL ,
	[ptype] [int] ,
	[name0] [char] (20)  ,
	[name1] [char] (20) ,
	[name2] [char] (20) ,
	[palms] [int]  ,
	[falm] [char] (50)  ,
	[fdel] [bit]  ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (20)  ,
	[Useriddel] [char] (20)  
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[pointdescription] (
	[PID] [int]  NOT NULL  PRIMARY KEY  IDENTITY(1,1),
	[Name] [char] (50) NOT NULL ,
	[pointnum] [char] (10),
	[ptype] [int] ,
	[utype] [char] (20)  ,
	[typeID] [int]   ,
	[positionid] [int]   ,
	[fds] [int]   ,
	[chan] [int]   ,
	[subOpr] [bit] ,
	[fdel] [bit]  ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (20)  ,
	[Useriddel] [char] (20)  
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[control] (
	[CID] [int]  NOT NULL  PRIMARY KEY IDENTITY(1,1),
	[ptype] [bit]  NOT NULL,
	[utype] [bit]  NOT NULL,
	[typeid] [int]  NOT NULL ,
	[positionid] [int]  NOT NULL ,
	[fds] [int]  NOT NULL ,
	[chan] [int]  NOT NULL ,
	[subOpr] [bit]  NOT NULL,
	[fdel] [bit]  NOT NULL,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) NOT NULL ,
	[Useriddel] [char] (10) NOT NULL 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[user] (
	[UID] [int]  NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name] [char] (20) NOT NULL ,
	[upwd] [char] (20) NOT NULL,
	[classer] [int] NOT NULL
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[feedelectricity] (
	[EID] [int]  NOT NULL  PRIMARY KEY IDENTITY(1,1),
	[kdid] [int]  NOT NULL,
	[ddid] [int]  NOT NULL,
	[dflag] [bit]  NOT NULL ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) NOT NULL ,
	[Useriddel] [char] (10) NOT NULL 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[adjustemendation] (
	[AEID] [int]  NOT NULL  PRIMARY KEY IDENTITY(1,1),
	[ptid] [int]  NOT NULL,
	[dflag] [bit]  NOT NULL ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (20) NOT NULL ,
	[Useriddel] [char] (20) NOT NULL 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[dispoint] (
	[DISID] [int]  ,
	[LP0] [char] (100) ,
	[LP1] [char] (100) ,
	[LP2] [char] (100) ,
	[LP3] [char] (100) ,
	[LP4] [char] (100) ,
	[LP5] [char] (100) ,
	[LP6] [char] (100) ,
	[LP7] [char] (100) ,
	[LP8] [char] (100) ,
	[LP9] [char] (100) ,
	[LP10] [char] (100) ,
	[LP11] [char] (100) ,
	[LP12] [char] (100) ,
	[LP13] [char] (100) ,
	[LP14] [char] (100) ,
	[LP15] [char] (100) ,
	[LP16] [char] (100) ,
	[LP17] [char] (100) ,
	[LP18] [char] (100) ,
	[LP19] [char] (100) ,
	[LP20] [char] (100) ,
	[LP21] [char] (100) ,
	[LP22] [char] (100) ,
	[LP23] [char] (100) ,
	[LP24] [char] (100) ,
	[LP25] [char] (100) ,
	[LP26] [char] (100) ,
	[LP27] [char] (100) ,
	[LP28] [char] (100) ,
	[LP29] [char] (100) ,
	[LP30] [char] (100) ,
	[LP31] [char] (100) ,
	[LP32] [char] (100) ,
	[LP33] [char] (100) ,
	[LP34] [char] (100) ,
	[LP35] [char] (100) ,
	[LP36] [char] (100) ,
	[LP37] [char] (100) ,
	[LP38] [char] (100) ,
	[LP39] [char] (100) ,
	[LP40] [char] (100) ,
	[LP41] [char] (100) ,
	[LP42] [char] (100) ,
	[LP43] [char] (100) ,
	[LP44] [char] (100) ,
	[LP45] [char] (100) ,
	[LP46] [char] (100) ,
	[LP47] [char] (100) ,
	[LP48] [char] (100) ,
	[LP49] [char] (100) ,
	[LP50] [char] (100) ,
	[LP51] [char] (100) ,
	[LP52] [char] (100) ,
	[LP53] [char] (100) ,
	[LP54] [char] (100) ,
	[LP55] [char] (100) ,
	[LP56] [char] (100) ,
	[LP57] [char] (100) ,
	[LP58] [char] (100) ,
	[LP59] [char] (100) ,
	[LP60] [char] (100) ,
	[LP61] [char] (100) ,
	[LP62] [char] (100) ,
	[LP63] [char] (100) ,
	[LP64] [char] (100) ,
	[LP65] [char] (100) ,
	[LP66] [char] (100) ,
	[LP67] [char] (100) ,
	[LP68] [char] (100) ,
	[LP69] [char] (100) ,
	[LP70] [char] (100) ,
	[LP71] [char] (100) ,
	[LP72] [char] (100) ,
	[LP73] [char] (100) ,
	[LP74] [char] (100) ,
	[LP75] [char] (100) ,
	[LP76] [char] (100) ,
	[LP77] [char] (100) ,
	[LP78] [char] (100) ,
	[LP79] [char] (100) 
) ON [PRIMARY] 
GO
