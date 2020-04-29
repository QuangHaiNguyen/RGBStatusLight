#include "cli.h"
#include <string.h>

#define VERSION         0
#define SUB_VERSION     99
#define S_SUB_VERSION   0


static char cmd_buff[20];
static bool cmd_found = false;
static uint8_t  buff_count = 0;
static command_t * cmd_table_ptr = NULL;
static uint8_t table_size = 0;


CLI_Status CLI_GetVersion(uint8_t * ver, uint8_t * s_version, uint8_t * ss_version)
{
    * ver = VERSION;
    * s_version = SUB_VERSION;
    * ss_version = S_SUB_VERSION;
    return CLI_OK;
}
CLI_Status CLI_Init(command_t * cmd_table, uint8_t cmd_table_size)
{
    cmd_table_ptr = cmd_table;
    table_size = cmd_table_size;
    
    return CLI_OK;
}

CLI_Status CLI_ProccessCommand(void)
{
    if(cmd_found){
        for(uint8_t i = 0; i < table_size; i++){
            if(strcmp(cmd_table_ptr[i].cmd_name, cmd_buff ) == 0){
                cmd_table_ptr[i].function();
                buff_count = 0;
                memset(cmd_buff, 0, 20);
                cmd_found = false;
                return CLI_OK;
            }
        }
        buff_count = 0;
        memset(cmd_buff, 0, 20);
        cmd_found = false;
        return CLI_CMD_NOTFOUND;
    }
    return CLI_OK;  
}

CLI_Status CLI_GetChar(char ch)
{
    //waiting for cartridge return to process the command  
    if('\n' == ch || '\r' == ch){
        cmd_found = true;
        return CLI_OK;
    }
    else{
        //buffer full, dump it by invoking process command
        if(buff_count == 20){
            cmd_found = true;
            return CLI_BUFF_FULL;
        }
        else{
            //saved received character
            cmd_buff[buff_count] = ch;
            ++buff_count;
            return CLI_OK;
        }
    }
    return CLI_OK;
}

CLI_Status CLI_Deinit(void)
{
    cmd_table_ptr = NULL;
    table_size = 0;
    
    return CLI_OK;
}