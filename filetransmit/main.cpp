#include "../lm_def.h"
#include "../lm_public.h"
#include "../socket.h"


int ft_server; //tcp server accept
int ft_control;
int ft_ui;  //check file send progress

void filetransmit_init()
{
    ft_control = create_udp_socket(FT_CONTROL_PORT);
    ft_ui = create_udp_socket(FT_UI_PORT);
    ft_server = create_server(FT_PORT, "127.0.0.1", 250);
}

void filetransmit_run();


int main()
{
    filetransmit_init();
    filetransmit_run();
    return 0;
}
