# Braindraw

BrainDraw is a graphical variant of Brainf***. It can be used to manipulate pixels for creating drawings. It uses an `8-color`, `3-bit` palette. If a cell with value `0-7` is printed, the relevent color corresponding to the cell is printed. A cell with a value greater that `7` prints white. In binary if the color is `abc_2`, then `a` corresponds to red, `b` corresponds to green and `c` corresponds to blue. See below for more details.

All credits to [Benzene](https://codegolf.stackexchange.com/a/136986/31561) and [juju2143](https://esolangs.org/wiki/User:Juju2143) for the ideas.

**WARNING:** it is not safe to type comments in the source because the character `v` has a special meaning.

**Commands**
* `>` Move one pixel right. It wraps if you are on the rightmost pixel.
* `<` Move one pixel left. It wraps if you are on the leftmost pixel.
* `v` Move one pixel down. It wraps if you are on the lowest pixel.
* `^` Move one pixel down. It wraps if you are on the highest pixel.
* `+` Increase the pixel's value by 1. Values are stored modulo `CELLMAXSIZE`.
* `-` Decrease the pixel's value by 1. Values are stored modulo `CELLMAXSIZE`.
* `.` Draw the cell's value. See above for more information.
* `,` Take input. Input is taken modulo `CELLMAXSIZE`. Input is taken only after entire code is inputted.
* `[` If the value at the current cell is zero, then instead of moving the instruction pointer forward to the next command, it is jumped forward to the command after the matching `]` command.
* `]` If the value at the current cell is non-zero, then instead of moving the instruction pointer forward to the next command, it is jumped backwards to the command after the matching `[` command.

**Running**

After compiling the code, enter the desired BrainDraw code into the terminal. Once this is done, press `CTRL+Z` in Windows or `CTRL+D` in Unix or Linux (If these commands don't work for you, try to figure out the command for inputting `EOF` in terminal for your OS).

The code will then be interpreted and if there are no errors, an image titled `img.bmp` will be created in the same directory. If you want to debug, you may pass in `-d` or `--debug` as an argument.

**Colors**
* ![0](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/0.jpg) `0` : `#000000`
* ![1](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/1.jpg) `1` : `#0000FF`
* ![2](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/2.jpg) `2` : `#00FF00`
* ![3](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/3.jpg) `3` : `#00FFFF`
* ![4](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/4.jpg) `4` : `#FF0000`
* ![5](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/5.jpg) `5` : `#FF00FF`
* ![6](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/6.jpg) `6` : `#FFFF00`
* ![7](https://raw.githubusercontent.com/cyc-func/Braindraw/master/Colors/7.jpg) `7 - 255` : `#FFFFFF`
