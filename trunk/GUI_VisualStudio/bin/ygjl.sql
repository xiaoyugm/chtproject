
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
	[ptype] [char] (20)  ,
	[name0] [char] (20)  ,
	[name1] [char] (20) ,
	[name2] [char] (20) ,
	[palms] [tinyint]  ,
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
	[ptype] [SMALLINT] ,
	[utype] [char] (20)  ,
	[typeID] [SMALLINT]   ,
	[positionid] [SMALLINT]   ,
	[fds] [SMALLINT]   ,
	[chan] [SMALLINT]   ,
	[subOpr] [char] (20)  ,
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
	[LocatinNamePoint0] [char] (100) ,
	[LocatinNamePoint1] [char] (100) ,
	[LocatinNamePoint2] [char] (100) ,
	[LocatinNamePoint3] [char] (100) ,
	[LocatinNamePoint4] [char] (100) ,
	[LocatinNamePoint5] [char] (100) ,
	[LocatinNamePoint6] [char] (100) ,
	[LocatinNamePoint7] [char] (100) ,
	[LocatinNamePoint8] [char] (100) ,
	[LocatinNamePoint9] [char] (100) ,
	[LocatinNamePoint10] [char] (100) ,
	[LocatinNamePoint11] [char] (100) ,
	[LocatinNamePoint12] [char] (100) ,
	[LocatinNamePoint13] [char] (100) ,
	[LocatinNamePoint14] [char] (100) ,
	[LocatinNamePoint15] [char] (100) ,
	[LocatinNamePoint16] [char] (100) ,
	[LocatinNamePoint17] [char] (100) ,
	[LocatinNamePoint18] [char] (100) ,
	[LocatinNamePoint19] [char] (100) ,
	[LocatinNamePoint20] [char] (100) ,
	[LocatinNamePoint21] [char] (100) ,
	[LocatinNamePoint22] [char] (100) ,
	[LocatinNamePoint23] [char] (100) ,
	[LocatinNamePoint24] [char] (100) ,
	[LocatinNamePoint25] [char] (100) ,
	[LocatinNamePoint26] [char] (100) ,
	[LocatinNamePoint27] [char] (100) ,
	[LocatinNamePoint28] [char] (100) ,
	[LocatinNamePoint29] [char] (100) ,
	[LocatinNamePoint30] [char] (100) ,
	[LocatinNamePoint31] [char] (100) ,
	[LocatinNamePoint32] [char] (100) ,
	[LocatinNamePoint33] [char] (100) ,
	[LocatinNamePoint34] [char] (100) ,
	[LocatinNamePoint35] [char] (100) ,
	[LocatinNamePoint36] [char] (100) ,
	[LocatinNamePoint37] [char] (100) ,
	[LocatinNamePoint38] [char] (100) ,
	[LocatinNamePoint39] [char] (100) ,
	[LocatinNamePoint40] [char] (100) ,
	[LocatinNamePoint41] [char] (100) ,
	[LocatinNamePoint42] [char] (100) ,
	[LocatinNamePoint43] [char] (100) ,
	[LocatinNamePoint44] [char] (100) ,
	[LocatinNamePoint45] [char] (100) ,
	[LocatinNamePoint46] [char] (100) ,
	[LocatinNamePoint47] [char] (100) ,
	[LocatinNamePoint48] [char] (100) ,
	[LocatinNamePoint49] [char] (100) ,
	[LocatinNamePoint50] [char] (100) ,
	[LocatinNamePoint51] [char] (100) ,
	[LocatinNamePoint52] [char] (100) ,
	[LocatinNamePoint53] [char] (100) ,
	[LocatinNamePoint54] [char] (100) ,
	[LocatinNamePoint55] [char] (100) ,
	[LocatinNamePoint56] [char] (100) ,
	[LocatinNamePoint57] [char] (100) ,
	[LocatinNamePoint58] [char] (100) ,
	[LocatinNamePoint59] [char] (100) ,
	[LocatinNamePoint60] [char] (100) ,
	[LocatinNamePoint61] [char] (100) ,
	[LocatinNamePoint62] [char] (100) ,
	[LocatinNamePoint63] [char] (100) ,
	[LocatinNamePoint64] [char] (100) ,
	[LocatinNamePoint65] [char] (100) ,
	[LocatinNamePoint66] [char] (100) ,
	[LocatinNamePoint67] [char] (100) ,
	[LocatinNamePoint68] [char] (100) ,
	[LocatinNamePoint69] [char] (100) ,
	[LocatinNamePoint70] [char] (100) ,
	[LocatinNamePoint71] [char] (100) ,
	[LocatinNamePoint72] [char] (100) ,
	[LocatinNamePoint73] [char] (100) ,
	[LocatinNamePoint74] [char] (100) ,
	[LocatinNamePoint75] [char] (100) ,
	[LocatinNamePoint76] [char] (100) ,
	[LocatinNamePoint77] [char] (100) ,
	[LocatinNamePoint78] [char] (100) ,
	[LocatinNamePoint79] [char] (100) 
) ON [PRIMARY] 
GO
