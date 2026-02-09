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

/**
 * Splits a string by a delimiter into an array.
 * Allocates a NULL-terminated array containing the substrings
 * of `s` separated by the character `c`.
 * @param {const char*} s - String to split.
 * @param {char} c - Delimiter.
 * @returns {char**} Array of substrings or NULL.
 */
char	**ft_split(char const *s, char c);

/**
 * Joins two strings into a new allocated string.
 * Param indicate which strings to free.
 * 0 : don't free input strings ;
 * 1 : free first string ;
 * 2 : free second string ;
 * 3 : free both strings.
 * @param {char**} s1 - Prefix string.
 * @param {char**} s2 - Suffix string.
 * @param {int} param - indication on strings to free
 * @returns {char*} Joined string.
 * @warning strings are freed even if malloc failed
 */
char	*ft_strjoin_free(char **s1, char **s2, int param);

/**
 * @brief Free the strings of a NULL terminated array of strings,
 * created with split for instance.
 * @param {char **s} - array of strings, NULL terminated
 * @warning Does not free the array.
 */
void	ft_empty_array_strs(char **s);

/**
 * Duplicates a string.
 * Allocates memory and copies the node of `s1`.
 * @param {const char*} s1 - String to duplicate.
 * @returns {char*} Newly allocated copy of the string.
 */
char	*ft_strdup(const char *s);

/**
 * Searches for a character in a string.
 * Returns a pointer to the first occurrence of `c`
 * within the string `s`, or NULL if not found.
 * @param {const char*} s - String to search.
 * @param {int} c - Character to locate.
 * @returns {char*} Pointer to match or NULL.
 */
char	*ft_strchr(const char *s, int c);
/**
* Compares two strings for up to `n` characters.
* @param {const char*} s1 - First string.
* @param {const char*} s2 - Second string.
* @param {size_t} n - Maximum number of bytes to compare.
* @returns {int} Difference between first mismatched bytes.
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * Extracts a substring from a string.
 * Allocates and returns up to `len` characters
 * from `s` starting at position `start`.
 * @param {const char*} s - Original string.
 * @param {unsigned int} start - Index of start.
 * @param {size_t} len - Max length of substring.
 * @returns {char*} New substring or empty string on error.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * Add a new string to the end of an array of strings,
 * malloc a new array and returns it. The array of strings is freed.
 * @param {const char**} arr - array of strings.
 * @param {const char*} s - string to add at the end of the array.
 * @returns {char**} Newly allocated copy of the string.
 * @warning returns null if arr null, or any malloc fails
 */
char	**ft_add_str_array(char **arr, char *s);

/**
 * @brief Free a NULL terminated array of strings,
 * created with split for instance.
 * @param {char ***s} - array of strings, NULL terminated
 */
void	ft_free_array_strs(char ***s);

/**
 * Converts an integer to a string.
 * Handles negative values and zero.
 * @param {int} n - Number to convert.
 * @returns { char * } - Numeric string representation.
 */
char	*ft_itoa(int n);

/**
 * Checks if a character is alphanumeric.
 * Returns true for ASCII letters and digits.
 * @param {int} c - Character to test.
 * @returns {int} 1 if `c` is alphanumeric, otherwise 0.
 */
int		ft_isalnum(int c);

/**
 * Reads the next line from a file descriptor `fd`.
 * Supports reading from multiple file descriptors simultaneously (bonus).
 * Each call returns a newly allocated string ending with a newline character
 * if present.
 * The function maintains an internal static buffer for each file descriptor.
 * Returns NULL on end-of-file or error.
 * @param {int} fd - File descriptor to read from.
 * @returns {char*} Pointer to a newly allocated string containing the next line,
 * including the newline character if present. Returns NULL on EOF or error.
 * The caller is responsible for freeing the returned string.
 */
char	*ft_get_next_line(int fd);

/**
 * Converts a pointer to a string.
 * If pointer is null returns NULL.
 * @param {void *} ptr - Pointer to convert.
 * @returns { char * } - string representation.
 */
char	*ft_ptoa(void *ptr);

/**
 * Copies a block of memory.
 * Copies `n` bytes from `src` to `dst`. Undefined behavior if memory overlaps.
 * @param {void*} dst - Destination buffer.
 * @param {const void*} src - Source buffer.
 * @param {size_t} n - Number of bytes to copy.
 * @returns {void*} Pointer to `dst`.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * Converts a null-terminated string to an int.
 * Skips leading whitespace, handles optional '+'/'-' and digits.
 * @param {const char*} str - Input string.
 * @returns {int} Converted integer.
 */
int		ft_atoi(const char *str);

#endif
