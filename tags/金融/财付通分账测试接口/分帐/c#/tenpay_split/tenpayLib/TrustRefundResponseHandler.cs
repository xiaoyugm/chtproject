using System;
using System.Collections;
using System.Text;
using System.Web;

namespace tenpay
{
	/// <summary>
	/// TrustRefundResponseHandler ��ժҪ˵����
	/// </summary>
	/**
	* ί���˿�ǩԼӦ����
	* ============================================================================
	* api˵����
	* getKey()/setKey(),��ȡ/������Կ
	* getParameter()/setParameter(),��ȡ/���ò���ֵ
	* getAllParameters(),��ȡ���в���
	* isTenpaySign(),�Ƿ�Ƹ�ͨǩ��,true:�� false:��
	* doShow(),��ʾ������
	* getDebugInfo(),��ȡdebug��Ϣ
	* 
	* ============================================================================
	*
	*/
	public class TrustRefundResponseHandler:ResponseHandler
	{
		public TrustRefundResponseHandler(HttpContext httpContext) : base(httpContext)
		{
			//
			// TODO: �ڴ˴���ӹ��캯���߼�
			//
		}
		/**
	 * �Ƿ�Ƹ�ͨǩ��
	 * @Override
	 * @return boolean
	 */
		
		public override Boolean isTenpaySign() 
		{
		
			//��ȡ����
			string cmdno = getParameter("cmdno");
            string spid = getParameter("spid");
            string uin = getParameter("uin");
            string status = getParameter("status");
            string tenpaySign = getParameter("cftsign").ToUpper();
			string key = this.getKey();
			
			//��֯ǩ����
			StringBuilder sb = new StringBuilder();
			sb.Append("cmdno=" + cmdno + "&");
            sb.Append("spid=" + spid + "&");
            sb.Append("uin=" + uin + "&");
            sb.Append("status=" + status );
			sb.Append(key);
		
			//���ժҪ
			string sign = MD5Util.GetMD5(sb.ToString(),getCharset());	

			//debug��Ϣ
			setDebugInfo(sb.ToString() + " => sign:" + sign +
				" tenpaySign:" + tenpaySign);
		
			 return sign.Equals(tenpaySign);
		} 
	
	
	}
}
