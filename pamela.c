#define _GNU_SOURCE
#include <stdio.h>
#include <linux/limits.h>
#include "pamela.h"
#include <syslog.h>

PAM_EXTERN
int pam_sm_open_session(pam_handle_t *pamh, int flags,
			int argc, const char **argv) {
  char const *user;
  int pam_error;

  // get user name
  if ((pam_error = pam_get_user(pamh, &user, NULL)) != PAM_SUCCESS) {
    fprintf(stderr, "%sn", pam_strerror(pamh, pam_error));
    syslog(LOG_USER | LOG_ERR, "Error pam_get_user()\n");
    return pam_error;
  }
  // open / create volume
  char *cmd_open;
  if (!asprintf(&cmd_open, "su -l root -c \"pamela_manager open %s\"", user, user)) {
    syslog(LOG_USER | LOG_ERR, "Error asprintf()\n");
    // log error
    return PAM_ABORT;
  }
  if (system(cmd_open) != 0) {
    free(cmd_open);
    syslog(LOG_USER | LOG_ERR, "Error during the pamela_manager script\n");
    return PAM_ABORT;
  }
  free(cmd_open);
  return PAM_SUCCESS;
}


PAM_EXTERN
int pam_sm_close_session(pam_handle_t *pamh, int flags,
			 int argc, const char *argv[]) {
  syslog(LOG_USER | LOG_ERR, "close()\n");
  char const *user;
  int pam_error;
  // get user name
  if ((pam_error = pam_get_user(pamh, &user, NULL)) != PAM_SUCCESS) {
    fprintf(stderr, "%sn", pam_strerror(pamh, pam_error));
    syslog(LOG_USER | LOG_ERR, "Error pam_get_user()\n");
    return pam_error;
  }
  // open / create volume
  char *cmd_open;
  if (!asprintf(&cmd_open, "su -l root -c \"pamela_manager close %s\"", user, user)) {
    // log error
    return PAM_ABORT;
  }
  if (system(cmd_open) != 0) {
    free(cmd_open);
    syslog(LOG_USER | LOG_ERR, "Error during the pamela_manager script\n");
    return PAM_ABORT;
  }
  free(cmd_open);
  return PAM_SUCCESS;
}

/*
PAM_EXTERN
int pam_sm_authenticate(pam_handle_t *pamh, int flags,
			int argc, const char *argv[])
{
  syslog(LOG_USER | LOG_ERR, "authenticate()\n");
  (void)pamh;
  (void)flags;
  (void)argc;
  (void)argv;
  return (PAM_SUCCESS);
}

PAM_EXTERN
int pam_sm_setcred(pam_handle_t *pamh, int flags,
		   int argc, const char *argv[])
{
  syslog(LOG_USER | LOG_ERR, "setcred()\n");
  (void)pamh;
  (void)flags;
  (void)argc;
  (void)argv;
  return (PAM_SUCCESS);
}


PAM_EXTERN
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags,
		     int argc, const char *argv[])
{
  syslog(LOG_USER | LOG_ERR, "acct_mgmt()\n");
  (void)pamh;
  (void)flags;
  (void)argc;
  (void)argv;
  return (PAM_SUCCESS);
}
*/
