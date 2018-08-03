/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicConfig.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_CONFIG_H
#define DIC_CONFIG_H "@(#)dicConfig.h $Revision: 1.1 $"

#ifndef DIC_PRIMARY_ADMINISTRATOR_EMAIL
#define DIC_PRIMARY_ADMINISTRATOR_EMAIL "renanpassos@poli.ufrj.br"
#endif /* #ifndef DIC_PRIMARY_ADMINISTRATOR_EMAIL */

#ifndef DIC_WEB_SERVER_URL
#define DIC_WEB_SERVER_URL "http://www02.del.ufrj.br/~renan.passos/DIC/"
#endif /* #ifndef DIC_WEB_SERVER_URL */

#ifndef DIC_ADMINISTRATOR_USER_IDENTIFIER
#define DIC_ADMINISTRATOR_USER_IDENTIFIER      45056
#endif /* #ifndef DIC_ADMINISTRATOR_USER_IDENTIFIER */

#ifndef DIC_PRIVATE_ROOT_DIRECTORY
#define DIC_PRIVATE_ROOT_DIRECTORY "/users/renan.passos/private/EEL270/2016-1/DIC/"
#endif /* #ifndef DIC_PRIVATE_ROOT_DIRECTORY */

#ifndef DIC_DATA_DIRECTORY
#define DIC_DATA_DIRECTORY "/users/renan.passos/private/EEL270/2016-1/DIC/Data/"
#endif /* #ifndef DIC_DATA_DIRECTORY */

#ifndef DIC_COOKIES_DIRECTORY
#define DIC_COOKIES_DIRECTORY "/users/renan.passos/private/EEL270/2016-1/DIC/Data/Cookies/"
#endif /* #ifndef DIC_COOKIES_DIRECTORY */

#ifndef DIC_USERS_DATA_FILENAME
#define DIC_USERS_DATA_FILENAME "users"
#endif /* #ifndef DIC_USERS_DATA_FILENAME */

#ifndef DIC_INVITED_USERS_DATA_FILENAME
#define DIC_INVITED_USERS_DATA_FILENAME "invited.users"
#endif /* #ifndef DIC_INVITED_USERS_DATA_FILENAME */

#ifndef DIC_REQUESTING_USERS_DATA_FILENAME 
#define DIC_REQUESTING_USERS_DATA_FILENAME "requesting.users"
#endif /* #ifndef DIC_REQUESTING_USERS_DATA_FILENAME  */

#ifndef DIC_LOCKED_USERS_DATA_FILENAME
#define DIC_LOCKED_USERS_DATA_FILENAME "locked.users"
#endif /* #ifndef DIC_LOCKED_USERS_DATA_FILENAME */

#ifndef DIC_UNLOCKING_USERS_DATA_FILENAME
#define DIC_UNLOCKING_USERS_DATA_FILENAME "unlocking.users"
#endif /* #indef DIC_UNLOCKING_USERS_DATA_FILENAME */

/*SEND EMAIL*/
#ifndef DIC_SMTP_CLIENT_DOMAIN
#define DIC_SMTP_CLIENT_DOMAIN "del.ufrj.br"
#endif

#ifndef DIC_SMTP_SERVER_FULL_HOSTNAME
#define DIC_SMTP_SERVER_FULL_HOSTNAME "smtp.del.ufrj.br"
#endif

#ifndef DIC_SMTP_SERVER_PORT
#define DIC_SMTP_SERVER_PORT 25
#endif

#endif /* #ifndef DIC_CONFIG_H */ 

/*$RCSfile: dicConfig.h,v $*/
