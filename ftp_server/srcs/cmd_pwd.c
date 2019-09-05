#include "server.h"

void		cmd_pwd(t_user *user, char **cmd)
{
	char *pwd;
	char *client_pwd;
	char *msg;

	if (ft_tablen(cmd) > 1)
		return (send_to_user_ctrl(user, RESP_501));
	if (!(pwd = getcwd(NULL, 0)))
	{
		free(pwd);
		return (send_to_user_ctrl(user, RESP_550_1));
	}
	client_pwd = convert_path_real_to_virtual(pwd);
	if (client_pwd)
	{
		msg = ft_strnew(ft_strlen(RESP_257) + ft_strlen(client_pwd) + 1);
		msg = ft_strcat(ft_strcat(ft_strcpy(msg, RESP_257), client_pwd), "\"");
		send_to_user_ctrl(user, msg);
		free(pwd);
		free(client_pwd);
		free(msg);
	}
	else
	{
		send_to_user_ctrl(user, RESP_550_1);

	}
}
