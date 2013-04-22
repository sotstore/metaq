import java.io.*;
import java.util.concurrent.Executor;

 
import com.taobao.metamorphosis.Message;
import com.taobao.metamorphosis.client.MessageSessionFactory;
import com.taobao.metamorphosis.client.MetaClientConfig;
import com.taobao.metamorphosis.client.MetaMessageSessionFactory;
import com.taobao.metamorphosis.client.consumer.ConsumerConfig;
import com.taobao.metamorphosis.client.consumer.MessageConsumer;
import com.taobao.metamorphosis.client.consumer.MessageListener;
import com.taobao.metamorphosis.utils.ZkUtils.ZKConfig;

/* javac  -cp /home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/metamorphosis-client-1.4.4.jar:/home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/metamorphosis-commons-1.4.4.jar AsyncConsumer.java; java -cp /home/metamorphosis/taobao/metamorphosis-server-wrapper/lib/*:. AsyncConsumer*/
public class AsyncConsumer {

	/**
	 * @param args
	 */
	
	static {
		// export LD_LIBRARY_PATH=/home/panthera/lab/msg_queue
		// echo $LD_LIBRARY_PATH
		// target lib: metaq_clib
		System.loadLibrary("metaq_clib");
	}
	
	MetaClientConfig metaClientConfig = null;
	ZKConfig zkConfig = null;
	MessageSessionFactory sessionFactory = null;
	
	public native static void reserved_test_method();
	public native static void jni_proc_msg(int msg_type, String msg_content);
	public int init(String host, int port) throws Exception {
		zkConfig = new ZKConfig();		
		metaClientConfig = new MetaClientConfig();
		// zkConfig.zkConnect = "192.168.150.11:33339";
		// host: 192.168.150.12
		// port: 12181
		zkConfig.zkConnect = host + ":" + port;		
		metaClientConfig.setZkConfig(zkConfig);
		sessionFactory = new MetaMessageSessionFactory(metaClientConfig);
		return 0;
	}

	public void listen(String topic, String group) throws Exception {
		// these will also be read from configuration?
		// final String topic = "test";
		// final String group = "meta-example";
		reserved_test_method();
 		final PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream("debug.txt")),true);  

		String topic_String = "[dbg] " + System.nanoTime() + ": topic is " + topic ; 
		String group_String = "[dbg] " + System.nanoTime() + ": group is " + group ;
		pw.println(topic_String);
		pw.println(group_String);  
		pw.flush();  
		
		pw.println("[dbg] issue on the sessionFactory?...");
		MessageConsumer consumer = sessionFactory
				.createConsumer(new ConsumerConfig(group));
		pw.println("[dbg] run after sessionFactory.createConsumer...");  
		pw.flush();  
		consumer.subscribe(topic, 1024 * 1024, new MessageListener() {
			public void recieveMessages(Message message) {
				//System.out.println("Receive message "
				//		+ new String(message.getData()));
				try {
					pw.println("[dbg] current thread is: " + Thread.currentThread().getId());
					pw.println("[dbg] running inside recieveMessages");
					pw.flush();
					final String msg = new String(message.getData());
					String logstr = "Receive message "	+ msg + "\n";
					String[] parts = msg.split(" ");
					
					pw.println("[dbg] msg_key: " + parts[0]);
					StringBuilder sb = new StringBuilder();
					for (int i = 1; i < parts.length; i++) {						
						sb.append(parts[i]);
						sb.append(" ");
					}
					pw.println("[dbg] msg_content: " + sb.toString());
					pw.flush();
					
					jni_proc_msg(Integer.valueOf(parts[0]).intValue(), sb.toString());
				} catch (Exception e) {
					e.printStackTrace();
				}
				
			}

			public Executor getExecutor() {
				// Thread pool to process messages,maybe null.
				return null;
			}
		});
		consumer.completeSubscribe();
		pw.println("[dbg] run after consumer.completeSubscribe();");
		pw.println("[dbg] current thread is: " + Thread.currentThread().getId());
		pw.flush();
		//synchronized (this) {
		//	this.wait();
		//}
		
				
	}

	public static void main(String[] args) throws Exception {
		//the main function is used to test
		AsyncConsumer ac = new AsyncConsumer();		
		//zkConfig.zkConnect = "172.16.115.22:12181";
		//ac.init("192.168.150.12", 12181);
		ac.init("127.0.0.1", 12181);
		ac.listen("test", "meta-example");

	}

}
