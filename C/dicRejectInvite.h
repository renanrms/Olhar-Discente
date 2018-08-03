/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicRejectInvite.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_REJECTINVITE_H
#define DIC_REJECTINVITE_H "@(#)dicRejectInvite.h $Revision: 1.1 $"

#include "dicErrors.h"

/*
 * dicErrorType
 * DicRejectInvite (char*, char*);
 *
 * Arguments:
 * char* - password of invited user (I)
 * char* - nickname of invited user (I)
 *
 * Returned values:
 * dicOk - invite was rejected successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotInvitedUser - if user is not invited or your invite has expired
 * dicIcorrectPassword - user authentication failed
 *
 * Description:
 * This function rejects a invite to register in the system if user was invited,
 * your invite is not expired and your password is correct.
 */
dicErrorType
DicRejectInvite (char*, char*);

#endif 

/*$RCSfile: dicRejectInvite.h,v $*/
