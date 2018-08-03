/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicGetUsers.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicGetUsers.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicConfig.h"
#include "dicConst.h"
#include "dicTypes.h"

/*
 * dicErrorType
 * DicGetUsers (dicUserDataType**);
 *
 * Arguments:
 * dicUserDataType** - pointer to pointer to first user of list (O)
 *
 * Returned values:
 * dicOk - users list obtained successfully
 * dicInvalidArgument - received argument is NULL pointer
 * dicUsersFileNotExist - the users file not exist
 *
 * Description:
 * This function gives back a pointer to first user of a doubly linked list.
 * (If the users file is empty the function gives back a ponter to NULL)
 */
dicErrorType
DicGetUsers (dicUserDataType **dicFirstUser)
{
   FILE *dicUsersFile;
   char *validation;
   char *dicTokenPointer;
   char dicUserLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
   dicUserDataType *dicUser;
   dicUserDataType *dicPreviousUser = NULL;

   if (dicFirstUser == NULL)
      return dicInvalidArgument;

   dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
   if (dicUsersFile == NULL)
      return dicUsersFileNotExist;

   *dicFirstUser = NULL;

   while (fgets (dicUserLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
   {
      dicUser = malloc (sizeof (dicUserDataType));

      if (dicPreviousUser != NULL)
         *dicFirstUser = dicUser;

      dicUser->userId = strtoul (strtok (dicUserLine, ":"), &validation, 10);
      strcpy (dicUser->nickname, strtok (NULL, ":"));
      dicTokenPointer = strtok (NULL, ":");
      if (*(dicTokenPointer - 1) == ':')
      {
         dicUser->password[0] = DIC_EOS;
         dicUser->profile = strtoul (dicTokenPointer, &validation, 10);
      }
      else
      {
         strcpy (dicUser->password, dicTokenPointer);
         dicUser->profile = strtoul (strtok (NULL, ":"), &validation, 10);
      }
      strcpy (dicUser->username, strtok (NULL, ":"));
      strcpy (dicUser->email, strtok (NULL, "\n"));

      dicUser->previous = dicPreviousUser;

      if (dicPreviousUser != NULL)
         dicPreviousUser->next = dicUser;

      dicPreviousUser = dicUser;
      dicUser++;
   }
   dicUser->next = NULL;

   fclose (dicUsersFile);

   return dicOk;
}


/*$RCSfile: dicGetUsers.c,v $*/
