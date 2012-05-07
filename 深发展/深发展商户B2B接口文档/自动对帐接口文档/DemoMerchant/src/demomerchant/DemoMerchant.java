package demomerchant;

import java.util.ArrayList;
import java.util.HashMap;

import com.sdb.ebank.bean.data.AllOrderListReceive;
import com.sdb.ebank.bean.data.AllOrderListSend;
import com.sdb.ebank.bean.data.CommonReceive;
import com.sdb.ebank.bean.data.SettledOrderListReceive;
import com.sdb.ebank.bean.data.SettledOrderListSend;
import com.sdb.ebank.bean.data.UnsettledOrderListReceive;
import com.sdb.ebank.bean.data.UnsettledOrderListSend;
import com.sdb.ebank.bean.exception.CsiiException;
import com.sdb.payment.core.PaymentInterfaceUtil;


public class DemoMerchant {

	public static void main(String[] args) throws CsiiException {
		System.out.println(System.getProperty("java.home"));
		PaymentInterfaceUtil util = new PaymentInterfaceUtil();
		System.out
				.println("****************************************登录(开始)************************************************");
		util.login("test1", "111111");
		System.out
		.println("****************************************登录(结束)************************************************\n\n");

//		testQueryAllOrderList(util);		
//		testQueryUnsettledOrderList(util);
//		testQuerySettledOrderList(util);
//		testQueryOrderById(util);
		testAutoRefund(util);
		testAutoRefundQuery(util);
		System.out.println("end of demo");
		
		

	}
	public static void testQueryAllOrderList(PaymentInterfaceUtil util)throws CsiiException{
		// 所有清单
		System.out.println("****************************************所有清单(开始)********************************************");
		AllOrderListSend send1 = new AllOrderListSend(java.sql.Date
				.valueOf("2009-07-09"), java.sql.Date.valueOf("2009-07-09"),
				" 00:00:00.0000", " 23:59:59.999999");
		AllOrderListReceive rec1 = util.getAllOrderList(send1);

		System.out
				.println("\n----------------------------------------------------------------\n"
						+"all order list count="
						+ rec1.getCount());
		ArrayList allOrders = rec1.getOrders();
		for (int i = 0; i < allOrders.size(); i++) {
			System.out.println((HashMap) allOrders.get(i));
		}
		System.out.println("****************************************所有清单(结束)**********************************************\n\n");
	}
	public static void testQueryUnsettledOrderList(PaymentInterfaceUtil util)throws CsiiException{
		// 未入帐清单
		System.out.println("****************************************未入帐清单(开始)********************************************");
		UnsettledOrderListSend send2 = new UnsettledOrderListSend(java.sql.Date
				.valueOf("2009-07-09"), java.sql.Date.valueOf("2009-07-09"),
				"", "");
		UnsettledOrderListReceive rec2 = util.getUnsettledList(send2);
		System.out.println("----------------------------------------------------------------\n"
				+"unsettled order list=" + rec2.getCount());
		ArrayList UnsettledOrders = rec2.getOrders();
		for (int i = 0; i < UnsettledOrders.size(); i++) {
			System.out.println((HashMap) UnsettledOrders.get(i));
		}
		System.out.println("****************************************未入帐清单(结束)********************************************\n\n");

	}
	public static void testQuerySettledOrderList(PaymentInterfaceUtil util)throws CsiiException{
		// 已入帐清单
		System.out.println("****************************************已入帐清单(开始)********************************************");
		SettledOrderListSend send3 = new SettledOrderListSend(java.sql.Date
				.valueOf("2009-07-09"), java.sql.Date.valueOf("2009-07-09"),
				" 00:00:00.0000", " 23:59:59.999999");
		SettledOrderListReceive rec3 = util.getSettledList(send3);
		System.out.println("----------------------------------------------------------------\n"
				+"settled order list=" + rec3.getCount());
		ArrayList SettledOrders = rec3.getOrders();
		for (int i = 0; i < SettledOrders.size(); i++) {
			System.out.println((HashMap) SettledOrders.get(i));
		}
		System.out.println("****************************************已入帐清单(结束)********************************************\n\n");

	}
	public static void testQueryOrderById(PaymentInterfaceUtil util)throws CsiiException{
		// 按订单号查清单
		System.out.println("****************************************按订单号查清单(开始)*****************************************");
		AllOrderListSend send4 = new AllOrderListSend(java.sql.Date
				.valueOf("2009-07-09"), java.sql.Date.valueOf("2009-07-09"),
				" 00:00:00.0000", " 23:59:59.999999", "2017922691");
		AllOrderListReceive rec4 = util.getAllOrderList(send4);
		System.out.println("orderbyid  list count=" + rec4.getCount());
		ArrayList Ordersbyid = rec4.getOrders();
		for (int i = 0; i < Ordersbyid.size(); i++) {
			System.out.println((HashMap) Ordersbyid.get(i));
		}
		System.out.println("****************************************按订单号查清单(结束)*****************************************\n\n");

	}
	
	public static void testAutoRefund(PaymentInterfaceUtil util)throws CsiiException{
		System.out.println("****************************************自动退款(开始)*****************************************");
		    String customerId = "customerId=2000000833";
		    String orderno = "orderno=774297546";
		    String orderAmt = "orderAmt=144.4";
		    String ordertime = "ordertime=20111028";
		    String amt = "amt=144.40";
		    String flag = "flag=1";
		    String userId = "userId=102550";
		    String PostScript = "PostScript=自动退款测试20111028";
		    
		    String sendData = customerId+"|"+orderno+"|"+orderAmt+"|"+ordertime+"|"+amt+"|"+flag+"|"+userId+"|"+PostScript;
		     CommonReceive rec2 = util.getCommonReceive(sendData,"AutoRefundUrl","AutoRefundFormat");
		     System.out.println("all order list count=" + rec2.getCount());
		     ArrayList allOrders2 = rec2.getOrders();
		     for (int i = 0; i < allOrders2.size(); i++) {
		       System.out.println( (HashMap) allOrders2.get(i));
		     }
		     System.out.println("****************************************自动退款(结束)*****************************************\n\n");

	}
	public static void testAutoRefundQuery(PaymentInterfaceUtil util)throws CsiiException{
		System.out.println("****************************************退款查询(开始)*****************************************");
		 //退款查询

		  String sendData1=new String("customerId=2000000833|"+"orderno=62969784|"+"beginTime=20090107|"+"endTime=20090707|"+"flag=1|state=01");
		    CommonReceive rec1 = util.getCommonReceive(sendData1,"AutoQueryRefundUrl","AutoQueryRefundFormat");
		    System.out.println("all order list count=" + rec1.getCount());
		    ArrayList allOrders1 = rec1.getOrders();
		    for (int i = 0; i < allOrders1.size(); i++) {
		      System.out.println( (HashMap) allOrders1.get(i));
		    }

		     System.out.println("****************************************退款查询(结束)*****************************************\n\n");

	}
}
