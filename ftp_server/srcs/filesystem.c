#include "server.h"

char		*convert_path_real_to_virtual(char *path)
{
	char *start;

	if (ft_strcmp(g_server.root_dir, path) == 0)
		return (ft_strdup("/"));
	else if (ft_strlen(g_server.root_dir) < ft_strlen(path))
	{
		start = path + ft_strlen(g_server.root_dir);
		return (ft_strdup(start));
	}
	else
		return (NULL);
}

char		*convert_path_virtual_to_real(char *path)
{
	if (ft_strcmp("/", path) == 0)
		return (ft_strdup(g_server.root_dir));
	else
		return (ft_strdup2(g_server.root_dir, path));
}

char		*get_virtual_absolute_path(t_user *user, char *path)
{
	char	*tmp;

	if (ft_strcmp(user->cwd, path) == 0)
		return (ft_strdup("/"));
	if (ft_strcmp(".", path) == 0)
		return (ft_strdup(user->cwd));
	else
	{
		if (ft_strlen(user->cwd) > 1
			&& user->cwd[ft_strlen(user->cwd) - 1] != '/')
		{
			tmp = user->cwd;
			user->cwd = ft_strdup2(user->cwd, "/");
			free(tmp);
		}
		return (ft_strdup2(user->cwd, path));
	}
}

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
	free(user->cwd);
	virtual_path = convert_path_real_to_virtual(real_path);
	if (!virtual_path)
	{
		user->cwd = real_path;
		log_error("Oups! User has accessed an unauthorized directory...");
		return ;
	}
	user->cwd = virtual_path;
	free(real_path);
}
