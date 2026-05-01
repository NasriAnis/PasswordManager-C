## Presentation
Secure Password Manager project I'am currently working on, implementing hash and encryption algorithms to store passwords and keys securely.

## Project structure
In the `src` folder all the source code for the functions used in the CLI tool inside the `cli` folder and for the GUI application inside the `gui` folder. Header files are in `include` folder inside both `cli` and `gui`, as well as other features and wrapper functions inside the `features` folder in `src` and `gui`.

```
Lokr
├── .clangd
├── .gitignore
├── cli
│   ├── cli.c                       # Entry point for the CLI tool 
│   │                                 (helper cli functions under cli/features are called from there)
│   │ 
│   ├── features                    # wrappers used in (cli.c) using (src/) fucntions
│   │   ├── authentication.c 
│   │   ├── cred_cli_init.c         # intialize credentials heap space
│   │   ├── help.c
│   │   └── password_handling.c
│   │ 
│   └── include
│       ├── authentication.h
│       ├── cred_cli.h
│       ├── help.h
│       └── password_handling.h
├── gui
│   ├── entry.c                     # Entry point for the GUI tool
│   │
│   ├── features                    # wrappers that the GUI tool needs
│   │   ├── cred.c
│   │   ├── credential_handling.c
│   │   └── view_vault.c
│   │
│   ├── include
│   │   ├── cred.h
│   │   ├── credential_handling.h
│   │   ├── login_window.h
│   │   ├── main_window.h
│   │   ├── signup_window.h
│   │   └── view_vault.h
│   │
│   └── windows                     # GUI windows initialisation
│       ├── login_window.c
│       ├── main_window.c
│       └── signup_window.c
│
└── src                             # Source function folder
    ├── auth.c                      # user authentication related functions
    ├── crypto.c                    # Cryptography related functions 
    ├── misc.c                      # Function wrappers
    ├── vault.c                     # Vault handling functions
    └── include
        ├── auth.h
        ├── crypto.h
        ├── misc.h
        └── vault.h
```

## Dependencies
For the CLI tool to work you need to have both `argon2` and `sodium` libraries in your system, for the GUI `GTK4` is needed. Make sure to have the right dependencies before building the project.

## Building the project
You can clone this repository and build it using the command `make` inside the root project folder for the CLI and `make gui` for the GUI app.

Or using `Cmake` which fetch dependencies automatically and locally, Steps are listed below :

```
mkdir build && cd build
cmake ..
cmake --build .
```

## CLI Usage
When first running the program it scans for a `user.bin` file where user credentials are stored then asks you for your password (that will be saved in this `user.bin` file and used as an encryption key) and username, then you can add and see stored passwords using the commands :

```
add [site] [username] [password]
show site=[site] or user=[username]
delete [site] [username]
gen [site] [username]
dump-all
help
```

Other options will be added in future versions...
