
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
	[falm] [char] (300)  ,
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
	[falm] [char] (300)  ,
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
	[Name] [char] (50) NOT NULL ,
	[pointnum] [char] (10),
	[PID] [int]  ,
	[cpointnum] [char] (10),
	[cPID] [int]  ,
	[ByFds] [bit]  ,
	[pcpointnum] [char] (10),
	[fdel] [bit]  ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (20) ,
	[Useriddel] [char] (20) 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[ygjluser] (
	[UID] [int]  NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name] [char] (20) ,
	[upwd] [char] (20) ,
	[classer] [int] 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[feedelectricity] (
	[EID] [int]  NOT NULL  PRIMARY KEY IDENTITY(1,1),
	[Name] [char] (50) NOT NULL ,
	[cpointnum] [char] (5),
	[epointnum] [char] (5),
	[ecpointnum] [char] (10),
	[fdel] [bit]  ,
	[recdate] [datetime] ,
	[deldate] [datetime] ,
	[Useridadd] [char] (10) ,
	[Useriddel] [char] (10) 
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
	[LP19] [char] (100) 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[specialcontrol] (
	[SID] [int]  ,
	[SpeCtrol] [bit] ,
	[Serialnum] [int] 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[colorset] (
	[ColorID] [int]  ,
	[Colorrefset] [int] 
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[rtadjustdata] (
	[ADID] [int] NOT NULL PRIMARY KEY IDENTITY(1,1),
	[PID] [int] ,
	[ptype] [int] ,
	[fds] [int]   ,
	[chan] [int]   ,
	[CDValue] [int] ,
	[AValue] [float] (8) ,
	[ADStatus] [int] ,
	[recdate] [datetime] ,
	[Useridadd] [char] (20),
	[safemtext] [char] (50),
	[ffds] [int]   ,
	[fchan] [int]   ,
	[FeedStatus] [char] (20)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[rt201008data] (
	[RTID] [int] NOT NULL PRIMARY KEY IDENTITY(1,1),
	[PID] [int] ,
	[ptype] [int] ,
	[fds] [int]   ,
	[chan] [int]   ,
	[CDValue] [int] ,
	[AValue] [float] (8) ,
	[ADStatus] [int] ,
	[recdate] [datetime] ,
	[Useridadd] [char] (20),
	[safemtext] [char] (50),
	[ffds] [int]   ,
	[fchan] [int]   ,
	[FeedStatus] [char] (20)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[rt201009data] (
	[RTID] [int] NOT NULL PRIMARY KEY IDENTITY(1,1),
	[PID] [int] ,
	[ptype] [int] ,
	[fds] [int]   ,
	[chan] [int]   ,
	[CDValue] [int] ,
	[AValue] [float] (8) ,
	[ADStatus] [int] ,
	[recdate] [datetime] ,
	[Useridadd] [char] (20),
	[safemtext] [char] (50),
	[ffds] [int]   ,
	[fchan] [int]   ,
	[FeedStatus] [char] (20)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[rt5mdata] (
	[RT5ID] [int] NOT NULL PRIMARY KEY IDENTITY(1,1),
	[PID] [int] ,
	[ptype] [int] ,
	[fds] [int]   ,
	[chan] [int]   ,
	[AMinValue] [float] (8) ,
	[AValue] [float] (8) ,
	[ADStatus] [int] ,
	[recdate] [datetime] ,
	[Useridadd] [char] (20),
	[AMaxValue] [float] (8)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[commonset] (
	[CommonID] [int] NOT NULL,
	[strc1] [char] (100),
	[strc2] [char] (100),
	[strc3] [char] (100),
	[strc4] [char] (100),
	[strc5] [char] (100),
	[strc6] [char] (100),
	[strc7] [char] (100),
	[strc8] [char] (100),
	[strc9] [char] (100),
	[strc10] [char] (100),
	[strc11] [char] (100),
	[strc12] [char] (100),
	[strc13] [char] (100),
	[strc14] [char] (100),
	[strc15] [char] (100),
	[strc16] [char] (100),
	[strc17] [char] (100),
	[strc18] [char] (100),
	[strc19] [char] (100),
	[strc20] [char] (100),
	[strc21] [char] (100),
	[strc22] [char] (100),
	[strc23] [char] (100),
	[strc24] [char] (100),
	[strc25] [char] (100),
	[strc26] [char] (100),
	[strc27] [char] (100),
	[strc28] [char] (100),
	[strc29] [char] (100),
	[strc30] [char] (100)
) ON [PRIMARY] 
GO

CREATE TABLE [BJygjl].[dbo].[fanscon] (
	[FansID] [int] NOT NULL PRIMARY KEY IDENTITY(1,1),
	[Name1] [char] (100),
	[pointnum1] [char] (100) ,
	[Name2] [char] (100) ,
	[pointnum2] [char] (100),
	[AStatus] [int] 
) ON [PRIMARY] 
GO
