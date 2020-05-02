/*******************************************************************************
* Title                 :   winc1500 tcp server component   
* Filename              :   winc1500_tcp_server.c
* Author                :   Quang Hai Nguyen
* Origin Date           :   26.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** SOURCE REVISION LOG *****************************************
*
*  Date         Version     Author              Description 
*  26.04.2020   0.0.99       Quang Hai Nguyen    Initial Release.
*  01.05.2020   0.0.99       Quang Hai Nguyen    Modify ReOpen function to ErrorHandler function 
*
*******************************************************************************/
/** @file  winc1500_tcp_server.c
 *  @brief This is the source file for winc1500 tcp server component
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "winc1500_tcp_server.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/** \brief server socket id */
SOCKET tcp_server_socket;

/** \brief client socket id */
SOCKET tcp_client_socket;

/** \brief pointer to read data buffer */
uint8_t * read_data;

/** \brief pointer to write buffer */
uint8_t * write_data;

/** \brief size of read and write buffer, read and write buffer have the same size */
uint16_t size;

/** \brief size of read and write buffer, read and write buffer have the same size */
void (*read_cb)(void);

/** \brief store the server configuration */
static struct sockaddr_in addr;

/** \brief store the status of the server */
static TCP_Server_Status status;

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg);
static void WINC1500_TCPServerErrorHandler(TCP_Server_Status status);

/******************************************************************************
* Function : WINC1500_TCPServerOpen
*//** 
* \b Description:
*
* This function initializes a TCP server. Under the hood, the function allocates
* memory for read write buffer, initialize the socket library from winc1500 
*
* PRE-CONDITION: Underlying hardware must be initialized
*
* POST-CONDITION: None
* 
* @param    port: (IN) port of the server
* @param    **socket_read_data: (OUT) pointer to the read buffer
* @param    **socket_write_data: (OUT) pointer to the write data
* @param    socket_data_size: (IN) size of the buffer
* @param    *ip: (OUT) address of the server, not used
* @return   TCP server status
*
* \b Example Example:
* @code
* uint8_t *read_data;
* uint8_t *write_data;
* uint32_t ip;
* WINC1500_TCPServerOpen(13000, &read_data, &write_data, 32, &ip);
* @endcode
*
* @see WINC1500_TCPServerOpen
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerOpen( uint16_t port,
                                uint8_t **socket_read_data,
                                uint8_t **socket_write_data,
                                uint16_t socket_data_size,
                                uint32_t *ip)
{
    //store size locally
    size = socket_data_size;
    
    //allocate memory for read and write buffer
    read_data = (uint8_t*)malloc(size *sizeof(uint8_t));
    if(read_data == NULL)
    {
        return TCP_SERVER_NOT_MEMO;
    }
    
    write_data = (uint8_t*)malloc(size *sizeof(uint8_t));
    if(write_data == NULL)
    {
        return TCP_SERVER_NOT_MEMO;
    }
    
    /* Initialize socket address structure. */
	addr.sin_family      = AF_INET;
	addr.sin_port        = _htons(port);
	addr.sin_addr.s_addr = 0;
    
    //Initialize socket
    socketInit();
    registerSocketCallback(socket_cb, NULL);
    
    //create service
    if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        PRINT_ERROR("%s", "socket create error!\r\n");
        return TCP_SERVER_OPEN_ERR;
    }

    /* Bind service*/
    bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    
    //return pointer to ip address, read buffer and write buffer
    *ip = (uint32_t)addr.sin_addr.s_addr;
    *socket_read_data = read_data;
    *socket_write_data = write_data;
    
    

    return TCP_SERVER_OK;
}

