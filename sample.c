/*
 * main.c
 *
 *  Created on: Apr 11, 2013
 *      Author: Administrator
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#include "metaq_clib.h"

#define _NEWLINE_ "\n"

#define MAX_LINE 80
#define MY_MQ_ID 1233
typedef struct {
	long type;
	float fval;
	unsigned int uival;
	char strval[MAX_LINE + 1];
} MY_TYPE_T;

//example callback function:
int proc_msg(int msg_type, const char msg[]) {
	printf("[dbg] proc_msg receive message of type[%d], msg[%s]\n", msg_type,
			msg);
	switch (msg_type) {
	case CREATE_DATABASE:
		printf("Msg(CREATE_DATABASE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALTER_DATABASE:
		printf("Msg(ALTER_DATABASE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALTER_DATABASE_ATTR:
		printf("Msg(ALTER_DATABASE_ATTR)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case DROP_DATABASE:
		printf("Msg(DROP_DATABASE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case CREATE_TABLE:
		printf("Msg(CREATE_TABLE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case RENAME_TABLE:
		printf("Msg(RENAME_TABLE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALTER_TABLE_DATA_DIST:
		printf("Msg(ALTER_TABLE_DATA_DIST)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case ALTER_TABLE_PART_FORMAT:
		printf("Msg(ALTER_TABLE_PART_FORMAT)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case ALTER_TABLE_DROP_COLUMN:
		printf("Msg(ALTER_TABLE_DROP_COLUMN)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case ALTER_TABLE_RENAME_COLUMN:
		printf("Msg(ALTER_TABLE_RENAME_COLUMN)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case ALTER_TABLE_RETYPE_COLUMN:
		printf("Msg(ALTER_TABLE_RETYPE_COLUMN)[%d] with Action[%s]\n", msg_type,
				msg);
		break;


	case NEW_PART:
		printf("Msg(NEW_PART)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_PART:
		printf("Msg(ALERT_PART)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case DROP_PART:
		printf("Msg(DROP_PART)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_PART_ADD_FILE:
		printf("Msg(ALERT_PART_ADD_FILE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_PART_ALTER_FILE:
		printf("Msg(ALERT_PART_ALTER_FILE)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case PART_FILE_REP_CHANGE:
		printf("Msg(PART_FILE_REP_CHANGE)[%d] with Action[%s]\n", msg_type,
				msg);
		break;

	case PART_FILE_STATUS_CHANGE:
		printf("Msg(PART_FILE_STATUS_CHANGE)[%d] with Action[%s]\n", msg_type,
				msg);
		break;

	
	case FILE_REP_ONOFF_LINE_CHANGE:
		printf("Msg(FILE_REP_ONOFF_LINE_CHANGE)[%d] with Action[%s]\n",
				msg_type, msg);
		break;
	case ALERT_PART_DROP_FILE:
		printf("Msg(ALERT_PART_DROP_FILE)[%d] with Action[%s]\n", msg_type,
				msg);
		break;

	case CREATE_COLUMN_IDX:
		printf("Msg(CREATE_COLUMN_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_COLUMN_IDX:
		printf("Msg(ALERT_COLUMN_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_COLUMN_IDX_ATTR:
		printf("Msg(ALERT_COLUMN_IDX_ATTR)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case DROP_COLUMN_IDX:
		printf("Msg(DROP_COLUMN_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case NEW_PART_IDX:
		printf("Msg(NEW_PART_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALERT_PART_IDX:
		printf("Msg(ALERT_PART_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;

	case DROP_PART_IDX:
		printf("Msg(DROP_PART_IDX)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case NEW_PART_IDX_FILE:
		printf("Msg(NEW_PART_IDX_FILE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	case ALTER_PART_IDX_FILE:
		printf("Msg(ALTER_PART_IDX_FILE)[%d] with Action[%s]\n", msg_type, msg);
		break;

	case PART_IDX_FILE_REP_CHANGE:
		printf("Msg(PART_IDX_FILE_REP_CHANGE)[%d] with Action[%s]\n", msg_type,
				msg);
		break;
	case PART_IDX_FILE_STATUS_CHANGE:
		printf("Msg(PART_IDX_FILE_STATUS_CHANGE)[%d] with Action[%s]\n",
				msg_type, msg);
		break;

	case PART_IDX_FILE_ONOFF_LINE_CHANGE:
		printf("Msg(PART_IDX_FILE_ONOFF_LINE_CHANGE)[%d] with Action[%s]\n",
				msg_type, msg);
		break;

	case DROP_PART_IDX_FILE:
		printf("Msg(DROP_PART_IDX_FILE)[%d] with Action[%s]\n", msg_type, msg);
		break;

	case NEW_NODE:
		printf("Msg(NEW_NODE)[%d] with Action[%s]\n", msg_type, msg);
		break;

	case DROP_NODE:
		printf("Msg(DROP_NODE)[%d] with Action[%s]\n", msg_type, msg);
		break;

	case NODE_FAILED:
		printf("Msg(NODE_FAILED)[%d] with Action[%s]\n", msg_type, msg);
		break;

	default:
		printf("Msg(UNKNOWN CODE)[%d] with Action[%s]\n", msg_type, msg);
		break;
	}

	return 0;
}

int main(int argc, char **argv) {

	const char* metaq_host = "localhost";
	const int metaq_port = 12181;
	printf("[dbg] tracing at LINE%d\n", __LINE__);
	set_msg_proc_callback(&proc_msg);
	set_topic("test");
	printf("[dbg] tracing at LINE%d\n", __LINE__);
	set_group("meta-example");

	int result = start_metaq_listener(metaq_host, metaq_port);

	return result;

}
