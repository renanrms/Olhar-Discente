/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicAcceptInvite.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_ACCEPTINVITE_H
#define DIC_ACCEPTINVITE_H "@(#)dicAcceptInvite.h $Revision: 1.1 $"

#include "dicErrors.h"
#include "dicTypes.h"

/*
 * dicErrorType
 * DicAcceptInvite (char*, dicUserDataType*);
 *
 * Arguments:
 * char* - password of invited user (I)
 * dicUserDataType* - structure containing nickname, new password and your confirmation 
 *
 * Returned values:
 * dicOk - invite was accept successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotInvitedUser - if user is not invited or your invite has expired
 * dicIcorrectPassword - user authentication failed
 * dicInvalidPassword - new password is not in the specifications
 * dicInvalidPasswordConfirmation - new password confirmation differs from new password
 *
 * Description:
 * This function accepts a invite to register in the system if user was invited,
 * your invite is not expired, your password is correct and your new password and confirmation is valid.
 */
dicErrorType
DicAcceptInvite (char*, dicUserDataType*);

#endif 

/*$RCSfile: dicAcceptInvite.h,v $*/
