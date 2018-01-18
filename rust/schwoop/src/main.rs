extern crate piston;
extern crate graphics;
extern crate glutin_window;
extern crate opengl_graphics;

extern crate rand;

use std::cell::RefCell;
use std::rc::Rc;

use piston::window::WindowSettings;
use piston::event_loop::*;
use piston::input::*;
use glutin_window::GlutinWindow as Window;
use opengl_graphics::{GlGraphics, OpenGL};

mod graphics_controller;

use graphics_controller::{GraphicsController,GraphicsEntryType};
pub struct App {
//    gl: GlGraphics,
    graphics_controller: Rc<RefCell<GraphicsController>>,
    rect_id: i32,
    x: f64,
    x_speed: f64,
    y: f64,
    y_speed: f64
}

impl App
{
    fn render(&mut self, args: &RenderArgs)
    {
        use graphics::*;

/*        const  BLUE: [f32;4] = [0.1, 0.1, 0.8, 1.0];
        const  RED: [f32;4] = [0.8, 0.1, 0.1, 1.0];

        let square = rectangle::square(self.x, self.y, 64.0);

        self.gl.draw(args.viewport(), |c, gl| {
            clear(RED, gl);
            let transform = c.transform.trans(-32., -32.);
            rectangle(BLUE, square, transform, gl);
        });
         */
        self.graphics_controller.borrow_mut().render(args);
    }

    fn update(&mut self, args: &UpdateArgs)
    {
        let (x, y) = self.graphics_controller.borrow_mut().get_position(GraphicsEntryType::ImageEntity, self.rect_id).unwrap();
//        println!("{} {}", x, y);
        self.graphics_controller.borrow_mut().translate(GraphicsEntryType::ImageEntity, self.rect_id, x + (self.x_speed * args.dt),
                                                        y + (self.y_speed * args.dt));
        {
                    let (x, y) = self.graphics_controller.borrow_mut().get_position(GraphicsEntryType::ImageEntity, self.rect_id).unwrap();
  //          println!("{} {}", x, y);
        }
    }

    fn input_press(&mut self, args: Button)
    {
        println!("foo");
        match args {
            Button::Keyboard(Key::Up) => { self.y_speed = -50.; }
            Button::Keyboard(Key::Down) => { self.y_speed = 50.; }
            Button::Keyboard(Key::Left) => { self.x_speed = -50.; }
            Button::Keyboard(Key::Right) => { self.x_speed = 50.; }
            _ => {}
        }
    }


    fn input_release(&mut self, args: Button)
    {
        match args  {
            Button::Keyboard(Key::Up) => { self.y_speed = 0.; }
            Button::Keyboard(Key::Down) => { self.y_speed = 0.; }
            Button::Keyboard(Key::Left) => { self.x_speed = 0.; }
            Button::Keyboard(Key::Right) => { self.x_speed = 0.; }
            _ => {}

        }
    }

    fn new(gl: GlGraphics) -> App {
        let mut gc = GraphicsController::new(gl);
        let mut rid = gc.register_image(632., 530., "dino.png");
        return App {x: 512., y: 384., x_speed: 0.0, y_speed: 0.0, graphics_controller: Rc::new(RefCell::new(gc)),
                rect_id: rid};
    }
}

fn main() {
    println!("Hello, world!");

    let opengl = OpenGL::V3_2;

    let mut window: Window = WindowSettings::new("duh", [1024, 768]).opengl(opengl).build().unwrap();

    let mut app = App::new(GlGraphics::new(opengl));

    let mut events = window.events();

    while let Some(e) = events.next(&mut window){

        if let Some(r) = e.render_args() { app.render(&r)}
        if let Some(u) = e.update_args() { app.update(&u)}
        if let Some(b) = e.press_args() {app.input_press(b);}
        if let Some(b) = e.release_args() {app.input_release(b);}
    }
}
