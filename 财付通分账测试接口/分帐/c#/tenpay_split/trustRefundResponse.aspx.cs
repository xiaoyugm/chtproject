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

public partial class trustRefundResponse : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //密钥
        string key = "82d2f8b9fd7695aec51415ab2900a755";

        //创建TrustRefundResponseHandler实例
        TrustRefundResponseHandler resHandler = new TrustRefundResponseHandler(Context);
        resHandler.setKey(key);

        //判断签名
        if (resHandler.isTenpaySign())
        {
            //财付通账号
            string uin = resHandler.getParameter("uin");

            //状态
            string status = resHandler.getParameter("status");

            if ("1".Equals(status))
            {
                //处理添加关系逻辑
                Response.Write("签约成功<br/>");
            }
            else if ("2".Equals(status))
            {
                //处理撤销关系逻辑
                Response.Write("已撤销签约<br/>");
            }

        }
        else
        {
            Response.Write("认证签名失败");

        }

        //获取debug信息,建议把debug信息写入日志，方便定位问题
        //string debuginfo = resHandler.getDebugInfo();
        //Response.Write("<br/>debuginfo:" + debuginfo + "<br/>");
    }
}
