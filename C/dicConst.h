/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicConst.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_CONST_H
#define DIC_CONST_H "@(#)dicConst.h $Revision: 1.1 $"

#include "dicTypes.h"

#define DIC_EOS                        '\0'

#define DIC_BACKGROUND_COLOR           0xE0FFE0
#define DIC_CENTRAL_FRAME_COLOR        0xD0D0FF

#define DIC_BASE_64_CHARACTERS         "/+ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

/*for invited users*/
#define DIC_TEMP_PASSWORD_CHARACTERS   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define DIC_TEMP_PASSWORD_LENGTH       16

#define DIC_PROFILE_MAX_LENGTH         65

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

#define DIC_LANGUAGE_MAX_LENGTH        64
#define DIC_FILE_PATH_MAX_LENGTH       512
#define DIC_TEXT_PARAGRAPH_MAX_LENGTH  2048
#define DIC_HTMLLINE_MAX_LENGTH        1024      /*used in reading of static html files by CGIs*/
#define DIC_SALT_MAX_LENGTH            16        /*salt used in Sha and Md5 algorithms*/
#define DIC_EMAIL_BODY_MAX_LENGTH      4095
                                       /*userId(unsigned long long):nickname:hash:profile:username:email\n*/
#define DIC_USERSFILE_LINE_MAX_LENGTH  6 + 29 + DIC_NICKNAME_MAX_LENGTH + DIC_PASSWORD_MAX_LENGTH + 1 + DIC_USERNAME_MAX_LENGTH + DIC_EMAIL_MAX_LENGTH

#define DIC_INVITE_EXPIRATION_TIME     3*(24*60*60)
#define DIC_REQUESTING_EXPIRATION_TIME 7*(24*60*60)

#endif
/*$RCSfile: dicConst.h,v $*/
