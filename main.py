import pygame
import ctypes

# Load the shared C++ library
game_lib = ctypes.CDLL('./game2048.so')

# Initialize the game through C++ library
game_lib.initializeGame()

# Define constants
SIZE = 4
TILE_SIZE = 100
GRID_SIZE = SIZE * TILE_SIZE

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((GRID_SIZE, GRID_SIZE))
pygame.display.set_caption('2048 Game')

# Helper functions to draw the game grid
def draw_grid(grid):
    screen.fill((187, 173, 160))  # Background color
    for i in range(SIZE):
        for j in range(SIZE):
            value = grid[i * SIZE + j]
            color = (205, 193, 180) if value == 0 else (238, 228, 218)
            pygame.draw.rect(screen, color, (j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE))
            if value != 0:
                font = pygame.font.Font(None, 55)
                text = font.render(str(value), True, (119, 110, 101))
                text_rect = text.get_rect(center=(j * TILE_SIZE + TILE_SIZE // 2, i * TILE_SIZE + TILE_SIZE // 2))
                screen.blit(text, text_rect)

def get_game_state():
    buffer = (ctypes.c_int * (SIZE * SIZE))()
    game_lib.getGridState(buffer)
    return list(buffer)

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key in [pygame.K_w, pygame.K_a, pygame.K_s, pygame.K_d]:
                move = {pygame.K_w: 'w', pygame.K_a: 'a', pygame.K_s: 's', pygame.K_d: 'd'}[event.key]
                game_lib.makeMove(ctypes.c_char(move.encode('utf-8')))
    
    game_state = get_game_state()
    draw_grid(game_state)

    if game_lib.checkGameOver():
        print("Game Over")
        running = False

    pygame.display.flip()

pygame.quit()
