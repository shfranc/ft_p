#include "server.h"

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

t_bool		is_valid_path(char *virtual_path)
{
	char	**steps;
	int		move;
	int		i;

	steps = ft_strsplit(virtual_path, '/');
	move = g_server.tree_lvl;
	i = 0;
	while (steps[i])
	{
		if (ft_strcmp(steps[i], "..") == 0)
			move--;
		else if (move < g_server.tree_lvl
			&& !ft_strstr(g_server.root_dir, steps[i]))
		{
			move = -1;
			break ;
		}
		else
			move++;
		i++;
	}
	ft_freetab(&steps);
	if (move >= g_server.tree_lvl)
		return (TRUE);
	return (FALSE);
}

void		going_back_to_root_dir(t_user *user)
{
	log_info_str("Going back to root dir", g_server.root_dir);
	if (chdir(g_server.root_dir) == 0)
	{
		free(user->cwd);
		user->cwd = ft_strdup("/");
		return (send_to_user_ctrl(user, RESP_250));
	}
	else
	return (send_to_user_ctrl(user, RESP_550_1));
}
