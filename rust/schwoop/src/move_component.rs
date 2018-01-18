use std::conversion::TryFrom;

mod entity;
mod component;

pub struct MoveComponent {
    x: f64;
    y: f64;
    x_speed: f64;
    y_speed: f64;
}

impl Component for MoveComponent {
    fn update(&mut self, owner: &mut Entity) {
        self.x += self.x_speed;
        self.y += self.y_speed;
    }

    fn typeof(&mut self){
        "MoveComponent";
    }
}

impl TryFrom<T> for MoveComponent {
    type Err = ();
    fn try_from(&self: T) -> Result<T, Self::Err>
    {
        if self.typeof() == "MoveComponent" {
            Ok(self);
        }
        Err();
            
    }
}
