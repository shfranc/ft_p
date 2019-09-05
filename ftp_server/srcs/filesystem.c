#include "server.h"

char		*convert_path_real_to_virtual(char *path)
{
	char *start;

	if (ft_strcmp(g_server.root_dir, path) == 0)
		return (ft_strdup("/"));
	else
	{
		start = path + ft_strlen(g_server.root_dir);
		return (ft_strdup(start));
	}
}

char		*convert_path_virtual_to_real(char *path)
{
	if (ft_strcmp(g_server.root_dir, path) == 0)
		return (ft_strdup("/"));
	else
		return (ft_strdup2(g_server.root_dir, path));
}

char		*get_virtual_absolute_path(t_user *user, char *path)
{
	if (ft_strcmp(user->cwd, path) == 0)
		return (ft_strdup("/"));
	else
		return (ft_strdup2(user->cwd, path));
}
