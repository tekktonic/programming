use std::collections::HashMap;

use std::conversion::TryFrom;
pub struct Entity
{
    HashMap<str, T: Component + TryFrom> components;
    i32 id;
}
