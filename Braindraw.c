/**
 * BrainDraw is a graphical variant of Brainf***. It can be used to manipulate
 * pixels for creating drawings. It uses an 8-color, 3-bit palette. If a cell
 * with value 0-7 is printed, the relevent color corresponding to the cell is
 * printed. A cell with a value greater that 7 prints white. In binary if the
 * color is abc_2, then a corresponds to red, b corresponds to green and c
 * corresponds to blue.
 *
 * All credits to Benzene (https://codegolf.stackexchange.com/a/136986/31561)
 * and juju2143 (https://esolangs.org/wiki/User:Juju2143) for the ideas.
 *
 * The image resolution and other important constants can be found at the
 * beginning of the code and can be modified to suit your requirements.
 *
 * Commands
 * > Move one pixel right. It wraps if you are on the rightmost pixel.
 * < Move one pixel left. It wraps if you are on the leftmost pixel.
 * v Move one pixel down. It wraps if you are on the lowest pixel.
 * ^ Move one pixel down. It wraps if you are on the highest pixel.
 * + Increase the pixel's value by 1. Values are stored modulo CELLMAXSIZE.
 * - Decrease the pixel's value by 1. Values are stored modulo CELLMAXSIZE.
 * . Draw the cell's value. See above for more information.
 * , Take input. Input is taken modulo CELLMAXSIZE. Input is taken only after
 *   entire code is inputted.
 * [ If the value at the current cell is zero, then instead of moving the
 *   instruction pointer forward to the next command, it is jumped forward
 *   to the command after the matching ] command.
 * ] If the value at the current cell is non-zero, then instead of moving the
 *   instruction pointer forward to the next command, it is jumped backwards
 *   to the command after the matching [ command.
 *
 * After entering the desired code, press CTRL+Z in Windows or CTRL+D in Unix
 * or Linux. If the above commands don't work for you, try to figure out the
 * command for inputting EOF in terminal for your OS.
 * An image titled img.bmp will be created in the same directory.
 *
 * Author: Yasharyan Gaikwad
 * Email : yasharyang@gmail.com
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  MAXSIZE     65535
#define  CELLMAXSIZE 256

#define  FRAMEWIDTH  32
#define  FRAMEHEIGHT 32

#define  ERR_SIZEEXCEED        "Program is too large"
#define  ERR_UNMATCHEDBRACKETS "Please match all the brackets"

#define  DEBUG_FLAG_1 "-d"
#define  DEBUG_FLAG_2 "--debug"


typedef struct
{
  int r;
  int g;
  int b;
} Color;

void drawbmp(char *filename, Color frame[FRAMEWIDTH][FRAMEHEIGHT]);


int main(int argc, char *argv[])
{
  int code[MAXSIZE][2];     // if code[i][0] = [ or ], code[i][1] points
                            // to the corresponding bracket
  int codeLength = 0;
  int i, j;

  int debug = 0;
  for(i = 0; i < argc; i++)
  {
    if((strcmp(argv[i], DEBUG_FLAG_1) == 0)|| (strcmp(argv[i], DEBUG_FLAG_2) == 0))
    {
      debug = 1;
    }
  }


  while((i = getchar()) != EOF)
  {
    switch(i)
    {
      case '>':
      case '<':
      case 'v':
      case '^':
      case '+':
      case '-':
      case '.':
      case ',':
      case '[':
      case ']':
        if(codeLength == MAXSIZE)
        {
          printf("ERROR: %s. Terminating.\n", ERR_SIZEEXCEED);
          exit(1);
        }
        else
        {
          code[codeLength++][0] = i;
        }
        break;
    }
  }

  int stack[MAXSIZE];
  int stackSize = 0;
  for(i = 0; i < codeLength; i++)
  {
    switch(code[i][0])
    {
      case '[':
        stack[stackSize++] = i;
        break;
      case ']':
        if(stackSize == 0)
        {
          printf("ERROR: %s. Terminating.\n", ERR_UNMATCHEDBRACKETS);
          return 1;
        }
        else
        {
          code[i][1] = stack[stackSize - 1];
          code[stack[stackSize - 1]][1] = i;
          stackSize--;
        }
        break;
    }
  }

  if(stackSize != 0)
  {
    printf("ERROR: %s. Terminating.\n", ERR_UNMATCHEDBRACKETS);
    return 1;
  }

  int grid[FRAMEWIDTH][FRAMEHEIGHT];
  int row = 0, col = 0;

  Color frame[FRAMEWIDTH][FRAMEHEIGHT];


  for(i = 0; i < FRAMEWIDTH; i++)
  {
    for(j = 0; j < FRAMEHEIGHT; j++)
    {
      frame[i][j].r = 255;
      frame[i][j].g = 255;
      frame[i][j].b = 255;
    }
  }

  for(i = 0; i < codeLength; i++)
  {
    switch(code[i][0])
    {
      case '>':
        if(col == FRAMEWIDTH-1)
        {
          col = 0;
        }
        else
        {
          col++;
        }
        break;
      case '<':
        if(col == 0)
        {
          col = FRAMEWIDTH-1;
        }
        else
        {
          col--;
        }
        break;
      case 'v':
        if(row == FRAMEHEIGHT-1)
        {
          row = 0;
        }
        else
        {
          row++;
        }
        break;
      case '^':
        if(row == 0)
        {
          row = FRAMEHEIGHT-1;
        }
        else
        {
          row--;
        }
        break;
      case '+':
        if(grid[row][col] == CELLMAXSIZE-1)
        {
          grid[row][col] = 0;
        }
        else
        {
          grid[row][col]++;
        }
        break;
      case '-':
        if(grid[row][col] == 0)
        {
          grid[row][col] = CELLMAXSIZE-1;
        }
        else
        {
          grid[row][col]--;
        }
        break;
      case '.':
        if(grid[row][col] >= 8)
        {
          frame[row][col].r = 255;
          frame[row][col].g = 255;
          frame[row][col].b = 255;
        }
        else
        {
          if(1 & grid[row][col])
          {
            frame[row][col].b = 255;
          }
          else
          {
            frame[row][col].b = 0;
          }
          if((2 & grid[row][col]) >> 1)
          {
            frame[row][col].g = 255;
          }
          else
          {
            frame[row][col].g = 0;
          }
          if((4 & grid[row][col]) >> 2)
          {
            frame[row][col].r = 255;
          }
          else
          {
            frame[row][col].r = 0;
          }
        }
        break;
      case ',':
        scanf("%d", &grid[row][col]);
        grid[row][col] %= CELLMAXSIZE;
        if(grid[row][col] < 0) grid[row][col] + CELLMAXSIZE;
        break;
      case '[':
        if(grid[row][col] == 0)
        {
          i = code[i][1];
        }
        break;
      case ']':
        if(grid[row][col] != 0)
        {
          i = code[i][1];
        }
        break;
    }
  }

  if(debug)
  {
    for(i = 0; i < FRAMEWIDTH; i++)
    {
      for(j = 0; j < FRAMEHEIGHT; j++)
      {
        printf("%4d ", grid[i][j]);
      }
      printf("\n");
    }

    printf("\nPointer is at (%d, %d)\n", row, col);
  }

  drawbmp("img.bmp", frame);

  return 0;
}

void drawbmp(char *filename, Color frame[FRAMEWIDTH][FRAMEHEIGHT])
{
  FILE *fout;

  unsigned int headers[13];

  unsigned int extraBytes;
  unsigned int paddedImageSize;

  int i, j, x, y;

  extraBytes = 4 - ((FRAMEWIDTH * 3) % 4);
  if(extraBytes == 4) extraBytes = 0;
  paddedImageSize = ((FRAMEWIDTH * 3) + extraBytes) * FRAMEHEIGHT;

  headers[0] = paddedImageSize + 54;
  headers[1] = 0;
  headers[2] = 54;
  headers[3] = 40;
  headers[4] = FRAMEWIDTH;
  headers[5] = FRAMEHEIGHT;

  headers[7]  = 0;
  headers[8]  = paddedImageSize;
  headers[9]  = 0;
  headers[10] = 0;
  headers[11] = 0;
  headers[12] = 0;

  fout = fopen(filename, "wb");

  fprintf(fout, "BM");

  for(i = 0; i <= 5; i++)
  {
    fprintf(fout, "%c", headers[i] & 0x000000FF);
    fprintf(fout, "%c", (headers[i] & 0x0000FF00) >> 8);
    fprintf(fout, "%c", (headers[i] & 0x00FF0000) >> 16);
    fprintf(fout, "%c", (headers[i] & (unsigned int) 0xFF000000) >> 24);
  }

  fprintf(fout, "%c", 1);
  fprintf(fout, "%c", 0);
  fprintf(fout, "%c", 24);
  fprintf(fout, "%c", 0);

  for(i = 7; i <= 12; i++)
  {
    fprintf(fout, "%c", headers[i] & 0x000000FF);
    fprintf(fout, "%c", (headers[i] & 0x0000FF00) >> 8);
    fprintf(fout, "%c", (headers[i] & 0x00FF0000) >> 16);
    fprintf(fout, "%c", (headers[i] & (unsigned int) 0xFF000000) >> 24);
  }

  for(y = FRAMEWIDTH - 1; y >= 0; y--)
  {
    for(x = 0; x < FRAMEHEIGHT; x++)
    {
      fprintf(fout, "%c", frame[y][x].b);
      fprintf(fout, "%c", frame[y][x].g);
      fprintf(fout, "%c", frame[y][x].r);
    }

    if(extraBytes)
    {
      for(i = 0; i < extraBytes; i++)
      {
        fprintf(fout, "%c", 0);
      }
    }
  }

  fclose(fout);
}
