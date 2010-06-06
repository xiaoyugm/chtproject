
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
