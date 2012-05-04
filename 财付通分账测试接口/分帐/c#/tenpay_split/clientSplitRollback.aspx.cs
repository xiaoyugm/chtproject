using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using tenpay;

public partial class clientSplitRollback : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //商户号
        string bargainor_id = "1900000107";
        //密钥
        string key = "82d2f8b9fd7695aec51415ab2900a755";

        //创建请求对象
        BaseSplitRequestHandler reqHandler = new BaseSplitRequestHandler(Context);

        //通信对象
        TenpayHttpClient httpClient = new TenpayHttpClient();

        //应答对象
        ScriptClientResponseHandler resHandler = new ScriptClientResponseHandler();

        //-----------------------------
        //设置请求参数
        //-----------------------------
        reqHandler.init();
        reqHandler.setKey(key);
        reqHandler.setGateUrl("https://mch.tenpay.com/cgi-bin/split_rollback.cgi");

        reqHandler.setParameter("cmdno", "95");
        reqHandler.setParameter("version", "4");
        reqHandler.setParameter("fee_type", "1");
        reqHandler.setParameter("bargainor_id", bargainor_id);		//商户号
        reqHandler.setParameter("sp_billno", "0953141483");				//商家订单号
        reqHandler.setParameter("transaction_id", "1900000107201006290953141483");	//财付通交易单号
        reqHandler.setParameter("return_url", "http://127.0.0.1/");			//后台系统调用，必现填写为http://127.0.0.1/
        reqHandler.setParameter("total_fee", "1");
        //退款ID，同个ID财付通认为是同一个退款,格式为109+10位商户号+8位日期+7位序列号
        reqHandler.setParameter("refund_id", "1091900000107201006290000100");
        reqHandler.setParameter("bus_type", "97");
        reqHandler.setParameter("bus_args", "1|68084040^1");


        //-----------------------------
        //设置通信参数
        //-----------------------------
        //证书必须放在用户下载不到的目录，避免证书被盗取
        httpClient.setCertInfo("c:/key/1900000107.pfx", "1900000107");

        string requestUrl = reqHandler.getRequestURL();
        //设置请求内容
        httpClient.setReqContent(requestUrl);
        //设置超时
        httpClient.setTimeOut(10);

        string rescontent = "";
        //后台调用
        if (httpClient.call())
        {
            //获取结果
            rescontent = httpClient.getResContent();

            resHandler.setKey(key);
            //设置结果参数
            resHandler.setContent(rescontent);

            //判断签名及结果
            if (resHandler.isTenpaySign() && resHandler.getParameter("pay_result") == "0")
            {
                //取结果参数做业务处理
                Response.Write("OK,transaction_id=" + resHandler.getParameter("transaction_id") + "<br>");
            }
            else
            {
                //错误时，返回结果未签名。
                //如包格式错误或未确认结果的，请使用原来订单号重新发起，确认结果，避免多次操作
                Response.Write("业务错误信息或签名错误:" + resHandler.getParameter("pay_result") + "," + resHandler.getParameter("pay_info") + "<br>");
            }

        }
        else
        {
            //后台调用通信失败
            Response.Write("call err:" + httpClient.getErrInfo() + "<br>" + httpClient.getResponseCode() + "<br>");
            //有可能因为网络原因，请求已经处理，但未收到应答。
        }


        //获取debug信息,建议把请求、应答内容、debug信息，通信返回码写入日志，方便定位问题
        /*
        Response.Write("http res:" + httpClient.getResponseCode() + "," + httpClient.getErrInfo() + "<br>");
        Response.Write("req url:" + requestUrl + "<br/>");
        Response.Write("req debug:" + reqHandler.getDebugInfo() + "<br/>");
        Response.Write("res content:" + Server.HtmlEncode(rescontent) + "<br/>");
        Response.Write("res debug:" + Server.HtmlEncode(resHandler.getDebugInfo()) + "<br/>");
        */
   
        
    }
}
