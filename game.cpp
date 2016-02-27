#include "game.h"
#include "entity.h"

#define FRAME_PER_SECOND 60

static EventHandler event_handler;

Game::Game() : running_(true), time_per_frame_(1000/FRAME_PER_SECOND) {

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
	past_time_ = SDL_GetTicks();
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
		
		Uint32 time_current_frame = SDL_GetTicks() - past_time_;
		if(time_current_frame < time_per_frame_) {
			SDL_Delay(time_per_frame_ - time_current_frame);
		}
		past_time_ = SDL_GetTicks();
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
	scene_.update();
}

void Game::render() {
	SDL_RenderClear(renderer_);
	scene_.draw(renderer_);
   	SDL_RenderPresent(renderer_);
}
