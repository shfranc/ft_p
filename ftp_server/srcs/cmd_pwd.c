#include "server.h"

char		*get_client_pwd(char *pwd)
{
	char *start;

	if (ft_strcmp(g_server.root_dir, pwd) == 0)
		return (ft_strdup("/"));
	else
	{
		start = pwd + ft_strlen(g_server.root_dir);
		return (ft_strdup(start));
	}
}

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
	client_pwd = get_client_pwd(pwd);
	msg = ft_strnew(ft_strlen(RESP_257) + ft_strlen(client_pwd) + 1);
	msg = ft_strcat(ft_strcat(ft_strcpy(msg, RESP_257), client_pwd), "\"");
	send_to_user_ctrl(user, msg);
	free(pwd);
	free(client_pwd);
	free(msg);
}
