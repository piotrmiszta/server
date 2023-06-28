#include "client_connection.h"
#include "server_defs.h"
#include "client_defs.h"
#include "messages.h"
#include "error_codes.h"
#include "client_connection_cfm.h"
#include "client_connection_rej.h"
#include "client_connection_req.h"
#include <utility.h>
#include <threads.h>
#include <unistd.h>
#include <stdio.h>

static MessageS* client_connection_parse_msg(MessageS* msg_in, ServerConnectionS* client);
static bool client_connection_auth(int sock);
int client_connection_start_thread(void* arg) {
    ServerConnectionS* client = arg;
    /* do it before loop, we dont need to reg client, he must be hard register only check login and pass */

    /* ITS ONE THING THAT CLIENT MUST SEND INFO, LOGIN PASS EXACTLY WHEN HE JOIN TO THE SERVER */
    if( client_connection_auth(client->sock) == true) {
        LOG_INFO("Authentiaction successfull");
    }
    else {
        client->thread_run = false;
        LOG_INFO("Authentication failed! Ending thread");
    }
    while(client->thread_run) {
        /* RECV MSG */
        MessageS* msg_in = messages_read(client->sock);
        if(!msg_in) {
            LOG_ERROR("Msg is null pointer");
            client->thread_run = false;
            break;
        }
        /* CREATE MSG TO SEND */
        MessageS* msg_out = client_connection_parse_msg(msg_in, client);
        if(msg_out) {
            messages_write(client->sock, msg_out);
        }
        /* FREE MSGS */
        messages_free(msg_in);
        messages_free(msg_out);
        sleep(2);
    }
    return 0;
}

MessageS* client_connection_parse_msg(MessageS* msg_in, ServerConnectionS* client) {
    MessageS* msg_out;
    switch(msg_in->header.msg_type) {
        case MESSAGE_TYPE_REQ:
            LOG_TRACE("Get msg req");
            msg_out = client_connection_req(msg_in, client);
            break;
        case MESSAGE_TYPE_CFM:
            LOG_TRACE("Get msg cfm");
            msg_out = client_connection_cfm(msg_in, client);
            break;
        case MESSAGE_TYPE_REJ:
            LOG_TRACE("Get msg rej");
            msg_out = client_connection_rej(msg_in, client);
            break;
    }
    return msg_out;
}

MessageS* client_connection_parse_req(MessageS* msg_in) {
    MessageS* msg_out = messages_alloc(MSG_SIZE(sizeof(uint16_t)));
    uint16_t test = 100;
    messages_set_payload(msg_out, &test, sizeof(test));
    return msg_out;
}

MessageS* client_connection_parse_cfm(MessageS* msg_in) {
    return NULL;
}

MessageS* client_connection_parse_rej(MessageS* msg_in) {
    return NULL;
}

static bool client_connection_auth(int sock) {
    /* expected login and pass in msg so read it */
    MessageS* msg = messages_read(sock);
    /* if readed check login and pass */
    if(msg) {
        bool ret = true;
        ClientAuthS auth;
        messages_get_payload(msg, &auth);
        FILE* file = fopen("users.txt", "r");
        if(!file) {
            LOG_ERROR("Can't open file with user data, 'users.txt' %s", print_err());
            return false;
        }
        char login[LOGIN_SIZE];
        char pass[PASS_SIZE];
        while(!feof(file)) {
            for(int i = 0; i < 20; i++) {
                fscanf(file,"%d", (int*)(&login[i]));
            }
            for(int i = 0; i < 20; i++) {
                fscanf(file,"%d",(int*)(&pass[i]));
            }

            /* strcmp expected login and pass */
            for(int i = 0; i < LOGIN_SIZE; i++) {
                if(login[i] != auth.login[i]) {
                    ret = false;
                }
            }
            if(ret == true) {
                for(int i = 0; i < LOGIN_SIZE; i++) {
                    if(pass[i] != auth.pass[i]) {
                        ret = false;
                    }
                }
            }
            if(ret == true) {
                fclose(file);
                messages_free(msg);
                return true;
            }
        }
        fclose(file);
        messages_free(msg);
        return false;
    }
    else {
        LOG_ERROR("Msg is null pointer!!!");
        return false;
    }

}