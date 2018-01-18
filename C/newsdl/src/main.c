#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL.h>
#include "room.h"
#include "window.h"
#include "entity.h"
#include "sample.h"
#include "game.h"

int main(int argc, char **argv)
{
    Room first;
    
    ResourceManager rm;
    
    Window window;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = new_Window("a test window", 640, 480, SDL_WINDOW_RESIZABLE);
    rm = new_ResourceManager();
    
    currentRoom = first = new_Room(rm, window, "bg.png", NULL);


    struct timeval time;
    gettimeofday(&time, NULL);
    int simTime = (time.tv_usec / 1000);
    while (1)
    {
	List events = new_List(0);
	gettimeofday(&time, NULL);

	while (simTime < (time.tv_usec / 1000))
	{
	    simTime += 17; // 1000 / 60 is 16 + (2/3), so round to 17

	    SDL_Event *e = malloc(sizeof(SDL_Event));
	    while(SDL_PollEvent(e))
	    {
		switch (e->type)
		{
		case SDL_QUIT:
		    List_free(events, free);
		    goto cleanup;
		    break;
		case SDL_WINDOWEVENT:
		    if (e->window.event == SDL_WINDOWEVENT_RESIZED)
		    {
			Window_resizedCB(window);
			break;
		    }
		    // INTENTIONAL FALLTHROUGH
		default:
		List_enqueue(events, e);
		}
	    }
	    Room_update(currentRoom);
	    Room_react(currentRoom);
	}

	Room_draw(currentRoom);

	List_free(events, free);
	simTime = 0;
    }

cleanup:
    	Room_kill(&currentRoom, GAME_KILLED);
	ResourceManager_kill(rm);
	Window_kill(window);
	SDL_Quit();
    return 0;
}
