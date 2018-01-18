mod entity;

pub trait Component
{
    fn update(&mut self, Entity owner);
}
