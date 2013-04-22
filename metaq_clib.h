/*
 * test.h
 *
 *  Created on: Apr 11, 2013
 *      Author: Administrator
 */

#ifndef TEST_H_
#define TEST_H_

//for debug
void set_value(int para);
int get_value();

void set_msg_proc_callback(int (*para)(int msg_type, const char msg[]));
int start_metaq_listener(const char host[], const int port);
int stop_metaq_listener();
void set_topic(const char* topic_para);
void set_group(const char* topic_para);


/*
 * MSG_ID	LONG		消息ID
 DB_ID	LONG		库ID
 NODE_ID	LONG		节点ID
 ENENT_ID	LONG		事件类型
 EVENT_TIME	DATE		事件发生事件
 EVENT_HANDLER	STRING		事件处理函数（可能为空）
 MSG_DATA	STRING		事件内容（可能为空）
 *
 */
//const define
#define MSG_ID
#define DB_ID
#define NODE_ID
#define ENENT_ID
#define EVENT_TIME
#define EVENT_HANDLER
#define MSG_DATA

#define CREATE_DATABASE 			1001
#define ALTER_DATABASE 				1002
#define ALTER_DATABASE_ATTR 		1003
#define DROP_DATABASE		 		1004


#define CREATE_TABLE		 		1101
#define RENAME_TABLE		 		1102
#define ALTER_TABLE_DATA_DIST		1103
#define ALTER_TABLE_PART_FORMAT	 	1104
#define ALTER_TABLE_DROP_COLUMN		1201
#define ALTER_TABLE_ADD_COLUMN		1202
#define ALTER_TABLE_RENAME_COLUMN	1203
#define ALTER_TABLE_RETYPE_COLUMN	1204
//#define ALTER_TABLE_DROP_COLUMN		1205

#define NEW_PART		 				1301
#define ALERT_PART		 				1302
#define DROP_PART						1303
#define ALERT_PART_ADD_FILE				1304
#define ALERT_PART_ALTER_FILE			1305
#define PART_FILE_REP_CHANGE			1306
#define PART_FILE_STATUS_CHANGE			1307
#define FILE_REP_ONOFF_LINE_CHANGE		1308
#define ALERT_PART_DROP_FILE		 	1309

#define CREATE_COLUMN_IDX	 			1401
#define ALERT_COLUMN_IDX		 		1402
#define ALERT_COLUMN_IDX_ATTR		 	1403
#define DROP_COLUMN_IDX		 			1404
#define NEW_PART_IDX		 			1405
#define ALERT_PART_IDX		 			1406
#define DROP_PART_IDX			 		1407
#define NEW_PART_IDX_FILE		 		1408
#define ALTER_PART_IDX_FILE	 			1409

#define PART_IDX_FILE_REP_CHANGE		1410
#define PART_IDX_FILE_STATUS_CHANGE		1411
#define PART_IDX_FILE_ONOFF_LINE_CHANGE	1412
#define DROP_PART_IDX_FILE		 		1413

#define NEW_NODE	 					1501
#define DROP_NODE				 		1502
#define NODE_FAILED				 		1503


#endif /* TEST_H_ */
