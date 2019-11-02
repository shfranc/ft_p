#include "server.h"

int				exec_cmd(t_user *user, char **args)
{
	int		pid;
	int		waitstatus;
	int		ret;

	if ((pid = fork()) < 0)
		return(ret_error("fork: error"));
	if (pid == 0)
	{
		handle_child_signals();
		if (dup2(user->data_sock, STDOUT_FILENO) == -1
			|| dup2(user->data_sock, STDERR_FILENO) == -1)
			exit(ret_error("dup2: error"));
		execv(LS_PATH, args);
		log_error("execv: error");
		exit(FAILURE);
	}
	else
	{
        wait(&waitstatus);
        ret = WEXITSTATUS(waitstatus);
	}
	return (ret);
}

void		prepare_args(char **args, char *path)
{
	args[0] = LS_PATH;
	args[1] = LS_OPTIONS;
	args[2] = LS_SEP;
	args[3] = path;
	args[4] = NULL;
}

static void		list_directory(t_user *user, char *real_path)
{
	char	*args[5];
	char	*virtual_path;

	if (real_path)
	{
		virtual_path = convert_path_real_to_virtual(real_path);
		if (is_valid_path(virtual_path) == FALSE)
		{
			free(virtual_path);
			logger(LOG_INFO, "Invalid move, no ls performed.", NULL);
			return (send_to_user_ctrl(user, RESP_550));
		}
		free(virtual_path);
	}
	prepare_args(args, real_path);
	logger(LOG_DATA,  "Sending ls output", NULL);
	if (exec_cmd(user, args) != 0)
		return (send_to_user_ctrl(user, RESP_550));
	else
		return (send_to_user_ctrl(user, RESP_226));
}

void		cmd_list(t_user *user, char **cmd)
{
	char 	*abs_virtual_path;
	char 	*real_path;

	if (ft_tablen(cmd) > 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock != -1)
		send_to_user_ctrl(user, RESP_125);
	else
		return (send_to_user_ctrl(user, RESP_425));
	abs_virtual_path = NULL;
	real_path = NULL;
	if (cmd[1])
	{
		abs_virtual_path = get_virtual_absolute_path(user, cmd[1]);
		real_path = convert_path_virtual_to_real(abs_virtual_path);
	}
	list_directory(user, real_path);
	abs_virtual_path ? free(abs_virtual_path) : 0;
	real_path ? free(real_path) : 0;
	close_data_channel(user);
	logger(LOG_DATA,  "Output ls sent", NULL);
}
