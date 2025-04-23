#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "termui.h"
#include "login.h"

void login_menu() {
    char c = '0';
    puts("1. Log in");
    puts("2. Create account");
    puts("0. Exit");
    print_newline();
    printf("? ");
    scanf("%c", &c);

    switch (c) {
        case '0':
            exit(0);
            break;
        case '1':
            login();
            break;
        case '2':
            createaccount();
            break;
    }
}

void createaccount() {
    struct User new_user;
    char temp_pass[64];
    printf("Masukkan username:");
    scanf("%s", new_user.username);
    printf("Masukkan password");
    scanf("%s", new_user.password);
    printf("Masukkan password yang sama lagi:");
    scanf("%s", temp_pass);

    if (strcmp(new_user.password, temp_pass) != 0) {
        puts("Password tidak sesuai!");
        return;
    }
    else {
        puts("Menyimpan akun...");
        FILE* userfile = fopen(new_user.username, "w");
        if (userfile == NULL) {
            puts("Gagal menyimpan file");
            return;
        }
        if (fwrite(&new_user, sizeof(struct User), 1, userfile)) {
            puts("User created");
            fclose(userfile);
        }
        else {
            puts("Failed to create user");
            fclose(userfile);
        }
    }
}

void login() {

}