/******************************************************************************
* Function : WINC1500_TCPServerClose
*//** 
* \b Description:
*
* This function close the socket and free the resources 
*
* PRE-CONDITION: Underlying hardware must be initialized
*
* POST-CONDITION: None
* 
* @param    None
* @return   TCP server status
*
* \b Example Example:
* @code
* WINC1500_TCPServerClose();
* @endcode
*
* @see WINC1500_TCPServerClose
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerClose()
{
    close(tcp_server_socket);
    close(tcp_client_socket);
    socketDeinit();
    tcp_client_socket = -1;
    tcp_server_socket = -1;
    free(read_data);
    free(write_data);
    return TCP_SERVER_OK;
}

/******************************************************************************
* Function : WINC1500_TCPServerWrite
*//** 
* \b Description:
*
* This function sends the data thru socket
*
* PRE-CONDITION: server must be initialized. user must modify the write buffer
* before send the data. pointer to the write buffer is obtained in the 
* initialize function.
*
* POST-CONDITION: None
* 
* @param    num_of_byte: (IN)number of data will be sent
* @return   TCP server status
*
* \b Example Example:
* @code
* uint8_t *read_data;
* uint8_t *write_data;
* uint32_t ip;
* WINC1500_TCPServerOpen(13000, &read_data, &write_data, 32, &ip);
* memset(write_data, "hello client", 12);
* WINC1500_TCPServerWrite(12);//send 12 bytes
* @endcode
*
* @see WINC1500_TCPServerOpen
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerWrite(uint16_t num_of_byte)
{
    if(SOCK_ERR_NO_ERROR != send(tcp_client_socket, write_data, num_of_byte, 0)){
        return TCP_SERVER_WRITE_ERR;
    }
    return 0;
}

/******************************************************************************
* Function : WINC1500_TCPServerRead
*//** 
* \b Description:
*
* This function receives the data thru socket
*
* PRE-CONDITION: server must be initialized. user must read the read buffer
* to obtain the data. Pointer to the read buffer is obtained in the 
* initialize function.
*
* POST-CONDITION: None
* 
* @param    num_of_byte: (IN)number of data will be received
* @return   TCP server status
*
* \b Example Example:
* @code
* uint8_t *read_data;
* uint8_t *write_data;
* uint32_t ip;
* WINC1500_TCPServerOpen(13000, &read_data, &write_data, 32, &ip);
* WINC1500_TCPServerRead(3);//receive 3 bytes
* printf("%s\n", read_data);
* @endcode
*
* @see WINC1500_TCPServerOpen
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerRead(uint16_t num_of_byte)
{
    //clean up the  buffer before operating
    //memset(read_data, 0, 32);
    if(SOCK_ERR_NO_ERROR != recv(tcp_client_socket, read_data, num_of_byte, 0)){
        return TCP_SERVER_READ_ERR;
    }
    return TCP_SERVER_OK;
}

/******************************************************************************
* Function : WINC1500_TCPServerSetCallback
*//** 
* \b Description:
*
* This function set the callback for the message receive event. We implement
* the callback to handle the data received from the client
*
* PRE-CONDITION: server must be initialized.
*
* POST-CONDITION: None
* 
* @param    cb: (IN)callback function
* @return   TCP server status
*
* \b Example Example:
* @code
* uint8_t *read_data;
* uint8_t *write_data;
* uint32_t ip;
* TCPServer_cb_t callback(void);
* WINC1500_TCPServerOpen(13000, &read_data, &write_data, 32, &ip);
* WINC1500_TCPServerSetCallback(callback);
* @endcode
*
* @see WINC1500_TCPServerOpen
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerSetCallback(TCPServer_cb_t  cb)
{
    read_cb = cb;
    return TCP_SERVER_OK;
}

/******************************************************************************
* Function : WINC1500_TCPServerErrorHandler
*//** 
* \b Description:
*
* This function restart the serve again. In case of error, we call this function 
* to reset the server. This function is executed in the socket call back function.
*
* PRE-CONDITION: Internal use
*
* POST-CONDITION: None
* 
* @param    status: the status of the server (focus only on the error status)
* @return   None
*
*
* @see WINC1500_TCPServerErrorHandler
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Change interface implementation </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
static void WINC1500_TCPServerErrorHandler(TCP_Server_Status status)
{
    switch(status){
        case TCP_SERVER_OK:
        case TCP_SERVER_NOT_MEMO:
        case TCP_SERVER_OPEN_ERR:
            //do nothing, take care by the application
            break;
        case TCP_SERVER_WRITE_ERR:
            break;
        case TCP_SERVER_READ_ERR:
            //take it as disconnect
            PRINT_DEBUG("%s", "client discconnect\r\n");
            close(tcp_client_socket);
            tcp_client_socket = -1;
            break;
        case TCP_SERVER_BIND_ERR:
            PRINT_DEBUG("%s", "socket bind error!\r\n");
            WINC1500_TCPServerClose();
            status = TCP_SERVER_BIND_ERR;
            break;
        case TCP_SERVER_LISTEN_ERR:
            PRINT_DEBUG("%s", "socket listen error!\r\n");
            WINC1500_TCPServerClose();
            status = TCP_SERVER_LISTEN_ERR;
            break;
        case TCP_SERVER_ACCEPT_ERR:
            PRINT_DEBUG("%s", "socket_cb: accept error!\r\n");
            close(tcp_client_socket);
            tcp_client_socket = -1;
            break;
        default:
            break;
    }
}

/******************************************************************************
* Function : WINC1500_TCPServerGetStatus
*//** 
* \b Description:
*
* This function returns the status of the server
*
* PRE-CONDITION: server must be initialized.
*
* POST-CONDITION: None
* 
* @param    None
* @return   TCP server status
*
* \b Example Example:
* @code
* uint8_t *read_data;
* uint8_t *write_data;
* uint32_t ip;
* TCP_Server_Status status;
* 
* TCPServer_cb_t callback(void);
* 
* WINC1500_TCPServerOpen(13000, &read_data, &write_data, 32, &ip);
* WINC1500_TCPServerSetCallback(callback);
* status = WINC1500_TCPServerGetStatus();
* @endcode
*
* @see WINC1500_TCPServerOpen
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
TCP_Server_Status WINC1500_TCPServerGetStatus(void)
{
    return status;
}

/******************************************************************************
* Function : socket_cb
*//** 
* \b Description:
*
* Call back function for the socket server
*
* PRE-CONDITION: Internal use
*
* POST-CONDITION: None
* 
* @param    None
* @return   None
*
*
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 26.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
    switch (u8Msg) {
	/* Socket bind */
	case SOCKET_MSG_BIND: {
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			PRINT_DEBUG("%s", "socket bind success!\r\n");
            listen(tcp_server_socket, 0);
		} else {
            WINC1500_TCPServerErrorHandler(TCP_SERVER_BIND_ERR);
		}
	} break;

	/* Socket listen */
	case SOCKET_MSG_LISTEN: {
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			PRINT_DEBUG("%s", "socket listen success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
            WINC1500_TCPServerErrorHandler(TCP_SERVER_LISTEN_ERR);
		}
	} break;

	/* Connect accept */
	case SOCKET_MSG_ACCEPT: {
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			PRINT_DEBUG("%s", "socket accept success!\r\n");
			tcp_client_socket = pstrAccept->sock;
            WINC1500_TCPServerRead(size);
		} else {		
            status = TCP_SERVER_ACCEPT_ERR;
            WINC1500_TCPServerErrorHandler(status);
		}
	} break;

	/* Message send */
	case SOCKET_MSG_SEND: {
		PRINT_DEBUG("%s", "socket send success!\r\n");
	} break;

	/* Message receive */
	case SOCKET_MSG_RECV: {
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			PRINT_DEBUG("%s", "socket recv success!\r\n");
            if (read_cb != NULL)
                (*read_cb)();
            WINC1500_TCPServerRead(size);
		} else {
            WINC1500_TCPServerErrorHandler(TCP_SERVER_READ_ERR);
        }
	break;
    }
	default:
		break;
	}
}
/*** End of File **************************************************************/
