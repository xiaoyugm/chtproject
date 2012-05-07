<%@ page contentType="text/html; charset=gbk" %> 
<html>
<head>
<title>演示程序</title>
</head>
<body>
<br>

<%
	
	String orig = request.getParameter("orig");
	String sign = request.getParameter("sign"); 

	boolean result;		// 校验结果
	result = com.sdb.payment.core.MerchantSignVerify.merchantVerifyPayGate_ABA(sign,orig);
%>
原始数据:<%=orig%><br>
签名为:<br>
<%=sign%>
<br><br>
校验结果:<%=result%>
<br>
</body>
</html>