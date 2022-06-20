from asyncio import Handle
import pygame as pg
import ctypes
import os

lib = ctypes.cdll.LoadLibrary(r"D:\BadProjects\BadCode\Steamy\src\build\main_.dll")
lib.createChessBoard.restype=ctypes.c_void_p
lib.createChessBoard.argtypes=[ctypes.c_bool]
lib.getPiece.restype=ctypes.c_void_p
lib.getPiece.argtypes=[ctypes.c_void_p, ctypes.c_int, ctypes.c_int]

# Util random functions
def drawscene(screen):
    # Draw checker board
    for i in range(0, 8):
        for j in range(0, 8):
            if (i + j) % 2 == 0:
                pg.draw.rect(screen, (0, 0, 0), (i * 100, j * 100, 100, 100))
            else:
                pg.draw.rect(screen, (255, 255, 255), (i * 100, j * 100, 100, 100))


class Main:
    def __init__(self):
        pg.init()
        pg.font.init()
        self.screen = pg.display.set_mode((800, 800))
        self.clock = pg.time.Clock()
        self.running = True
        self.fps = 60
        self.font = pg.font.SysFont('Arial', 30)
        self.text = self.font.render('Hello World', True, (255, 255, 255))
        self.text_rect = self.text.get_rect()
        self.text_rect.center = (400, 300)
        # Get board pointer from dll
        self.p = lib.createChessBoard(True)
        lib.getPiece(ctypes.POINTER(self.p), 0, 0)
    def event_loop(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
    def draw(self):
        drawscene(self.screen)
        pg.display.flip()
    def update(self):
        self.clock.tick(self.fps)
    def main_loop(self):
        while self.running:
            self.event_loop()
            self.update()
            self.draw()
        pg.quit()

a = Main()
a.main_loop()