using System;
using System.Text;
using System.Web;
using System.Web.UI;


namespace tenpay
{
	/// <summary>
	/// BaseSplitRequestHandler ��ժҪ˵����
	/// </summary>
	public class BaseSplitRequestHandler:RequestHandler
	{
		public BaseSplitRequestHandler(HttpContext httpContext) : base(httpContext)
		{
			//
			// TODO: �ڴ˴���ӹ��캯���߼�
			//
		}

		protected override void createSign() 
		{
			base.createSign();
		
			this.setParameter("sign", this.getParameter("sign").ToUpper());

		}

	
	}
}
