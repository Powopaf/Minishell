#ifndef REDIR_H
# define REDIR_H

typedef struct s_redir
{
	t_token_kw		kw;
	char			*file;
	char			*eofkw;
	int				fd_in;
	int				fd_out;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

#endif