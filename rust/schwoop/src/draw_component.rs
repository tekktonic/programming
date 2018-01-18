use std::collections::Vec;
use std::conversion::TryFrom;
mod entity;
mod component;
mod graphics_controller;

pub struct DrawComponent
{
    draw_ids: Vec<(GraphicsEntryType, i32)>;
    gc: Rc<RefCell<GraphicsController>>;
}

impl Component for DrawComponent {
    fn update(&mut self, &mut Entity owner) {
        let gc = self.gc.borrow_mut();
        for pair in self.draw_ids {
            let (typ, id) = pair;
            let mc = MoveComponent::try_from(owner.components.get("MoveComponent").unwrap());
            gc.translate(typ, id, mc.x, mc.y)
        }
    }

    fn typeof(&mut self)
    {
        "MoveComponent";
    }
}


impl TryFrom<T> for DrawComponent {
    type Err = ();
    fn try_from(&self: T) -> Result<T, Self::Err>
    {
        if self.typeof() == "DrawComponent" {
            Ok(self);
        }
        Err();
            
    }
}
