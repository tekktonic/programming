extern mod sdl;
extern mod std;
//extern mod img;

use sdl;
use std;

trait Drawable
{
    fn Draw(&self, dest: &sdl::video::Surface);
}

trait Object : Drawable
{
    fn Update(&self);
}

struct Entity
{
    x: int,
    y: int,
    mut xSpeed: int,
    mut ySpeed: int,
    image: ~sdl::video::Surface
}

impl Entity
{
    static fn new(mut x: int,mut  y: int, xs: int, ys: int, img: str) -> Entity {Entity { x: x, y: y, xSpeed: xs, ySpeed: ys,
                                                                                    image: sdl::img::load_img(img)}}

    fn Update(&self)
    {
        if ((self.p[0] == 0 || self.p[0] == 800))
        {
            self.xSpeed *= -1;
        }

        if ((self.p[1] == 0 || self.p[1] == 600))
        {
            self.ySpeed *= -1;
        }

        self.p[0] += self.xSpeed;
        self.p[0] += self.ySpeed;
    }

    fn Draw(&self, dest: &sdl::video::Surface)
    {
        dest.blit_surface_rect(self.image, ~0, &{x: self.p[0], y: self.p[1], w: 128, h: 128});
    }
}


fn main()
{
    let test = Entity::new(0, 0, 1, 1, "rust.png");
    let mut running = false;
    sdl::sdl::init(~[sdl::sdl::InitVideo]);
    let screen = sdl::video::set_video_mode(800, 600, 32, ~[sdl::video::HWSurface], ~[sdl::video::DoubleBuf]);

    while(running)
    {
        match sdl::event::poll_event()
        {
            sdl::event::QuitEvent => {running = false;}
            _ => {}
        };

        test.Update();
        test.Draw(screen);
    }
}

/*struct Engine
{
    mut running: bool,
    entities: Entity,
    screen: &sdl::video::Surface
}

impl Engine
{
    fn OnLoad()
    {
        while (self.running)
        {
            match event::poll_event()
            {
                event::QuitEvent => {self.running = false;}
                _ => {}
            };
            
        }
    }

    fn Step(&engi)
    {
        s
}
*/

