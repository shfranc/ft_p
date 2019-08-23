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
		perror("execv");
		ft_putendl("execv: error");
		exit(FAILURE);
	}
	else
	{
        wait(&waitstatus);
        ret = WEXITSTATUS(waitstatus);
	}
	return (ret);
}

void		prepare_args(char **args, char *param)
{
	args[0] = LS_PATH;
	args[1] = LS_OPTIONS;
	args[2] = LS_SEP;
	args[3] = param;
	args[4] = NULL;
}

void		cmd_list(t_user *user, char **cmd)
{
	char	*args[5];
	int		ret;

	if (ft_tablen(cmd) > 2)
	{
		close_data_channel(user);
		return (send_to_user_ctrl(user, RESP_501));
	}
	if (user->data_sock != -1)
		send_to_user_ctrl(user, RESP_125);
	else
		return (send_to_user_ctrl(user, RESP_425));
	log_data_str("Sending", "ls output");
	prepare_args(args, cmd[1]);
	ret = exec_cmd(user, args);
	if (ret != 0)
		send_to_user_ctrl(user, RESP_550);
	else
		send_to_user_ctrl(user, RESP_226);
	close_data_channel(user);
}
