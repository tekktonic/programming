use std::collections::hash_map::HashMap;
use std::path::Path;
use std::f64;

use opengl_graphics::{GlGraphics, OpenGL, Texture};

use graphics::math::Scalar;
use graphics::image::Image;
use graphics::ImageSize;
use graphics::rectangle::*;

use rand;



use piston::input::RenderArgs;

pub enum GraphicsEntryType
{
    ImageEntity,
    RectEntity
}

struct ImageEntry
{
    tex: Texture,
    img: Image,
    x: Scalar,
    y: Scalar,
    rot: f64
}

struct RectEntry
{
    x: Scalar,
    y: Scalar,
    w: Scalar,
    h: Scalar,
    color: [f32; 4],
    rot: f64
}

pub struct GraphicsController
{
    gl: GlGraphics,
    images: HashMap<i32, ImageEntry>,
    rects: HashMap<i32, RectEntry>
}

impl GraphicsController
{
    pub fn register_image(&mut self, x: Scalar, y: Scalar, tex_name: &str) -> i32
    {
        let mut id = rand::random::<i32>();
        while self.images.contains_key(&id)
        {
            id = rand::random::<i32>();
        }

        let path = &("resources/images/".to_string() + tex_name);

        let tex = Texture::from_path(Path::new(path)).unwrap();
                println!("{} {} {}", path, tex.get_width(), tex.get_height());
        let img = Image::new().rect(centered([x, y, f64::from(tex.get_width()) / 2., f64::from(tex.get_height()) / 2.]));
        let rect = img.rectangle.unwrap();
        println!("{} {} {} {}", rect[0], rect[1], rect[2], rect[3]);
        let mut image = ImageEntry {tex: tex, img: img, x: x, y: y, rot: 0.};
        self.images.insert(id, image);
        return id;
    }
    
    pub fn register_rectangle(&mut self, rect: [f64; 4]) -> i32
    {
        let mut id = rand::random::<i32>();
        while self.images.contains_key(&id)
        {
            id = rand::random::<i32>();
        }

        let mut rect = RectEntry {x: rect[0], y: rect[1], w: rect[2], h: rect[3], color: [1.0, 1.0, 1.0, 1.0], rot: 0.};
        self.rects.insert(id, rect);
        return id;
    }
    
    pub fn deregister(&mut self, typ: GraphicsEntryType, id: i32)
    {
        match typ {
            GraphicsEntryType::ImageEntity => {self.images.remove(&id); ();},
            GraphicsEntryType::RectEntity => {self.rects.remove(&id); ();},
        }
        return; 
    }
    
    pub fn rotate(&mut self, typ: GraphicsEntryType, id: i32, rotation: f64)
    {
        match typ {
            
            GraphicsEntryType::ImageEntity => {
                match self.images.get_mut(&id) {
                    Some(image) => image.rot = rotation,
                    None => println!("{} doesn't exist", id),
                }
            }
            
            GraphicsEntryType::RectEntity => {
                match self.rects.get_mut(&id) {
                    Some(rect) => rect.rot = rotation,
                    None => println!("{} doesn't exist", id),
                }
            }
        }
    }
    pub fn translate(&mut self, typ: GraphicsEntryType, id: i32, x: Scalar, y: Scalar)
    {
        match typ {
            GraphicsEntryType::ImageEntity => {
                match self.images.get_mut(&id) {
                    Some(image) => {image.x = x; image.y = y},
                    None => println!("{} doesn't exist", id),
                }
            },
            GraphicsEntryType::RectEntity => {
                
                match self.rects.get_mut(&id) {
                    Some(rect) => {rect.x = x; rect.y = y},
                    None => println!("{} doesn't exist", id),
                }
            }
        }
    }

    pub fn get_position(&mut self, typ: GraphicsEntryType, id: i32) -> Result<(f64, f64), i32> {
        match typ {
            GraphicsEntryType::ImageEntity => {
                match self.images.get(&id) {
                    Some (image) => return Ok((image.x, image.y)),
                    None => println!("{} doesn't exist", id),
                }
            },
            GraphicsEntryType::RectEntity => {
                match self.rects.get(&id) {
                    Some(rect) => return Ok((rect.x, rect.y)),
                    None => println!("{} doesn't exist", id),
                }
            }
        }

        return Err(0);
    }
    
    pub fn render(&mut self, args: &RenderArgs) {
        use graphics::*;
        let ref mut images = self.images;
        let ref mut rects = self.rects;
        self.gl.draw(args.viewport(), |c, gl| {
//            clear([0.0, 0.0, 0.0, 1.0], gl);
            for image in images.values() {
                let trans = c.transform.rot_rad(image.rot).trans(0., 0.);
                println!("{} {}", image.x, image.y);
                image.img.draw(&image.tex, &(DrawState::default()), trans, gl);
            }
            
/*            for rect in rects.values() {
                let trans = c.transform.rot_rad(rect.rot);
                rectangle(rect.color, centered([rect.x, rect.y, rect.w / 2., rect.h / 2.]), trans, gl)
            }*/
        });
    }




    pub fn new(gl: GlGraphics) -> GraphicsController
    { 
        return GraphicsController {gl: gl, images: HashMap::new(), rects: HashMap::new()};
    }
    
}
