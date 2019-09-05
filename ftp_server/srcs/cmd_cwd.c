#include "server.h"

void		change_directory(t_user *user, char *path)
{
	log_info_str("moving to", path);
	send_to_user_ctrl(user, RESP_250);
}

void		cmd_cwd(t_user *user, char **cmd)
{
	char 	*abs_virtual_path;
	char 	*real_path;

	(void)user;
	(void)cmd;
	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	
	abs_virtual_path = get_virtual_absolute_path(user, cmd[1]);
	real_path = convert_path_virtual_to_real(abs_virtual_path);
	change_directory(user, real_path);
	user->cwd = convert_path_real_to_virtual(real_path);
	log_info_str("new cwd", user->cwd);
}
