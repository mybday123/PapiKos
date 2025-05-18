#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/termui.h"
#include "../include/login.h"

void login_menu() {
    char c = '0';
    puts("1. Log in");
    puts("2. Create account");
    puts("0. Exit");
    print_newline();
    printf("? ");
    if (!scanf("%c", &c)) {
        return 0;
    }
    int ch = getchar();
    (void)ch;

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
    printf("Masukkan username: ");
    scan_input(new_user.username, 63);
    if (strcmp(new_user.username, "admin") != 0) {
        puts("Username tidak bisa admin.");
        return;
    }

    printf("Masukkan password: ");
    disable_echo();
    scan_input(new_user.password, 63);
    enable_echo();
    printf("Masukkan password yang sama lagi:");
    disable_echo();
    scan_input(temp_pass, 63);
    enable_echo();
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
    struct User user;
    char temp_user[64];
    char temp_pass[64];

    printf("Masukkan username: ");
    scan_input(temp_user, 63);
    disable_echo();
    printf("Masukkan password: ");
    enable_echo();
    scan_input(temp_pass, 63);

    FILE* userfile = fopen(temp_user, "r");
    if (userfile == NULL) {
        puts("Login gagal");
        return;
    }
    if (fread(&user, sizeof(struct User), 1, userfile)) {
        if (strcmp(user.password, temp_pass) == 0) {
            puts("Login berhasil");
            fclose(userfile);
            return;
        }
        else {
            puts("Login gagal");
            fclose(userfile);
            return;
        }
    }
    else {
        puts("Login gagal");
        fclose(userfile);
        return;
    }
}
