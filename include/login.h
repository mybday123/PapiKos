#ifndef LOGIN_H
#define LOGIN_H

struct User {
    char username[64];
    char password[64];
};

/*
Login flow

Login or register
    Login
        Enter Username
        Enter Password
        Check user exist
        check password if exist
        login success
    Register
        Enter username
        Enter Password
        Confirm Password
        User data written to file
*/

void login_menu();
void login();
void createaccount();
#endif // !LOGIN_H
