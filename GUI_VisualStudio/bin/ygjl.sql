
CREATE DATABASE BJygjl
Go

USE BJygjl

CREATE TABLE [BJygjl].[dbo].[fixlocation] (
	[locationID] [int]  NOT NULL PRIMARY KEY,
	[Name] [varchar] (20)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[analogtype] (
	[AID] [int]  NOT NULL PRIMARY KEY,
	[Name] [char] (10) NOT NULL ,
	[ltop] [float] (8) NOT NULL,
	[lbom] [float] (8) NOT NULL,
	[palmu] [float] (8) NOT NULL,
	[palmd] [float] (8) NOT NULL,
	[pbrk] [float] (8) NOT NULL,
	[prtn] [float] (8) NOT NULL,
	[punit] [char] (10) NOT NULL ,
	[pico] [int] ,
	[falm] [char] (50)  ,
	[fdel] [bit]  NOT NULL,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) NOT NULL ,
	[Useriddel] [char] (10) NOT NULL 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[digitaltype] (
	[DID] [int]  NOT NULL PRIMARY KEY,
	[Name] [char] (10) NOT NULL ,
	[ptype] [char] (10) NOT NULL ,
	[name0] [char] (10) NOT NULL ,
	[name1] [char] (10) ,
	[name2] [char] (10) ,
	[palms] [tinyint]  NOT NULL,
	[falm] [char] (50)  ,
	[fdel] [bit]  NOT NULL,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) NOT NULL ,
	[Useriddel] [char] (10) NOT NULL 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[pointdescription] (
	[PID] [int]  NOT NULL  PRIMARY KEY,
	[ptype] [bit] NOT NULL,
	[utype] [bit]  NOT NULL,
	[typeID] [int]  NOT NULL ,
	[potioinid] [int]  NOT NULL ,
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

CREATE TABLE [BJygjl].[dbo].[control] (
	[CID] [int]  NOT NULL  PRIMARY KEY,
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
	[UID] [int]  NOT NULL PRIMARY KEY,
	[Name] [char] (10) NOT NULL ,
	[upwd] [char] (10) NOT NULL,
	[classer] [int] NOT NULL
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[feedelectricity] (
	[EID] [int]  NOT NULL  PRIMARY KEY,
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
	[AEID] [int]  NOT NULL  PRIMARY KEY,
	[ptid] [int]  NOT NULL,
	[dflag] [bit]  NOT NULL ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) NOT NULL ,
	[Useriddel] [char] (10) NOT NULL 
) ON [PRIMARY] 
GO
