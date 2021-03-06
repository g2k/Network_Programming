/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年03月19日 星期三 17时29分14秒
* 
* FileName:     sock_server.c
* 
* Description:  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/in.h>
#include <string.h>
#include <sys/socket.h>

int main(void)
{
	int sfp,nfp;//两个描述符
	struct sockaddr_in server_addr,client_addr;//服务器地址，客户端地址
	int sin_size;//???
	unsigned short portnum = 0x8888;//服务器使用端口

	printf("Here's a socket server\n");
	sfp = socket(AF_INET, SOCK_STREAM,0);
	if(sfp == -1)
	{
		printf("SOCKET FAILED\n");
		exit(1);
	}
	printf("SOCKET SUCCEED\n");

	/*设置监听的端口和IP信息*/
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(portnum);
	
	/*bind() 端口绑定函数*/
	if(-1 == bind(sfp,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))
	{
		printf("BIND FAILED\n");
		exit(1);
	}
	printf("BIND SUCCEED\n");
	
	/*listen 监听端口函数*/
	if(-1 == listen(sfp,5))
	{
		printf("LISTEN FAILED\n");
		exit(1);
	}
	printf("LISTEN SUCCEED\n");

	sin_size = sizeof(struct sockaddr_in);
	/*服务端accept函数，调用即进入阻塞状态，等待用户连接。
	 *在没有用户进行连接时，程序停在此处。
	 *此处accpet的第二个参数用于获取客户端的端口和地址信息。
	 */
	nfp = accept(sfp,(struct sockaddr *)(&client_addr),&sin_size);
	if(nfp == -1)
	{
		printf("ACCEPT FAILED\n");
		exit(1);
	}
	printf("ACCEPT SUCCEED\nSERVER START GET CONNECT FROM %#x\n",ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));

	/*函数向客户端使用write函数发送信息，也可以尝试使用其他函数实现*/
	if(-1 == write(nfp,"SOCKET CONNECTED,WELCOME!\n",30))
	{
		printf("WRITE FAILED\n");
		exit(1);
	}
	printf("WRITE SUCCEED\n");
	close(nfp);
	close(sfp);
	
	return 0;
}
