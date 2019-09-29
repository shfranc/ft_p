#include "client.h"

static char		*get_cwd(char *resp)
{
	char 	*path;

	if (!*resp)
		return (NULL);
	else
	{
		path = ft_strsub(resp, 1, ft_strrchr(resp, '"') - resp - 1);
		printf("got remotecwd as `%s'\n", path);
		return (path);
	}

}

void			cmd_pwd(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") != 0)
		ft_putendl("usage: pwd");
	send_to_server_ctrl("PWD");
	get_server_response();
	if (parse_response(g_client.resp) == RESP_SUCCESS)
	{
		free(g_client.cwd);
		g_client.cwd = get_cwd(ft_strchr(g_client.resp, '"'));
		printf("Remote directory: %s\n", g_client.cwd);
	}
}
