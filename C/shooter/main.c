#include <stdio.h>
#include <stdbool.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#include "Owner.h"
#include "Direction.h"

#include "CDrawable.h"
#include "CPosition.h"

#include "Bullet.h"

#define BULLETARRAY_SIZE 30


typedef struct
{
    CPosition_t pos;
    CDrawable_t drawable;
}Player;


typedef Player Enemy;

int main(void)
{
    ALLEGRO_EVENT_QUEUE *eq;
    ALLEGRO_EVENT e;
    ALLEGRO_TIMEOUT t;
    ALLEGRO_DISPLAY *w;
    char *joystickName;
    bool keys[ALLEGRO_KEY_MAX];

    ALLEGRO_JOYSTICK *j;
    ALLEGRO_JOYSTICK_STATE js;

    Player *p;

    Enemy *en;
    CDrawable_t bg;
    Bullet_t bullets[BULLETARRAY_SIZE];



    for (int i = 0; i < BULLETARRAY_SIZE - 1; ++i)
    {
	bullets[i] = NULL;
    }

    int i = 0; // keeps track of bullets
    int bulletTimeout = 0;

    int enemyTimeout = 0;

    al_init();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(1); // music

    al_install_joystick();

    w = al_create_display(640, 480);

    eq = al_create_event_queue();

    j = al_get_joystick(0);

    al_register_event_source(eq, al_get_display_event_source(w));

    bg = new_CDrawable("bg.jpg", new_CPosition(0, 0));
    p = malloc(sizeof(Player));
    p->pos = new_CPosition(0, 0);
    p->drawable = new_CDrawable("ship.png", p->pos);

    p->pos->x = (32 + (al_get_bitmap_width(p->drawable->i) / 2));
    p->pos->y = (320 - (al_get_bitmap_height(p->drawable->i) / 2));

    en = malloc(sizeof(Enemy));

    en->pos = new_CPosition(320, 150);
    en->drawable = new_CDrawable("ship.png", en->pos);


    Bullet_t enemyBullet = new_Bullet(new_CPosition(en->pos->x + 16, en->pos->y + 16), new_CPosition(p->pos->x + 16, p->pos->y + 16), ENEMY);
    ALLEGRO_SAMPLE *music = al_load_sample("neckbreaker_ed.wav");

    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


    while(true)
    {
	CDrawable_Draw(bg);
	al_init_timeout(&t, 0.06);
	if (al_wait_for_event_until(eq, &e, &t) && e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	    break;

	al_get_joystick_state(j, &js);

	p->pos->x += (js.stick[0].axis[0] > 0.08 || js.stick[0].axis[0] < -0.08) ? js.stick[0].axis[0] * 20: 0; // my left stick is iffy
	p->pos->y += js.stick[0].axis[1] * 15;

	if (js.stick[2].axis[1] == 1.0)
	{
	    if (bulletTimeout == 0) // if we can fire another bullet...
	    {
		i = (i == BULLETARRAY_SIZE - 1) ? 0 : i + 1;

		if (bullets[i])
		    free(bullets[i]);
		bullets[i] = new_Bullet(new_CPosition(p->pos->x + 16, p->pos->y + 16), new_CPosition(p->pos->x + 640, p->pos->y + 16), PLAYER);
		printf("%d, %p\n", i, bullets[i]);
		bulletTimeout = 2;
	    }
	}

	for (int ii = 0; ii < BULLETARRAY_SIZE - 1; ++ii)
	{
	    if (bullets[ii])
	    {
		bool bulletDeleted = Bullet_Update(bullets[ii]);
		if (bulletDeleted)
		{
		    bullets[ii] = NULL;
		    bulletDeleted = false;
		    continue;
		}
		printf("%p\n", bullets[ii]);
		Bullet_Draw(bullets[ii]);
	    }
	}


	if (!enemyTimeout)
	{
	    enemyBullet = new_Bullet(new_CPosition(en->pos->x + 16, en->pos->y + 16), new_CPosition(p->pos->x + 16, p->pos->y + 16), ENEMY);
	    assert(enemyBullet);
	    printf("%p\n", enemyBullet);
	    enemyTimeout = 15;
	}

	bool enemyBulletd = true;
	if (enemyBullet)
	{
	    enemyBulletd = Bullet_Update(enemyBullet);
	}

	if (enemyBulletd == true)
	{
	    enemyBulletd = false;
	    enemyBullet = NULL;
	}
	else
	{
	    printf("Drawing\n");
	    fflush(stdout);
	    Bullet_Draw(enemyBullet);
	    printf("Done Drawing\n");
	    fflush(stdout);
	}
	al_draw_bitmap(p->drawable->i, p->pos->x, p->pos->y, 0);
	al_draw_bitmap(en->drawable->i, en->pos->x, en->pos->y, 0);

	al_flip_display();

	if (bulletTimeout > 0)
	    --bulletTimeout;

	if (enemyTimeout > 0)
	    --enemyTimeout;
    }

    return 0;
}
