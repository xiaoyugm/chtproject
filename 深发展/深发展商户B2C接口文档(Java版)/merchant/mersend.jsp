<%@ page contentType="text/html; charset=gbk" %> 
 <HTML> 
 <HEAD> 
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
 <TITLE>buy</TITLE> 
 </HEAD> 
 <BODY BACKGROUND="/images/logo2.gif" BGCOLOR= "#FFFFFF" LINK= "#0000FF " VLINK= "#800080 " TEXT= "#000000 " TOPMARGIN=0 LEFTMARGIN=0 MARGINWIDTH=0 MARGINHEIGHT=0 > 
   <%
	//����ǩ���ؼ�����
	request.setCharacterEncoding("gbk");
String  payee=request.getParameter("Payee");
	int orderid ;// '������
		java.util.Random r=new java.util.Random();
	orderid=r.nextInt();
	if (orderid<0)
	orderid=-orderid;
	int count= Integer.parseInt(request.getParameter("count"));
	int price= Integer.parseInt(request.getParameter("price"));
	long timestamp=System.currentTimeMillis();
	String orig;		//ԭʼ����
	orig = "masterid=2000000833|orderid="+orderid+"|currency=RMB|amount="+(count*price)+"|date=20060828|timestamp="+timestamp+"|remark=sdb";

 	//����ǩ��
	String sign = com.sdb.payment.core.MerchantSignVerify.merchantSignData_ABA(orig);

%>

     <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=555> 
         <TR VALIGN=TOP ALIGN=LEFT> 
             <TD WIDTH=30 HEIGHT=30><IMG SRC= "/images/clearpixel.gif " WIDTH=30 HEIGHT=1 BORDER=0></TD> 
             <TD WIDTH=293><IMG SRC= "/images/clearpixel.gif " WIDTH=293 HEIGHT=1 BORDER=0></TD> 
             <TD WIDTH=232><IMG SRC= "/images/clearpixel.gif " WIDTH=232 HEIGHT=1 BORDER=0></TD> 
         </TR><TR VALIGN=TOP ALIGN=LEFT><TD></TD> 
             <TD WIDTH=293><P><FONT COLOR= "#003399 " FACE= "���� ">���Ѿ�ѡ��������Ʒ��</FONT></TD> 
             <TD></TD></TR> 
         <TR VALIGN=TOP ALIGN=LEFT><TD COLSPAN=3 HEIGHT=9></TD></TR> 
 <TR VALIGN=TOP ALIGN=LEFT> 
 <TD HEIGHT=125></TD> 
 <TD WIDTH=525 COLSPAN=2> 

	 <form  NAME= "NetPayForm" ACTION="https://testebank.sdb.com.cn/perbank/merpayb2c.do" target=_blank METHOD=POST>
<!--
 <form  NAME= "NetPayForm" ACTION="https://ebank.sdb.com.cn/perbank/merpayb2c.do"  METHOD=POST>
-->
 <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>
 <TR VALIGN=TOP ALIGN=LEFT> 
 <TD WIDTH=521> 
 <TABLE ID= "Table1 " BORDER=0 CELLSPACING=3 CELLPADDING=0 WIDTH=521> 
 <TR> 
 <TD ROWSPAN=5 WIDTH=105><P><IMG ID= "Picture11 " HEIGHT=106 WIDTH=75 SRC= "./images/<%= request.getParameter("type")%>.gif " VSPACE=0 HSPACE=0 ALIGN= "TOP " BORDER=0>&nbsp;</TD> 
 <TD COLSPAN=2><P><FONT COLOR= "#003399 " FACE= "���� ">Ħ������-<%=request.getParameter("type") %></FONT></TD> 
 </TR><TR> 
 <TD >
                    <P><font color="#003399 " face="���� ">����: </font>
                  </TD> 
				  <TD>&nbsp;<%=request.getParameter("price") %>Ԫ</TD>
 </TR><TR> 
                  <TD WIDTH=67>
<P><FONT COLOR= "#003399 " FACE= "���� ">������</FONT></TD>
                  <TD WIDTH=337>&nbsp;<%=request.getParameter("count" )%></TD>
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
                      <INPUT TYPE=SUBMIT NAME= "Paygate" VALUE= "���ڷ�չ����֧������" onClick="NetPayForm.action='https://testebank.sdb.com.cn/perbank/merpayb2c.do';">
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
         <input type='hidden' name='returnurl' value='http://10.1.9.160:8080/b2c_merchant/receivedemo.jsp'>
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
