
import pygame
import pygame_gui
import sys
import threading
import time

pygame.init()

#Constantes de configuração
LARGURA_TELA = 600
ALTURA_TELA = 400
LARGURA_RETANGULO = 195
ALTURA_RETANGULO = 92
RAIO_RETANGULO = 20
TAM_TREM = 20
FPS = 60

#Cores
VERMELHO = (255, 0, 0)
VERDE = (50, 205, 50)
AZUL = (30, 144, 255)
AMARELO = (255, 215, 0)
BRANCO = (255, 255, 255)
PRETO = (0, 0, 0)

trens = [
    {'x': 90, 'y': 80, 'velocidade': 4, 'direcao': 'direita', 'cor': VERMELHO},
    {'x': 300, 'y': 80, 'velocidade': 4, 'direcao': 'direita', 'cor': VERDE},
    {'x': 90, 'y': 190, 'velocidade': 4, 'direcao': 'direita', 'cor': AZUL},
    {'x': 300, 'y': 190, 'velocidade': 1, 'direcao': 'direita', 'cor': AMARELO},
]

#posisões dos trilhos
retangulos = [
    (100, 90),
    (310, 90),
    (100, 200),
    (310, 200)
]

#Tela do pygame
tela = pygame.display.set_mode((LARGURA_TELA, ALTURA_TELA))
pygame.display.set_caption('Simulação de Trens')

#Cria o gerenciador de interface do pygame_gui
gerenciador = pygame_gui.UIManager((LARGURA_TELA, ALTURA_TELA))

#Sliders de velocidade
slider_velocidade1 = pygame_gui.elements.UIHorizontalSlider(
    relative_rect=pygame.Rect((45, 350, 120, 20)),
    start_value=4.0,
    value_range=(1.0, 10.0),
    manager=gerenciador
)

slider_velocidade2 = pygame_gui.elements.UIHorizontalSlider(
    relative_rect=pygame.Rect((175, 350, 120, 20)),
    start_value=4.0,
    value_range=(1.0, 10.0),
    manager=gerenciador
)

slider_velocidade3 = pygame_gui.elements.UIHorizontalSlider(
    relative_rect=pygame.Rect((305, 350, 120, 20)),
    start_value=4.0,
    value_range=(1.0, 10.0),
    manager=gerenciador
)

slider_velocidade4 = pygame_gui.elements.UIHorizontalSlider(
    relative_rect=pygame.Rect((435, 350, 120, 20)),
    start_value=0.5,
    value_range=(0.1, 1),
    manager=gerenciador
)

#controlar a taxa de atualização
relógio = pygame.time.Clock()

#Semáforos
semaforo_vermelho = threading.Semaphore(1)
semaforo_verde = threading.Semaphore(1)
semaforo_azul = threading.Semaphore(1)
semaforo_amarelo = threading.Semaphore(1)

def colisoes():
    while True:

        #if(semaforo_azul == 0 and semaforo_vermelho == 0 and semaforo_verde == 0):
            # semaforo_verde.release()

        #prioridade do trem amarelo em relação ao verde
        if (trens[3]['direcao'] == 'direita' or trens[3]['direcao'] == 'cima' or trens[3]['direcao'] == 'esquerda') and trens[1]['direcao'] == 'baixo':
            if semaforo_verde._value == 1:
                semaforo_verde.acquire()  
        elif trens[3]['direcao'] == 'baixo' and semaforo_verde._value == 0 and trens[1]['direcao'] == 'baixo':
                semaforo_verde.release()  
        
        #prioridade do trem amarelo em relação ao azul
        if (trens[3]['direcao'] == 'esquerda' or trens[3]['direcao'] == 'cima') and trens[2]['direcao'] == 'direita':
            if semaforo_azul._value == 1:
                semaforo_azul.acquire()  
        elif trens[3]['direcao'] == 'direita' and semaforo_azul._value == 0 and trens[2]['direcao'] == 'direita':
                semaforo_azul.release() 

         #prioridade do trem azul em relação ao vermelho
        if (trens[2]['direcao'] == 'cima' or trens[2]['direcao'] == 'direita') and trens[0]['direcao'] == 'baixo':
            if semaforo_vermelho._value == 1:
                semaforo_vermelho.acquire()  
        elif trens[2]['direcao'] == 'baixo' and semaforo_vermelho._value == 0 and trens[0]['direcao'] == 'baixo':
                semaforo_vermelho.release() 

        #prioridade do trem vermelho em relação ao azul
        if trens[0]['direcao'] == 'esquerda' and trens[2]['direcao'] == 'cima':
            if semaforo_azul._value == 1:
                semaforo_azul.acquire()  
        elif trens[0]['direcao'] == 'cima' and semaforo_azul._value == 0 and trens[2]['direcao'] == 'cima':
                semaforo_azul.release()
        
        #prioridade do trem verde em relação ao vermelho
        if (trens[1]['direcao'] == 'esquerda' or trens[1]['direcao'] == 'cima') and trens[0]['direcao'] == 'direita':
            if semaforo_vermelho._value == 1:
                semaforo_vermelho.acquire()  
        elif trens[1]['direcao'] == 'direita' and semaforo_vermelho._value == 0 and trens[0]['direcao'] == 'direita':
                semaforo_vermelho.release() 
        
         #prioridade do trem vermelho em relação ao verde
        if trens[0]['direcao'] == 'baixo' and trens[1]['direcao'] == 'esquerda':
            if semaforo_verde._value == 1:
                semaforo_verde.acquire()  
        elif trens[0]['direcao'] == 'esquerda' and semaforo_verde._value == 0 and trens[1]['direcao'] == 'esquerda':
                semaforo_verde.release()


        time.sleep(0.1)

