#include "shell.h"

int print_env_list(info_t *info)
{
	print_list_str(info->env_list);
	return (0);
}

char *get_env_var(info_t *info, const char *var_name)
{
	list_t *node = info->env_list;
	char *var_value;

	while (node)
	{
		var_value = starts_with(node->str, var_name);
		if (var_value && *var_value)
			return (var_value);
		node = node->next;
	}
	return (NULL);
}

int set_env_var(info_t *info)
{
	if (info->arg_count != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (add_env_var(info, info->args[1], info->args[2]))
		return (0);
	return (1);
}

int unset_env_var(info_t *info)
{
	int i;

	if (info->arg_count == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->arg_count; i++)
		remove_env_var(info, info->args[i]);

	return (0);
}

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env_list = node;
	return (0);
}

