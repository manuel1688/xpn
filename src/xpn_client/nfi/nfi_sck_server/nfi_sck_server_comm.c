/*
 *  Copyright 2020-2024 Felix Garcia Carballeira, Diego Camarmas Alonso, Alejandro Calderon Mateos, Dario Muñoz Muñoz
 *
 *  This file is part of Expand.
 *
 *  Expand is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Expand is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Expand.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* ... Include / Inclusion ........................................... */

#include "nfi_sck_server_comm.h"
#include "socket.h"
#include "xpn_server/xpn_server_conf.h"


/* ... Const / Const ................................................. */


/* ... Global variables / Variables globales ........................ */


/* ... Functions / Funciones ......................................... */

int nfi_sck_server_comm_connect ( char * srv_name, char * port_name, int *out_socket )
{
  struct hostent * hp;
  struct sockaddr_in server_addr;
  int ret, sd, flag, val;
  int connection_socket;

  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] >> Begin\n");

  // Lookup port name
  ret = socket_client_connect(srv_name, &connection_socket);
  if (ret < 0)
  {
    debug_error("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] ERROR: socket connect\n");
    return -1;
  }
  int buffer = SOCKET_ACCEPT_CODE;
  ret = socket_send(connection_socket, &buffer, sizeof(buffer));
  if (ret < 0)
  {
    debug_error("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] ERROR: socket send\n");
    socket_close(connection_socket);
    return -1;
  }
  ret = socket_recv(connection_socket, port_name, XPN_SERVER_MAX_PORT_NAME);
  if (ret < 0)
  {
    debug_error("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] ERROR: socket read\n");
    socket_close(connection_socket);
    return -1;
  }
  socket_close(connection_socket);

  if (ret < 0) {
    printf("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] ERROR: Lookup %s Port %s\n", srv_name, port_name);
    return -1;
  }

  debug_info("[NFI_SCK_SERVER_COMM] ----SERVER = %s PORT = %s\n", srv_name, port_name);

  // Socket...
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sd < 0) {
    perror("socket: ");
    return -1;
  }
  debug_info("[NFI_SCK_SERVER_COMM] ----SERVER = %s PORT = %s ==> %d\n", srv_name, port_name, sd);

  // Set sockopt
  flag = 1;
  ret = setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, & flag, sizeof(flag));
  if (ret < 0) {
    perror("setsockopt: ");
    return -1;
  }

  val = 1024 * 1024; //1 MB
  ret = setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (char * ) & val, sizeof(int));
  if (ret < 0) {
    perror("setsockopt: ");
    return -1;
  }

  val = 1024 * 1024; //1 MB
  ret = setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (char * ) & val, sizeof(int));
  if (ret < 0) {
    perror("setsockopt: ");
    return -1;
  }

  // gethost by name
  hp = gethostbyname(srv_name);
  if (hp == NULL)
  {
    fprintf(stderr, "nfi_sck_server_init: error gethostbyname %s (%s,%s)\n",
    srv_name, srv_name, port_name);
    return -1;
  }

  // Connect...
  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] Connect port %s\n", port_name);

  bzero((char * ) & server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(atoi(port_name));
  memcpy( & (server_addr.sin_addr), hp->h_addr, hp->h_length);

  int connect_retries = 0;
  do
  {
    ret = connect(sd, (struct sockaddr * ) & server_addr, sizeof(server_addr));
    if (ret < 0)
    {
      if (connect_retries == 0)
      {
        char cli_name  [HOST_NAME_MAX];
        gethostname(cli_name, HOST_NAME_MAX);
        printf("----------------------------------------------------------------\n");
        printf("XPN Client %s : Waiting for servers being up and runing...\n", cli_name);
        printf("----------------------------------------------------------------\n\n");
      }
      connect_retries++;
      sleep(2);
    }
  } while(ret < 0 && connect_retries < 1);

  if (ret < 0)
  {
    printf("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] ERROR: connect fails\n");
    return -1;
  }

  *out_socket = sd;

  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_connect] << End\n");

  return ret;
}

int nfi_sck_server_comm_disconnect(int socket) 
{
  int ret;
  int code = XPN_SERVER_DISCONNECT;

  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] >> Begin\n");

  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] Send disconnect message\n");
  ret = socket_send(socket, &code, sizeof(code));
  if (ret < 0) {
    printf("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] ERROR: nfi_sck_server_comm_write_operation fails\n");
    return ret;
  }

  // Disconnect
  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] Disconnect\n");

  ret = socket_close(socket);
  if (ret < 0) {
    printf("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] ERROR: MPI_Comm_disconnect fails\n");
    return ret;
  }

  debug_info("[NFI_SCK_SERVER_COMM] [nfi_sck_server_comm_disconnect] << End\n");

  // Return OK
  return ret;
}
/* ................................................................... */
