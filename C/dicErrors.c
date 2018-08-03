/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicErrors.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdlib.h>

#include "dicErrors.h"
#include "dicTypes.h"

char *DicCliErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Operation was successful.",
      /*Invalid fields*/
      "You not define all required arguments.",
      "Invalid e-mail.",
      "The e-mail confirmation differs from e-mail.",
      "Invalid username.",
      "Few names written. The username must have two or more names.",
      "Very large names. Check the username typing.",
      "The username confirmation differs from username.",
      "Invalid password.",
      "The password confirmation differs from password.",
      /*Incorrect fields*/
      "Incorrect login.",
      "Incorrect password.",
      "This e-mail is already registered.",
      "The responsible user e-mail is not registered.",
      "This user is already registered.",
      "You was not invited, or the invite is expired. Request your registration",
      "This user not request registration, or the request is expired.",
      "You is't the responsible for this request.",
      "The user that you want to unlock is not locked.",
      "The user that you want to lock already is in pending state.",
      "The user that you want to unlock is not registered.",
      /*File not found*/
      "sorry, the help in this language was not found.",
      NULL,
      /*CLI error messages*/
      "No specified option.",
      "Invalid option",
      "Invalid suboption",
      "Invalid profile",
      "The arguments not respects the syntax name=value or are not separeted for spaces.",
      "Is not permited request registration with this profile.",
      "You have not permission for this action.",
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   },
   {
      "Operação realizada com sucesso.",
      /*Invalid fields*/
      "Voce não definiu todos os argumentos obrigatórios.",
      "Email inválido.",
      "A confirmação do e-mail difere do e-mail.",
      "Nome do usuário inválido.",
      "Poucos nomes escritos. O nome de usuário deve conter ao menos dois nomes.",
      "Nomes muito grandes. Verifique a digitação do seu nome.",
      "A cofirmação do nome difere do nome.",
      "Senha inválida.",
      "A confirmação da senha difere da senha.",
      /*Incorrect fields*/
      "Usuário incorreto.",
      "Senha incorreta.",
      "Este e-mail já está cadastrado.",
      "O e-mail do usuário responsável não está cadastrado.",
      "Este usuário já estava registrado.",
      "Você não foi convidado, ou o convite já expirou. Solicite cadastramento",
      "Este usuário não solicitou cadastro, ou a solicitação já expirou.",
      "Você não é o responsável por esta solicitação.",
      "O usuário que você quer desbloquear não está bloqueado.",
      "O usuário que você quer bloquear já está pendente.",
      "O usuário que você quer desbloquear não está registrado.",
      /*File not found*/
      "Desculpe, a ajuda neste idioma não foi encontrada.",
      NULL,
      /*CLI error messages*/
      "Nenhuma opção especificada.",
      "Opção inválida.",
      "Subopção inválida.",
      "Perfil invávido",
      "Os argumentos não respeitam a sintaxe nome=valor ou não estão separados por espaços.",
      "Não é permitido solicitar cadastramento com este perfil.",
      "Voce não tem permissão para realizar esta ação.",
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   }
};

char *DicNcursesErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Operation was successful.",
      /*Invalid fields*/
      "You not define all required arguments.",
      "Invalid e-mail.",
      "The e-mail confirmation differs from e-mail.",
      "Invalid username.",
      "Few names written. The username must have two or more names.",
      "Very large names. Check the username typing.",
      "The username confirmation differs from username.",
      "Invalid password.",
      "The password confirmation differs from password.",
      /*Incorrect fields*/
      "Incorrect login.",
      "Incorrect password.",
      "This e-mail is already registered.",
      "The responsible user e-mail is not registered.",
      "This user is already registered.",
      "You was not invited, or the invite is expired. Request your registration",
      "This user not request registration, or the request is expired.",
      "You is't the responsible for this request.",
      "The user that you want to unlock is not locked.",
      "The user that you want to lock already is in pending state.",
      "The user that you want to unlock is not registered.",
      /*File not found*/
      "sorry, the help in this language was not found.",
      NULL,
      /*CLI error messages*/
      "No specified option.",
      "Invalid option.",
      "Invalid suboption.",
      "Invalid profile",
      "Is not permited request registration with this profile.",
      "You have not permission for this action.",
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   },
   {
      "Operação realizada com sucesso.",
      /*Invalid fields*/
      "Voce não definiu todos os argumentos obrigatórios.",
      "Email inválido.",
      "A confirmação do e-mail difere do e-mail.",
      "Nome do usuário inválido.",
      "Poucos nomes escritos. O nome de usuário deve conter ao menos dois nomes.",
      "Nomes muito grandes. Verifique a digitação do seu nome.",
      "A cofirmação do nome difere do nome.",
      "Senha inválida.",
      "A confirmação da senha difere da senha.",
      /*Incorrect fields*/
      "Usuário incorreto.",
      "Senha incorreta.",
      "Este e-mail já está cadastrado.",
      "O e-mail do usuário responsável não está cadastrado.",
      "Este usuário já estava registrado.",
      "Você não foi convidado, ou o convite já expirou. Solicite cadastramento",
      "Este usuário não solicitou cadastro, ou a solicitação já expirou.",
      "Você não é o responsável por esta solicitação.",
      "O usuário que você quer desbloquear não está bloqueado.",
      "O usuário que você quer bloquear já está pendente.",
      "O usuário que você quer desbloquear não está registrado.",
      /*File not found*/
      "Desculpe, a ajuda neste idioma não foi encontrada.",
      NULL,
      /*CLI error messages*/
      "Nenhuma opção especificada.",
      "Opção inválida.",
      "Subopção inválida.",
      "Perfil invávido",
      "Não é permitido solicitar cadastramento com este perfil.",
      "Voce não tem permissão para realizar esta ação.",
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   }
};


