# get_next_line

`Get_next_line` is a function permitting to read line by line any stream of string. The function uses static buffer avoiding data loses.
 
 It is defined as `int get_next_line( int fd, char **line)`.
 
 The return value of the function has the following behaviour : 
 
 | Value | Behaviour | 
 | ---| ---| 
 |  1 | One line got read | 
 |  0| End of stream got reached | 
 | -1 |  An error has occured | 
