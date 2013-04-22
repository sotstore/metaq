/*
 * test.c
 *
 *  Created on: Apr 11, 2013
 *      Author: Administrator
 */
//#include "test.h"
#include <jni.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINE 80
#define MY_MQ_ID 1233

typedef struct {
	long type;
	float fval;
	unsigned int uival;
	char strval[MAX_LINE + 1];
} MY_TYPE_T;

//for test
int value = -1;
void set_value(int para) {
	value = para;
}
int get_value() {
	return value;
}

void reserved_test_method() {
	printf("This is the RegisterNatives method in metaq_clib\n");

}

//=====================================================
//set callback
JavaVM *jvm;
JNIEnv *env;
int msgid;
int (*msg_proc_callback)(int msg_type, const char msg[]) = NULL;
void set_msg_proc_callback(int (*para)(int msg_type, const char msg[])) {
	msg_proc_callback = para;
}
char* topic;
char* group;
void set_topic(const char* topic_para) {
	topic = topic_para;
}
void set_group(const char* group_para) {
	group = group_para;
}

void msg_proc(void) {
	msgid = msgget(MY_MQ_ID, 0666 | IPC_CREAT);
	while (1) {
		printf("[dbg] going to receive msgs...\n");
		MY_TYPE_T recMessage;
		int ret = msgrcv(msgid, (struct msgbuf*) &recMessage, sizeof(MY_TYPE_T),
				1, 0); //这个地方Message Type要和欲接受的消息类型相同
		if (ret != -1) {
			printf("Read a message from the queue\n");
			printf("Message Type:%ld\n", recMessage.type);
			printf("Float value:%f\n", recMessage.fval);
			printf("Uint value:%d\n", recMessage.uival);
			printf("String value:%s\n", recMessage.strval);
		}
		//destroy a message queue
		//printf("get_value: %d\n", get_value());
		if (msg_proc_callback != NULL ) {
			(*msg_proc_callback)(123, recMessage.strval);
		} else {
			printf("sorry, callback pointer not set...");
		}

	}
}

//==========================================================

#define  macro_metamorphosis_client_jar 	"metamorphosis-client-1.4.4.jar"
#define  macro_metamorphosis_commons_jar 	"metamorphosis-commons-1.4.4.jar"
#define  macro_metamorphosis_server_jar 	"metamorphosis-server-1.4.4.jar"
#define  macro_metamorphosis_tools_jar 		"metamorphosis-tools-1.4.4.jar"
#define  macro_commons_lang_jar 			"commons-lang-2.6.jar"
#define  macro_commons_logging_jar 			"commons-logging-1.1.jar"
#define  macro_gecko_jar 					"gecko-1.1.2.jar"
#define  macro_zkclient_jar 				"zkclient-0.1.jar"
#define  macro_zookeeper_jar 				"zookeeper-3.4.3.jar"
#define  macro_log4j_jar 					"log4j-1.2.14.jar"
#define  macro_slf4j_api_jar 				"slf4j-api-1.6.2.jar"
#define  macro_jackson_mapper_lgpl_jar 		"jackson-mapper-lgpl-1.4.0.jar"
#define  macro_jackson_core_lgpl_jar		"jackson-core-lgpl-1.4.0.jar"

int verify_jar() {
	printf("Verifying essential jar files:\n");
	int file_test_result;
	file_test_result = access("./lib/"macro_metamorphosis_client_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_metamorphosis_client_jar);
		return -1;
	}
	file_test_result = access("./lib/"macro_metamorphosis_commons_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_metamorphosis_commons_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_metamorphosis_server_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_metamorphosis_server_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_metamorphosis_tools_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_metamorphosis_tools_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_commons_lang_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_commons_lang_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_commons_logging_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_commons_logging_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_gecko_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n", macro_gecko_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_zkclient_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n", macro_zkclient_jar);
		return -1;
	}
	file_test_result = access("./lib/"macro_zookeeper_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n", macro_zookeeper_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_log4j_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n", macro_log4j_jar);
		return -1;
	}
	file_test_result = access("./lib/"macro_slf4j_api_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n", macro_slf4j_api_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_jackson_mapper_lgpl_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_jackson_mapper_lgpl_jar);
		return -1;
	}

	file_test_result = access("./lib/"macro_jackson_core_lgpl_jar, F_OK);
	if (file_test_result == -1) {
		printf("missing jar file: [%s] in ./lib, exit\n",
				macro_jackson_core_lgpl_jar);
		return -1;
	}
	return 0;
}

