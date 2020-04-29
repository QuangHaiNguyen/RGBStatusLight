/* 
 * File:   cli.h
 * Author: haing
 *
 * Created on April 6, 2020, 12:27 AM
 */

#ifndef CLI_H
#define	CLI_H

#include "../common.h"

typedef enum CLI_STATUS{
    CLI_OK = 0,
    CLI_CMD_NOTFOUND,
    CLI_BUFF_FULL,
}CLI_Status;

typedef struct{
	char const *cmd_name;
	void (*function)(void);
}command_t;

CLI_Status CLI_Init(command_t * cmd_table, uint8_t cmd_table_size);
CLI_Status CLI_Deinit(void);
CLI_Status CLI_GetVersion(uint8_t * ver, uint8_t * s_version, uint8_t * ss_version);
CLI_Status CLI_ProccessCommand(void);
CLI_Status CLI_GetChar(char ch);

#endif	/* CLI_H */

