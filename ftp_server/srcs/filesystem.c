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
	return (path);
}

char		*get_virtual_absolute_path(char *path)
{
	return (path);
}
