<%@ page contentType="text/html; charset=gbk" %> 
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=gbk">
<TITLE>select</TITLE>
<script language="JavaScript">
<!--hide
function check()
{
    if(document.forms[0].count.value=="")
	{
	    alert("�����빺������");
		document.forms[0].count.focus();
		
		return false;
	}

	
	return true;
}
//endhide-->
</script>
</HEAD>
<BODY BACKGROUND="./images/logo2.gif" BGCOLOR="#FFFFFF" LINK="#0000FF" VLINK="#800080" TEXT="#000000" TOPMARGIN=0 LEFTMARGIN=0 MARGINWIDTH=0 MARGINHEIGHT=0>
    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=555>
        <TR VALIGN=TOP ALIGN=LEFT>
            <TD WIDTH=30 HEIGHT=30><IMG SRC="./images/clearpixel.gif" WIDTH=30 HEIGHT=1 BORDER=0></TD>
            <TD WIDTH=293><IMG SRC="./images/clearpixel.gif" WIDTH=293 HEIGHT=1 BORDER=0></TD>
            <TD WIDTH=232><IMG SRC="./images/clearpixel.gif" WIDTH=232 HEIGHT=1 BORDER=0></TD>
        </TR>
        <TR VALIGN=TOP ALIGN=LEFT>
            <TD></TD>
            <TD WIDTH=293>
      <P><FONT COLOR="#003399" FACE="����">��ѡ������Ʒ���£�</FONT>
    </TD>
            <TD></TD>
        </TR>
        <TR VALIGN=TOP ALIGN=LEFT>
            <TD COLSPAN=3 HEIGHT=9></TD>
        </TR>
        <TR VALIGN=TOP ALIGN=LEFT>
            <TD HEIGHT=125></TD>
            <TD WIDTH=525 COLSPAN=2>
                <form  NAME="LayoutRegion1FORM" ACTION="mersend.jsp" METHOD=POST onSubmit="return check()">
                    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>
                        <TR VALIGN=TOP ALIGN=LEFT>
                            <TD WIDTH=518>
                                <TABLE ID="Table1" BORDER=0 CELLSPACING=3 CELLPADDING=0 WIDTH=518>
                                    <TR>
                                        <TD ROWSPAN=5 WIDTH=105><P><IMG ID="Picture11" HEIGHT=106 WIDTH=75 SRC="./images/<%= request.getParameter("type")%>.gif" VSPACE=0 HSPACE=0 ALIGN="TOP" BORDER=0>&nbsp;</TD>
                                        <TD COLSPAN=2><P><FONT COLOR="#003399" FACE="����">Ħ������-<%= request.getParameter("type") %></FONT></TD>
                                    </TR>
                                    <TR>
                                        <TD ><P><FONT COLOR="#003399" FACE="����">�ػݼ�: </FONT></TD>
										<TD><%= request.getParameter("price") %>Ԫ</TD>
                                    </TR>
                                   <TR>
                                        <TD WIDTH=80><P><FONT COLOR="#003399" FACE="����">������</FONT></TD>
                                        <TD WIDTH=342><P><INPUT ID="FormsEditField1" TYPE=TEXT NAME="count" VALUE="" SIZE=4 MAXLENGTH=4>&nbsp;
                                        <INPUT TYPE=hidden NAME="price" VALUE="<%= request.getParameter("price") %>" >
                                        </TD>
                                    </TR>
									<TR>
                                        <TD WIDTH=59><P><FONT COLOR="#003399" FACE="����">��Ӧ�̣�</FONT></TD>
                                        <TD WIDTH=342>
										 <select name="Payee">
										  <option value="�Ͼ��̳ǣ�ͬ�У�">�Ͼ��̳ǣ�ͬ�У�</option>
										  <option value="��������ͨѶ���޹�˾�����У�">��������ͨѶ���޹�˾�����У�</option>
										  <option value="���ͨѶ���޹�˾��ͬ�У�">���ͨѶ���޹�˾��ͬ�У�</option>
										  <option value="���Ħ������ͨѶ���޹�˾�����У�">���Ħ������ͨѶ���޹�˾�����У�</option>
										  <option value="111">Ħ������ͨѶ���޹�˾�����ݣ������У�</option>
										 </select>
                                        </TD>
                                    </TR>
                                    <TR>
                                        <TD COLSPAN=2><P><INPUT TYPE=SUBMIT NAME="FormsButton1" VALUE="�ύѡ��" ID="FormsButton2">&nbsp;</TD>
                                    </TR>
                                    <TR>
                                        <TD COLSPAN=2 HEIGHT=16>&nbsp;</TD>
                                    </TR>
                                </TABLE>
                            </TD>
                        </TR>
                    </TABLE>
					
					<input type="hidden" name="type" value="<%=request.getParameter("type")%>">
                </FORM>
            </TD>
        </TR>
    </TABLE>
	
</BODY>
</HTML>
 
