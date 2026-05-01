## Presentation
Secure Password Manager project I'am currently working on, implementing hash and encryption algorithms to store passwords and keys securely.

## Project structure
In the `src` folder all the source code for the functions used in the CLI tool inside the `cli` folder and for the GUI application inside the `gui` folder. Header files are in `include` folder inside both `cli` and `gui`, as well as other features and wrapper functions inside the `features` folder in `src` and `gui`.

### Directory Overview :

```
lokr/
├── src/                        # Shared library — used by both CLI and GUI
│   ├── auth/
│   │   ├── include/
│   │   │   ├── login.h
│   │   │   └── signup.h
│   │   ├── login.c
│   │   └── signup.c
│   ├── crypto/
│   │   ├── include/
│   │   │   ├── base64.h
│   │   │   ├── encrypt.h
│   │   │   ├── gen.h
│   │   │   └── hash.h
│   │   ├── base64.c
│   │   ├── encrypt.c
│   │   ├── gen.c
│   │   └── hash.c
│   ├── init/
│   │   ├── include/
│   │   │   └── cred_init.h
│   │   └── cred.c
│   ├── misc/
│   │   ├── include/
│   │   │   ├── debug.h
│   │   │   ├── helper.h
│   │   │   └── wrapper.h
│   │   ├── debug.c
│   │   ├── helper.c
│   │   └── wrapper.c
│   └── vault/
│       ├── include/
│       │   ├── vault.h
│       │   └── vault_helper.h
│       ├── vault.c
│       └── vault_helper.c
│
├── cli/                        # CLI frontend (target: lokr)
│   ├── include/
│   │   ├── authentication.h
│   │   ├── help.h
│   │   └── password_handling.h
│   ├── features/
│   │   ├── authentication.c
│   │   ├── help.c
│   │   └── password_handling.c
│   └── cli.c                   # CLI entry point
│
└── gui/                        # GTK4 GUI frontend (target: lokr_gui)
    ├── include/
    │   ├── credential_handling.h
    │   ├── login_window.h
    │   ├── main_window.h
    │   ├── signup_window.h
    │   └── view_vault.h
    ├── features/
    │   ├── credential_handling.c
    │   └── view_vault.c
    ├── windows/
    │   ├── login_window.c
    │   ├── main_window.c
    │   └── signup_window.c
    └── entry.c                 # GUI entry point
```

### Module Breakdown

#### `src/` — Shared Core

| Module   | Files                                      | Responsibility                                                              |
| -------- | ------------------------------------------ | --------------------------------------------------------------------------- |
| `auth`   | `login.c`, `signup.c`                      | User authentication — master password verify / account creation             |
| `crypto` | `base64.c`, `encrypt.c`, `gen.c`, `hash.c` | Encryption (libsodium), password generation, Argon2id hashing, base64 codec |
| `init`   | `cred.c`                                   | Vault/credential store initialization                                       |
| `misc`   | `debug.c`, `helper.c`, `wrapper.c`         | Debug utils, shared helpers, libsodium/Argon2 wrappers                      |
| `vault`  | `vault.c`, `vault_helper.c`                | Vault CRUD operations and helper logic                                      |

#### `cli/` — Command-Line Interface

| File                           | Responsibility                                        |
| ------------------------------ | ----------------------------------------------------- |
| `cli.c`                        | Argument parsing, command dispatch — main entry point |
| `features/authentication.c`    | CLI-layer auth flow (login / logout prompts)          |
| `features/help.c`              | `--help` output and usage strings                     |
| `features/password_handling.c` | Add / retrieve / delete credential commands           |

#### `gui/` — GTK4 Graphical Interface

|File|Responsibility|
|---|---|
|`entry.c`|`gtk_application_new` bootstrap — GUI entry point|
|`windows/login_window.c`|Login screen widget|
|`windows/signup_window.c`|Account creation screen widget|
|`windows/main_window.c`|Primary dashboard window|
|`features/credential_handling.c`|Add / edit / delete credential UI logic|
|`features/view_vault.c`|Vault list / search view|

### Dependency Graph :

```
           ┌─────────────────────────────┐
           │          src/               │
           │  auth  crypto  vault  misc  │
           │         init               │
           └──────────┬──────────────────┘
                      │  (shared by both)
          ┌───────────┴───────────┐
          ▼                       ▼
   ┌─────────────┐       ┌──────────────────┐
   │    cli/     │       │      gui/        │
   │  cli.c      │       │  entry.c         │
   │  features/  │       │  windows/        │
   │    auth     │       │  features/       │
   │    help     │       │    cred_handling │
   │    pw_hdlg  │       │    view_vault    │
   └─────────────┘       └──────────────────┘
   (target: lokr)        (target: lokr_gui)
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
