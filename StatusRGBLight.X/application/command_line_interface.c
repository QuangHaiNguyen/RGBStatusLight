#include "command_line_interface.h"
#include"../cli/cli.h"

static char ch;
void Test1(void);
void Test2(void);
void Test3(void);
CLI_Status cli_stt;

command_t cmd_table[3] = {
        {"test_1", Test1},
		{"test_2", Test2},
        {"test_3", Test3},
};

typedef enum{
    INIT = 0,
    IDLE,
    ERROR,
}CLI_State;

CLI_State state;

void Test1(void)
{
    PRINT_DEBUG("%s","test 1\n");
}
void Test2(void)
{
    PRINT_DEBUG("%s","test 1\n");
}
void Test3(void)
{
    PRINT_DEBUG("%s","test 1\n");
}

void UART2_RXCallback(void)
{
    ch = USART2.RXDATAL;
    USART2.TXDATAL = ch;
    CLI_GetChar(ch);
}

void Command_Line_Task(void)
{
    switch(state){
        case INIT:{
            USART2_SetISRCb(UART2_RXCallback, USART2_RX_CB);
            CLI_Init(cmd_table, 3);
            CLI_GetVersion(&version, &sub_version, &ssub_version);
            PRINT_INFO("CLI version %02d.%02d.%02d\n", version, sub_version,ssub_version);
            state = IDLE;
            break;
        }
        case IDLE:{
            cli_stt = CLI_ProccessCommand();
            if(CLI_CMD_NOTFOUND == cli_stt){
                PRINT_INFO("%s", "command not found\r\n");
            }
            break;
        case ERROR:{
            break;
        }
        default:{
            break;
        }
        }
    }
}