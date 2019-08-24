#include "server.h"

void		cmd_cwd(t_user *user, char **cmd)
{
	char 	*abs_virtual_path;
	char 	*real_path;

	(void)user;
	(void)cmd;
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	
	abs_virtual_path = get_virtual_absolute_path(cmd[1]);
	real_path = convert_path_virtual_to_real(cmd[1]);
	
	send_to_user_ctrl(user, RESP_250);
}
