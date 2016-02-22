#include "game.h"
#include "polygon.h"
#include "quadtree.h"
#include "rectangle.h"

Game::Game() : running_(true) {
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

/*	quadtree_ptr_ = std::make_shared<Quadtree<Rectangle>>([](const Rectangle& rect, const typename Quad<Rectangle>::Rect_t& rect_qt) -> bool {
			if(rect.get_pos().x_ + rect.get_size().x_ < rect_qt.x || 
		   rect.get_pos().y_ + rect.get_size().y_ < rect_qt.y ||
			   rect_qt.x + rect_qt.w < rect.get_pos().x_ ||
			   rect_qt.y + rect_qt.h < rect.get_pos().y_) {
				return false;
			}

			return true;
		});	*/
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
