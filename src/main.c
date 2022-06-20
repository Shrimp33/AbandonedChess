#include <stdio.h>
#include <stdbool.h>  // tfw bools arn't a thing
#include <math.h>


/*
    Chess board
    [[r, h, b, q, k, b, h, r],
    [p, p, p, p, p, p, p, p],
    [e, e, e, e, e, e, e, e],
    [e, e, e, e, e, e, e, e],
    [e, e, e, e, e, e, e, e],
    [e, e, e, e, e, e, e, e],
    [p, p, p, p, p, p, p, p],
    [r, h, b, q, k, b, h, r]]
*/

typedef struct {
    char class;
    char color;
    int x;
    int y;
} Piece;

typedef struct {
    Piece matrix[8][8];
} ChessBoard;

Piece createPiece(char class, char color, int x, int y) {
    Piece piece;
    piece.class = class;
    piece.color = color; // 'w' or 'b' or 'e'
    piece.x = x;
    piece.y = y;
    return piece;
}

ChessBoard *createChessBoard(bool isWhite) {  // TODO: create a chess board with black
    static ChessBoard chessBoard;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessBoard.matrix[i][j] = createPiece('e', 'e', i, j);
        }
    }
    // White pieces
    chessBoard.matrix[0][0] = createPiece('r', 'w', 0, 0);
    chessBoard.matrix[0][1] = createPiece('h', 'w', 0, 1);
    chessBoard.matrix[0][2] = createPiece('b', 'w', 0, 2);
    chessBoard.matrix[0][3] = createPiece('q', 'w', 0, 3);
    chessBoard.matrix[0][4] = createPiece('k', 'w', 0, 4);
    chessBoard.matrix[0][5] = createPiece('b', 'w', 0, 5);
    chessBoard.matrix[0][6] = createPiece('h', 'w', 0, 6);
    chessBoard.matrix[0][7] = createPiece('r', 'w', 0, 7);
    for (int i = 0; i < 8; i++) {
        chessBoard.matrix[1][i] = createPiece('p', 'w', 1, i);
    }
    // Black pieces
    chessBoard.matrix[7][0] = createPiece('r', 'b', 7, 0);
    chessBoard.matrix[7][1] = createPiece('h', 'b', 7, 1);
    chessBoard.matrix[7][2] = createPiece('b', 'b', 7, 2);
    chessBoard.matrix[7][3] = createPiece('q', 'b', 7, 3);
    chessBoard.matrix[7][4] = createPiece('k', 'b', 7, 4);
    chessBoard.matrix[7][5] = createPiece('b', 'b', 7, 5);
    chessBoard.matrix[7][6] = createPiece('h', 'b', 7, 6);
    chessBoard.matrix[7][7] = createPiece('r', 'b', 7, 7);
    for (int i = 0; i < 8; i++) {
        chessBoard.matrix[6][i] = createPiece('p', 'b', 6, i);
    }
    // Print reference address
    printf("%p\n", &chessBoard);
    return &chessBoard;
}

char *getPiece(ChessBoard *chessBoard, int x, int y) {
    static char piece[2];
    printf("%p\n", &chessBoard);
    printf("%ld\n", &chessBoard);
}