jclass jni_cls;
int start_metaq_listener(const char *host, const int port) {

	/*pthread_t msg_proc_thread;
	 int ret = pthread_create(&msg_proc_thread, NULL, (void *) msg_proc, NULL );
	 if (ret != 0) {
	 printf("Create pthread error!\n");
	 return -1;
	 }
	 //pthread_join(msg_proc_thread, NULL );
	 pthread_detach(msg_proc_thread);*/
	if (verify_jar() < 0) {
		printf("[dbg] failed to verify jars, exit\n");
		return -1;
	}

	printf("[dbg] connect to metaq:\n");
	printf("[dbg] host:[%s], port:[%d]\n", host, port);
	JavaVMOption options[1];
	options[0].optionString =
			"-Djava.class.path=./lib/"macro_metamorphosis_client_jar":"
			"./lib/"macro_metamorphosis_commons_jar":"
			"./lib/"macro_metamorphosis_server_jar":"
			"./lib/"macro_metamorphosis_tools_jar":"
			"./lib/"macro_commons_lang_jar":"
			"./lib/"macro_commons_logging_jar":"
			"./lib/"macro_gecko_jar":"
			"./lib/"macro_zkclient_jar":"
			"./lib/"macro_zookeeper_jar":"
			"./lib/"macro_log4j_jar":"
			"./lib/"macro_slf4j_api_jar":"
			"./lib/"macro_jackson_mapper_lgpl_jar":"
			"./lib/"macro_jackson_core_lgpl_jar":"
			".";
	JavaVMInitArgs vm_args;
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 1;
	vm_args.options = options;
	long status = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);
	if (status == JNI_ERR) {
		printf("failed to create jvm, exit...\n");
	}
	printf("create jvm: done...\n");
	printf("[dbg] Executing@LINE%d\n", __LINE__);

	printf("[dbg] Executing@LINE%d\n", __LINE__);
	//javap -s -private testjni
	/*Compiled from "AsyncConsumer.java"
	 public class AsyncConsumer extends java.lang.Object{
	 com.taobao.metamorphosis.client.MetaClientConfig metaClientConfig;
	 Signature: Lcom/taobao/metamorphosis/client/MetaClientConfig;
	 com.taobao.metamorphosis.utils.ZkUtils$ZKConfig zkConfig;
	 Signature: Lcom/taobao/metamorphosis/utils/ZkUtils$ZKConfig;
	 com.taobao.metamorphosis.client.MessageSessionFactory sessionFactory;
	 Signature: Lcom/taobao/metamorphosis/client/MessageSessionFactory;
	 public AsyncConsumer();
	 Signature: ()V
	 public int init()   throws java.lang.Exception;
	 Signature: ()I
	 public void listen(java.lang.String, java.lang.String)   throws java.lang.Exception;
	 Signature: (Ljava/lang/String;Ljava/lang/String;)V
	 public static void main(java.lang.String[])   throws java.lang.Exception;
	 Signature: ([Ljava/lang/String;)V
	 }
	 */
	const char * classname = "AsyncConsumer";
	jni_cls = (*env)->FindClass(env, classname);
	if (jni_cls == 0) {
		printf("[dbg] JNIENV FindClass[%s] failed, return;\n", classname);
		return -1;
	}
	jobject jni_jobj = (*env)->AllocObject(env, jni_cls);
	printf("[dbg] Executing@LINE%d\n", __LINE__);
	if (jni_jobj == NULL ) {
		printf("[dbg] JNIENV AllocObject<jni_jobj> failed, return;\n");
		return -1;
	}

	printf("[dbg] Initiating jni_jobj at LINE%d\n", __LINE__);
	jmethodID obj_init_mid = (*env)->GetMethodID(env, jni_cls, "init",
			"(Ljava/lang/String;I)I");
	if (obj_init_mid == 0) {
		printf("[dbg] JNIENV GetMethodID<send_msg> failed, return;\n");
		return -1;
	}
	printf("[dbg] JNIENV GetMethodID<send_msg>[%d] obtained, go;\n",
			obj_init_mid);

	jstring zk_hostname = (*env)->NewStringUTF(env, host);
	jint zk_port = (jint) port;
	jint result = (*env)->CallIntMethod(env, jni_jobj, obj_init_mid,
			zk_hostname, zk_port);
	if (check_jvm_exception() != 0) {
		return -1;
	} else {
		printf(
				"[dbg] JNIENV call AsyncConsumer.init done, returned value[%d]\n",
				result);
	}

	jmethodID listen_mid = (*env)->GetMethodID(env, jni_cls, "listen",
			"(Ljava/lang/String;Ljava/lang/String;)V");
	if (listen_mid == 0) {
		printf("[dbg] GetMethodID<listen> failed, return;\n");
		return -1;
	}
	printf("[dbg] AsyncConsumer.listen: MethodID[%d] obtained\n", listen_mid);

	//sorry not working...
	/*status = (*jvm)->AttachCurrentThread(jvm, &env, NULL );
	 if (status < 0) {
	 printf("[dbg] failed to AttachCurrentThread, return");
	 return -1;
	 }
	 printf("[dbg] AttachCurrentThread done\n");*/

	//public void listen(String topic, String group) throws Exception {
	// final String topic = "test";
	// final String group = "meta-example";
	jstring topic_arg = (*env)->NewStringUTF(env, topic);
	jstring group_arg = (*env)->NewStringUTF(env, group);
	(*env)->CallVoidMethod(env, jni_jobj, listen_mid, topic_arg, group_arg);
	if (check_jvm_exception() != 0) {
		(*env)->ExceptionDescribe(env);
		return -1;
		//env->ExceptionClear();
		//env->ThrowNew(env->FindClass("java/lang/Exception"),"xx异常");
	} else {
		printf("[dbg] call CallVoidMethod done, return value[%d]\n", result);
	}

	if ((*env)->MonitorEnter(env, jni_jobj) != JNI_OK) {
		printf("[dbg] MonitorEnter FAILED...\n");
		return -1;
	} else {
		printf("[dbg] MonitorEnter...\n");
		jmethodID wait_mid = (*env)->GetMethodID(env, jni_cls, "wait", "()V");
		if (wait_mid == 0) {
			printf("[dbg] GetMethodID<wait> failed, return;\n");
			return -1;
		}
		(*env)->CallVoidMethod(env, jni_jobj, wait_mid);
		if (check_jvm_exception() != 0) {
			(*env)->ExceptionDescribe(env);
			return -1;
		}

	}

	return 0;

	jmethodID post_msg_method = (*env)->GetStaticMethodID(env, jni_cls,
			"send_msg", "()I");

	if (post_msg_method == 0) {
		printf("[dbg] obtain send_msg method failed!\n");
		return -1;
	} else {
		printf("[dbg] obtain send_msg method done\n");
	}
	printf("[dbg] Executing@LINE%d\n", __LINE__);
	//before call the method
	//attach to the thread first
	//    jint (JNICALL *AttachCurrentThreadAsDaemon)(JavaVM *vm, void **penv, void *args);

	//calling method
	(*env)->CallStaticVoidMethod(env, jni_jobj, post_msg_method);
	//current thread will be blocked...
	printf("[dbg] static void method[send_msg] called");
	if ((*env)->ExceptionCheck(env)) {
		printf("[dbg] ExceptionCheck found...\n");
		printf("[dbg] Let us see what happened...\n");
		(*env)->ExceptionDescribe(env);
		return -1;
		//env->ExceptionClear();
		//env->ThrowNew(env->FindClass("java/lang/Exception"),"xx异常");
	}
	printf("[dbg] message posted...\n");
	printf("[dbg] Executing@LINE%d\n", __LINE__);

	return 0;
}

