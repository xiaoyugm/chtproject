<%@ Page Language="C#" Debug="true" %>
<%@Import Namespace="System"%>
<%@Import Namespace="MerchantLibrary"%>
<HTML> 
	<HEAD> 
		<meta http-equiv="Content-Type" content="text/html; charset=gbk">
		<TITLE>buy</TITLE> 
	</HEAD> 
<BODY BACKGROUND="/images/logo2.gif" BGCOLOR= "#FFFFFF" LINK= "#0000FF " VLINK= "#800080 " TEXT= "#000000 " TOPMARGIN=0 LEFTMARGIN=0 MARGINWIDTH=0 MARGINHEIGHT=0 > 

<%

	string  payee=Request.Params["Payee"].ToString();
	string  countstr=Request.Params["count"].ToString();
	string  pricestr=Request.Params["price"].ToString();
	string  type=Request.Params["type"].ToString();
	long orderid = System.DateTime.Now.AddYears(-1969).ToUniversalTime().Ticks/TimeSpan.TicksPerMillisecond;
	int count= Convert.ToInt32(countstr);
	int price= Convert.ToInt32(pricestr);
	System.DateTime currentTime=System.DateTime.Now.AddYears(-1969);  
	long timestamp=currentTime.ToUniversalTime().Ticks/TimeSpan.TicksPerMillisecond;
	string date = "date="+System.DateTime.Now.ToString("yyyyMMdd");
	string orig = "masterid=2000000833|orderid="+orderid+ "|" + date + "|currency=RMB|amount="+(count*price)+"|timestamp="+timestamp+"|validtime=0|remark=sdb";
	string sign = PaymentInterfaceUtil.merchantSignData_ABA(orig);
	//string orig ="status=0|errdesc=|paydate=20071029|paytimestamp=1193623040772|masterid=tianyi|orderid=1193623390468|date=00381029|currency=RMB|amount=5|timestamp=1193623390468|validtime=0|remark=sdb";
	//string sign ="608ed3d3423194295a14a4135edbb80375b35243c13131f8e75448f2f6795e902a08e6024008350f259ef08dfbdec8715312d02c12de01dda1436eeebe4223f8e5881a219ccc6ba01031fd39bc8ba2b3a9412f5c103ea513754454040e04ca0c22498071c4d2af8a0ab2dce3ad17f5af83492536a703856cc0ca6c2e024693c0";
			
%>

<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=555>
 
		<TR VALIGN=TOP ALIGN=LEFT> 
			<TD WIDTH=30 HEIGHT=30><IMG SRC= "/images/clearpixel.gif " WIDTH=30 HEIGHT=1 BORDER=0></TD> 
			<TD WIDTH=293><IMG SRC= "/images/clearpixel.gif " WIDTH=293 HEIGHT=1 BORDER=0></TD> 
			<TD WIDTH=232><IMG SRC= "/images/clearpixel.gif " WIDTH=232 HEIGHT=1 BORDER=0></TD> 
		</TR>
		
		<TR VALIGN=TOP ALIGN=LEFT>
			<TD></TD> 
			<TD WIDTH=293><P><FONT COLOR= "#003399 " FACE= "���� ">���Ѿ�ѡ��������Ʒ��</FONT></TD> 
			<TD></TD>
    </TR>
     
		<TR VALIGN=TOP ALIGN=LEFT>
			<TD COLSPAN=3 HEIGHT=9></TD>
		</TR>
		
		<TR VALIGN=TOP ALIGN=LEFT> 
		<TD HEIGHT=125></TD> 
		<TD WIDTH=525 COLSPAN=2>

 <form  NAME= "PayForm" ACTION="https://testebank.sdb.com.cn/perbank/merpayb2c.do"  METHOD=POST>

		<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>
					<TR VALIGN=TOP ALIGN=LEFT> 
						<TD WIDTH=521> 
							<TABLE ID= "Table1 " BORDER=0 CELLSPACING=3 CELLPADDING=0 WIDTH=521> 
		<TR> 
		<TD ROWSPAN=5 WIDTH=105><P><IMG ID= "Picture11 " HEIGHT=106 WIDTH=75 SRC= "./images/<%=type%>.gif " VSPACE=0 HSPACE=0 ALIGN= "TOP " BORDER=0>&nbsp;</TD> 
		<TD COLSPAN=2><P><FONT COLOR= "#003399 " FACE= "���� ">Ħ������-<%=type%></FONT></TD> 
		</TR><TR> 
		<TD >
			<P><font color="#003399 " face="���� ">����: </font>
		</TD> 
		<TD>&nbsp;<%=price%>Ԫ</TD>
		</TR>
		
		<TR> 
                  <TD WIDTH=67>
<P><FONT COLOR= "#003399 " FACE= "���� ">������</FONT></TD>
                  <TD WIDTH=337>&nbsp;<%=count%></TD>
                </TR><TR> 
                  <TD WIDTH=67> 
                    <P><FONT COLOR= "#003399 " FACE= "���� ">�ܽ�</FONT>
                  </TD>
                  <TD width="337"><FONT COLOR= "#003399 " FACE= "���� ">&nbsp;<%=count*price%>Ԫ</FONT></TD>
                </TR>
				<TR> 
                  <TD WIDTH=67> 
                    <P><FONT COLOR= "#003399 " FACE= "���� ">��Ӧ�̣�</FONT>
                  </TD>
                  <TD width="337"><FONT COLOR= "#003399 " FACE= "���� ">&nbsp;<%=payee%></FONT></TD>
                </TR>
                <TR> 
		<TD COLSPAN=2 HEIGHT=16><P>
                      <INPUT TYPE=SUBMIT NAME= "Paygate" VALUE= "���ڷ�չ����֧������" onClick="PayForm.action='https://testebank.sdb.com.cn/perbank/merpayb2c.do';">
                </TD> 
 		</TR>
 		</TABLE>
 		</TD>
 		</TR>
 		</TABLE>
		<input type=hidden name=sign value="<%=sign%>" >
		<input type=hidden name=orig value="<%=orig%>" >
    	        <input type=hidden name="transName" value="paygate" >
<!--����url��ַ���̻������Լ�ϵͳ����趨-->
         <input type='hidden' name='returnurl' value='http://10.1.9.58:8080/receivedemo.aspx'>
         <br>
         <br>
         <br>
         <br><br><br>
		 ԭ���ݣ�<%=orig%>
		 <br>
		 ǩ�����ݣ�<%=sign%>
		 <br>
        </FORM>
 		</TD></TR></TABLE>
</BODY>
</HTML> 
