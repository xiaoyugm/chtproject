using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {
        Response.Write("页面跳转调用:</br>");
        Response.Write("<a target=\"_blank\" href=\"" + "payRequest.aspx" + "\">" + "支付请求" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "splitPayRequest.aspx" + "\">" + "支付并分账请求" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "trustRefundRequest.aspx" + "\">" + "建立委托退款关系" + "</a></br>");
        Response.Write("</br>后台调用：</br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientSplit.aspx" + "\">" + "分账(带证书后台https）" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientSplitRollback.aspx" + "\">" + "分账回退(带证书后台https）" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientPlatformRefund.aspx" + "\">" + "平台退款(带证书后台https）" + "</a></br>");

        Response.Write("<a target=\"_blank\" href=\"" + "clientSplitInquire.aspx" + "\">" + "订单查询(带证书后台https)" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientUserCheck.aspx" + "\">" + "用户信息验证(后台https)" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientFreeze.aspx" + "\">" + "冻结(带证书后台https)" + "</a></br>");
        Response.Write("<a target=\"_blank\" href=\"" + "clientThaw.aspx" + "\">" + "解冻(带证书后台https)" + "</a></br>");
       

    }
}