int stop_metaq_listener() {
	printf("[dbg] shuting down metaq listener\n");
	(*jvm)->DestroyJavaVM(jvm);
	//should we notify?
	return 0;
	int ret = msgctl(msgid, IPC_RMID, NULL );
	if (ret != -1)
		printf("Message queue %d sucessfully removed.\n", msgid);
	return 0;
}

//========================================================
// util function

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	printf("JNI_OnLoad startup~~!\n");
	//public static native void reserved_test_method();
	//Signature: ()V
	const char * classname = "AsyncConsumer";
	if (env == NULL ) {
		//used to eanble standalone jvm
		(*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6);

	}

	jni_cls = (*env)->FindClass(env, classname);
	if (jni_cls == 0) {
		printf("[dbg] JNIENV FindClass[%s] failed, return;\n", classname);
		return -1;
	}

	static JNINativeMethod methods[] = { { "reserved_test_method", "()V",
			&reserved_test_method }, };
	int methodsLenght = sizeof(methods) / sizeof(methods[0]);
	if ((*env)->RegisterNatives(env, jni_cls, methods, methodsLenght) < 0) {
		printf("RegisterNatives failed for '%s'\n", classname);
		return -1;
	} else {
		printf("Native method registered for '%s'\n", classname);
	}

	return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
	printf("call JNI_OnUnload ~~!!\n");
}

