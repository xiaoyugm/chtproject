<%@ Page Language="C#" Debug="true" %>
<%@Import Namespace="MerchantLibrary"%>
<html>
<head>
<title>演示程序</title>
</head>
<body>
<br>
<%
	string  orig=Request.Params["orig"].ToString();
	string  sign=Request.Params["sign"].ToString();
	bool verified = PaymentInterfaceUtil.merchantVerifyPayGate_ABA(orig, sign);
			
%>
原始数据:<%=orig%>
<br>
<br>
签名为:<%=sign%>
<br>
<br>
校验结果:<%=verified%>
<br>
</body>
</html>