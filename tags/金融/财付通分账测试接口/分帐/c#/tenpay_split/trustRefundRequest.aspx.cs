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

public partial class trustRefundRequest : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        //商户号
        string bargainor_id = "1900000107";
        string a_link = "<a target=\"_blank\" href=\"https://www.tenpay.com/cgi-bin/trust/showtrust.cgi?spid=" + bargainor_id + "\">" + "建立委托退款关系" + "</a>";
        Response.Write(a_link);
    }
}