char* jstringTostring(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env, "utf-8");
	jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
			strencode);
	jsize alen = (*env)->GetArrayLength(env, barr);
	jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env, barr, ba, 0);
	return rtn;
}

int check_jvm_exception() {
	if ((*env)->ExceptionCheck(env)) {
		printf("[dbg]Exception rised from JVM, dump:\n");
		(*env)->ExceptionDescribe(env);
		return -1;
		//env->ExceptionClear();
		//env->ThrowNew(env->FindClass("java/lang/Exception"),"xx异常");
	}

	return 0;

}

//==============================================================
/*
 * Class:     AsyncConsumer
 * Method:    jni_proc_msg
 * Signature: (ILjava/lang/String;)V
 */JNIEXPORT void JNICALL Java_AsyncConsumer_jni_1proc_1msg(JNIEnv * env,
		jclass jcls, jint msg_type, jstring msg_content) {
	const char* str = (*env)->GetStringUTFChars(env, msg_content, 0);
	if (msg_proc_callback != NULL ) {
		printf("[dbg] msg proc callback function is not NULL\n");
		printf("[dbg] calling\n");
		(*msg_proc_callback)((int) msg_type, str);
	} else {
		printf("[dbg] msg proc callback function is NULL\n");
		printf("[dbg] msg_type is [%d]\n", msg_type);
		//char* cstr = jstringTostring(env, msg_content);
		//printf("[dbg] msg_content is [%s]\n", cstr);
		printf("[dbg] msg_content is [%s]\n", str);
		//free(cstr);

	}

}

//========================================================
//used to post message in jni;
//C process -> internal JVM -JNI-> libtest.so
//in such case, (*msg_proc_callback) will not be set;
JNIEXPORT void JNICALL Java_testjni_post_1msg(JNIEnv * jenv, jclass jcls) {

	if (msg_proc_callback == NULL ) {
		printf("FATAL ERROR: the callback function pointer is null\n");
		return;
	} else {
		printf("the callback function pointer WORKING...\n");
		(*msg_proc_callback)(100, "hello echo...");
	}
	return;

	int msgid, ret;
	//create the message queue with the id MY_MQ_ID
	msgid = msgget(MY_MQ_ID, 0666 | IPC_CREAT);
	if (msgid >= 0)
		printf("Created a Message Queue,message queue identifier is %d\n",
				msgid);
	//modify the size of message queue
	struct msqid_ds buf;
	ret = msgctl(msgid, IPC_STAT, &buf);
	printf("The origianl size of queue is %d\n", buf.msg_qbytes);

	buf.msg_qbytes = 4096;
	ret = msgctl(msgid, IPC_SET, &buf);
	if (ret == 0)
		printf(
				"Size sucessfully changed for queue,message queue identifier is %d\n",
				msgid);
	//send a message
	MY_TYPE_T myMessage;
	myMessage.type = 1L;   //消息的类型,msgrcv会用到
	myMessage.fval = 128.256;
	myMessage.uival = 512;
	strncpy(myMessage.strval, "This is a test.\n", MAX_LINE);
	ret = msgsnd(msgid, (struct msgbuf*) &myMessage, sizeof(MY_TYPE_T), 0); //0是消息旗标
	if (ret != -1)
		printf("Message send successfully.\n");

	//
	/*set_value(777);
	 */
	/*#
	 # A fatal error has been detected by the Java Runtime Environment:
	 #
	 #  SIGSEGV (0xb) at pc=0x0000000000000000, pid=48583, tid=140004926609152
	 #
	 # JRE version: 6.0_24-b24
	 # Java VM: OpenJDK 64-Bit Server VM (20.0-b12 mixed mode linux-amd64 compressed oops)
	 # Derivative: IcedTea6 1.11.5
	 # Distribution: CentOS release 6.3 (Final), package rhel-1.50.1.11.5.el6_3-x86_64
	 # Problematic frame:
	 # C  0x0000000000000000
	 #
	 # An error report file with more information is saved as:
	 # /home/panthera/lab/msg_queue/hs_err_pid48583.log
	 #
	 # If you would like to submit a bug report, please include
	 # instructions how to reproduce the bug and visit:
	 #   http://icedtea.classpath.org/bugzilla
	 # The crash happened outside the Java Virtual Machine in native code.
	 # See problematic frame for where to report the bug.
	 #
	 Aborted (core dumped)*/

}
