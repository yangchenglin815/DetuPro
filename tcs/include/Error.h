#ifndef _TCS_ERROE_H_
#define _TCS_ERROE_H_

#define ERROR_SUCCESS		0
#define ERROR_FAILED		-1

//file operation
#define ERROR_SYSTEM_FILE_ALREADY_OPENED    1001
#define ERROR_SYSTEM_FILE_OPENE             1002
#define ERROR_SYSTEM_FILE_CLOSE             1003
#define ERROR_SYSTEM_FILE_READ              1004
#define ERROR_SYSTEM_FILE_WRITE             1005
#define ERROR_SYSTEM_FILE_EOF               1006
#define ERROR_SYSTEM_FILE_RENAME            1007
#define ERROR_SYSTEM_FILE_SEEK              1008

//config
#define ERROR_SYSTEM_CONFIG_INVALID         1020
#define ERROR_SYSTEM_CONFIG_DIRECTIVE       1021
#define ERROR_SYSTEM_CONFIG_BLOCK_START     1022
#define ERROR_SYSTEM_CONFIG_BLOCK_END       1023
#define ERROR_SYSTEM_CONFIG_EOF             1024

//system
#define ERROR_SOCKET_CREATE                 1030
#define ERROR_SOCKET_SETREUSE               1031
#define ERROR_SOCKET_BIND                   1032
#define ERROR_SOCKET_LISTEN                 1033
#define ERROR_SOCKET_CLOSED                 1034
#define ERROR_SOCKET_GET_PEER_NAME          1035
#define ERROR_SOCKET_GET_PEER_IP            1036
#define ERROR_SOCKET_READ                   1037
#define ERROR_SOCKET_READ_FULLY             1038
#define ERROR_SOCKET_WRITE                  1039
#define ERROR_SOCKET_WAIT                   1040
#define ERROR_SOCKET_TIMEOUT                1041
#define ERROR_SOCKET_CONNECT                1042
#define ERROR_SOCKET_SETOPT					1043
#define ERROR_SOCKET_ERROR					1044

//transcode
#define ERROR_TRASCODE_PARAM_NULL			1060
#define ERROR_TRANSCODE_EXIST				1061
#define ERROR_TRANSCODE_PLAYER_ERROR		1062
#define ERROR_TRANSCODE_ENCODE				1063
#define ERROR_TRANSCODE_PUBLISH				1064

//others
#define ERROR_MESSAGE_REGISTER				3001
#define ERROR_SESSION_CLOSED				3002

#endif
