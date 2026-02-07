#ifndef CLEAN_SHELL_H
# define CLEAN_SHELL_H

#include "../../struct.h"
#include "../../redir.h"

void	clean_prompt(t_shell *shell);
void	clean_redir(t_redir	*redir);
void	clean_shell(t_shell *shell);
void	redir_clear(t_redir **redir, void (*del)(t_redir *));
void	tokens_clear(t_token **token, void (*del)(t_token *));


#endif
