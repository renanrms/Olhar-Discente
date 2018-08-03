/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef DIC_CONST_H
#define DIC_CONST_H "@(#)dicConst.h $Revision$"

#define DIC_EOS                        '\0'
#define DIC_BACKGROUND_COLOR           0xE0FFE0
#define DIC_CENTRAL_FRAME_COLOR        0xD0D0FF

#define DIC_LANGUAGE_MAX_LENGTH        64
#define DIC_FILE_PATH_MAX_LENGTH       1024
#define DIC_HTMLLINE_MAX_LENGTH        512       /*used in reading of static html files by CGIs*/
#define DIC_SALT_MAX_LENGTH            16        /*salt used in Sha and Md5 algorithms*/
#define DIC_BASE_64_CHARACTERS         "/+ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define DIC_TEMP_PASSWORD_CHARACTERS   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

#define DIC_NICKNAME_MIN_LENGTH        5
#define DIC_NICKNAME_MAX_LENGTH        65
#define DIC_NICKNAME_CARACTERS         ".abcdefghijklmnopqrstuvwxyz"

#define DIC_PASSWORD_MIN_LENGTH        8
#define DIC_PASSWORD_MAX_LENGTH        127
#define DIC_PASSWORD_CARACTERS         " .-'\"()[]{}!?@#$%%&*/\\+=,;:ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

#define DIC_USERNAME_MIN_LENGTH        11
#define DIC_USERNAME_MAX_LENGTH        256
#define DIC_USERNAME_CARACTERS         " .-'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

#define DIC_EMAIL_MIN_LENGTH           11
#define DIC_EMAIL_MAX_LENGTH           1024
#define DIC_EMAIL_CARACTERS            "@.-_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

#endif
/*$RCSfile$*/