char *DicWebErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Operation was successful.",
      /*Invalid fields*/
      "Fill all required fields.",
      "Invalid e-mail.",
      "The e-mail confirmation differs from e-mail.",
      "Invalid username.",
      "Few names written. The username must have two or more names.",
      "Very large names. Check the username typing.",
      "The username confirmation differs from username.",
      "Invalid password.",
      "The password confirmation differs from password.",
      /*Incorrect fields*/
      "Incorrect login.",
      "Incorrect password.",
      "This e-mail is already registered.",
      "The responsible user e-mail is not registered.",
      "This user is already registered.",
      "This user was not invited, or the invite is expired.",
      "This user not request registration, or the request is expired.",
      "You is't the responsible for this request.",
      "The user that you want to unlock is not locked.",
      "The user that you want to lock already is in pending state.",
      "The user that you want to unlock is not registered.",
      /*File not found*/
      "sorry, the help in this language was not found.",
      "sorry, the license in this language was not found.",
      /*CLI error messages*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   },
   {
      "Opera&ccedil;&atilde;o realizada com sucesso.",
      /*Invalid fields*/
      "Preencha todos os campos obrigat&oacute;rios.",
      "Email inv&aacute;lido.",
      "A confirma&ccedil;&atilde;o do e-mail difere do e-mail.",
      "Nome do usu&aacute;rio inv&aacute;lido.",
      "Poucos nomes escritos. O nome de usu&aacute;rio deve conter ao menos dois nomes.",
      "Nomes muito grandes. Verifique a digita&ccedil;&atilde;o do seu nome.",
      "A cofirma&ccedil;&atilde;o do nome difere do nome.",
      "Senha inv&aacute;lida.",
      "A confirma&ccedil;&atilde;o da senha difere da senha.",
      /*Incorrect fields*/
      "Usu&aacute;rio incorreto.",
      "Senha incorreta.",
      "Este e-mail j&aacute; est&aacute; cadastrado.",
      "O e-mail do usu&aacute;rio respons&aacute;vel n&atilde;o est&aacute; cadastrado.",
      "Este usu&aacute;rio j&aacute; estava registrado.",
      "Você n&atilde;o foi convidado, ou o convite j&aacute; expirou. Solicite cadastramento",
      "Este usu&aacute;rio n&atilde;o solicitou cadastro, ou a solicita&ccedil;&atilde;o j&aacute; expirou.",
      "Você n&atilde;o &eacute; o respons&aacute;vel por esta solicita&ccedil;&atilde;o.",
      "O usu&aacute;rio que voc&ecirc; quer desbloquear n&atilde;o est&aacute; bloqueado.",
      "O usu&aacute;rio que voc&ecirc; quer bloquear j&aacute; est&aacute; pendente.",
      "O usu&aacute;rio que voc&ecirc; quer desbloquear n&atilde;o est&aacute; registrado.",
      /*File not found*/
      "Desculpe, a ajuda neste idioma n&atilde;o foi encontrada.",
      "Desculpe, a licensa neste idioma n&atilde;o foi encontrada.",
      /*CLI error messages*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Internal error codes*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL
   }
};


/* 
 * char *
 * DicGetCliErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 * 
 * Description:
 * This function gives the error mensage for CLI
 */
char *
DicGetCliErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicCliErrorMessages [dicLanguage][dicError];
}

/*
 * char *
 * DicGetNcursesErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 *
 * Description:
 * This function gives the error mensage for Ncurses interface
 */
char *
DicGetNcursesErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicNcursesErrorMessages [dicLanguage][dicError];
}

/*
 * char *
 * DicGetWebErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 *
 * Description:
 * This function gives the error mensage for web interface
 */
char *
DicGetWebErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicWebErrorMessages [dicLanguage][dicError];
}

/*$RCSfile: dicErrors.c,v $*/
