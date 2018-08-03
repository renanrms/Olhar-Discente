/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicGetUsers.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_GETUSERS_H
#define DIC_GETUSERS_H "@(#)dicGetUsers.h $Revision: 1.1 $"

#include "dicTypes.h"
#include "dicErrors.h"

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
DicGetUsers (dicUserDataType**);

#endif 

/*$RCSfile: dicGetUsers.h,v $*/
