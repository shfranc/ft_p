#include "server.h"

void		update_user_cwd(t_user *user)
{
	char	*real_path;
	char	*virtual_path;

	if (!(real_path = getcwd(NULL, 0)))
	{
		free(real_path);
		log_error("Enable to update user cwd");
		return ;
	}
	virtual_path = convert_path_real_to_virtual(real_path);
	if (!virtual_path)
	{
		log_error("Oups! User has accessed an unauthorized directory.");
		free(real_path);
		return (going_back_to_root_dir(user));
	}
	free(user->cwd);
	user->cwd = virtual_path;
	free(real_path);
	send_to_user_ctrl(user, RESP_250);
}

void		change_directory(t_user *user, char *path)
{
	char	*virtual_path;

	log_info_str("Trying to move to", path);
	virtual_path = convert_path_real_to_virtual(path);
	if (is_valid_path(virtual_path) == FALSE)
	{
		free(virtual_path);
		log_info("Invalid move, no chdir performed.");
		return (send_to_user_ctrl(user, RESP_550_1));
	}
	free(virtual_path);
	if (chdir(path) == 0)
		return (update_user_cwd(user));
	else
		return (send_to_user_ctrl(user, RESP_550_1));
}

void		cmd_cwd(t_user *user, char **cmd)
{
	char 	*abs_virtual_path;
	char 	*real_path;

	if (ft_tablen(cmd) != 2)
		return (send_to_user_ctrl(user, RESP_501));
	abs_virtual_path = get_virtual_absolute_path(user, cmd[1]);
	real_path = convert_path_virtual_to_real(abs_virtual_path);
	change_directory(user, real_path);
	free(abs_virtual_path);
	free(real_path);
	log_info_str("User cwd", user->cwd);
}
