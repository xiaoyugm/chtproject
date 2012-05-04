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

public partial class splitPayRequest : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //商户号
        string bargainor_id = "1900000107";

        //密钥
        string key = "82d2f8b9fd7695aec51415ab2900a755";

        //当前时间 yyyyMMdd
        string date = DateTime.Now.ToString("yyyyMMdd");
        //生成订单10位序列号，此处用时间和随机数生成，商户根据自己调整，保证唯一
        string strReq = "" + DateTime.Now.ToString("HHmmss") + TenpayUtil.BuildRandomStr(4);

        //商户订单号，不超过32位，财付通只做记录，不保证唯一性
        string sp_billno = strReq;

        // 财付通交易单号，规则为：10位商户号+8位时间（YYYYmmdd)+10位流水号 ,商户根据自己情况调整，只要保证唯一及符合规则就行
        string transaction_id = bargainor_id + date + strReq;


        //创建BaseSplitRequestHandler实例
        BaseSplitRequestHandler reqHandler = new BaseSplitRequestHandler(Context);
        //初始化
        reqHandler.init();
        //设置密钥
        reqHandler.setKey(key);
        reqHandler.setGateUrl("https://www.tenpay.com/cgi-bin/v4.0/pay_set.cgi");



        //-----------------------------
        //设置支付参数
        //-----------------------------
        reqHandler.setParameter("bank_type", "0");
        reqHandler.setParameter("cmdno", "1");
        reqHandler.setParameter("date", DateTime.Now.ToString("yyyyMMdd"));
        reqHandler.setParameter("fee_type", "1");
        reqHandler.setParameter("version", "4");

        reqHandler.setParameter("bargainor_id", bargainor_id);		//商户号
        reqHandler.setParameter("sp_billno", sp_billno);				//商家订单号
        reqHandler.setParameter("transaction_id", transaction_id);	//财付通交易单号
        reqHandler.setParameter("return_url", "http://127.0.0.1:2346/tenpay_split/splitPayResponse.aspx");			//支付通知url
        reqHandler.setParameter("desc", "支付并分账测试");						//商品名称
        reqHandler.setParameter("total_fee", "1");				//商品金额,以分为单位

        //业务类型
        reqHandler.setParameter("bus_type", "97");
        /**
         * 业务参数
         * 帐号^分帐金额^角色
         * 角色说明:	1:供应商 2:平台服务方 4:独立分润方
         * 帐号1^分帐金额1^角色1|帐号2^分帐金额2^角色2|...
         */
        reqHandler.setParameter("bus_args", "944933417^1^1");
        //行业描述信息
        reqHandler.setParameter("bus_desc","12345^深圳-上海^1^fady^庄^13800138000");


        //获取请求带参数的url
        string requestUrl = reqHandler.getRequestURL();

        //Get的实现方式
        string a_link = "<a target=\"_blank\" href=\"" + requestUrl + "\">" + "财付通支付" + "</a>";
        Response.Write(a_link);


        //post实现方式
        /*
        Response.Write("<form method=\"post\" action=\""+ reqHandler.getGateUrl() + "\" >\n");
        Hashtable ht = reqHandler.getAllParameters();
        foreach(DictionaryEntry de in ht) 
        {
            Response.Write("<input type=\"hidden\" name=\"" + de.Key + "\" value=\"" + de.Value + "\" >\n");
        }
        Response.Write("<input type=\"submit\" value=\"财付通支付\" >\n</form>\n");
        */

        //获取debug信息,建议把请求和debug信息写入日志，方便定位问题
        //string debuginfo = reqHandler.getDebugInfo();
        //Response.Write("<br/>requestUrl:" + requestUrl + "<br/>");
        //Response.Write("<br/>debuginfo:" + debuginfo + "<br/>");

    }
}
