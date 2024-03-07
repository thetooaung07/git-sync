#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
constexpr int MAP_MAX = 200;
#endif /* __PROGTEST__ */

int isOutOfBounds (int index, int size) {
    return (index < 0) || (index > size - 1);
}

int max (int m1, int m2) {
    return m1 > m2 ? m1 : m2;
}

int min (int m1, int m2) {
    return m1 > m2 ? m2 : m1;
}

typedef struct visitedup {
  int Tstartrow;
  int Tstartcol;
  int Tendcol;
} VisitedUp;

typedef struct visiteddown {
  int Tendrow;
  int Tstartcol;
  int Tendcol;
} VisitedDown;

void castleArea ( int altitude[][MAP_MAX], int size, int area[][MAP_MAX] )
{
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int startrow = row;
            int startcol = col;
            int endrow = row;
            int endcol = col;
            VisitedUp visitedUpArray[10000];
            VisitedDown visitedDownArray[10000];

            for (int i = col-1; !isOutOfBounds(i, size) && (altitude[row][i] < altitude[row][col]) ; i--) {
                startcol = i;
            }

            for (int i = col+1; !isOutOfBounds(i, size) && (altitude[row][i] < altitude[row][col]); i++) {
                endcol = i;
            }
            

            int maxsize = endcol - startcol + 1;

            int i = row - 1;
            int j = row + 1;
            int indexup = 0;
            int indexdown = 0;
            
            int upstop = 0;
            int downstop = 0;

            int startcolup = startcol;
            int endcolup = endcol; 
            int startcoldown = startcol; 
            int endcoldown = endcol;

            while (1) {
                if (!isOutOfBounds(i, size) && !upstop) {
                    if (altitude[i][col] < altitude[row][col]) {
                        for (int j = startcolup; j < col; j++) {
                            if (altitude[i][j] >= altitude[row][col]) {
                                startcolup = j + 1;
                            }
                        }

                        for (int k = endcolup; k > col; k-- ) {
                            if (altitude[i][k] >= altitude[row][col]) {
                                
                                endcolup = k - 1;
                            }
                        }

                        startrow = i;
                        visitedUpArray[indexup].Tstartrow = startrow;
                        visitedUpArray[indexup].Tstartcol = startcolup;
                        visitedUpArray[indexup].Tendcol = endcolup;
                        indexup++;
                        
                        maxsize = max(maxsize, (endcolup - startcolup + 1) * (row - startrow + 1));
                    }
                    else upstop = 1;
                }

                if (!isOutOfBounds(j, size) && !downstop) {
                    if (altitude[j][col] < altitude[row][col]) {
                        for (int k = startcoldown; k < col; k++) {
                            if (altitude[j][k] >= altitude[row][col]) {
                                
                                startcoldown = k + 1;
                            }
                        }

                        for (int l = endcoldown; l > col; l--) {
                            if (altitude[j][l] >= altitude[row][col]) {
                                
                                endcoldown = l - 1;
                            }
                        }

                        endrow = j;
                        visitedDownArray[indexdown].Tendrow = endrow;
                        visitedDownArray[indexdown].Tstartcol = startcoldown;
                        visitedDownArray[indexdown].Tendcol = endcoldown;
                        indexdown++;
                        
                        maxsize = max(maxsize, (endcoldown - startcoldown + 1) * (endrow - row + 1));
                    }
                    else downstop = 1;
                }

                for (int i = 0; i < indexup; i++){
                    for (int j = 0; j < indexdown; j++) {
                        maxsize = max (maxsize, (visitedDownArray[j].Tendrow - visitedUpArray[i].Tstartrow + 1) * 
                                                (min(visitedDownArray[j].Tendcol, visitedUpArray[i].Tendcol) - 
                                                max(visitedDownArray[j].Tstartcol, visitedUpArray[i].Tstartcol) + 1));
                    }
                }

                if ((isOutOfBounds(i, size) || upstop) && (isOutOfBounds(j, size) || downstop)) {
                    break;
                }

                i--;
                j++;

            }

            //maxsize = max (maxsize, (endrow - startrow + 1) * (endcol - startcol + 1));
            area[row][col] = maxsize;

        }
    }
}

#ifndef __PROGTEST__
bool identicalMap ( const int a[][MAP_MAX], const int b[][MAP_MAX], int n )
{
  /* todo */
}
int main ( int argc, char * argv [] )
{
  static int result[MAP_MAX][MAP_MAX];

  static int alt0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 3, 4 }
  };
  static int area0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 2, 4 }
  };
  castleArea ( alt0, 2, result );
  for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
  assert ( identicalMap ( result, area0, 2 ) );
  static int alt1[MAP_MAX][MAP_MAX] =
  {
    { 2, 7, 1, 9 },
    { 3, 5, 0, 2 },
    { 1, 6, 3, 5 },
    { 1, 2, 2, 8 }
  };
  static int area1[MAP_MAX][MAP_MAX] =
  {
    { 1, 12, 2, 16 },
    { 4, 4, 1, 2 },
    { 1, 9, 4, 4 },
    { 1, 2, 1, 12 }
  };
  castleArea ( alt1, 4, result );
  for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
  assert ( identicalMap ( result, area1, 4 ) );
  static int alt2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 3, 4, 5 },
    { 3, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 4, 6, 8 },
    { 3, 6, 9, 12 },
    { 4, 8, 12, 16 }
  };
  castleArea ( alt2, 4, result );
  for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
  assert ( identicalMap ( result, area2, 4 ) );
  static int alt3[MAP_MAX][MAP_MAX] =
  {
    { 7, 6, 5, 4 },
    { 6, 5, 4, 5 },
    { 5, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area3[MAP_MAX][MAP_MAX] =
  {
    { 12, 6, 2, 1 },
    { 6, 2, 1, 2 },
    { 2, 1, 2, 6 },
    { 1, 2, 6, 12 }
  };
  castleArea ( alt3, 4, result );
  for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
  assert ( identicalMap ( result, area3, 4 ) );
  static int alt4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 2, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  static int area4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 25, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  castleArea ( alt4, 5, result );
  for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
  assert ( identicalMap ( result, area4, 5 ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */