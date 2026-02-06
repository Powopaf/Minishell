#ifndef LIBFT_H
# define LIBFT_H

#include <stddef.h>

/**
 * Writes a string to a file descriptor.
 * @param {const char*} s - String to write.
 * @param {int} fd - File descriptor.
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * Writes a string followed by a newline to a file descriptor.
 * @param {const char*} s - String to write.
 * @param {int} fd - File descriptor.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * Joins two strings into a new allocated string.
 * @param {const char*} s1 - Prefix string.
 * @param {const char*} s2 - Suffix string.
 * @returns {char*} Joined string.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * Computes the length of a string.
 * Iterates over the characters of `s` until a null terminator is found.
 * @param {char*} s - Null-terminated string.
 * @returns {size_t} Number of characters before '\0'.
 */
size_t	ft_strlen(const char *s);

/**
 * Joins a char to a string into a new allocated string.
 * Position 0 : put char at the beginning of the string ; 1 : at the end ;
 * Param 0 : don't free input string ; * 1 : free input string ;
 * @param { char**} s1 - string.
 * @param { char} c - char to add.
 * @param {int} param - indication free
 * @returns {char*} Joined string.
 * @warning string is freed even if malloc failed
 */
char	*ft_strjoin_char(char *s1, char c, int position, int param);

/**
 * Joins a char to a string into a new allocated string.
 * Position 0 : put char at the beginning of the string ; 1 : at the end ;
 * Param 0 : don't free input string ;
 * 1 : free input string ;
 * @param { char**} s1 - string.
 * @param { char} c - char to add.
 * @param {int} param - indication on strings to free
 * @returns {char*} Joined string.
 * @warning string is freed even if malloc failed
 */
char	*ft_strjoin_char_p(char **s1, char c, int position, int param);

/**
 * Duplicates an array of strings.
 * Allocates memory and copies the node of `s`.
 * Free and returns null if malloc error.
 * Protected if s null.
 * @param {const char**} s - array of strings to duplicate.
 * @returns {char**} Newly allocated copy of the string.
 */
char	**ft_strsdup(char **s);

/**
 * Searches for the last occurrence of a character in a string.
 * @param {const char*} s - String to search.
 * @param {int} c - Character to locate.
 * @returns {char*} Pointer to match or NULL.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Free a NULL terminated array of strings,
 * created with split for instance.
 * @param {char ***s} - array of strings, NULL terminated
 */
void	ft_free_array_strs(char ***s);

#endif
