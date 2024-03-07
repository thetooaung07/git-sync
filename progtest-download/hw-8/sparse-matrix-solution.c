#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct TCell
{
    struct TCell             * m_Right;
    struct TCell             * m_Down;
    int                        m_Row;
    int                        m_Col;
    int                        m_Data;
} TCELL;

typedef struct TRowCol
{
    struct TRowCol           * m_Next;
    TCELL                    * m_Cells;
    int                        m_Idx;
} TROWCOL;

typedef struct TSparseMatrix
{
    TROWCOL                  * m_Rows;
    TROWCOL                  * m_Cols;
} TSPARSEMATRIX;
#endif /* __PROGTEST__ */

void initMatrix   ( TSPARSEMATRIX   * m )
{
    m->m_Cols = NULL;
    m->m_Rows = NULL;
}

void addSetCell(TSPARSEMATRIX * m, int rowIdx, int colIdx, int data) {
    TROWCOL * prevRow = NULL;
    TROWCOL * currRow = m->m_Rows;
    while (currRow && currRow->m_Idx < rowIdx) {
        prevRow = currRow;
        currRow = currRow->m_Next;
    }
    if (!currRow || currRow->m_Idx > rowIdx) {
        TROWCOL * newRow = (TROWCOL *)malloc(sizeof(TROWCOL));
        newRow->m_Idx = rowIdx;
        newRow->m_Cells = NULL;
        newRow->m_Next = currRow;
        if (prevRow) {
            prevRow->m_Next = newRow;
        } else {
            m->m_Rows = newRow;
        }
        currRow = newRow;
    }

    TROWCOL * prevCol = NULL;
    TROWCOL * currCol = m->m_Cols;
    while (currCol && currCol->m_Idx < colIdx) {
        prevCol = currCol;
        currCol = currCol->m_Next;
    }
    if (!currCol || currCol->m_Idx > colIdx) {
        TROWCOL * newCol = (TROWCOL *)malloc(sizeof(TROWCOL));
        newCol->m_Idx = colIdx;
        newCol->m_Cells = NULL;
        newCol->m_Next = currCol;
        if (prevCol) {
            prevCol->m_Next = newCol;
        } else {
            m->m_Cols = newCol;
        }
        currCol = newCol;
    }

    TCELL * prevCell = NULL;
    TCELL * currCell = currRow->m_Cells;
    while (currCell && currCell->m_Col < colIdx) {
        prevCell = currCell;
        currCell = currCell->m_Right;
    }
    if (!currCell || currCell->m_Col > colIdx) {
        TCELL * newCell = (TCELL *)malloc(sizeof(TCELL));
        newCell->m_Row = rowIdx;
        newCell->m_Col = colIdx;
        newCell->m_Data = data;
        newCell->m_Right = currCell;
        newCell->m_Down = NULL;
        if (prevCell) {
            prevCell->m_Right = newCell;
        } else {
            currRow->m_Cells = newCell;
        }

        prevCell = NULL;
        currCell = currCol->m_Cells;
        while (currCell && currCell->m_Row < rowIdx) {
            prevCell = currCell;
            currCell = currCell->m_Down;
        }
        newCell->m_Down = currCell;
        if (prevCell) {
            prevCell->m_Down = newCell;
        } else {
            currCol->m_Cells = newCell;
        }
    } else {
        currCell->m_Data = data;
    }
}

bool removeCell(TSPARSEMATRIX * m, int rowIdx, int colIdx) {
    TROWCOL *prevRow = NULL, *row;
    TROWCOL *prevCol = NULL, *col;
    TCELL *prevCell = NULL, *cell;
    bool found = false;

    for (row = m->m_Rows; row != NULL && row->m_Idx <= rowIdx; prevRow = row, row = row->m_Next) {
        if (row->m_Idx == rowIdx) {
            for (cell = row->m_Cells; cell != NULL && cell->m_Col <= colIdx; prevCell = cell, cell = cell->m_Right) {
                if (cell->m_Col == colIdx) {
                    found = true;
                    if (prevCell) {
                        prevCell->m_Right = cell->m_Right;
                    } else {
                        row->m_Cells = cell->m_Right;
                    }
                    break;
                }
            }
            break;
        }
    }

    if (!found) return false;

    if (row && row->m_Cells == NULL) {
        if (prevRow) {
            prevRow->m_Next = row->m_Next;
        } else {
            m->m_Rows = row->m_Next;
        }
        free(row);
    }

    for (col = m->m_Cols; col != NULL && col->m_Idx <= colIdx; prevCol = col, col = col->m_Next) {
        if (col->m_Idx == colIdx) {
            prevCell = NULL;
            for (cell = col->m_Cells; cell != NULL; prevCell = cell, cell = cell->m_Down) {
                if (cell->m_Row == rowIdx) {
                    if (prevCell) {
                        prevCell->m_Down = cell->m_Down;
                    } else {
                        col->m_Cells = cell->m_Down;
                    }
                    break;
                }
            }
            break;
        }
    }

    if (col && col->m_Cells == NULL) {
        if (prevCol) {
            prevCol->m_Next = col->m_Next;
        } else {
            m->m_Cols = col->m_Next;
        }
        free(col);
    }

    free(cell);
    return true;
}

