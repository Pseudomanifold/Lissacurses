# Lissacurses - Lissajous curves on the console

`Lissacurses` draws Lissajous curves on the console. It requires a
working installation of the `ncurses` library.

## Building

    $ git clone http://git.annwfn.net/Lissacurses.git
    $ cd Lissacurses
    $ mkdir build
    $ cd build
    $ cmake ../
    $ make
    $ ./lissacurses

## Usage

* Press `a`/`A` to decrease/increase the value of the "a" variable
* Press `b`/`B` to decrease/increase the value of the "b" variable
* Press `-`/`+` to decrease/increase the value of the "delta" variable,
  resulting in the curve being rotated
* Press `q` to quit the program

## Licence

`Lissacurses` is released under the MIT licence. See the source code for
more details.
