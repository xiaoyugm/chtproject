<%@ Page Language="C#" Debug="true" %>
<%@Import Namespace="MerchantLibrary"%>
<html>
<head>
<title>��ʾ����</title>
</head>
<body>
<br>
<%
	string  orig=Request.Params["orig"].ToString();
	string  sign=Request.Params["sign"].ToString();
	bool verified = PaymentInterfaceUtil.merchantVerifyPayGate_ABA(orig, sign);
			
%>
ԭʼ����:<%=orig%>
<br>
<br>
ǩ��Ϊ:<%=sign%>
<br>
<br>
У����:<%=verified%>
<br>
</body>
</html>