void freeCellsInRow(TROWCOL *row) {
    TCELL *cell = row->m_Cells;
    while (cell) {
        TCELL *nextCell = cell->m_Right;
        free(cell);
        cell = nextCell;
    }
}

void freeRowsAndCells(TROWCOL *row) {
    while (row) {
        TROWCOL *nextRow = row->m_Next;
        freeCellsInRow(row);
        free(row);
        row = nextRow;
    }
}

void freeColumns(TROWCOL *col) {
    while (col) {
        TROWCOL *nextCol = col->m_Next;
        free(col);
        col = nextCol;
    }
}

void freeMatrix(TSPARSEMATRIX *m) {
    freeRowsAndCells(m->m_Rows);
    freeColumns(m->m_Cols);
    m->m_Rows = NULL;
    m->m_Cols = NULL;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TSPARSEMATRIX  m;
    initMatrix ( &m );
    addSetCell ( &m, 0, 1, 10 );
    addSetCell ( &m, 1, 0, 20 );
    addSetCell ( &m, 1, 5, 30 );
    addSetCell ( &m, 2, 1, 40 );
    assert ( m . m_Rows
             && m . m_Rows -> m_Idx == 0
             && m . m_Rows -> m_Cells
             && m . m_Rows -> m_Cells -> m_Row == 0
             && m . m_Rows -> m_Cells -> m_Col == 1
             && m . m_Rows -> m_Cells -> m_Data == 10
             && m . m_Rows -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next
             && m . m_Rows -> m_Next -> m_Idx == 1
             && m . m_Rows -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
             && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
             && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
             && m . m_Rows -> m_Next -> m_Cells -> m_Right
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next
             && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
             && m . m_Rows -> m_Next -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Cols
             && m . m_Cols -> m_Idx == 0
             && m . m_Cols -> m_Cells
             && m . m_Cols -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Cells -> m_Col == 0
             && m . m_Cols -> m_Cells -> m_Data == 20
             && m . m_Cols -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next
             && m . m_Cols -> m_Next -> m_Idx == 1
             && m . m_Cols -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
             && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
             && m . m_Cols -> m_Next -> m_Cells -> m_Down
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next
             && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
    addSetCell ( &m, 230, 190, 50 );
    assert ( m . m_Rows
             && m . m_Rows -> m_Idx == 0
             && m . m_Rows -> m_Cells
             && m . m_Rows -> m_Cells -> m_Row == 0
             && m . m_Rows -> m_Cells -> m_Col == 1
             && m . m_Rows -> m_Cells -> m_Data == 10
             && m . m_Rows -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next
             && m . m_Rows -> m_Next -> m_Idx == 1
             && m . m_Rows -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
             && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
             && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
             && m . m_Rows -> m_Next -> m_Cells -> m_Right
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
             && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next
             && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
             && m . m_Rows -> m_Next -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Next
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Idx == 230
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
             && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Cols
             && m . m_Cols -> m_Idx == 0
             && m . m_Cols -> m_Cells
             && m . m_Cols -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Cells -> m_Col == 0
             && m . m_Cols -> m_Cells -> m_Data == 20
             && m . m_Cols -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next
             && m . m_Cols -> m_Next -> m_Idx == 1
             && m . m_Cols -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
             && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
             && m . m_Cols -> m_Next -> m_Cells -> m_Down
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
             && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next
             && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
    assert ( removeCell ( &m, 0, 1 ) );
    assert ( !removeCell ( &m, 0, 1 ) );
    assert ( !removeCell ( &m, 1, 2 ) );
    assert ( m . m_Rows
             && m . m_Rows -> m_Idx == 1
             && m . m_Rows -> m_Cells
             && m . m_Rows -> m_Cells -> m_Row == 1
             && m . m_Rows -> m_Cells -> m_Col == 0
             && m . m_Rows -> m_Cells -> m_Data == 20
             && m . m_Rows -> m_Cells -> m_Right
             && m . m_Rows -> m_Cells -> m_Right -> m_Row == 1
             && m . m_Rows -> m_Cells -> m_Right -> m_Col == 5
             && m . m_Rows -> m_Cells -> m_Right -> m_Data == 30
             && m . m_Rows -> m_Cells -> m_Right -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next
             && m . m_Rows -> m_Next -> m_Idx == 2
             && m . m_Rows -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Cells -> m_Row == 2
             && m . m_Rows -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Rows -> m_Next -> m_Cells -> m_Data == 40
             && m . m_Rows -> m_Next -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next
             && m . m_Rows -> m_Next -> m_Next -> m_Idx == 230
             && m . m_Rows -> m_Next -> m_Next -> m_Cells
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 230
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 190
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 50
             && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Cols
             && m . m_Cols -> m_Idx == 0
             && m . m_Cols -> m_Cells
             && m . m_Cols -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Cells -> m_Col == 0
             && m . m_Cols -> m_Cells -> m_Data == 20
             && m . m_Cols -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next
             && m . m_Cols -> m_Next -> m_Idx == 1
             && m . m_Cols -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Cells -> m_Row == 2
             && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
             && m . m_Cols -> m_Next -> m_Cells -> m_Data == 40
             && m . m_Cols -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next
             && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
             && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
             && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
    assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
    assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Cells );
    assert ( m . m_Rows -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
    assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
    freeMatrix ( &m );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
