一、tenpayLib下文件：实现基础接口逻辑，一般无需修改
1、RequestHandler.cs所有请求类的基类
2、PayRequestHandler.cs支付请求类
3、BaseSplitRequestHandler.cs分账、支付并分账、冻结、解冻、分账回退、平台退款、订单查询的请求类
4、ResponseHandler.cs页面交互模式的应答基类
5、ClientResponseHandler.cs后台系统调用模式的应答基类，支持XML格式
6、ScriptClientResponseHandler.cs后台系统调用模式处理返回类HTML格式的应答类
7、TrustRefundResponseHandler.cs委托退款关系建立、撤销的应答类
8、TenpayHttpClient.cs通讯类，支持http、https、双向https

二、根目录下的aspx的文件：调用的例子，需要根据业务情况调整，client开头的为后台系统调用模式接口
1、payRequest.aspx支付请求例子
2、payResponse.aspx支付应答例子
3、show.aspx结果展现页
4、splitPayRequest.aspx支付并分账请求例子
5、splitPayRequest.aspx支付并分账应答例子
6、trustRefundRequest.aspx建立委托退款关系请求例子
7、trustRefundRequest.aspx委托退款关系建立、撤销应答例子
8、clientSplit.aspx分账调用例子
9、clientSplitRollback.aspx分账退款调用例子
10、clientPlatformRefund.aspx平台退款调用例子
11、clientSplitInquire.aspx订单查询调用例子
12、clientUserCheck.aspx用户信息验证调用例子
13、clientFreeze.aspx冻结调用例子
14、clientThaw.aspx解冻调用例子

