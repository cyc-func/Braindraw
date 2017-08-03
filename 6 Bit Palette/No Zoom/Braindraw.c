#include <stdio.h>
#include <stdlib.h>

#define  MAXSIZE     60000
#define  CELLMAXSIZE 256

#define  FRAMEWIDTH  10
#define  FRAMEHEIGHT 10

#define  ERR_SIZEEXCEED        "Program is too large"
#define  ERR_UNMATCHEDBRACKETS "Please match all the brackets"


typedef struct
{
  int r;
  int g;
  int b;
} Color;

void drawbmp(char *filename, Color frame[FRAMEWIDTH][FRAMEHEIGHT]);

/**
 * A 8 color, 3-bit palette is used. A single integer n holds the RGB values.
 * If we write n in base 2, abc_2, a_2 corresponds to R, b_2 corresponds to g,
 * c_2 corresponds to b. Anything n larger than 7 is printed as white.
 *
 * Author: Yasharyan Gaikwad
 * Email : yasharyang@gmail.com
 */



int main(void)
{
  int code[MAXSIZE][2];     // if code[i][0] = [ or ], code[i][1] points
                            // to the corresponding bracket
  int codeLength = 0;
  int i, j;

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
            frame[row][col].r = 255;
          }
          else
          {
            frame[row][col].r = 0;
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
            frame[row][col].b = 255;
          }
          else
          {
            frame[row][col].b = 0;
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
