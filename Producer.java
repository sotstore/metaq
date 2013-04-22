

import com.taobao.metamorphosis.Message;
import com.taobao.metamorphosis.client.MessageSessionFactory;
import com.taobao.metamorphosis.client.MetaClientConfig;
import com.taobao.metamorphosis.client.MetaMessageSessionFactory;
import com.taobao.metamorphosis.client.producer.MessageProducer;
import com.taobao.metamorphosis.client.producer.SendResult;
import com.taobao.metamorphosis.utils.ZkUtils.ZKConfig;

/*
 * javac  -cp /home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/metamorphosis-client-1.4.4.jar:/home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/metamorphosis-commons-1.4.4.jar Producer.java; java -cp /home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/*:. Producer*/
public class Producer {

	/**
	 * @param args
	 */
	static MetaClientConfig metaClientConfig = null;
	static ZKConfig zkConfig = null;
	static MessageSessionFactory sessionFactory = null;
	static MessageProducer producer = null;

	public int init() {
		try {
			metaClientConfig = new MetaClientConfig();
			zkConfig = new ZKConfig();
			//zkConfig.zkConnect = "192.168.150.12:12181";
			zkConfig.zkConnect = "127.0.0.1:12181";
			// server.1=debian1:25550:35550
			// clientPort=21810
			// metaq: serverPort=8123
			//zkConfig.zkConnect = "172.16.115.128:21810"; 
			//XXX this will be read from the configuration file
			metaClientConfig.setZkConfig(zkConfig);
			sessionFactory = new MetaMessageSessionFactory(metaClientConfig);
			producer = sessionFactory.createProducer();

		} catch (Exception e) {
			System.out.println(e);
			return -1;
		}
		return 0;
	}

	public int produce_message() throws Exception {

		final String topic = "test";
		producer.publish(topic);
		StringBuilder line = new StringBuilder();
		long retvalue = System.nanoTime();
		//line.append("hello_world:this is a test message->nanotime: ");
		line.append("1001 nanotime: ");
		line.append(retvalue);
		SendResult sendResult = producer.sendMessage(new Message(topic, line
				.toString().getBytes()));
		if (!sendResult.isSuccess()) {
			System.out.println("Send message failed,error message:"
					+ sendResult.getErrorMessage());
		} else {
			System.out.println("Send message successfully,sent to "
					+ sendResult.getPartition());
		}
		producer.shutdown();
		return 0;

	}

	public static void main(String[] args) throws Exception {
		Producer producer = new Producer();
		producer.init();
		producer.produce_message();
		System.out.println("[dbg] send message done, exit");
		System.exit(0);
		
 		// BufferedReader reader = new BufferedReader(new
		// InputStreamReader(System.in));

	}

}
