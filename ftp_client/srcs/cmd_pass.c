#include "client.h"

static void			put_passive_desc(void)
{
	if (g_client.pass == ON)
		ft_putendl("Passive mode: on; fallback to active mode: off.");
	if (g_client.pass == OFF)
		ft_putendl("Passive mode: off; fallback to active mode: off.");
	if (g_client.pass == AUTO)
		ft_putendl("Passive mode: on; fallback to active mode: on.");
}

void			cmd_pass(char *cmd)
{
	char	**params;

	params = ft_strsplit(cmd, ' ');
	ft_puttab(params);
	if (ft_tablen(params) > 2)
		return (ft_putendl("usage: pass [ on | off | auto ]"));
	if (!params[1])
	{
		g_client.pass = (g_client.pass == ON
			|| g_client.pass == AUTO) ? OFF : AUTO;
	}
	else if (params[1] && ft_strcmp(params[1], "on") == 0)
		g_client.pass = ON;
	else if (params[1] && ft_strcmp(params[1], "off") == 0)
		g_client.pass = OFF;
	else if (params[1] && ft_strcmp(params[1], "auto") == 0)
		g_client.pass = AUTO;
	else
		return (ft_putendl("usage: pass [ on | off | auto ]"));
	put_passive_desc();
}
