#ifndef SERVER_LISTEN_H_
#define SERVER_LISTEN_H_

int server_listen_start_thread(void* arg);
void server_listen_end_thread(int sock);

#endif //SERVER_LISTEN_H_
