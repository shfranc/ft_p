#include "server.h"

int				ret_error(char *message)
{
	log_error(message);
	return (-1);
}

t_ex_ret		ret_failure(char *message)
{
	log_error(message);
	return (FAILURE);
}

char		*ft_strdup2(char *s1, char *s2)
{
	int		len;
	char	*new;

	len = ft_strlen(s1) + ft_strlen(s2);
	new = ft_strnew(len);
	return (ft_strcat(ft_strcpy(new, s1), s2));
}
