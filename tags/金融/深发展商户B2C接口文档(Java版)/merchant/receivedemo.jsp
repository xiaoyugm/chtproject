<%@ page contentType="text/html; charset=gbk" %> 
<html>
<head>
<title>��ʾ����</title>
</head>
<body>
<br>

<%
	
	String orig = request.getParameter("orig");
	String sign = request.getParameter("sign"); 

	boolean result;		// У����
	result = com.sdb.payment.core.MerchantSignVerify.merchantVerifyPayGate_ABA(sign,orig);
%>
ԭʼ����:<%=orig%><br>
ǩ��Ϊ:<br>
<%=sign%>
<br><br>
У����:<%=result%>
<br>
</body>
</html>