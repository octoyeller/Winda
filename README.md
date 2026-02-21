# Winda

Cross-platform template for GUI C++ apps utilizing GTK 4. Features proper window decorations. Creates a stand-alone bundle that should work even if half of your OS is gone.

Developed on Debian 12 and tiny11. Tested on Arch v.?? and windows 11.

## Set up

### Linux / Debian

1. Just apt install [requirements](linux_req)`*`.
2. Clone this repo or something.
3. Makefile setup build and hope it won't scream at you.
`*` you may want to read [Docs](Docs.md).

### Windows

First of all F you, because apparently there isn't any native compiler for windows (except for VS which I don't like and Clion which I cannot afford). So I'm using LINUX to compile this thing.

1. Install [MSYS2](https://www.msys2.org/)
2. Open "MSYS2 MINGW64" - following commands go here
3. ``
4. Restart MSYS2
5. ``
6. Install make if you don't have it
7. Go to your soon-detested folder `cd /c/Users/you/path/winda`
8. `make setup; make build` 
9. Pray to RNGesus it'll work on the first try because I'm not fixing it
10. If `app/winda.exe` is not working then reinstall windows or something...

## Troubleshooting

Doesn't work? Sucks to be you ¯\_(ツ)_/¯ I'm on a stage of screw-the-tech-return-to-paper. If you need help I suggest you also relearn how to use the damn pen.
