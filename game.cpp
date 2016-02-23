#include <ctime>

#include "game.h"
#include "polygon.h"
#include "entity.h"

#include "quadtree_handler.h"
#include "rectangle.h"

static EventHandler event_handler;

Game::Game() : running_(true) {
	std::srand(std::time(0));

    if(SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
	{
	    std::cerr << "Erreur d'initialisation de la SDL : " << SDL_GetError();
	    exit(EXIT_FAILURE);
	}

	// Création de la fenêtre :
	window_ = SDL_CreateWindow("sdl window" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED ,WINDOW_WIDTH, WINDOW_HEIGHT , SDL_WINDOW_RESIZABLE);
	if(window_ == NULL) // Gestion des erreurs
	{
	    std::cerr << "Erreur lors de la creation d'une fenetre : " << SDL_GetError();
	    exit(EXIT_FAILURE);
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer

	if(renderer_ == NULL)//gestion des erreurs
	{
	    std::cerr << "Erreur lors de la creation d'un renderer : " << SDL_GetError();
	    exit(EXIT_FAILURE);
	}
		
	register_events();
    
    QuadtreeHandler handler;   
    
    for(unsigned int i = 0; i < 10; i++) {
        Rectangle box = Rectangle(Vector2<float>(std::rand()%WINDOW_WIDTH, std::rand()%WINDOW_HEIGHT), 50.0f, 50.0f);
        EntityPtr entity_ptr = std::make_shared<Entity>(box);

        handler.insert(entity_ptr);
    }
}

Game::~Game() {
	// Destruction du renderer et de la fenêtre :
	SDL_DestroyRenderer(renderer_); 
	SDL_DestroyWindow(window_);
	SDL_Quit(); // On quitte la SDL
}

void Game::run() {
	while(running_) {
		get_events();
		update();
		render();
	}
}

void Game::register_events() {
	event_handler.add(SDL_KEYDOWN, [this] (const SDL_Event& event) {
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
			std::cout << "up detected !" << std::endl;
		}
	});

	event_handler.add(SDL_KEYDOWN, [this] (const SDL_Event& event) {
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
			std::cout << "down detected !" << std::endl;
		}
	});

	event_handler.add(SDL_KEYDOWN, [this] (const SDL_Event& event) {
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			running_ = false;
		}
	});

	event_handler.add(SDL_QUIT, [this] (const SDL_Event& event) {
		if(event.type == SDL_QUIT) {
			running_ = false;
		}
	});
}

void Game::get_events() {
	while(SDL_PollEvent(&event_)) {
	}
}

void Game::update() {
	/** handle player events */
	event_handler.handle(event_);

	/** run world update, enemys, environments, particules ... */
}

void Game::render() {
	SDL_RenderClear(renderer_);
	
	Polygon poly({Vector2<float>(10.0f, 10.f),
		      Vector2<float>(50.0f, 50.f),
		      Vector2<float>(30.0f, 70.f)});

	poly.draw(renderer_);
	SDL_RenderPresent(renderer_);
}