bool isValidMove(ChessBoard *chessBoard, int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) {
        return false;
    }
    if ((*chessBoard).matrix[y1][x1].color == 'e') {
        return false;
    }
    if ((*chessBoard).matrix[y2][x2].color == (*chessBoard).matrix[y1][x1].color) {
        return false;
    }
    if ((*chessBoard).matrix[y1][x1].class == 'p') {
        if ((*chessBoard).matrix[y1][x1].color == 'w') {
            if (x1 == x2 && y1 == y2 + 1) {
                return true;
            }
            if (x1 == x2 && y1 == y2 + 2 && y2 == 1) {
                return true;
            }
            if (x1 == x2 + 1 && y1 == y2 + 1 && (*chessBoard).matrix[y2][x2].color == 'b') {
                return true;
            }
            if (x1 == x2 - 1 && y1 == y2 + 1 && (*chessBoard).matrix[y2][x2].color == 'b') {
                return true;
            }
        } if ((*chessBoard).matrix[y1][x1].color == 'b') {
            if (x1 == x2 && y1 == y2 - 1) {
                return true;
            }
            if (x1 == x2 && y1 == y2 - 2 && y2 == 6) {
                return true;
            }
            if (x1 == x2 + 1 && y1 == y2 - 1 && (*chessBoard).matrix[y2][x2].color == 'w') {
                return true;
            }
            if (x1 == x2 - 1 && y1 == y2 - 1 && (*chessBoard).matrix[y2][x2].color == 'w') {
                return true;
            }
        }
        return false;
    }
    if ((*chessBoard).matrix[y1][x1].class == 'r') {
        if (x1 == x2) {
            if (y1 < y2) {
                for (int i = y1 + 1; i < y2; i++) {
                    if ((*chessBoard).matrix[i][x1].color != 'e') {
                        return false;
                    }
                }
                    return true;
                return true;
            } else {
                for (int i = y1 - 1; i > y2; i--) {
                    if ((*chessBoard).matrix[i][x1].color != 'e') {
                        return false;
                    }
                }
                    return true;
            }
        }
        if (y1 == y2) {
            if (x1 < x2) {
                for (int i = x1 + 1; i < x2; i++) {
                    if ((*chessBoard).matrix[y1][i].color != 'e') {
                        return false;
                    }
                }
                    return true;
            } else {
                for (int i = x1 - 1; i > x2; i--) {
                    if ((*chessBoard).matrix[y1][i].color != 'e') {
                        return false;
                    }
                }
                    return true;
            }
        }
        return false;
    }
    if ((*chessBoard).matrix[y1][x1].class == 'k') {
        if (x1 == x2 && y1 == y2) {
            return true;
        }
        if (x1 == x2 + 1 && y1 == y2) {
            return true;
        }
        if (x1 == x2 - 1 && y1 == y2) {
            return true;
        }
        if (x1 == x2 && y1 == y2 + 1) {
            return true;
        }
        if (x1 == x2 && y1 == y2 - 1) {
            return true;
        }
        if (x1 == x2 + 1 && y1 == y2 + 1) {
            return true;
        }
        if (x1 == x2 - 1 && y1 == y2 + 1) {
            return true;
        }
        if (x1 == x2 + 1 && y1 == y2 - 1) {
            return true;
        }
        if (x1 == x2 - 1 && y1 == y2 - 1) {
            return true;
        }
        return false;
    }
    if ((*chessBoard).matrix[y1][x1].class == 'b') {
        if (abs(x2 - x1) != abs(y2 - y1)) {
            return false;
        }
        if (x1 < x2) {
            for (int i = x1 + 1; i < x2; i++) {
                if ((*chessBoard).matrix[y1][i].color != 'e') {
                    return false;
                }
            }
            if (y1 < y2) {
                for (int i = y1 + 1; i < y2; i++) {
                    if ((*chessBoard).matrix[i][x2].color != 'e') {
                        return false;
                    }
                }
            } else {
                for (int i = y1 - 1; i > y2; i--) {
                    if ((*chessBoard).matrix[i][x2].color != 'e') {
                        return false;
                    }
                }
            }
                return true;
        }

    if (x1 > x2) {
        for (int i = x1 - 1; i > x2; i--) {
            if ((*chessBoard).matrix[y1][i].color != 'e') {
                return false;
            }
        }
        if (y1 < y2) {
            for (int i = y1 + 1; i < y2; i++) {
                if ((*chessBoard).matrix[i][x2].color != 'e') {
                    return false;
                }
            }
        } else {
            for (int i = y1 - 1; i > y2; i--) {
                if ((*chessBoard).matrix[i][x2].color != 'e') {
                    return false;
                }
            }
        }
            return true;
        }
    return false;
    }
    if ((*chessBoard).matrix[y1][x1].class == 'q') {
        if (abs(x2 - x1) == abs(y2 - y1)) {
            if (x1 < x2) {
                for (int i = x1 + 1; i < x2; i++) {
                    if ((*chessBoard).matrix[y1][i].color != 'e') {
                        return false;
                    }
                }
                if (y1 < y2) {
                    for (int i = y1 + 1; i < y2; i++) {
                        if ((*chessBoard).matrix[i][x2].color != 'e') {
                            return false;
                        }
                    }
                } else {
                    for (int i = y1 - 1; i > y2; i--) {
                        if ((*chessBoard).matrix[i][x2].color != 'e') {
                            return false;
                        }
                    }
                }
                    return true;
            }

        if (x1 > x2) {
            for (int i = x1 - 1; i > x2; i--) {
                if ((*chessBoard).matrix[y1][i].color != 'e') {
                    return false;
                }
            }
            if (y1 < y2) {
                for (int i = y1 + 1; i < y2; i++) {
                    if ((*chessBoard).matrix[i][x2].color != 'e') {
                        return false;
                    }
                }
            } else {
                for (int i = y1 - 1; i > y2; i--) {
                    if ((*chessBoard).matrix[i][x2].color != 'e') {
                        return false;
                    }
                }
            }
                    return true;
            }
        }
        else {
            if (x1 == x2) {
                if (y1 < y2) {
                    for (int i = y1 + 1; i < y2; i++) {
                        if ((*chessBoard).matrix[i][x1].color != 'e') {
                            return false;
                        }
                    }
                        return true;
                    return true;
                } else {
                    for (int i = y1 - 1; i > y2; i--) {
                        if ((*chessBoard).matrix[i][x1].color != 'e') {
                            return false;
                        }
                    }
                        return true;
                }
            }
            if (y1 == y2) {
                if (x1 < x2) {
                    for (int i = x1 + 1; i < x2; i++) {
                        if ((*chessBoard).matrix[y1][i].color != 'e') {
                            return false;
                        }
                    }
                        return true;
                } else {
                    for (int i = x1 - 1; i > x2; i--) {
                        if ((*chessBoard).matrix[y1][i].color != 'e') {
                            return false;
                        }
                    }
                        return true;
                }
            }
        }
    }
    if ((*chessBoard).matrix[y1][x1].class == 'h') {
        if (abs(x2 - x1) < 3 && abs(y2 - y1) < 3) {
            if (abs(x2 - x1) + abs(y2 - y1) == 3) {
                return true;
            }
        }
        return false;
    }
    return false;
}