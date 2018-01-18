extern crate pencil;

use pencil::{Pencil, Request, Response, PencilResult};

fn index(r: &mut Request) -> PencilResult {
    
}

fn submit(r: &mut Request) -> PencilResult {
    let url = r.args().get("u").unwrap();
    
}
fn main() {
    
}