def desenhar_trilhos():
    for (x, y) in retangulos:
        pygame.draw.rect(tela, BRANCO, (x, y, LARGURA_RETANGULO, ALTURA_RETANGULO), 2, RAIO_RETANGULO)

def desenhar_trens():
    for trem in trens:
        pygame.draw.rect(tela, trem['cor'], (trem['x'], trem['y'], TAM_TREM, TAM_TREM))

def desenhar_sliders():
    #Desenha as bordas (os retangulos coloridos) dos sliders
    pygame.draw.rect(tela, VERMELHO, (40, 345, 130, 30), 3)
    pygame.draw.rect(tela, VERDE, (170, 345, 130, 30), 3)
    pygame.draw.rect(tela, AZUL, (300, 345, 130, 30), 3)
    pygame.draw.rect(tela, AMARELO, (430, 345, 130, 30), 3)

def desenhar_titulo():
    fonte = pygame.font.SysFont('Comic Sans MS', 30)
    texto = fonte.render("Trem de Threads", True, BRANCO)
    tela.blit(texto, (LARGURA_TELA // 2 - texto.get_width() // 2, 10))

def atualizar_trem(trem, slider, retangulo, semaforo=None):
    while True:
        if semaforo:
            semaforo.acquire()
              #Aguarda a liberação do semáforo se fornecido

        if trem['direcao'] == 'direita':
            trem['x'] += trem['velocidade']
            if trem['x'] >= retangulo[0] + LARGURA_RETANGULO - TAM_TREM / 2:
                trem['direcao'] = 'baixo'
        elif trem['direcao'] == 'baixo':
            trem['y'] += trem['velocidade']
            if trem['y'] >= retangulo[1] + ALTURA_RETANGULO - TAM_TREM / 2:
                trem['direcao'] = 'esquerda'
        elif trem['direcao'] == 'esquerda':
            trem['x'] -= trem['velocidade']
            if trem['x'] <= retangulo[0] - TAM_TREM / 2:
                trem['direcao'] = 'cima'
        elif trem['direcao'] == 'cima':
            trem['y'] -= trem['velocidade']
            if trem['y'] <= retangulo[1] - TAM_TREM / 2:
                trem['direcao'] = 'direita'
        #if trem != trens[3]:
        trem['velocidade'] = slider.get_current_value()

        if semaforo:
            semaforo.release() 

        time.sleep(1 / FPS)

def painel_velocidade():
    while True:
        gerenciador.update(relógio.tick(FPS) / 1000.0)
        time.sleep(1 / FPS)

def main():
    threading.Thread(target=atualizar_trem, args=(trens[0], slider_velocidade1, retangulos[0], semaforo_vermelho), daemon = True).start()
    threading.Thread(target=atualizar_trem, args=(trens[1], slider_velocidade2, retangulos[1], semaforo_verde), daemon=True).start()
    threading.Thread(target=atualizar_trem, args=(trens[2], slider_velocidade3, retangulos[2], semaforo_azul), daemon=True).start()
    threading.Thread(target=atualizar_trem, args=(trens[3], slider_velocidade4, retangulos[3], semaforo_amarelo), daemon=True).start()
    threading.Thread(target=painel_velocidade, daemon=True).start()
    threading.Thread(target=colisoes, daemon=True).start()

    while True:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            gerenciador.process_events(evento)
        
        tela.fill(PRETO)
        desenhar_trilhos()
        desenhar_trens()
        desenhar_sliders()
        desenhar_titulo()
        gerenciador.draw_ui(tela)

        pygame.display.flip()
        relógio.tick(FPS)

if __name__ == "__main__":
    main()