/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:21:34 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/01/31 09:59:59 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
/* Set bytes after defined memory address to zero;
*@param s Memory address
*@param n Number of bytes
*/
void	ft_bzero(void *s, size_t n);
/* Set bytes after defined memory address to desired value;
*@param s Memory address
*@param c Desired value
*@param n Number of bytes
*@return Returns the same passed memory address
*/
void	*ft_memset(void *s, char c, size_t n);
/*Returns the first memory address that matches desired value;
*@param s Memory address
*@param c Desired value
*@param n Max number of bytes to verify
*@return Match memory address or NULL
*/
void	*ft_memchr(const void *s, int c, size_t n);
/*Copies content from one address to another.
*Will cause SEGFAULT if memory delimitations are not met.
*@param dest Memory address to copy content to.
*@param src Memory address to copy content from.
*@param n Number of bytes to copy from src to dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
/*Move memory from one address to another without overriding content from src.
*Will cause SEGFAULT if memory delimitation are not met.
*@param dest Memory address to move content to.
*@param src Memory address to move content from.
*@param n Number of bytes to move.
*/
void	*ft_memmove(void *dest, const void *src, size_t n);
/*Compares two addresses of memory;
*@param s1 First memory address.
*@param s2 Second memory address.
*@param n Number of bytes to compare.
*@return Return the distance between the first diferent bytes.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/* Allocates and zeroes block of size [nmemb] x [size].
*@param nmemb Number of "members" to alocate.
*@param size Size of "member" block.
*@return Memory address of allocated memory, zeroed out.
*[NULL] if memory allocation fails. */
void	*ft_calloc(size_t nmemb, size_t size);
/*Integer absolute.
*@param n Integer number.
*/
int		ft_abs(int n);
/*Long absolute.
*@param n Long number.
*/
long	ft_absl(long n);
/*Integer to string conversion.
*@param n Integer number.
*@return char* Char vector
*/
char	*ft_itoa(int n);
/*String to integer conversion.
*Ignores beggining blank chars. Converts everything before nondigit char.
*@param nptr char*
*/
int		ft_atoi(const char *nptr);
/*Integer to variable base string conversion.
*@param nb Integer number.
*@param base Set of characters to use as numeric base.
*@return char* Char vector
*/
char	*ft_itob(unsigned int nb, char *base);
/*Unsigned integer to string conversion.
*@param nb Integer number.
*@return char* Char vector
*/
char	*ft_utoa(unsigned int nb);
/*Get char * size
*@param s char *
*/
size_t	ft_strlen(const char *s);
/*Copies string from one address to another.
*Copies n bytes or src lenght bytes.
*@param dest Address to copy string to
*@param src Address to copy string from
*@param n Number of bytes to copy
*@return Total number of bytes copied for verification purposes.
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
/*Contatenates string from one string to the end another.
*Copies [size] or [src lenght] number of bytes,
*[size] being the parameter summed to the lenght of dest.
*It will cause segfault if there is no room for copying in dest.
*@param dest Address to copy string to
*@param src Address to copy string from
*@param size Number of bytes to copy, counting from the beggining of dest.
*@return Total number of bytes copied for verification purposes.
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size);
/*Compares two strings.
*@param s1 First string to compare
*@param s2 Second string to compare
*@param size Number of bytes to compare
*@return Returns the distance between the first different bytes.
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*Gets first occurrence of char on string
*@param s String to lookup.
*@param c char to look for.
*@return The address of the first occurance of desired char. 
*NULL if nothing is found
*/
char	*ft_strchr(const char *s, int c);
/*Gets first occurrence of char on string, from left to right
*@param s String to lookup.
*@param c char to look for.
*@return The address of the first occurance of desired char. 
*[NULL] if nothing is found
*/
char	*ft_strrchr(const char *s, int c);
/*Gets first occurrence of substring on string.
*@param big String to lookup.
*@param little Substring to look for.
*@param len Max number of bytes to compare.
*@return The address of the first occurance of [little].
*[NULL] if nothing is found
*/
char	*ft_strnstr(const char *big, const char *little, size_t len);
/*Duplicates string on heap memory
*@param s String to duplicate.
*@return The address of the duplicated string.
*[NULL] If memory allocation or copy execution fails
*/
char	*ft_strdup(const char *s);
/*Extracts substring from string to heap.
*@param s string to extract from.
*@param start extraction start postition.
*@param len size of bytes to be extracted.
*@return Memory address with extracted substring.
*[NULL] If memory allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*Joins two strings in heap memory
*@param s1 first string.
*@param s2 second string.
*@return Memory address with both strings joined.
*[NULL] If memory allocation fails.
*/
char	*ft_strjoin(char const *s1, char const *s2);
/*Trims desired set of chars from both ends of a string.
*@param s1 String to trim.
*@param set Set of chars to trim,
*the order of the characters makes no difference.
*@returns Memory address with trimmed string.
*[NULL] If memory allocation fails.
*/
char	*ft_strtrim(char const *s1, char const *set);
/*Iterates through string, mapping a function into another.
*@param s string to map.
*@param f function with modifying logic.
*@return Memory address with mapped string.
*[NULL] if memory allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*Iterates through string, modifying its own value.
*@param s string to iterate.
*@param f funtion with modifying logic.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*Splits string at desired char.
*If there are multiple [c] in the original string, 
multiple strings will be created.
*@param s string to be splited.
*@param c char to split.
*@return Null terminated vector of allocated string addresses.
*[NULL] If memory allocation fails.
*/
char	**ft_split(char const *s, char c);
/*Writes char into desired fd.
*@param c char to write.
*@param fd fd to write to.
*/
void	ft_putchar_fd(char c, int fd);
/*Writes string into desired fd.
*@param s char to write.
*@param fd fd to write to.
*/
void	ft_putstr_fd(char *s, int fd);
/*Writes "\n" terminated string into desired fd.
*@param s char to write.
*@param fd fd to write to.
*/
void	ft_putendl_fd(char *s, int fd);
/*Writes number into desired fd.
*@param n integer to write.
*@param fd fd to write to.
*/
void	ft_putnbr_fd(int n, int fd);
/*Initiates t_list node.
*@param content Memory address.
*@return Memory address of allocated t_list node.
*/
t_list	*ft_lstnew(void *content);
/*Inserts node to the beggining of a list.
*@param lst Lists first node memory address.
*@param new Node to insert into list.
*@return Memory address of inserted node, as the lists first node.
*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/*Get list size
*@param lst 
*@return Total number of nodes of list
*/
int		ft_lstsize(t_list *lst);
/*Get lists last node.
*@param lst First node address.
*@return Last node address.
*/
t_list	*ft_lstlast(t_list *lst);
/*Inserts node to the end of a list.
*@param lst Lists first node memory address.
*@param new Node to insert into list.
*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*Properly free of list node.
*@param lst Node address to be freed.
*@param del Function to properly content inside it.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/*Iterates through list, properly freeing nodes.
*@param list Pointer to first node address
*@param del Function to properly content inside nodes.
*/
void	ft_lstclear(t_list **list, void (*del)(void *));
/*Iterates through list, modifing its nodes.
*@param lst First node address.
*@param f Function with modifying logic.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));
/*Iterates through list, mapping its nodes to another list.
*If something goes wrong, properly frees allocated nodes from the new list.
*@param lst First node address.
*@param f Funciton with modifiying logic.
*@param del Function to properly free list nodes.
*@return First address of allocated new mapped list.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif